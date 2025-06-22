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

    ValueStorage<bool>[] connected = await connection.RequestArrayAsync<ValueStorage<bool>>(TelemetryID.TrailerChannelConnected, new TrailerIndexOrCount(true, 10));

    Console.WriteLine("Trailers Connection Status:");
    for (int i = 0; i < connected.Length; i++)
        if (connected[i].Initialized)
            Console.WriteLine($"Trailer {i + 1}: {(connected[i].Value ? "Connected" : "Not connected")}");
        else
            break;

    var trailerConfigs = await connection.RequestArrayAsync<MasterStorage.ConfigurationStorage.ConfigurationTrailerStorage>(TelemetryID.ConfigurationTrailerInfo, new(true, TrailerIndexOrCount.SCS_TELEMETRY_trailers_count));
    Console.WriteLine("Trailer Names:");
    for (int i = 0; i < connected.Length; i++)
        if (trailerConfigs[i].Id.Initialized)
            Console.WriteLine($"{trailerConfigs[i].Brand.Value} {trailerConfigs[i].Name.Value}");
        else
            break;
    await Task.Delay(1000);
}

connection.Disconnect();
