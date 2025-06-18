namespace TruckConnect
{
    public struct TrailerIndexOrCount : IEquatable<TrailerIndexOrCount>
    {
        public const int SCS_TELEMETRY_trailers_count = 10;

        public bool IsCount;

        public int IndexOrCount;

        public TrailerIndexOrCount()
            : this(false, 0)
        {}

        public TrailerIndexOrCount(bool isCount, int indexOrCount)
        {
            IsCount = isCount;
            IndexOrCount = (byte)indexOrCount;
        }

        public static TrailerIndexOrCount Parse(byte data) =>
            new((1 & data) > 0, data >> 1);

        public byte AsByteForTelemetryRequest() => (byte)((IsCount ? 1 : 0) | (IndexOrCount << 1));

        public byte AsByteForDataDefinitionRegistration() => (byte)IndexOrCount;

        public override int GetHashCode() => AsByteForTelemetryRequest();

        public bool Equals(TrailerIndexOrCount other) => IsCount == other.IsCount && IndexOrCount == other.IndexOrCount;

        public override bool Equals(object? obj) =>
            obj is not TrailerIndexOrCount other ? false :
            IsCount == other.IsCount && IndexOrCount == other.IndexOrCount;

        public static bool operator ==(TrailerIndexOrCount a, object? b) => a.Equals(b);

        public static bool operator !=(TrailerIndexOrCount a, object? b) => !a.Equals(b);
    }
}

