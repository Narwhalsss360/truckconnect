using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);

GameStatus gameStatus = new();
Connection connection = new("127.0.0.1");
connection.Connect();
await connection.RegisterDataDefinitionAsync(gameStatus);

DateTime start = DateTime.Now;
while (DateTime.Now - start < runFor)
{
    await connection.RequestAsync(gameStatus);
    if (gameStatus.Paused.Value)
    {
        Console.WriteLine(".");
        continue;
    }

    Console.Write($"{(gameStatus.LocalScale.Initialized ? gameStatus.LocalScale.Value : "---")} | {(gameStatus.GameTime.Initialized ? gameStatus.GameTime.Value : "---")} | Trailers: ");
    foreach (ValueStorage<bool> trailerConnected in gameStatus.TrailersConencted)
        Console.Write(trailerConnected.Initialized ? (trailerConnected.Value ? "." : "x") : "?");
    Console.WriteLine();
}
await connection.UnregisterDataDefinitionAsync(gameStatus);
connection.Disconnect();


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

