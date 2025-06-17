using System;
using TruckConnect;

TimeSpan runFor = TimeSpan.FromMinutes(2);

Connection connection = new("127.0.0.1");
connection.Connect();

DateTime start = DateTime.Now;
while (DateTime.Now - start < runFor)
{
    connection.SendRequestForAsync(TelemetryID.ChannelGameTime).Wait();
    connection.ReceiveForRequest(TelemetryID.ChannelGameTime).Wait();

    bool initialzied = connection.Collector.Data[Connection.TELEMTRY_DATA_START] > 0;
    UInt32 gameTime = BitConverter.ToUInt32(connection.Collector.Data, Connection.TELEMTRY_DATA_START + 1);
    Console.WriteLine(initialzied ? gameTime : "---");
}
connection.Disconnect();

