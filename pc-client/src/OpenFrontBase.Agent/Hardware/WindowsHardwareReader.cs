using LibreHardwareMonitor.Hardware;
using OpenFrontBase.Agent.Models;

namespace OpenFrontBase.Agent.Hardware;

/// <summary>
/// CZ: Čtení senzorů na Windows 11 pomocí knihovny LibreHardwareMonitorLib (MPL 2.0).
/// EN: Windows 11 sensor reader using LibreHardwareMonitorLib (MPL 2.0).
/// </summary>
public class WindowsHardwareReader : IHardwareReader {
    private const int BaseSystemPowerWatts = 35;
    private readonly Computer _computer;

    private long _prevNetRxBytes;
    private long _prevNetTxBytes;
    private DateTime _prevNetTime = DateTime.UtcNow;
    private double _peakDlMbps = 0.0;
    private double _peakUlMbps = 0.0;

    public WindowsHardwareReader() {
        _computer = new Computer {
            IsCpuEnabled = true,
            IsGpuEnabled = true,
            IsMemoryEnabled = true,
            IsMotherboardEnabled = true,
            IsStorageEnabled = true,
            IsNetworkEnabled = true
        };
        _computer.Open();
    }

    public SpecsMessage GetStaticSpecs() {
        string cpuVendor = "Unknown";
        string cpuName = "Windows CPU";
        string gpuVendor = "Unknown";
        string gpuName = "Windows GPU";
        string mbName = "Windows Motherboard";
        string ramName = "Windows RAM";
        string diskName = "Windows System Disk";

        foreach (IHardware hw in _computer.Hardware) {
            if (hw.HardwareType == HardwareType.Cpu) {
                cpuName = hw.Name;
                if (cpuName.Contains("AMD", StringComparison.OrdinalIgnoreCase)) {
                    cpuVendor = "AMD";
                }
                else if (cpuName.Contains("Intel", StringComparison.OrdinalIgnoreCase)) {
                    cpuVendor = "Intel";
                }
            }
            else if (hw.HardwareType == HardwareType.GpuNvidia ||
                     hw.HardwareType == HardwareType.GpuAmd ||
                     hw.HardwareType == HardwareType.GpuIntel) {
                gpuName = hw.Name;
                gpuVendor = hw.HardwareType switch {
                    HardwareType.GpuNvidia => "NVIDIA",
                    HardwareType.GpuAmd => "AMD",
                    HardwareType.GpuIntel => "Intel",
                    _ => "Unknown"
                };
            }
            else if (hw.HardwareType == HardwareType.Motherboard) {
                mbName = hw.Name;
            }
            else if (hw.HardwareType == HardwareType.Memory) {
                ramName = hw.Name;
            }
            else if (hw.HardwareType == HardwareType.Storage && diskName == "Windows System Disk") {
                diskName = hw.Name;
            }
        }

        int diskTotalGb = 0;
        try {
            string sysRoot = Path.GetPathRoot(Environment.SystemDirectory) ?? "C:\\";
            var drive = new DriveInfo(sysRoot);
            diskTotalGb = (int)Math.Round(drive.TotalSize / 1024.0 / 1024.0 / 1024.0);
        }
        catch {
            // Ignorujeme chybu čtení DriveInfo
        }

        return new SpecsMessage {
            CpuVendor = cpuVendor,
            CpuName = cpuName,
            GpuVendor = gpuVendor,
            GpuName = gpuName,
            MotherboardName = mbName,
            RamName = ramName,
            RamTotalGb = (int)Math.Ceiling(GC.GetGCMemoryInfo().TotalAvailableMemoryBytes / 1024.0 / 1024.0 / 1024.0),
            DiskName = diskName,
            DiskTotalGb = diskTotalGb,
            NetName = DetectNetworkAdapterName()
        };
    }

    private static string DetectNetworkAdapterName() {
        try {
            foreach (var nic in System.Net.NetworkInformation.NetworkInterface.GetAllNetworkInterfaces()) {
                if (nic.OperationalStatus == System.Net.NetworkInformation.OperationalStatus.Up &&
                    nic.NetworkInterfaceType != System.Net.NetworkInformation.NetworkInterfaceType.Loopback) {
                    return !string.IsNullOrWhiteSpace(nic.Description) ? nic.Description : nic.Name;
                }
            }
        }
        catch { }
        return "Network";
    }

