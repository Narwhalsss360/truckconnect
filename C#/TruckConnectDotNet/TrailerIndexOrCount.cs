namespace TruckConnect
{
    public struct TrailerIndexOrCount : IEquatable<TrailerIndexOrCount>
    {
        public static readonly int SCS_TELEMETRY_trailers_count = 10;

        public bool IsCount;

        public int IndexOrCount;

        public TrailerIndexOrCount()
            : this(true, 0)
        {}

        public TrailerIndexOrCount(bool isCount, int indexOrCount)
        {
            IsCount = isCount;
            IndexOrCount = (byte)indexOrCount;
        }

        public static TrailerIndexOrCount Parse(byte data) =>
            new((1 & data) > 0, data >> 1);

        public byte AsByte() => (byte)(1 | (IndexOrCount << 1));

        public override int GetHashCode() => AsByte();

        public bool Equals(TrailerIndexOrCount other) => IsCount == other.IsCount && IndexOrCount == other.IndexOrCount;

        public override bool Equals(object? obj) =>
            obj is not TrailerIndexOrCount other ? false :
            IsCount == other.IsCount && IndexOrCount == other.IndexOrCount;

        public static bool operator ==(TrailerIndexOrCount a, object? b) => a.Equals(b);

        public static bool operator !=(TrailerIndexOrCount a, object? b) => !a.Equals(b);
    }
}

