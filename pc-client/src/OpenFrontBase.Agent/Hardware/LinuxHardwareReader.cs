using System.Diagnostics;
using System.Globalization;
using OpenFrontBase.Agent.Models;

namespace OpenFrontBase.Agent.Hardware;

/// <summary>
/// CZ: Čtení senzorů na Linuxu přes /proc, /sys/class/hwmon, RAPL, nvidia-smi a sysfs.
/// EN: Linux sensor reader using /proc, /sys/class/hwmon, RAPL, nvidia-smi, and sysfs.
/// </summary>
public class LinuxHardwareReader : IHardwareReader {
    private const int BaseSystemPowerWatts = 35;

    private ulong _prevCpuIdle;
    private ulong _prevCpuTotal;

    private long _prevCpuEnergyUj;
    private DateTime _prevCpuEnergyTime = DateTime.UtcNow;

    private long _prevNetRxBytes;
    private long _prevNetTxBytes;
    private DateTime _prevNetTime = DateTime.UtcNow;

    private readonly string? _cpuTempFile;
    private readonly string? _cpuFanFile;
    private readonly string? _cpuEnergyFile;
    private readonly string? _diskTempFile;
    private readonly SpecsMessage _cachedSpecs;

    public LinuxHardwareReader() {
        _cpuTempFile = FindCpuTempFile();
        _cpuFanFile = FindCpuFanFile();
        _cpuEnergyFile = FindCpuRaplFile();
        _diskTempFile = FindNvmeTempFile();
        _cachedSpecs = ReadStaticSpecsInternal();

        ReadCpuLoad();
        ReadCpuPowerWatts();
        ReadNetworkSpeed();
    }

    public SpecsMessage GetStaticSpecs() {
        return _cachedSpecs;
    }

    public StatMessage GetCurrentTelemetry() {
        var now = DateTime.Now;
        var cpu = new CpuStats {
            Load = ReadCpuLoad(),
            Temp = ReadSensorMilliValue(_cpuTempFile),
            Freq = ReadCpuFreqMhz(),
            FanRpm = ReadRawIntFile(_cpuFanFile),
            PowerWatts = ReadCpuPowerWatts()
        };

        var gpu = ReadGpuStats();
        int totalPowerW = cpu.PowerWatts + gpu.PowerWatts + BaseSystemPowerWatts;

        return new StatMessage {
            Time = now.ToString("HH:mm:ss"),
            Date = now.ToString("dd.MM.yyyy"),
            PcPowerWatts = totalPowerW,
            Cpu = cpu,
            Gpu = gpu,
            Ram = ReadRamStats(),
            Disk = ReadSystemDiskStats(),
            Net = ReadNetworkSpeed(),
            ScreenOn = true
        };
    }

    private SpecsMessage ReadStaticSpecsInternal() {
        string cpuName = "Linux CPU";
        string cpuVendor = "Unknown";
        try {
            foreach (string line in File.ReadLines("/proc/cpuinfo")) {
                if (line.StartsWith("vendor_id", StringComparison.OrdinalIgnoreCase)) {
                    string rawVendor = line.Split(':').Last().Trim();
                    cpuVendor = rawVendor switch {
                        "AuthenticAMD" => "AMD",
                        "GenuineIntel" => "Intel",
                        _ => rawVendor
                    };
                }
                else if (line.StartsWith("model name", StringComparison.OrdinalIgnoreCase)) {
                    cpuName = line.Split(':').Last().Trim();
                    break;
                }
            }
        }
        catch {
            // Fallback na výchozí hodnoty
        }

        int totalRamGb = 0;
        try {
            foreach (string line in File.ReadLines("/proc/meminfo")) {
                if (line.StartsWith("MemTotal:")) {
                    long kb = ParseMemInfoKb(line);
                    totalRamGb = (int)Math.Ceiling(kb / 1024.0 / 1024.0);
                    break;
                }
            }
        }
        catch {
            // Fallback na 0 GB
        }

        (string gpuVendor, string gpuName) = DetectLinuxGpuIdentity();
        string mbName = ReadMotherboardName();
        (string diskName, int diskTotalGb) = DetectSystemDiskIdentity();

        return new SpecsMessage {
            CpuVendor = cpuVendor,
            CpuName = cpuName,
            GpuVendor = gpuVendor,
            GpuName = gpuName,
            MotherboardName = mbName,
            RamName = ReadLinuxRamName(totalRamGb),
            RamTotalGb = totalRamGb,
            DiskName = diskName,
            DiskTotalGb = diskTotalGb
        };
    }

