using System.Net;
using System.Net.Sockets;
using NStreamCom;

namespace TruckConnect
{
    public class Connection
    {
        public static readonly ushort PORT = 52878;

        public static readonly long RECEIVE_ALL_BUFFER_SIZE = 32;

        public static readonly int TELEMETRY_DATA_START = 1 + 2;

        public static readonly int DATA_DEFINITION_DATA_START = 1 + 1;

        public static readonly int DEFINED_DATA_DATA_START = 1 + 1;

        public enum RequestType
        {
            None,
            TelemetryID,
            RegisterDataDefinition,
            DefinedData,
            UnregisterDataDefinition,
            Version,
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

        private readonly List<DataDefinition> m_definitions = new();

        public RequestType PendingRequest { get; private set; } = RequestType.None;

        public bool Connected { get => m_socket.Connected; }

        public Connection(string ip = "127.0.0.1")
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
            if (id == TelemetryID.Invalid)
                throw new CommunicationErrorException(CommunicationResult.InvalidTelemetry);

            await m_socket.SendAsync(
                NEncode.EncodeWithSize([
                    (byte)RequestType.TelemetryID,
                    (byte)id,
                    trailerIndexOrCount.Value.AsByteForTelemetryRequest()
                ]),
                cancellationToken
            );
            PendingRequest = RequestType.TelemetryID;
            m_pendingID = id;
            m_pendingTrailerIndexOrCount = trailerIndexOrCount.Value;
        }

        public async Task<Version> GetVersion(CancellationToken cancellationToken = default)
        {
            EnsureConnected(nameof(GetVersion));
            EnsurePendingRequest(RequestType.None, "Request already pending.");
            PendingRequest = RequestType.Version;
            await m_socket.SendAsync(
                NEncode.EncodeWithSize([
                    (byte)RequestType.Version
                ])
            );

            await ReceiveAllAsync(cancellationToken);
            ClearPendingRequest();

            if (Collector.Size == 0)
                throw new CommunicationErrorException(CommunicationResult.UnknownData, new InvalidDataException("Received unknown data."));

            if ((RequestType)Collector.Data[0] == RequestType.ErrorResponse)
                throw new CommunicationErrorException((CommunicationResult)Collector.Data[1]);

            if ((RequestType)Collector.Data[0] != RequestType.Version)
                throw new CommunicationErrorException(CommunicationResult.ReceivedOtherResponse , new InvalidDataException("Received unexpected response."));

            if (Collector.Size != 1 + 4)
                throw new CommunicationErrorException(CommunicationResult.UnknownData, new InvalidDataException("Received unknown data."));

            return new Version(BitConverter.ToUInt32(Collector.Data, 1));
        }


        public async Task ReceiveOne(CancellationToken cancellationToken = default)
        {
            EnsureConnected(nameof(ReceiveOne));
            EnsureAnyPendingRequest();
            byte[] buffer = new byte[1];
            await m_socket.ReceiveAsync(buffer, cancellationToken);
            Collector.Collect(buffer[0]);
        }

        public async Task ReceiveAllAsync(CancellationToken cancellationToken = default)
        {
            EnsureConnected(nameof(ReceiveOne));
            EnsureAnyPendingRequest();
            do
            {
                byte[] buffer = new byte[1];
                await m_socket.ReceiveAsync(buffer, cancellationToken);
                Collector.Collect(buffer[0]);
            } while (Collector.State == Collector.States.WaitingSize || Collector.State == Collector.States.WaitingData);
        }

