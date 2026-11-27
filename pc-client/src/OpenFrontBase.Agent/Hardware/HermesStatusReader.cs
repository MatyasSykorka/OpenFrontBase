using System.IO;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using OpenFrontBase.Agent.Models;

namespace OpenFrontBase.Agent.Hardware;

/// <summary>
/// CZ: Čtenář lokálního stavu Hermes Agenta a lokálních LLM pro Windows i Linux.
/// EN: Local Hermes Agent and local LLM status reader for Windows and Linux.
/// </summary>
public static class HermesStatusReader {
    private static readonly AgentStats _mergedStats = new() {
        Active = false,
        Name = "-",
        Status = "Waiting for Agent",
        Tool = "-",
        TokensPerSecond = 0.0,
        MemoryUsageMb = 0,
        ContextWindow = "-"
    };
    private static DateTime _lastActiveTime = DateTime.MinValue;
    private static readonly object _lock = new();
    private static readonly HttpClient _httpClient = new() { Timeout = TimeSpan.FromMilliseconds(500) };

    static HermesStatusReader() {
        StartLocalHttpServer();
        StartLocalLlmMonitor();
    }

    private static void StartLocalHttpServer() {
        try {
            var listener = new HttpListener();
            listener.Prefixes.Add("http://127.0.0.1:28888/");
            listener.Start();

            Task.Run(async () => {
                while (listener.IsListening) {
                    try {
                        var ctx = await listener.GetContextAsync();
                        if (ctx.Request.HttpMethod == "POST") {
                            using var reader = new StreamReader(ctx.Request.InputStream, ctx.Request.ContentEncoding);
                            string body = await reader.ReadToEndAsync();
                            var stats = JsonSerializer.Deserialize<AgentStats>(body);
                            if (stats != null) {
                                MergeStats(stats);
                            }
                            ctx.Response.StatusCode = 200;
                        }
                        else {
                            ctx.Response.StatusCode = 200;
                            byte[] ok = "OK"u8.ToArray();
                            await ctx.Response.OutputStream.WriteAsync(ok);
                        }
                        ctx.Response.Close();
                    }
                    catch {
                        // Ignorujeme chyby jednotlivých spojení
                    }
                }
            });
        }
        catch {
            // Port již může být obsazen nebo nedostupný
        }
    }

    /// <summary>
    /// CZ: Monitoruje lokální LLM (Ollama / llama-server) na pozadí a zjišťuje obsazenou RAM/VRAM.
    /// </summary>
    private static void StartLocalLlmMonitor() {
        Task.Run(async () => {
            while (true) {
                try {
                    await CheckLocalOllamaAsync();
                }
                catch {
                    // Ignorujeme chyby monitoru
                }
                await Task.Delay(3000);
            }
        });
    }

    private static async Task CheckLocalOllamaAsync() {
        string[] endpoints = ["http://127.0.0.1:11434/api/ps", "http://localhost:11434/api/ps"];
        foreach (var ep in endpoints) {
            try {
                var resp = await _httpClient.GetStringAsync(ep);
                using var doc = JsonDocument.Parse(resp);
                if (doc.RootElement.TryGetProperty("models", out var models) && models.GetArrayLength() > 0) {
                    var m = models[0];
                    string modelName = m.TryGetProperty("name", out var n) ? n.GetString() ?? "" : "";
                    long sizeBytes = m.TryGetProperty("size", out var s) ? s.GetInt64() : 0;
                    int ctxLen = m.TryGetProperty("context_length", out var c) ? c.GetInt32() : 0;

                    int memMb = (int)(sizeBytes / (1024 * 1024));
                    if (memMb > 0) {
                        lock (_lock) {
                            if (_mergedStats.MemoryUsageMb < memMb) {
                                _mergedStats.MemoryUsageMb = memMb;
                            }
                            if ((string.IsNullOrEmpty(_mergedStats.Name) || _mergedStats.Name == "-" || _mergedStats.Name == "Hermes Agent") && !string.IsNullOrEmpty(modelName)) {
                                _mergedStats.Name = modelName;
                            }
                            if ((string.IsNullOrEmpty(_mergedStats.ContextWindow) || _mergedStats.ContextWindow == "-") && ctxLen > 0) {
                                _mergedStats.ContextWindow = ctxLen >= 1000 ? $"{ctxLen / 1000}K" : ctxLen.ToString();
                            }
                        }
                    }
                    return;
                }
            }
            catch {
                // Endpoint neběží
            }
        }
    }