    private static (string Name, int TotalGb) DetectSystemDiskIdentity() {
        int totalGb = 0;
        try {
            var rootDrive = new DriveInfo("/");
            totalGb = (int)Math.Round(rootDrive.TotalSize / 1024.0 / 1024.0 / 1024.0);
        }
        catch {
            // Ignorujeme chybu čtení DriveInfo
        }

        try {
            string? rootDev = null;
            foreach (string line in File.ReadLines("/proc/mounts")) {
                string[] parts = line.Split(' ');
                if (parts.Length >= 2 && parts[1] == "/" && parts[0].StartsWith("/dev/")) {
                    rootDev = Path.GetFileName(parts[0]);
                    break;
                }
            }

            if (!string.IsNullOrEmpty(rootDev)) {
                string baseDisk = rootDev;
                if (baseDisk.StartsWith("nvme") && baseDisk.Contains('p')) {
                    baseDisk = baseDisk[..baseDisk.LastIndexOf('p')];
                }
                else {
                    baseDisk = new string(baseDisk.TakeWhile(c => !char.IsDigit(c)).ToArray());
                }

                string modelPath = $"/sys/class/block/{baseDisk}/device/model";
                if (File.Exists(modelPath)) {
                    string model = File.ReadAllText(modelPath).Trim();
                    if (!string.IsNullOrEmpty(model)) {
                        return (model, totalGb);
                    }
                }
            }

            foreach (string dir in Directory.GetDirectories("/sys/class/block")) {
                string modelFile = Path.Combine(dir, "device", "model");
                if (File.Exists(modelFile)) {
                    string model = File.ReadAllText(modelFile).Trim();
                    if (!string.IsNullOrEmpty(model)) {
                        return (model, totalGb);
                    }
                }
            }
        }
        catch {
            // Fallback na obecný název disku
        }

        return ("Linux System Disk", totalGb);
    }

    private DiskStats ReadSystemDiskStats() {
        int usedPct = 0;
        int usedGb = 0;
        try {
            var rootDrive = new DriveInfo("/");
            long total = rootDrive.TotalSize;
            long used = total - rootDrive.AvailableFreeSpace;
            if (total > 0) {
                usedGb = (int)Math.Round(used / 1024.0 / 1024.0 / 1024.0);
                usedPct = (int)Math.Round((double)used / total * 100.0);
            }
        }
        catch {
            // Ignorujeme chybu čtení kapacity disku
        }

        return new DiskStats {
            UsedPercent = usedPct,
            UsedGb = usedGb,
            Temp = ReadSensorMilliValue(_diskTempFile)
        };
    }

    private int ReadCpuLoad() {
        try {
            string? firstLine = File.ReadLines("/proc/stat").FirstOrDefault();
            if (firstLine == null || !firstLine.StartsWith("cpu ")) {
                return 0;
            }

            string[] parts = firstLine.Split(' ', StringSplitOptions.RemoveEmptyEntries);
            ulong user = ulong.Parse(parts[1]);
            ulong nice = ulong.Parse(parts[2]);
            ulong system = ulong.Parse(parts[3]);
            ulong idle = ulong.Parse(parts[4]);
            ulong iowait = parts.Length > 5 ? ulong.Parse(parts[5]) : 0;
            ulong irq = parts.Length > 6 ? ulong.Parse(parts[6]) : 0;
            ulong softirq = parts.Length > 7 ? ulong.Parse(parts[7]) : 0;
            ulong steal = parts.Length > 8 ? ulong.Parse(parts[8]) : 0;

            ulong idleAll = idle + iowait;
            ulong total = idleAll + user + nice + system + irq + softirq + steal;

            ulong totalDelta = total - _prevCpuTotal;
            ulong idleDelta = idleAll - _prevCpuIdle;

            _prevCpuTotal = total;
            _prevCpuIdle = idleAll;

            if (totalDelta == 0) {
                return 0;
            }

            double usage = (double)(totalDelta - idleDelta) / totalDelta * 100.0;
            return (int)Math.Clamp(Math.Round(usage), 0, 100);
        }
        catch {
            return 0;
        }
    }