        public async Task ReceiveForRequest(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = null, CancellationToken cancellationToken = default)
        {
            trailerIndexOrCount ??= new();
            EnsureConnected(nameof(ReceiveForRequest));
            EnsurePendingRequest(RequestType.TelemetryID, "There is another pending request.");

            if (Metadata.ByID(id) is not Metadata metadata)
                throw new ArgumentException("TelemetryID was invalid", nameof(id));

            if (m_pendingID != id)
                throw new CommunicationErrorException(CommunicationResult.OtherTelemetryIDPending);

            if (trailerIndexOrCount.Value != m_pendingTrailerIndexOrCount)
                throw new InvalidOperationException("Other trailer index/count does is pending.");

            await ReceiveAllAsync(cancellationToken);
            ClearPendingRequest();
            m_pendingID = TelemetryID.Invalid;

            if (Collector.Size < 2)
                throw new CommunicationErrorException(CommunicationResult.UnknownData, new InvalidDataException("Received unknown data."));

            if ((RequestType)Collector.Data[0] == RequestType.ErrorResponse)
                throw new CommunicationErrorException((CommunicationResult)Collector.Data[1]);

            if ((RequestType)Collector.Data[0] != RequestType.TelemetryID)
                throw new CommunicationErrorException(CommunicationResult.ReceivedOtherResponse , new InvalidDataException("Received unexpected response."));

            if ((TelemetryID)Collector.Data[1] != id)
                throw new CommunicationErrorException(CommunicationResult.ReceivedOtherTelemetry , new InvalidDataException("Received response for another telemetry."));

            if (TrailerIndexOrCount.Parse(Collector.Data[2]) != trailerIndexOrCount)
                throw new CommunicationErrorException(CommunicationResult.ReceivedOtherTrailerIndex , new InvalidDataException("Received response for another trailer index/count"));
        }

        public async Task RequestAsync(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default)
        {
            await SendRequestForAsync(id, trailerIndexOrCount, cancellationToken);
            await ReceiveForRequest(id, trailerIndexOrCount, cancellationToken);
        }

        public async Task<T> RequestAsync<T>(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default) where T : struct
        {
            trailerIndexOrCount ??= new();
            if (Metadata.ByID(id) is not Metadata metadata)
                throw new ArgumentException("ID was invalid", nameof(id));

            if (trailerIndexOrCount.Value.IsCount)
                throw new ArgumentException($"For a trailer count, use {nameof(RequestArrayAsync)}", nameof(trailerIndexOrCount));

            if (metadata.TelemetryType != TelemetryType.Channel && typeof(T).IDOfStructure() != id)
                throw new ArgumentException("id did not match generic argument type.", nameof(id));

            await RequestAsync(id, trailerIndexOrCount, cancellationToken);
            return
                metadata.TelemetryType == TelemetryType.Channel ?
                    Collector.Data.ConstructStorage<T>(metadata, TELEMETRY_DATA_START) :
                    Collector.Data.ConstructTelemetryStructure<T>(TELEMETRY_DATA_START);
        }

        public async Task<T> RequestAsync<T>(TrailerIndexOrCount? trailerIndexOrCount = null, CancellationToken cancellationToken = default) where T : struct
        {
            TelemetryID id = typeof(T).IDOfStructure();
            if (id == TelemetryID.Invalid)
                throw new ArgumentException("Generic argument was not a telemetry structure.", nameof(T));
            return await RequestAsync<T>(id, trailerIndexOrCount, cancellationToken);
        }

        public async Task<T[]> RequestArrayAsync<T>(TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = default, CancellationToken cancellationToken = default) where T : struct
        {
            trailerIndexOrCount ??= new();
            if (Metadata.ByID(id) is not Metadata metadata)
                throw new ArgumentException("ID was invalid", nameof(id));

            if (!trailerIndexOrCount.Value.IsCount)
                throw new ArgumentException($"For a regular request, use {nameof(RequestAsync)}", nameof(trailerIndexOrCount));

            await RequestAsync(id, trailerIndexOrCount, cancellationToken);
            return
                metadata.TelemetryType == TelemetryType.Channel ?
                    Collector.Data.ConstructStorageArray<T>(trailerIndexOrCount.Value.IndexOrCount, metadata, TELEMETRY_DATA_START) :
                    Collector.Data.ConstructTelemetryStructureArray<T>(trailerIndexOrCount.Value.IndexOrCount, TELEMETRY_DATA_START);
        }

        public DataDefinition? GetDefinition(int definitionID)
            => m_definitions.Find(definition => definition.DefinitionID == definitionID);

