using System.IO;
using System.Net;
using System.Text;
using System.Text.Json;
using OpenFrontBase.Agent.Models;

namespace OpenFrontBase.Agent.Hardware;

/// <summary>
/// CZ: Čtenář lokálního stavu Hermes Agenta pro Windows i Linux (přes sdílený soubor i lokální HTTP API).
/// EN: Local Hermes Agent status reader for both Windows and Linux (via shared file and local HTTP API).
/// </summary>
public static class HermesStatusReader {
    private static AgentStats? _latestHttpStats;
    private static DateTime _latestHttpTime = DateTime.MinValue;
    private static readonly object _lock = new();

    static HermesStatusReader() {
        StartLocalHttpServer();
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
                                lock (_lock) {
                                    _latestHttpStats = stats;
                                    _latestHttpTime = DateTime.UtcNow;
                                }
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
                        // Ignorujeme chyby jednotlivých požadavků
                    }
                }
            });
        }
        catch {
            // Pokud nelze otevřít port, pokračujeme čistě přes soubor
        }
    }

    public static AgentStats ReadStatus() {
        // 1. Nejprve zkontrolujeme data z HTTP endpointu (pokud přišla v posledních 30 s)
        lock (_lock) {
            if (_latestHttpStats != null && (DateTime.UtcNow - _latestHttpTime).TotalSeconds <= 30) {
                return _latestHttpStats;
            }
        }

        // 2. Pokud není HTTP, zkontrolujeme soubory (multiplatformní cesty pro Windows i Linux)
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
                    bool isRecent = (DateTime.UtcNow - lastWrite).TotalSeconds <= 30;

                    // Otevření s FileShare.ReadWrite pro bezpečné čtení na Windows během zápisu Pythonem
                    using var fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.ReadWrite | FileShare.Delete);
                    using var reader = new StreamReader(fs, Encoding.UTF8);
                    string json = reader.ReadToEnd();

                    var stats = JsonSerializer.Deserialize<AgentStats>(json);
                    if (stats != null) {
                        if (!isRecent && stats.Status != "Offline") {
                            stats.Status = "Idle (Stale)";
                        }
                        return stats;
                    }
                }
            }
            catch {
                // Ignorujeme chyby čtení stavu
            }
        }

        return new AgentStats {
            Active = false,
            Name = "Hermes Agent",
            Status = "Waiting for Agent",
            Tool = "-",
            TokensPerSecond = 0.0,
            MemoryUsageMb = 0,
            ContextWindow = "-"
        };
    }
}
