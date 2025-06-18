using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);

Connection connection = new("127.0.0.1");
connection.Connect();

GameStatus gameStatus = new();
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

    Console.WriteLine($"{(gameStatus.LocalScale.Initialized ? gameStatus.LocalScale.Value : "---")} | {(gameStatus.GameTime.Initialized ? gameStatus.GameTime.Value : "---")}");
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

    public GameStatus()
        : base(1) {}
}

