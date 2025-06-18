using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);

Connection connection = new("127.0.0.1");
connection.Connect();

DataDefinition definition = DataDefinition.Define(
    0,
    [
        new(TelemetryID.ChannelPaused),
        new(TelemetryID.ChannelGameTime),
        new(TelemetryID.ChannelLocalScale)
    ]
);

await connection.RegisterDataDefinitionAsync(definition);

DateTime start = DateTime.Now;
while (DateTime.Now - start < runFor)
{
    await connection.RequestAsync(0);
    object[] boxed = definition.Construct(connection.Collector.Data, Connection.DEFINED_DATA_DATA_START);
    ValueStorage<bool> paused = (ValueStorage<bool>)boxed[0];
    ValueStorage<UInt32> gameTime = (ValueStorage<UInt32>)boxed[1];
    ValueStorage<float> localScale = (ValueStorage<float>)boxed[2];

    if (paused.Value)
    {
        Console.WriteLine(".");
        continue;
    }

    Console.WriteLine($"{(localScale.Initialized ? localScale.Value : "---")} | {(gameTime.Initialized ? gameTime.Value : "---")}");
}
await connection.UnregisterDataDefinitionAsync(definition);
connection.Disconnect();
