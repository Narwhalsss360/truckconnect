using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);
Connection connection = new("127.0.0.1");
connection.Connect();

DateTime start = DateTime.Now;
while (DateTime.Now - start < runFor)
{
    var gameTime = await connection.Request<ValueStorage<UInt32>>(TelemetryID.ChannelGameTime);
    Console.WriteLine(gameTime.Initialized ? gameTime.Value : "---");
}
connection.Disconnect();

