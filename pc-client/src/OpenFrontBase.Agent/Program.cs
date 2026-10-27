using OpenFrontBase.Agent.Hardware;
using OpenFrontBase.Agent.Services;

var builder = Host.CreateApplicationBuilder(args);

// Automatický výběr čtečky senzorů podle operačního systému
// Automatic sensor reader selection based on the operating system
if (OperatingSystem.IsLinux()) {
    builder.Services.AddSingleton<IHardwareReader, LinuxHardwareReader>();
}
else if (OperatingSystem.IsWindows()) {
    builder.Services.AddSingleton<IHardwareReader, WindowsHardwareReader>();
}
else {
    throw new PlatformNotSupportedException("Podporován je pouze Linux a Windows / Only Linux and Windows are supported.");
}

builder.Services.AddHostedService<SerialWorker>();

var host = builder.Build();
host.Run();
