using System.IO.Ports;
using System.Text;
using System.Text.Json;
using OpenFrontBase.Agent.Hardware;
using OpenFrontBase.Agent.Models;

namespace OpenFrontBase.Agent.Services;

/// <summary>
/// CZ: Hlavní služba na pozadí, která udržuje spojení s ESP32 a každou sekundu odesílá reálná JSON data.
/// EN: Main background service that maintains ESP32 connection and sends real JSON data every second.
/// </summary>
public class SerialWorker : BackgroundService {
    private readonly ILogger<SerialWorker> _logger;
    private readonly IConfiguration _config;
    private readonly IHardwareReader _hardwareReader;
    private SerialPort? _serialPort;

    public SerialWorker(ILogger<SerialWorker> logger, IConfiguration config, IHardwareReader hardwareReader) {
        _logger = logger;
        _config = config;
        _hardwareReader = hardwareReader;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken) {
        var specs = _hardwareReader.GetStaticSpecs();
        _logger.LogInformation(
            "Detekovaný HW / Detected HW: MB={Mb} | CPU=[{CpuVendor}] {Cpu} | GPU=[{GpuVendor}] {Gpu} | RAM={Ram} GB ({RamName}) | Disk={DiskName} ({DiskGb} GB)",
            specs.MotherboardName, specs.CpuVendor, specs.CpuName, specs.GpuVendor, specs.GpuName, specs.RamTotalGb, specs.RamName, specs.DiskName, specs.DiskTotalGb);

        while (!stoppingToken.IsCancellationRequested) {
            try {
                if (_serialPort == null || !_serialPort.IsOpen) {
                    ConnectToBoard();
                }
                else {
                    SendTelemetryTick();
                    ReadIncomingMessages();
                }

                await Task.Delay(1000, stoppingToken);
            }
            catch (OperationCanceledException) when (stoppingToken.IsCancellationRequested) {
                // Čisté ukončení při stisku Ctrl+C
                break;
            }
            catch (Exception ex) {
                _logger.LogWarning("Spojení přerušeno / Connection lost: {Message}. Zkouším znovu za 3 s...", ex.Message);
                ClosePortSafely();
                await Task.Delay(3000, stoppingToken);
            }
        }

        ClosePortSafely();
    }

    private void ConnectToBoard() {
        string? configuredPort = _config["Serial:Port"];
        int baudRate = _config.GetValue<int>("Serial:BaudRate", 115200);

        string? portName = SerialPortDiscovery.FindBoardPort(configuredPort);

        if (string.IsNullOrEmpty(portName)) {
            PrintSimulatedTelemetry();
            return;
        }

        _logger.LogInformation("Připojuji se k portu / Connecting to port: {Port} ({Baud} baud)...", portName, baudRate);

        _serialPort = new SerialPort(portName, baudRate, Parity.None, 8, StopBits.One) {
            Encoding = Encoding.UTF8,
            NewLine = "\n",
            ReadTimeout = 500,
            WriteTimeout = 500,
            DtrEnable = false,
            RtsEnable = false
        };

        _serialPort.Open();

        // 1. Odešleme Handshake (hello)
        var hello = new HelloMessage {
            Os = OperatingSystem.IsLinux() ? "Linux" : "Windows",
            Timestamp = DateTimeOffset.Now.ToUnixTimeSeconds()
        };
        SendJsonLine(hello);

        // 2. Odešleme statické specifikace PC
        var specs = _hardwareReader.GetStaticSpecs();
        SendJsonLine(specs);

        _logger.LogInformation("Spojeno! Handshake a Specs odeslány / Connected! Handshake and Specs sent.");
    }

    private void SendTelemetryTick() {
        var msg = _hardwareReader.GetCurrentTelemetry();
        SendJsonLine(msg);
    }

    private void PrintSimulatedTelemetry() {
        var msg = _hardwareReader.GetCurrentTelemetry();
        string json = JsonSerializer.Serialize(msg);
        _logger.LogInformation("[DRY-RUN TX] {Json}", json);
    }

    private void SendJsonLine<T>(T payload) {
        if (_serialPort == null || !_serialPort.IsOpen) {
            return;
        }

        string json = JsonSerializer.Serialize(payload);
        _serialPort.WriteLine(json);
        _logger.LogDebug("[TX] {Json}", json);
    }

    private void ReadIncomingMessages() {
        if (_serialPort == null || !_serialPort.IsOpen) {
            return;
        }

        while (_serialPort.BytesToRead > 0) {
            try {
                string line = _serialPort.ReadLine().Trim();
                if (line.StartsWith('{')) {
                    _logger.LogInformation("[RX z ESP32] {Line}", line);
                }
            }
            catch (TimeoutException) {
                break;
            }
        }
    }

    private void ClosePortSafely() {
        try {
            if (_serialPort != null) {
                if (_serialPort.IsOpen) {
                    _serialPort.Close();
                }
                _serialPort.Dispose();
            }
        }
        catch {
            // Ignorujeme chybu při zavírání už odpojeného USB zařízení
        }
        finally {
            _serialPort = null;
        }
    }
}
