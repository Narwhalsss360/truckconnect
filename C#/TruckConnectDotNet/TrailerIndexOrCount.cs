namespace TruckConnect
{
    public struct TrailerIndexOrCount
    {
        public bool IsCount;

        public int IndexOrCount;

        public TrailerIndexOrCount()
        {
            IsCount = false;
            IndexOrCount = 0;
        }

        public TrailerIndexOrCount(bool isCount, int indexOrCount)
        {
            IsCount = isCount;
            IndexOrCount = (byte)indexOrCount;
        }

        public static TrailerIndexOrCount Parse(byte data)
        {
            TrailerIndexOrCount indexOrCount;
            indexOrCount.IsCount = (1 & (int)data) > 0;
            indexOrCount.IndexOrCount = data >> 1;
            return indexOrCount;
        }

        public byte AsByte()
        {
            return (byte)(1 | (IndexOrCount >> 1));
        }
    }
}

