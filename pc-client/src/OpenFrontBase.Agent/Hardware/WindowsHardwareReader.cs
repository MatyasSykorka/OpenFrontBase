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
            DiskTotalGb = diskTotalGb
        };
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
                        stat.Cpu.Freq = (int)Math.Round(s.Value ?? 0);
                    }
                    else if (s.SensorType == SensorType.Power && s.Name.Contains("Package")) {
                        stat.Cpu.PowerWatts = (int)Math.Round(s.Value ?? 0);
                    }
                }
            }
            else if (hw.HardwareType == HardwareType.Motherboard) {
                foreach (IHardware sub in hw.SubHardware) {
                    sub.Update();
                    foreach (ISensor s in sub.Sensors) {
                        if (s.SensorType == SensorType.Fan && stat.Cpu.FanRpm == 0 && (s.Value ?? 0) > 0) {
                            stat.Cpu.FanRpm = (int)Math.Round(s.Value ?? 0);
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

        stat.PcPowerWatts = stat.Cpu.PowerWatts + stat.Gpu.PowerWatts + BaseSystemPowerWatts;
        return stat;
    }

    public void Dispose() {
        _computer.Close();
    }
}
