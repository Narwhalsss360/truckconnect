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

        private readonly List<DataDefinition> m_definitions = new();

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
                    trailerIndexOrCount.Value.AsByteForTelemetryRequest()
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
            await ReceiveForRequest(id, trailerIndexOrCount);
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
                    Collector.Data.ConstructStorage<T>(metadata, TELEMTRY_DATA_START) :
                    Collector.Data.ConstructTelemetryStructure<T>(TELEMTRY_DATA_START);
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

            if (metadata.TelemetryType != TelemetryType.Channel)
                throw new NotImplementedException("Multiple structures are not currently implemented by the server.");

            await RequestAsync(id, trailerIndexOrCount, cancellationToken);
            return
                metadata.TelemetryType == TelemetryType.Channel ?
                    Collector.Data.ConstructStorageArray<T>(trailerIndexOrCount.Value.IndexOrCount, metadata, TELEMTRY_DATA_START) :
                    Collector.Data.ConstructTelemetryStructureArray<T>(trailerIndexOrCount.Value.IndexOrCount, TELEMTRY_DATA_START);
        }

        public DataDefinition? GetDefinition(int definitionID)
            => m_definitions.Find(definition => definition.DefinitionID == definitionID);

        public async Task RegisterDataDefinitionAsync(DataDefinition dataDefinition)
        {
            EnsureConnected(nameof(RegisterDataDefinitionAsync));
            EnsurePendingRequest(RequestType.None, "Request already pending.");
            if (GetDefinition(dataDefinition.DefinitionID) is not null)
                throw new InvalidOperationException("Data definition with same ID already registered");

            await m_socket.SendAsync(dataDefinition.FormRegistrationRequest().EncodeWithSize());
            PendingRequest = RequestType.RegisterDataDefinition;
            await ReceiveAllAsync();
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

        public async Task RequestAsync(int definitionID)
        {
            EnsureConnected(nameof(RequestAsync));
            EnsurePendingRequest(RequestType.None, "Reqest already pending.");
            if (GetDefinition(definitionID) is null)
                throw new InvalidOperationException("Data definition with ID not registered.");

            await m_socket.SendAsync(NEncode.EncodeWithSize([(byte)RequestType.DefinedData, (byte)definitionID]));
            PendingRequest = RequestType.DefinedData;
            await ReceiveAllAsync();
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

        public async Task RequestAsync(DataDefinition definition)
        {
            await RequestAsync(definition.DefinitionID);
            definition.Store(Collector.Data, DEFINED_DATA_DATA_START);
        }

        public async Task<T> RequestAsync<T>(DataDefinition definition) where T : struct
        {
            await RequestAsync(definition);
            object boxed = new T();
            definition.StoreInto(Collector.Data, DEFINED_DATA_DATA_START, boxed);
            return (T)boxed;
        }

        public async Task UnregisterDataDefinitionAsync(int definitionID)
        {
            EnsureConnected(nameof(UnregisterDataDefinitionAsync));
            EnsurePendingRequest(RequestType.None, "Request already pending.");
            if (GetDefinition(definitionID) is not DataDefinition dataDefinition)
                throw new InvalidOperationException("Data definition with ID not registered");

            await m_socket.SendAsync(dataDefinition.FormUnregistrationRequest().EncodeWithSize());
            PendingRequest = RequestType.UnregisterDataDefinition;
            await ReceiveAllAsync();
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

        public async Task UnregisterDataDefinitionAsync(DataDefinition definition) =>
            await UnregisterDataDefinitionAsync(definition.DefinitionID);

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
