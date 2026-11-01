using System.IO.Ports;

namespace OpenFrontBase.Agent.Services;

/// <summary>
/// CZ: Automatické vyhledání sériového portu desky Waveshare (čip WCH CH343).
/// EN: Automatic serial port discovery for the Waveshare board (WCH CH343 chip).
/// </summary>
public static class SerialPortDiscovery {
    // WCH (QinHeng Electronics) Vendor ID = 0x1A86
    private const string TargetVid = "1a86";

    // Podporované Product ID pro CH343 (55d3, 55d4) a starší CH340 (7523)
    private static readonly string[] TargetPids = ["55d3", "55d4", "7523"];

    public static string? FindBoardPort(string? configuredPort) {
        if (!string.IsNullOrWhiteSpace(configuredPort) && !configuredPort.Equals("auto", StringComparison.OrdinalIgnoreCase)) {
            return configuredPort;
        }

        if (OperatingSystem.IsLinux()) {
            return FindPortOnLinux();
        }

        string[] ports = SerialPort.GetPortNames();
        return ports.FirstOrDefault(p => p.Contains("ttyACM") || p.Contains("ttyUSB") || p.StartsWith("COM"));
    }

    private static string? FindPortOnLinux() {
        const string sysTtyPath = "/sys/class/tty";
        if (!Directory.Exists(sysTtyPath)) {
            return null;
        }

        foreach (string ttyDir in Directory.GetDirectories(sysTtyPath)) {
            string ttyName = Path.GetFileName(ttyDir);
            if (!ttyName.StartsWith("ttyACM") && !ttyName.StartsWith("ttyUSB")) {
                continue;
            }

            try {
                string deviceSymlink = Path.Combine(ttyDir, "device");
                if (!Directory.Exists(deviceSymlink)) {
                    continue;
                }

                // Nejprve převedeme symlink "/sys/class/tty/ttyACM0/device" na reálnou cestu v "/sys/devices/..."
                FileSystemInfo? resolved = Directory.ResolveLinkTarget(deviceSymlink, returnFinalTarget: true);
                DirectoryInfo? currentDir = resolved as DirectoryInfo ?? new DirectoryInfo(deviceSymlink);

                // Procházíme nadřazené složky USB stromu, dokud nenajdeme idVendor a idProduct
                for (int i = 0; i < 5 && currentDir != null; i++) {
                    string vidFile = Path.Combine(currentDir.FullName, "idVendor");
                    string pidFile = Path.Combine(currentDir.FullName, "idProduct");

                    if (File.Exists(vidFile) && File.Exists(pidFile)) {
                        string vid = File.ReadAllText(vidFile).Trim().ToLowerInvariant();
                        string pid = File.ReadAllText(pidFile).Trim().ToLowerInvariant();

                        if (vid == TargetVid && TargetPids.Contains(pid)) {
                            return $"/dev/{ttyName}";
                        }
                    }

                    currentDir = currentDir.Parent;
                }
            }
            catch {
                // Ignorujeme chyby čtení u nepřístupných systémových uzlů
            }
        }

        // Fallback: pokud existuje /dev/ttyACM0, vrátíme ho přímo
        if (File.Exists("/dev/ttyACM0")) {
            return "/dev/ttyACM0";
        }

        return null;
    }
}