        public async Task RegisterDataDefinitionAsync(DataDefinition dataDefinition, CancellationToken cancellationToken = default)
        {
            EnsureConnected(nameof(RegisterDataDefinitionAsync));
            EnsurePendingRequest(RequestType.None, "Request already pending.");
            if (GetDefinition(dataDefinition.DefinitionID) is not null)
                throw new InvalidOperationException("Data definition with same ID already registered");

            await m_socket.SendAsync(dataDefinition.FormRegistrationRequest().EncodeWithSize(), cancellationToken);
            PendingRequest = RequestType.RegisterDataDefinition;
            await ReceiveAllAsync(cancellationToken);
            ClearPendingRequest();

            if (Collector.Size < 2)
                throw new CommunicationErrorException(CommunicationResult.UnknownData , new InvalidDataException("Received unknown data."));

            if ((RequestType)Collector.Data[0] == RequestType.ErrorResponse)
                throw new CommunicationErrorException((CommunicationResult)Collector.Data[1]);

            if ((RequestType)Collector.Data[0] != RequestType.RegisterDataDefinition)
                throw new CommunicationErrorException(CommunicationResult.ReceivedOtherResponse , new InvalidDataException("Received unexpected response."));

            if (Collector.Data[1] != dataDefinition.DefinitionID)
                throw new CommunicationErrorException(CommunicationResult.UnknownData , new InvalidDataException("Received response for another definition."));

            m_definitions.Add(dataDefinition);
        }

        public async Task RequestAsync(int definitionID, CancellationToken cancellationToken = default)
        {
            EnsureConnected(nameof(RequestAsync));
            EnsurePendingRequest(RequestType.None, "Reqest already pending.");
            if (GetDefinition(definitionID) is null)
                throw new InvalidOperationException("Data definition with ID not registered.");

            await m_socket.SendAsync(NEncode.EncodeWithSize([(byte)RequestType.DefinedData, (byte)definitionID]), cancellationToken);
            PendingRequest = RequestType.DefinedData;
            await ReceiveAllAsync(cancellationToken);
            ClearPendingRequest();

            if (Collector.Size < 2)
                throw new CommunicationErrorException(CommunicationResult.UnknownData , new InvalidDataException("Received unknown data."));

            if ((RequestType)Collector.Data[0] == RequestType.ErrorResponse)
                throw new CommunicationErrorException((CommunicationResult)Collector.Data[1]);

            if ((RequestType)Collector.Data[0] != RequestType.DefinedData)
                throw new CommunicationErrorException(CommunicationResult.ReceivedOtherResponse , new InvalidDataException("Received unexpected response."));

            if (Collector.Data[1] != definitionID)
                throw new CommunicationErrorException(CommunicationResult.UnknownData , new InvalidDataException("Received response for another definition."));
        }

        public async Task RequestAsync(DataDefinition definition, CancellationToken cancellationToken = default)
        {
            await RequestAsync(definition.DefinitionID, cancellationToken);
            definition.Store(Collector.Data, DEFINED_DATA_DATA_START);
        }

        public async Task<T> RequestAsync<T>(DataDefinition definition, CancellationToken cancellationToken = default) where T : struct
        {
            await RequestAsync(definition, cancellationToken);
            object boxed = new T();
            definition.StoreInto(Collector.Data, DEFINED_DATA_DATA_START, boxed);
            return (T)boxed;
        }

        public async Task UnregisterDataDefinitionAsync(int definitionID, CancellationToken cancellationToken = default)
        {
            EnsureConnected(nameof(UnregisterDataDefinitionAsync));
            EnsurePendingRequest(RequestType.None, "Request already pending.");
            if (GetDefinition(definitionID) is not DataDefinition dataDefinition)
                throw new InvalidOperationException("Data definition with ID not registered");

            await m_socket.SendAsync(dataDefinition.FormUnregistrationRequest().EncodeWithSize(), default);
            PendingRequest = RequestType.UnregisterDataDefinition;
            await ReceiveAllAsync(cancellationToken);
            ClearPendingRequest();

            if (Collector.Size < 2)
                throw new CommunicationErrorException(CommunicationResult.UnknownData, new InvalidDataException("Received unknown data."));

            if ((RequestType)Collector.Data[0] == RequestType.ErrorResponse)
                throw new CommunicationErrorException((CommunicationResult)Collector.Data[1]);

            if ((RequestType)Collector.Data[0] != RequestType.UnregisterDataDefinition)
                throw new CommunicationErrorException(CommunicationResult.ReceivedOtherResponse, new InvalidDataException("Received unexpected response."));

            if (Collector.Data[1] != dataDefinition.DefinitionID)
                throw new CommunicationErrorException(CommunicationResult.UnknownData, new InvalidDataException("Received response for another definition."));

            m_definitions.Remove(dataDefinition);
        }

        public async Task UnregisterDataDefinitionAsync(DataDefinition definition, CancellationToken cancellationToken = default) =>
            await UnregisterDataDefinitionAsync(definition.DefinitionID, cancellationToken);

        public void Disconnect()
        {
            m_socket.Close();
            Collector.Reset();
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
