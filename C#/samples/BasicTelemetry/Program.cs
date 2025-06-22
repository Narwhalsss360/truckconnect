using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(5);

Connection connection = new();
await connection.ConnectAsync();

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

