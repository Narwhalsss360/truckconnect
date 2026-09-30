using NStreamCom;

namespace TruckConnect
{
    public class ChunkCollector : Collector
    {
        private List<byte> _flatChunks = new();

        private int _readOffset = 0;

        public bool ChunksAvailable
        {
            get => _flatChunks.Count != 0;
        }

        public States DigestChunk()
        {
            if (_readOffset >= _flatChunks.Count)
            {
                _flatChunks.Clear();
                _readOffset = 0;
                return State;
            }

            while (_readOffset < _flatChunks.Count)
            {
                Collect(_flatChunks[_readOffset]);
                _readOffset++;
                if (ErrorState || State == States.Collected)
                    break;
            }

            if (_readOffset >= _flatChunks.Count) {
                _flatChunks.Clear();
                _readOffset = 0;
            }

            return State;
        }

        public States CollectChunk(IEnumerable<byte> bytes)
        {
            if (bytes.Count() == 0)
                return State;

            if (_flatChunks.Count == 0)
                _readOffset = 0;

            _flatChunks.AddRange(bytes);
            return DigestChunk();
        }
    }
}
