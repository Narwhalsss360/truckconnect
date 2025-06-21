using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);
TimeSpan refreshInterval = TimeSpan.FromMilliseconds(1000 / 25);

await StructuresTest();
return;
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
        await Task.Delay(refreshInterval);
    }
    await connection.UnregisterDataDefinitionAsync(gameStatus);
    connection.Disconnect();
}

async Task StructuresTest()
{
    Connection connection = new("127.0.0.1");
    await connection.ConnectAsync();

    DateTime start = DateTime.Now;
    bool firstPause = true;
    while (DateTime.Now - start < runFor)
    {
        var master = await connection.RequestAsync<MasterStorage>();
        Console.SetCursorPosition(0, 0);

        if (master.Channels.General.ChannelPaused.Value)
        {
            if (firstPause)
            {
                firstPause = false;
                Console.Clear();
            }

            Console.WriteLine("Paused...");
            await Task.Delay(refreshInterval);
            continue;
        }
        firstPause = true;

        string line = "";
        line += $"Game Time: {master.Channels.General.ChannelGameTime.ValueOrDefault()} | ";
        line += $"Local Scale: {master.Channels.General.ChannelLocalScale.ValueOrDefault()} | ";
        line += $"Next Rest Stop: {master.Channels.General.ChannelNextRestStop.ValueOrDefault()}";
        Console.WriteLine(line.PadRight(Console.WindowWidth));

        line = "";
        line += $"{master.Channels.Truck.TruckChannelEngineRpm.ValueOrDefault(0)}rpm | ";
        line += $"{master.Channels.Truck.TruckChannelEngineGear.ValueOrDefault()} | ";
        line += $"{master.Channels.Truck.TruckChannelSpeed.ValueOrDefault()}m/s | ";
        line += $"{master.Channels.Truck.TruckChannelFuel.ValueOrDefault()}L";
        Console.WriteLine(line.PadRight(Console.WindowWidth));

        int trailerCount = TrailerCount(master.Configuration.ConfigurationTrailerInfo);

        for (int i = 0; i < trailerCount; i++)
        {
            Console.WriteLine($"Trailer {i + 1}".PadRight(Console.WindowWidth));
            line = "";
            line += $"\t{master.Channels.Trailer[i].TrailerChannelConnected.ValueOrDefault("Connected", "Disconnected")} | ";
            line += $"Cargo Damage: {master.Channels.Trailer[i].TrailerChannelCargoDamage.ValueOrDefault(3)}";
            Console.WriteLine(line.PadRight(Console.WindowWidth));
        }

        await Task.Delay(refreshInterval);
    }
    connection.Disconnect();
}

int TrailerCount(MasterStorage.ConfigurationStorage.ConfigurationTrailerStorage[] trailerConfigurations)
{
    if (trailerConfigurations.Length != 10)
        throw new InvalidProgramException();

    if (!trailerConfigurations[0].Latest.Initialized)
        return 0;

    UInt32 latest = trailerConfigurations[0].Latest.Value;
    for (int i = 1; i < 10; i++)
    {
        if (!trailerConfigurations[i].Latest.Initialized)
            return i;
        if (trailerConfigurations[i].Latest.Value != latest)
            return i;
    }

    return 10;
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

public static class ValueStorageStringifier
{
    public static string DynamicValueOrDefault(dynamic value, string @default = "---") =>
        value.Initialized ? $"{value.Value}" : @default;

    public static string ValueOrDefault(this object value, string @default = "---") =>
        DynamicValueOrDefault(value, @default);

    public static string ValueOrDefault(this ValueStorage<bool> value, string truthy = "true", string falsy = "false", string @default = "---")
        => value.Initialized ? (value.Value ? truthy : falsy) : @default;

    public static string ValueOrDefault(this ValueStorage<Single> value, int decimalPlaces = 2, string @default = "---") =>
        value.Initialized ? value.Value.ToString($"F{decimalPlaces}") : @default;
}

