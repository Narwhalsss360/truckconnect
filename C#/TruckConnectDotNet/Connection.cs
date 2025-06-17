using System;
using System.Net;
using System.Net.Sockets;
using NStreamCom;

namespace TruckConnect
{
    public class Connection
    {
        public static readonly ushort PORT = 52878;

        public static readonly long RECEIVE_ALL_BUFFER_SIZE = 32;

        public static readonly int TELEMTRY_DATA_START = 1 + 2;

        public static readonly int DATA_DEFINITION_DATA_START = 1 + 1;

        public static readonly int DEFINED_DATA_DATA_START = 1 + 1;

        public enum RequestType
        {
            None,
            TelemetryID,
            RegisterDataDefinition,
            DefinedData,
            UnregisterDataDefinition,
            ErrorResponse
        }

        readonly private Socket m_socket;

        readonly private IPAddress m_ipAddress;

        readonly public Collector Collector = new();

        private TelemetryID m_pendingID = TelemetryID.Invalid;

        private TrailerIndexOrCount m_pendingTrailerIndexOrCount = new();

        public RequestType PendingRequest { get; private set; } = RequestType.None;

        public bool Connected { get => m_socket.Connected; }

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

        public async Task SendRequestForAsync(TelemetryID id, TrailerIndexOrCount trailerIndexOrCount = default, CancellationToken cancellationToken = default)
        {
            EnsureConnected(nameof(SendRequestForAsync));
            EnsurePendingRequest(RequestType.None, "Request already pending.");
            await m_socket.SendAsync(
                NEncode.EncodeWithSize([
                    (byte)RequestType.TelemetryID,
                    (byte)id,
                    trailerIndexOrCount.AsByte()
                ]),
                cancellationToken
            );
            PendingRequest = RequestType.TelemetryID;
            m_pendingID = id;
            m_pendingTrailerIndexOrCount = trailerIndexOrCount;
        }

        public void ReceiveOne()
        {
            EnsureConnected(nameof(ReceiveOne));
            EnsureAnyPendingRequest();
            byte[] buffer = new byte[1];
            m_socket.Receive(buffer);
            Collector.Collect(buffer[0]);
        }

        public async Task ReceiveAllAsync()
        {
            EnsureConnected(nameof(ReceiveOne));
            EnsureAnyPendingRequest();
            do
            {
                byte[] buffer = new byte[1];
                await m_socket.ReceiveAsync(buffer);
                Collector.Collect(buffer[0]);
            } while (Collector.State == Collector.States.WaitingSize || Collector.State == Collector.States.WaitingData);
            PendingRequest = RequestType.None;
        }

        public void Disconnect()
        {
            Collector.Reset();
            m_socket.Close();
        }

        private void EnsureConnected(string operationName)
        {
            if (!Connected)
                throw new InvalidOperationException($"This operation ({operationName}) connection to be connected.");
        }

        private void EnsurePendingRequest(RequestType request, string errorMessage)
        {
            if (PendingRequest != request)
                throw new InvalidOperationException(errorMessage);
        }

        private void EnsureAnyPendingRequest()
        {
            if (PendingRequest == RequestType.None)
                throw new InvalidOperationException("There is no pending request.");
        }
    }
}
