using System.Net;
using System.Net.Sockets;
using NStreamCom;

namespace TruckConnect
{
    public class Connection
    {
        public static readonly ushort PORT = 52878;

        readonly private Socket m_socket;

        readonly private IPAddress m_ipAddress;

        readonly private Collector m_collector = new();

        public Connection(string ip)
        {
            m_socket = new(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            m_ipAddress = IPAddress.Parse(ip);
        }

        public async Task ConnectAsync(CancellationToken cancellationToken = default)
        {
            await m_socket.ConnectAsync(m_ipAddress, PORT, cancellationToken);
        }

        public void Connect()
        {
            ConnectAsync().Wait();
        }

        public void Disconnect()
        {
            m_socket.Close();
        }
    }
}
