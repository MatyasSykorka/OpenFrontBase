using System.Text.Json.Serialization;

namespace OpenFrontBase.Agent.Models;

/// <summary>
/// CZ: Úvodní handshake zpráva odesílaná z PC do ESP32 po otevření portu.
/// EN: Initial handshake message sent from PC to ESP32 upon opening the port.
/// </summary>
public class HelloMessage {
    [JsonPropertyName("v")]
    public int Version { get; set; } = 1;

    [JsonPropertyName("type")]
    public string Type { get; set; } = "hello";

    [JsonPropertyName("client")]
    public string Client { get; set; } = "OpenFrontBase.Agent";

    [JsonPropertyName("os")]
    public string Os { get; set; } = string.Empty;

    [JsonPropertyName("ts")]
    public long Timestamp { get; set; }
}

/// <summary>
/// CZ: Statické informace o hardwaru PC (posílají se jednou po připojení).
/// EN: Static PC hardware specifications (sent once after connection).
/// </summary>
public class SpecsMessage {
    [JsonPropertyName("v")]
    public int Version { get; set; } = 1;

    [JsonPropertyName("type")]
    public string Type { get; set; } = "specs";

    [JsonPropertyName("cpu_vendor")]
    public string CpuVendor { get; set; } = "Unknown";

    [JsonPropertyName("cpu_name")]
    public string CpuName { get; set; } = "Unknown CPU";

    [JsonPropertyName("gpu_vendor")]
    public string GpuVendor { get; set; } = "Unknown";

    [JsonPropertyName("gpu_name")]
    public string GpuName { get; set; } = "Unknown GPU";

    [JsonPropertyName("mb_name")]
    public string MotherboardName { get; set; } = "Unknown Motherboard";

    [JsonPropertyName("ram_name")]
    public string RamName { get; set; } = "System RAM";

    [JsonPropertyName("ram_total_gb")]
    public int RamTotalGb { get; set; }

    [JsonPropertyName("disk_name")]
    public string DiskName { get; set; } = "System Disk";

    [JsonPropertyName("disk_total_gb")]
    public int DiskTotalGb { get; set; }

    [JsonPropertyName("net_name")]
    public string NetName { get; set; } = "Network Adapter";
}

/// <summary>
/// CZ: Pravidelná telemetrická zpráva (posílá se 1x za sekundu).
/// EN: Periodic telemetry message (sent once per second).
/// </summary>
public class StatMessage {
    [JsonPropertyName("v")]
    public int Version { get; set; } = 1;

    [JsonPropertyName("type")]
    public string Type { get; set; } = "stat";

    [JsonPropertyName("time")]
    public string Time { get; set; } = string.Empty;

    [JsonPropertyName("date")]
    public string Date { get; set; } = string.Empty;

    [JsonPropertyName("pc_power_w")]
    public int PcPowerWatts { get; set; }

    [JsonPropertyName("cpu")]
    public CpuStats Cpu { get; set; } = new();

    [JsonPropertyName("gpu")]
    public GpuStats Gpu { get; set; } = new();

    [JsonPropertyName("ram")]
    public RamStats Ram { get; set; } = new();

    [JsonPropertyName("disk")]
    public DiskStats Disk { get; set; } = new();

    [JsonPropertyName("net")]
    public NetStats Net { get; set; } = new();

    [JsonPropertyName("agent")]
    public AgentStats Agent { get; set; } = new();

    [JsonPropertyName("scr_on")]
    public bool ScreenOn { get; set; } = true;
}

public class AgentStats {
    [JsonPropertyName("active")]
    public bool Active { get; set; } = false;

    [JsonPropertyName("name")]
    public string Name { get; set; } = "Hermes Agent";

    [JsonPropertyName("status")]
    public string Status { get; set; } = "Waiting...";

    [JsonPropertyName("tool")]
    public string Tool { get; set; } = "-";

    [JsonPropertyName("tok_s")]
    public double TokensPerSecond { get; set; } = 0.0;

    [JsonPropertyName("mem_mb")]
    public int MemoryUsageMb { get; set; } = 0;

    [JsonPropertyName("ctx")]
    public string ContextWindow { get; set; } = "-";
}

public class CpuStats {
    [JsonPropertyName("load")]
    public int Load { get; set; }

    [JsonPropertyName("temp")]
    public int Temp { get; set; }

    [JsonPropertyName("freq")]
    public double Freq { get; set; }

    [JsonPropertyName("fan_rpm")]
    public int FanRpm { get; set; }

    [JsonPropertyName("power_w")]
    public int PowerWatts { get; set; }
}

public class GpuStats {
    [JsonPropertyName("load")]
    public int Load { get; set; }

    [JsonPropertyName("temp")]
    public int Temp { get; set; }

    [JsonPropertyName("freq")]
    public int Freq { get; set; }

    [JsonPropertyName("fan_pct")]
    public int FanPercent { get; set; }

    [JsonPropertyName("fan_rpm")]
    public int FanRpm { get; set; }

    [JsonPropertyName("power_w")]
    public int PowerWatts { get; set; }

    [JsonPropertyName("vram_used")]
    public int VramUsedMb { get; set; }

    [JsonPropertyName("vram_total")]
    public int VramTotalMb { get; set; }
}

public class RamStats {
    [JsonPropertyName("load")]
    public int Load { get; set; }

    [JsonPropertyName("used_mb")]
    public int UsedMb { get; set; }
}

public class DiskStats {
    [JsonPropertyName("used_pct")]
    public int UsedPercent { get; set; }

    [JsonPropertyName("used_gb")]
    public int UsedGb { get; set; }

    [JsonPropertyName("temp")]
    public int Temp { get; set; }
}

public class NetStats {
    [JsonPropertyName("dl_kbps")]
    public double DownloadKbps { get; set; }

    [JsonPropertyName("ul_kbps")]
    public double UploadKbps { get; set; }

    [JsonPropertyName("dl_peak")]
    public double DownloadPeak { get; set; }

    [JsonPropertyName("ul_peak")]
    public double UploadPeak { get; set; }
}
