using TruckConnect;
using Version = TruckConnect.Version;

const int GAME_STATUS_ID = 0;

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
GaugeCluster cluster = new();

DataDefinition gameStatusDefinition = DataDefinition.Define<GameStatus>(GAME_STATUS_ID);
await connection.RegisterDataDefinitionAsync(cluster);
await connection.RegisterDataDefinitionAsync(gameStatusDefinition);

DateTime start = DateTime.Now;
bool clearRequired = true;
while (DateTime.Now - start < runFor)
{
    GameStatus status = await connection.RequestAsync<GameStatus>(gameStatusDefinition);

    Console.SetCursorPosition(0, 0);
    if (status.Paused.Value)
    {
        if (clearRequired)
        {
            Console.Clear();
            clearRequired = false;
        }
        Console.Write("<paused>");
        continue;
    }
    clearRequired = true;

    await connection.RequestAsync(cluster);
    if (!cluster.ElecricEnabled.Value)
    {
        if (clearRequired)
        {
            Console.Clear();
            clearRequired = false;
        }
        Console.Write("off");
        continue;
    }
    clearRequired = true;

    string line;
    line = (cluster.EngineRpm.Initialized ? $"{cluster.EngineRpm.Value:F0}" : "---") + "rpm | ";
    line += (cluster.Speed.Initialized ? $"{cluster.Speed.Value:F2}" : "---") + "m/s";
    Console.WriteLine(line.PadRight(Console.WindowWidth));

    line = "Trailer Cargo Damage:";
    Console.WriteLine(line.PadRight(Console.WindowWidth));

    for (int i = 0; i < cluster.CargoDamage.Length; i++)
    {
        line = $"  Trailer {i + 1}: " + (cluster.CargoDamage[i].Initialized ? $"{cluster.CargoDamage[i].Value * 100:F0}%" : "---");
        Console.WriteLine(line.PadRight(Console.WindowWidth));
    }
}

await connection.UnregisterDataDefinitionAsync(gameStatusDefinition);
await connection.UnregisterDataDefinitionAsync(cluster);
connection.Disconnect();

class GaugeCluster() : DataDefinition(GAUGE_CLUSTER_ID)
{
    const int GAUGE_CLUSTER_ID = 1;

    [DataDefinitionMember(TelemetryID.TruckChannelEngineEnabled)]
    public ValueStorage<bool> EngineEnabled = new();

    [DataDefinitionMember(TelemetryID.TruckChannelElectricEnabled)]
    public ValueStorage<bool> ElecricEnabled = new();

    [DataDefinitionMember(TelemetryID.TruckChannelEngineRpm)]
    public ValueStorage<float> EngineRpm = new();

    [DataDefinitionMember(TelemetryID.TruckChannelSpeed)]
    public ValueStorage<float> Speed = new();

    [DataDefinitionMember(TelemetryID.TrailerChannelCargoDamage, TrailerIndexOrCount.SCS_TELEMETRY_trailers_count)]
    public ValueStorage<float>[] CargoDamage = new ValueStorage<float>[TrailerIndexOrCount.SCS_TELEMETRY_trailers_count];
}

struct GameStatus()
{
    [DataDefinitionMember(TelemetryID.ChannelPaused)]
    public ValueStorage<bool> Paused = new();

    [DataDefinitionMember(TelemetryID.ChannelGameTime)]
    public ValueStorage<UInt32> GameTime = new();

    [DataDefinitionMember(TelemetryID.ChannelLocalScale)]
    public ValueStorage<float> LocalScale = new();
}