    private static string? FindCpuTempFile() {
        const string hwmonBase = "/sys/class/hwmon";
        if (!Directory.Exists(hwmonBase)) {
            return null;
        }

        foreach (string dir in Directory.GetDirectories(hwmonBase)) {
            string nameFile = Path.Combine(dir, "name");
            if (!File.Exists(nameFile)) {
                continue;
            }

            string sensorName = File.ReadAllText(nameFile).Trim().ToLowerInvariant();
            if (sensorName is "k10temp" or "zenpower" or "coretemp" or "cpu_thermal") {
                string tempFile = Path.Combine(dir, "temp1_input");
                if (File.Exists(tempFile)) {
                    return tempFile;
                }
            }
        }
        return null;
    }

    private static string? FindCpuFanFile() {
        const string hwmonBase = "/sys/class/hwmon";
        if (!Directory.Exists(hwmonBase)) {
            return null;
        }

        foreach (string dir in Directory.GetDirectories(hwmonBase)) {
            string nameFile = Path.Combine(dir, "name");
            string sensorName = File.Exists(nameFile) ? File.ReadAllText(nameFile).Trim().ToLowerInvariant() : "";
            if (sensorName is "amdgpu" or "nouveau") {
                continue;
            }

            for (int i = 1; i <= 5; i++) {
                string fanFile = Path.Combine(dir, $"fan{i}_input");
                if (File.Exists(fanFile) && ReadRawIntFile(fanFile) > 0) {
                    return fanFile;
                }
            }
        }
        return null;
    }

    private static string? FindNvmeTempFile() {
        const string hwmonBase = "/sys/class/hwmon";
        if (!Directory.Exists(hwmonBase)) {
            return null;
        }

        foreach (string dir in Directory.GetDirectories(hwmonBase)) {
            string nameFile = Path.Combine(dir, "name");
            if (!File.Exists(nameFile)) {
                continue;
            }

            string sensorName = File.ReadAllText(nameFile).Trim().ToLowerInvariant();
            if (sensorName is "nvme" or "drivetemp") {
                string tempFile = Path.Combine(dir, "temp1_input");
                if (File.Exists(tempFile)) {
                    return tempFile;
                }
            }
        }
        return null;
    }

    private static string? FindCpuRaplFile() {
        const string raplPath = "/sys/class/powercap/intel-rapl:0/energy_uj";
        if (File.Exists(raplPath)) {
            return raplPath;
        }
        return null;
    }

    private int ReadCpuPowerWatts() {
        if (_cpuEnergyFile == null) {
            return 0;
        }

        try {
            long currentUj = long.Parse(File.ReadAllText(_cpuEnergyFile).Trim());
            var now = DateTime.UtcNow;
            double seconds = (now - _prevCpuEnergyTime).TotalSeconds;

            int watts = 0;
            if (seconds > 0 && _prevCpuEnergyUj > 0 && currentUj >= _prevCpuEnergyUj) {
                double deltaJoules = (currentUj - _prevCpuEnergyUj) / 1_000_000.0;
                watts = (int)Math.Round(deltaJoules / seconds);
            }

            _prevCpuEnergyUj = currentUj;
            _prevCpuEnergyTime = now;
            return Math.Clamp(watts, 0, 500);
        }
        catch {
            return 0;
        }
    }

    private static int ReadSensorMilliValue(string? filePath) {
        if (filePath == null || !File.Exists(filePath)) {
            return 0;
        }

        try {
            return int.Parse(File.ReadAllText(filePath).Trim()) / 1000;
        }
        catch {
            return 0;
        }
    }

    private static int ReadRawIntFile(string? filePath) {
        if (filePath == null || !File.Exists(filePath)) {
            return 0;
        }

        try {
            return int.Parse(File.ReadAllText(filePath).Trim());
        }
        catch {
            return 0;
        }
    }

    private static int ReadCpuFreqMhz() {
        const string freqPath = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq";
        try {
            if (File.Exists(freqPath)) {
                return int.Parse(File.ReadAllText(freqPath).Trim()) / 1000;
            }
        }
        catch {
            // Ignorujeme chybu čtení frekvence
        }
        return 0;
    }

