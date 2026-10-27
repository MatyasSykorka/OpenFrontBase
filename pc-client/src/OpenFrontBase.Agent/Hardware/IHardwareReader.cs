using OpenFrontBase.Agent.Models;

namespace OpenFrontBase.Agent.Hardware;

/// <summary>
/// CZ: Společné rozhraní pro čtení hardwarových senzorů na Windows i Linuxu.
/// EN: Common interface for reading hardware sensors on both Windows and Linux.
/// </summary>
public interface IHardwareReader : IDisposable {
    SpecsMessage GetStaticSpecs();
    StatMessage GetCurrentTelemetry();
}
