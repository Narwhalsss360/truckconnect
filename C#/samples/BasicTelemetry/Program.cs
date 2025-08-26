using TruckConnect;
using Version = TruckConnect.Version;

TimeSpan runFor = TimeSpan.FromMinutes(5);

Connection connection = new();
await connection.ConnectAsync();
Version version = await connection.GetVersion();

if (version.Major != Version.CurrentVersion.Major || version.Minor != Version.CurrentVersion.Minor) {
    Console.Error.WriteLine($"Version Mismatch Client:{Version.CurrentVersion},  Server:{version}");
    return;
}

if (version.Patch != Version.CurrentVersion.Patch || version.Patch != Version.CurrentVersion.Patch) {
    Console.Error.WriteLine($"Version Mismatch Client:{Version.CurrentVersion},  Server:{version}");
    Console.Error.WriteLine($"{(version.Patch > Version.CurrentVersion.Patch ? "Client" : "Server")} is missing patches.");
}

DateTime start = DateTime.Now;
while (DateTime.Now - start < runFor)
{
    ValueStorage<bool> paused = await connection.RequestAsync<ValueStorage<bool>>(TelemetryID.ChannelPaused);

    if (paused.Value)
    {
        Console.WriteLine("<paused>");
        continue;
    }

    ValueStorage<float> speed = await connection.RequestAsync<ValueStorage<float>>(TelemetryID.TruckChannelSpeed);

    if (!speed.Initialized)
    {
        Console.WriteLine("<uninitialized>");
        continue;
    }

    Console.WriteLine($"{speed.Value:F3}m/s");
}

connection.Disconnect();