    /// <summary>
    /// CZ: Bezpečně sloučí nově příchozí data se stávajícími. Prázdné hodnoty nepřemazávají stávající.
    /// </summary>
    private static void MergeStats(AgentStats incoming) {
        if (incoming == null) return;
        lock (_lock) {
            _lastActiveTime = DateTime.UtcNow;
            _mergedStats.Active = incoming.Active;

            if (!string.IsNullOrWhiteSpace(incoming.Name) && incoming.Name != "-")
                _mergedStats.Name = incoming.Name.Trim();

            if (!string.IsNullOrWhiteSpace(incoming.Status) && incoming.Status != "-")
                _mergedStats.Status = incoming.Status.Trim();

            if (!string.IsNullOrWhiteSpace(incoming.Tool) && incoming.Tool != "-")
                _mergedStats.Tool = incoming.Tool.Trim();

            if (!string.IsNullOrWhiteSpace(incoming.ContextWindow) && incoming.ContextWindow != "-")
                _mergedStats.ContextWindow = incoming.ContextWindow.Trim();

            if (incoming.TokensPerSecond > 0.05)
                _mergedStats.TokensPerSecond = incoming.TokensPerSecond;

            if (incoming.MemoryUsageMb > 0) {
                // Ochrana proti dočasnému probliknutí paměti samostatného Python procesu (~270 MB),
                // pokud už víme, že běží model LLM s pamětí > 1 GB.
                if (_mergedStats.MemoryUsageMb >= 1024 && incoming.MemoryUsageMb < 1024) {
                    // Ignorujeme dočasný propad na CLI wrapper
                } else {
                    _mergedStats.MemoryUsageMb = incoming.MemoryUsageMb;
                }
            }
        }
    }

    public static AgentStats ReadStatus() {
        // Zkontrolujeme sdílené soubory
        string[] possibleStatusFiles = [
            Environment.GetEnvironmentVariable("HERMES_STATUS_FILE") ?? string.Empty,
            Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.UserProfile), ".hermes", "status.json"),
            Path.Combine(Path.GetTempPath(), "hermes_status.json"),
            "/tmp/hermes_status.json"
        ];

        foreach (var path in possibleStatusFiles) {
            if (string.IsNullOrEmpty(path)) continue;

            try {
                if (File.Exists(path)) {
                    var lastWrite = File.GetLastWriteTimeUtc(path);
                    if ((DateTime.UtcNow - lastWrite).TotalSeconds <= 60) {
                        using var fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.ReadWrite | FileShare.Delete);
                        using var reader = new StreamReader(fs, Encoding.UTF8);
                        string json = reader.ReadToEnd();

                        var stats = JsonSerializer.Deserialize<AgentStats>(json);
                        if (stats != null) {
                            MergeStats(stats);
                            break;
                        }
                    }
                }
            }
            catch {
                // Ignorujeme chyby čtení ze souboru
            }
        }

        lock (_lock) {
            if (_lastActiveTime != DateTime.MinValue && (DateTime.UtcNow - _lastActiveTime).TotalSeconds > 60) {
                if (_mergedStats.Status != "Offline") {
                    _mergedStats.Status = "Idle (Stale)";
                }
            }

            return new AgentStats {
                Active = _mergedStats.Active,
                Name = _mergedStats.Name,
                Status = _mergedStats.Status,
                Tool = _mergedStats.Tool,
                TokensPerSecond = _mergedStats.TokensPerSecond,
                MemoryUsageMb = _mergedStats.MemoryUsageMb,
                ContextWindow = _mergedStats.ContextWindow
            };
        }
    }
}