    public StatMessage GetCurrentTelemetry() {
        var now = DateTime.Now;
        var stat = new StatMessage {
            Time = now.ToString("HH:mm:ss"),
            Date = now.ToString("dd.MM.yyyy"),
            ScreenOn = true
        };

        foreach (IHardware hw in _computer.Hardware) {
            hw.Update();

            if (hw.HardwareType == HardwareType.Cpu) {
                foreach (ISensor s in hw.Sensors) {
                    if (s.SensorType == SensorType.Load && s.Name.Contains("Total")) {
                        stat.Cpu.Load = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Temperature && (s.Name.Contains("Package") || s.Name.Contains("Tctl") || s.Name.Contains("Core"))) {
                        stat.Cpu.Temp = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Clock && s.Name.Contains("Core #1")) {
                        stat.Cpu.Freq = Math.Round((s.Value ?? 0) / 1000.0, 2);
                    }
                    else if (s.SensorType == SensorType.Power && s.Name.Contains("Package")) {
                        stat.Cpu.PowerWatts = (int)Math.Round(s.Value ?? 0);
                    }
                }
            }
            else if (hw.HardwareType == HardwareType.Motherboard || hw.HardwareType == HardwareType.Cooler) {
                foreach (ISensor s in hw.Sensors) {
                    if (s.SensorType == SensorType.Fan && (s.Value ?? 0) > 0) {
                        if (s.Name.Contains("CPU", StringComparison.OrdinalIgnoreCase) || stat.Cpu.FanRpm == 0) {
                            stat.Cpu.FanRpm = (int)Math.Round(s.Value ?? 0);
                        }
                    }
                }
                foreach (IHardware sub in hw.SubHardware) {
                    sub.Update();
                    foreach (ISensor s in sub.Sensors) {
                        if (s.SensorType == SensorType.Fan && (s.Value ?? 0) > 0) {
                            if (s.Name.Contains("CPU", StringComparison.OrdinalIgnoreCase) || stat.Cpu.FanRpm == 0) {
                                stat.Cpu.FanRpm = (int)Math.Round(s.Value ?? 0);
                            }
                        }
                    }
                }
            }
            else if (hw.HardwareType == HardwareType.GpuNvidia ||
                     hw.HardwareType == HardwareType.GpuAmd ||
                     hw.HardwareType == HardwareType.GpuIntel) {
                foreach (ISensor s in hw.Sensors) {
                    if (s.SensorType == SensorType.Load && s.Name.Contains("Core")) {
                        stat.Gpu.Load = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Temperature && s.Name.Contains("Core")) {
                        stat.Gpu.Temp = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Clock && s.Name.Contains("Core")) {
                        stat.Gpu.Freq = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Control && s.Name.Contains("Fan")) {
                        stat.Gpu.FanPercent = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Fan && s.Name.Contains("Fan")) {
                        stat.Gpu.FanRpm = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Power && s.Name.Contains("Package")) {
                        stat.Gpu.PowerWatts = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.SmallData && s.Name.Contains("GPU Memory Used")) {
                        stat.Gpu.VramUsedMb = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.SmallData && s.Name.Contains("GPU Memory Total")) {
                        stat.Gpu.VramTotalMb = (int)Math.Round(s.Value ?? 0);
                    }
                }
            }
            else if (hw.HardwareType == HardwareType.Memory) {
                foreach (ISensor s in hw.Sensors) {
                    if (s.SensorType == SensorType.Load && s.Name == "Memory") {
                        stat.Ram.Load = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Data && s.Name == "Memory Used") {
                        stat.Ram.UsedMb = (int)Math.Round((s.Value ?? 0) * 1024);
                    }
                }
            }
            else if (hw.HardwareType == HardwareType.Storage && stat.Disk.Temp == 0) {
                foreach (ISensor s in hw.Sensors) {
                    if (s.SensorType == SensorType.Temperature) {
                        stat.Disk.Temp = (int)Math.Round(s.Value ?? 0);
                        break;
                    }
                }
            }
        }

        try {
            string sysRoot = Path.GetPathRoot(Environment.SystemDirectory) ?? "C:\\";
            var drive = new DriveInfo(sysRoot);
            long total = drive.TotalSize;
            long used = total - drive.AvailableFreeSpace;
            if (total > 0) {
                stat.Disk.UsedGb = (int)Math.Round(used / 1024.0 / 1024.0 / 1024.0);
                stat.Disk.UsedPercent = (int)Math.Round((double)used / total * 100.0);
            }
        }
        catch {
            // Ignorujeme chybu čtení kapacity disku
        }

        stat.Net = ReadNetworkSpeed();
        stat.Agent = HermesStatusReader.ReadStatus();

        stat.PcPowerWatts = stat.Cpu.PowerWatts + stat.Gpu.PowerWatts + BaseSystemPowerWatts;
        return stat;
    }

    private NetStats ReadNetworkSpeed() {
        try {
            long rxTotal = 0;
            long txTotal = 0;

            foreach (var nic in System.Net.NetworkInformation.NetworkInterface.GetAllNetworkInterfaces()) {
                if (nic.OperationalStatus == System.Net.NetworkInformation.OperationalStatus.Up &&
                    nic.NetworkInterfaceType != System.Net.NetworkInformation.NetworkInterfaceType.Loopback) {
                    var stats = nic.GetIPStatistics();
                    rxTotal += stats.BytesReceived;
                    txTotal += stats.BytesSent;
                }
            }

            var now = DateTime.UtcNow;
            double seconds = (now - _prevNetTime).TotalSeconds;

            double dlMbps = 0.0;
            double ulMbps = 0.0;

            if (seconds > 0 && _prevNetRxBytes > 0) {
                // (bytes * 8) / (1024 * 1024 * seconds) = megabits per second
                dlMbps = Math.Round(Math.Max(0.0, (rxTotal - _prevNetRxBytes) * 8.0 / 1024.0 / 1024.0 / seconds), 1);
                ulMbps = Math.Round(Math.Max(0.0, (txTotal - _prevNetTxBytes) * 8.0 / 1024.0 / 1024.0 / seconds), 1);
            }

            if (dlMbps > _peakDlMbps) _peakDlMbps = dlMbps;
            if (ulMbps > _peakUlMbps) _peakUlMbps = ulMbps;

            _prevNetRxBytes = rxTotal;
            _prevNetTxBytes = txTotal;
            _prevNetTime = now;

            return new NetStats {
                DownloadKbps = dlMbps,
                UploadKbps = ulMbps,
                DownloadPeak = _peakDlMbps,
                UploadPeak = _peakUlMbps
            };
        }
        catch {
            return new NetStats();
        }
    }

    public void Dispose() {
        _computer.Close();
    }
}
