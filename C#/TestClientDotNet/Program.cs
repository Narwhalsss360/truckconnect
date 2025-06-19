using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);
TimeSpan refreshRate = TimeSpan.FromMilliseconds(1000 / 25);

await DefinitionTest();

async Task DefinitionTest()
{
    GameStatus gameStatus = new();
    DataDefinition gaugeClusterDefinition = DataDefinition.Define<GaugeCluster>(2);

    Connection connection = new("127.0.0.1");
    await connection.ConnectAsync();
    await connection.RegisterDataDefinitionAsync(gameStatus);
    await connection.RegisterDataDefinitionAsync(gaugeClusterDefinition);

    DateTime start = DateTime.Now;
    while (DateTime.Now - start < runFor)
    {
        await connection.RequestAsync(gameStatus);
        if (gameStatus.Paused.Value)
        {
            Console.WriteLine(".");
            continue;
        }

        GaugeCluster gaugeCluster = await connection.RequestAsync<GaugeCluster>(gaugeClusterDefinition);

        Console.Write($"{(gameStatus.LocalScale.Initialized ? gameStatus.LocalScale.Value : "---")} | {(gameStatus.GameTime.Initialized ? gameStatus.GameTime.Value : "---")} | Trailers: ");
        foreach (ValueStorage<bool> trailerConnected in gameStatus.TrailersConencted)
            Console.Write(trailerConnected.Initialized ? (trailerConnected.Value ? "." : "x") : "?");
        Console.WriteLine();

        Console.Write($"{(gaugeCluster.engineRpm.Initialized ? gaugeCluster.engineRpm.Value.ToString("F0") : "---")}rpm | ");
        Console.Write($"{(gaugeCluster.speed.Initialized ? gaugeCluster.speed.Value.ToString("F2") : "---")}m/s | ");
        Console.Write($"{(gaugeCluster.lightLBlinker.Initialized ? (gaugeCluster.lightLBlinker.Value ? "<" : "-") : "?")}-");
        Console.WriteLine($"{(gaugeCluster.lightRBlinker.Initialized ? (gaugeCluster.lightRBlinker.Value ? ">" : "-") : "?")}");
        Console.Out.Flush();
        Thread.Sleep((int)refreshRate.TotalMilliseconds);
    }
    await connection.UnregisterDataDefinitionAsync(gameStatus);
    connection.Disconnect();
}

class GameStatus : DataDefinition
{
    [DataDefinitionMember(TelemetryID.ChannelPaused)]
    public ValueStorage<bool> Paused = default;

    [DataDefinitionMember(TelemetryID.ChannelGameTime)]
    public ValueStorage<UInt32> GameTime = default;

    [DataDefinitionMember(TelemetryID.ChannelLocalScale)]
    public ValueStorage<float> LocalScale = default;

    [DataDefinitionMember(TelemetryID.TrailerChannelConnected, TrailerIndexOrCount.SCS_TELEMETRY_trailers_count)]
    public ValueStorage<bool>[] TrailersConencted = new ValueStorage<bool>[TrailerIndexOrCount.SCS_TELEMETRY_trailers_count];

    public GameStatus()
        : base(1) {}
}

struct GaugeCluster()
{
    [DataDefinitionMember(TelemetryID.TruckChannelEngineRpm)]
    public ValueStorage<float> engineRpm = default;

    [DataDefinitionMember(TelemetryID.TruckChannelSpeed)]
    public ValueStorage<float> speed = default;

    [DataDefinitionMember(TelemetryID.TruckChannelLightLblinker)]
    public ValueStorage<bool> lightLBlinker = default;

    [DataDefinitionMember(TelemetryID.TruckChannelLightRblinker)]
    public ValueStorage<bool> lightRBlinker = default;
}