    private static RamStats ReadRamStats() {
        try {
            long totalKb = 0;
            long availKb = 0;

            foreach (string line in File.ReadLines("/proc/meminfo")) {
                if (line.StartsWith("MemTotal:")) {
                    totalKb = ParseMemInfoKb(line);
                }
                else if (line.StartsWith("MemAvailable:")) {
                    availKb = ParseMemInfoKb(line);
                    break;
                }
            }

            if (totalKb > 0) {
                long usedKb = totalKb - availKb;
                int usedMb = (int)(usedKb / 1024);
                int loadPercent = (int)Math.Round((double)usedKb / totalKb * 100.0);
                return new RamStats { Load = loadPercent, UsedMb = usedMb };
            }
        }
        catch {
            // Ignorujeme chybu čtení meminfo
        }
        return new RamStats();
    }

    private static long ParseMemInfoKb(string line) {
        string[] parts = line.Split(' ', StringSplitOptions.RemoveEmptyEntries);
        if (parts.Length >= 2 && long.TryParse(parts[1], out long val)) {
            return val;
        }
        return 0;
    }

    private static (string Vendor, string Name) DetectLinuxGpuIdentity() {
        string? nvidiaName = ReadNvidiaGpuName();
        if (!string.IsNullOrEmpty(nvidiaName)) {
            if (!nvidiaName.StartsWith("NVIDIA", StringComparison.OrdinalIgnoreCase)) {
                nvidiaName = "NVIDIA " + nvidiaName;
            }
            return ("NVIDIA", nvidiaName);
        }

        const string drmPath = "/sys/class/drm";
        if (Directory.Exists(drmPath)) {
            foreach (string cardDir in Directory.GetDirectories(drmPath, "card*")) {
                string vendorFile = Path.Combine(cardDir, "device", "vendor");
                if (!File.Exists(vendorFile)) {
                    continue;
                }

                string vendorHex = File.ReadAllText(vendorFile).Trim().ToLowerInvariant();
                if (vendorHex == "0x1002") {
                    return ("AMD", TryReadPciGpuName("AMD") ?? "AMD Radeon Graphics");
                }
                else if (vendorHex == "0x8086") {
                    return ("Intel", TryReadPciGpuName("Intel") ?? "Intel Integrated Graphics");
                }
            }
        }
        return ("Unknown", "Generic Linux GPU");
    }

    private static string? TryReadPciGpuName(string vendorFilter) {
        try {
            var psi = new ProcessStartInfo("lspci") {
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };
            using var proc = Process.Start(psi);
            if (proc == null) {
                return null;
            }

            string output = proc.StandardOutput.ReadToEnd();
            proc.WaitForExit(1000);

            foreach (string line in output.Split('\n')) {
                if ((line.Contains("VGA compatible controller", StringComparison.OrdinalIgnoreCase) ||
                     line.Contains("3D controller", StringComparison.OrdinalIgnoreCase) ||
                     line.Contains("Display controller", StringComparison.OrdinalIgnoreCase)) &&
                    line.Contains(vendorFilter, StringComparison.OrdinalIgnoreCase)) {
                    int colonIdx = line.IndexOf(": ", StringComparison.Ordinal);
                    if (colonIdx > 0) {
                        int secondColon = line.IndexOf(": ", colonIdx + 2, StringComparison.Ordinal);
                        if (secondColon > 0) {
                            return line[(secondColon + 2)..].Trim();
                        }
                    }
                }
            }
        }
        catch {
            // Ignorujeme chybu při absenci lspci
        }
        return null;
    }

    private static string ReadMotherboardName() {
        try {
            const string dmiBase = "/sys/devices/virtual/dmi/id";
            string vendorFile = Path.Combine(dmiBase, "board_vendor");
            string nameFile = Path.Combine(dmiBase, "board_name");

            string vendor = File.Exists(vendorFile) ? File.ReadAllText(vendorFile).Trim() : "";
            string name = File.Exists(nameFile) ? File.ReadAllText(nameFile).Trim() : "";

            string combined = $"{vendor} {name}".Trim();
            if (string.IsNullOrEmpty(combined)) {
                return "Linux Motherboard";
            }
            return combined;
        }
        catch {
            return "Linux Motherboard";
        }
    }

