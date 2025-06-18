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

        public enum CommunicationResult
        {
            Success,
            GenericSocketError,
            AlreadyConnected,
            NotConnected,
            Disconnected,
            Incomplete,
            CollectorError,
            NoPendingRequest,
            InvalidTelemetry,
            InvalidTrailerIndex,
            OtherRequestPending,
            OtherTelemetryIDPending,
            OtherTrailerIndexRequestPending,
            ReceivedOtherResponse,
            ReceivedOtherTelemetry,
            ReceivedOtherTrailerIndex,
            DeserializationFailure,
            TrailerIndexOutOfBounds,
            TrailerCountOutOfBounds,
            TrailerIndexOrCountWasCount,
            NullArgument,
            Empty,
            AlreadyRegistered,
            OtherDefinedDataPending,
            NotRegistered,
            ArrangeError,
            BadlyFormed,
            UnknownData
        }

        private readonly Socket m_socket;

        private readonly IPAddress m_ipAddress;

        public readonly Collector Collector = new();

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

        public void ClearPendingRequest() => PendingRequest = RequestType.None;

        public async Task SendRequestForAsync(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = null, CancellationToken cancellationToken = default)
        {
            trailerIndexOrCount ??= new();
            EnsureConnected(nameof(SendRequestForAsync));
            EnsurePendingRequest(RequestType.None, "Request already pending.");
            await m_socket.SendAsync(
                NEncode.EncodeWithSize([
                    (byte)RequestType.TelemetryID,
                    (byte)id,
                    trailerIndexOrCount.Value.AsByte()
                ]),
                cancellationToken
            );
            PendingRequest = RequestType.TelemetryID;
            m_pendingID = id;
            m_pendingTrailerIndexOrCount = trailerIndexOrCount.Value;
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
        }

        public async Task ReceiveForRequest(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = null)
        {
            trailerIndexOrCount ??= new();
            EnsureConnected(nameof(ReceiveForRequest));
            EnsurePendingRequest(RequestType.TelemetryID, "There is another pending request.");

            if (Metadata.ByID(id) is not Metadata metadata)
                throw new ArgumentException("TelemetryID was invalid", nameof(id));

            if (trailerIndexOrCount.Value != m_pendingTrailerIndexOrCount)
                throw new InvalidOperationException("Other trailer index/count does is pending.");

            await ReceiveAllAsync();
            ClearPendingRequest();
            if (Collector.Size < 2)
                throw new InvalidDataException("Received unknown data.");

            if ((RequestType)Collector.Data[0] == RequestType.ErrorResponse)
                throw new InvalidDataException("Received error response: {(CommunicationResult)Collector.Data[1]}.");

            if ((RequestType)Collector.Data[0] != RequestType.TelemetryID)
                throw new InvalidDataException("Received unexpected response.");

            if ((TelemetryID)Collector.Data[1] != id)
                throw new InvalidDataException("Received response for another telemetry.");

            if (TrailerIndexOrCount.Parse(Collector.Data[2]) != trailerIndexOrCount)
                throw new InvalidDataException("Received response for another trailer index/count");
        }

        public async Task RequestAsync(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default)
        {
            await SendRequestForAsync(id, trailerIndexOrCount, cancellationToken);
            await ReceiveForRequest(id, trailerIndexOrCount);
        }

        public async Task<T> RequestAsync<T>(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default) where T : struct
        {
            if (Metadata.ByID(id) is not Metadata metadata)
                throw new ArgumentException("ID was invalid", nameof(id));

            if (metadata.TelemetryType != TelemetryType.Channel)
                throw new NotImplementedException("Only channels are implemented");

            await RequestAsync(id, trailerIndexOrCount, cancellationToken);
            T result = default;
            result.StorageFromBytes(metadata.SCSValueType!.Value, Collector.Data, TELEMTRY_DATA_START);
            return result;
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
