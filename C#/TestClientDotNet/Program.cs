using TruckConnect;

Connection connection = new("127.0.0.1");
connection.Connect();
while (true)
{
    connection.SendRequestForAsync(TelemetryID.ChannelGameTime).Wait();
    connection.ReceiveAllAsync().Wait();
    bool initialzied = connection.Collector.Data[Connection.TELEMTRY_DATA_START] > 0;
    UInt32 gameTime = BitConverter.ToUInt32(connection.Collector.Data, Connection.TELEMTRY_DATA_START + 1);

    Console.WriteLine(initialzied ? gameTime : "---");
}
connection.Disconnect();