    private static string ReadLinuxRamName(int totalRamGb) {
        const string cacheFile = "/tmp/openfrontbase_ram_info";
        try {
            if (File.Exists(cacheFile)) {
                string cached = File.ReadAllText(cacheFile).Trim();
                if (!string.IsNullOrEmpty(cached)) {
                    return cached;
                }
            }
        }
        catch {
            // Ignorujeme chybu čtení cache
        }

        try {
            var psi = new ProcessStartInfo("dmidecode", "-t memory") {
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            using var proc = Process.Start(psi);
            if (proc != null) {
                string output = proc.StandardOutput.ReadToEnd();
                proc.WaitForExit(1000);

                if (proc.ExitCode == 0 && !string.IsNullOrWhiteSpace(output)) {
                    string parsed = ParseDmidecodeMemory(output, totalRamGb);
                    if (!string.IsNullOrEmpty(parsed)) {
                        return parsed;
                    }
                }
            }
        }
        catch {
            // Ignorujeme chybu při spuštění dmidecode bez root práv
        }

        return $"{totalRamGb} GB System RAM";
    }

    private static string ParseDmidecodeMemory(string dmiOutput, int totalRamGb) {
        string manufacturer = "";
        string partNumber = "";
        string memType = "";
        string speed = "";

        foreach (string rawLine in dmiOutput.Split('\n')) {
            string line = rawLine.Trim();
            if (line.StartsWith("Manufacturer:") && string.IsNullOrEmpty(manufacturer)) {
                string val = line["Manufacturer:".Length..].Trim();
                if (val is not "Unknown" and not "Not Specified" and not "None") {
                    manufacturer = val;
                }
            }
            else if (line.StartsWith("Part Number:") && string.IsNullOrEmpty(partNumber)) {
                string val = line["Part Number:".Length..].Trim();
                if (val is not "Unknown" and not "Not Specified" and not "None") {
                    partNumber = val;
                }
            }
            else if (line.StartsWith("Type:") && string.IsNullOrEmpty(memType)) {
                string val = line["Type:".Length..].Trim();
                if (val.StartsWith("DDR")) {
                    memType = val;
                }
            }
            else if (line.StartsWith("Configured Memory Speed:") && string.IsNullOrEmpty(speed)) {
                string val = line["Configured Memory Speed:".Length..].Trim();
                if (!val.Contains("Unknown")) {
                    speed = val;
                }
            }
        }

        var parts = new List<string>();
        if (!string.IsNullOrEmpty(manufacturer)) {
            parts.Add(manufacturer);
        }
        if (!string.IsNullOrEmpty(partNumber)) {
            parts.Add(partNumber);
        }
        if (!string.IsNullOrEmpty(memType)) {
            parts.Add(memType);
        }
        if (!string.IsNullOrEmpty(speed)) {
            parts.Add($"({speed})");
        }

        if (parts.Count > 0) {
            return string.Join(" ", parts);
        }
        return $"{totalRamGb} GB System RAM";
    }

    private static GpuStats ReadGpuStats() {
        var nvidia = TryReadNvidiaGpu();
        if (nvidia != null) {
            return nvidia;
        }

        return TryReadAmdGpu() ?? new GpuStats();
    }

    private static string? ReadNvidiaGpuName() {
        try {
            var psi = new ProcessStartInfo("nvidia-smi", "--query-gpu=name --format=csv,noheader") {
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };
            using var proc = Process.Start(psi);
            if (proc == null) {
                return null;
            }
            string output = proc.StandardOutput.ReadToEnd().Trim();
            proc.WaitForExit(1000);
            if (proc.ExitCode == 0 && !string.IsNullOrEmpty(output)) {
                return output.Split('\n')[0].Trim();
            }
            return null;
        }
        catch {
            return null;
        }
    }

    private static GpuStats? TryReadNvidiaGpu() {
        try {
            var psi = new ProcessStartInfo(
                "nvidia-smi",
                "--query-gpu=utilization.gpu,temperature.gpu,clocks.current.graphics,memory.used,memory.total,fan.speed,power.draw --format=csv,noheader,nounits") {
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };

            using var proc = Process.Start(psi);
            if (proc == null) {
                return null;
            }

            string line = proc.StandardOutput.ReadLine() ?? string.Empty;
            proc.WaitForExit(1000);

            if (proc.ExitCode != 0 || string.IsNullOrWhiteSpace(line)) {
                return null;
            }

            string[] parts = line.Split(',', StringSplitOptions.TrimEntries);
            if (parts.Length < 7) {
                return null;
            }

            int powerWatts = 0;
            if (double.TryParse(parts[6], NumberStyles.Float, CultureInfo.InvariantCulture, out double rawWatts)) {
                powerWatts = (int)Math.Round(rawWatts);
            }

            return new GpuStats {
                Load = int.TryParse(parts[0], out int load) ? load : 0,
                Temp = int.TryParse(parts[1], out int temp) ? temp : 0,
                Freq = int.TryParse(parts[2], out int freq) ? freq : 0,
                VramUsedMb = int.TryParse(parts[3], out int used) ? used : 0,
                VramTotalMb = int.TryParse(parts[4], out int total) ? total : 0,
                FanPercent = int.TryParse(parts[5], out int fan) ? fan : 0,
                PowerWatts = powerWatts
            };
        }
        catch {
            return null;
        }
    }

    private static GpuStats? TryReadAmdGpu() {
        const string drmPath = "/sys/class/drm";
        if (!Directory.Exists(drmPath)) {
            return null;
        }

        foreach (string cardDir in Directory.GetDirectories(drmPath, "card*")) {
            string busyFile = Path.Combine(cardDir, "device", "gpu_busy_percent");
            if (!File.Exists(busyFile)) {
                continue;
            }

            try {
                int load = int.Parse(File.ReadAllText(busyFile).Trim());
                int vramUsedMb = 0;
                int vramTotalMb = 0;

                string vramUsedFile = Path.Combine(cardDir, "device", "mem_info_vram_used");
                string vramTotalFile = Path.Combine(cardDir, "device", "mem_info_vram_total");

                if (File.Exists(vramUsedFile)) {
                    vramUsedMb = (int)(long.Parse(File.ReadAllText(vramUsedFile).Trim()) / (1024 * 1024));
                }
                if (File.Exists(vramTotalFile)) {
                    vramTotalMb = (int)(long.Parse(File.ReadAllText(vramTotalFile).Trim()) / (1024 * 1024));
                }

                int temp = 0;
                int powerWatts = 0;
                int fanPct = 0;

                string hwmonDir = Path.Combine(cardDir, "device", "hwmon");
                if (Directory.Exists(hwmonDir)) {
                    string? firstHwmon = Directory.GetDirectories(hwmonDir).FirstOrDefault();
                    if (firstHwmon != null) {
                        temp = ReadSensorMilliValue(Path.Combine(firstHwmon, "temp1_input"));
                        string powerFile = Path.Combine(firstHwmon, "power1_average");
                        if (File.Exists(powerFile) && long.TryParse(File.ReadAllText(powerFile).Trim(), out long uW)) {
                            powerWatts = (int)Math.Round(uW / 1_000_000.0);
                        }

                        string pwmFile = Path.Combine(firstHwmon, "pwm1");
                        if (File.Exists(pwmFile) && int.TryParse(File.ReadAllText(pwmFile).Trim(), out int pwm)) {
                            fanPct = (int)Math.Round(pwm / 255.0 * 100.0);
                        }
                    }
                }

                return new GpuStats {
                    Load = load,
                    Temp = temp,
                    FanPercent = fanPct,
                    PowerWatts = powerWatts,
                    VramUsedMb = vramUsedMb,
                    VramTotalMb = vramTotalMb
                };
            }
            catch {
                // Ignorujeme chybu čtení karty
            }
        }
        return null;
    }

    private NetStats ReadNetworkSpeed() {
        try {
            long rxTotal = 0;
            long txTotal = 0;

            foreach (string line in File.ReadLines("/proc/net/dev").Skip(2)) {
                string trimmed = line.Trim();
                if (trimmed.StartsWith("lo:")) {
                    continue;
                }

                string[] parts = trimmed.Split(new char[] { ':', ' ' }, StringSplitOptions.RemoveEmptyEntries);
                if (parts.Length >= 10) {
                    rxTotal += long.Parse(parts[1], CultureInfo.InvariantCulture);
                    txTotal += long.Parse(parts[9], CultureInfo.InvariantCulture);
                }
            }

            var now = DateTime.UtcNow;
            double seconds = (now - _prevNetTime).TotalSeconds;

            int dlKbps = 0;
            int ulKbps = 0;

            if (seconds > 0 && _prevNetRxBytes > 0) {
                dlKbps = (int)Math.Max(0, (rxTotal - _prevNetRxBytes) / 1024.0 / seconds);
                ulKbps = (int)Math.Max(0, (txTotal - _prevNetTxBytes) / 1024.0 / seconds);
            }

            _prevNetRxBytes = rxTotal;
            _prevNetTxBytes = txTotal;
            _prevNetTime = now;

            return new NetStats { DownloadKbps = dlKbps, UploadKbps = ulKbps };
        }
        catch {
            return new NetStats();
        }
    }

    public void Dispose() {
    }
}
