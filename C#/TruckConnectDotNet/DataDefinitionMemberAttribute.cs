namespace TruckConnect
{
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]
    public class DataDefinitionMemberAttribute(TelemetryID id, int trailerCount = 0) : Attribute
    {
        public readonly TelemetryID ID = id == TelemetryID.Invalid ? throw new ArgumentException($"{typeof(DataDefinitionMemberAttribute)} ID cannot be invalid.") : id;

        public readonly int TrailerCount = (trailerCount < 0 || trailerCount > 10) ? throw new ArgumentException("Trailer count must be between [0, 10].") : trailerCount;
    }
}

