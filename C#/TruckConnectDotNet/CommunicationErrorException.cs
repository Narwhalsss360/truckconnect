namespace TruckConnect
{
    public class CommunicationErrorException(Connection.CommunicationResult communicationResult, Exception? inner = null)
        : Exception($"Error communication result: {communicationResult}.", inner)
    {
        public readonly Connection.CommunicationResult CommunicationResult = communicationResult;
    }
}
