using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);
Connection connection = new("127.0.0.1");
connection.Connect();

ValueStorage<UInt32> gameTime = new();;
DateTime start = DateTime.Now;
while (DateTime.Now - start < runFor)
{
    connection.SendRequestForAsync(TelemetryID.ChannelGameTime).Wait();
    connection.ReceiveForRequest(TelemetryID.ChannelGameTime).Wait();
    gameTime.StorageFromBytes(connection.Collector.Data, Connection.TELEMTRY_DATA_START);
    Console.WriteLine(gameTime.Initialized ? gameTime.Value : "---");
}
connection.Disconnect();

