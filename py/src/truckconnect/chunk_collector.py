from nstreamcom import Collector, CollectorStates


class ChunkCollector(Collector):
    def __init__(self) -> None:
        super().__init__()
        self._flat_chunks: bytearray = bytearray()
        self._read_offset: int = 0

    @property
    def chunks_available(self) -> bool:
        return len(self._flat_chunks) > 0

    def digest_chunk(self) -> CollectorStates:
        if self._read_offset >= len(self._flat_chunks):
            self._flat_chunks.clear()
            self._read_offset = 0
            return self.state

        while self._read_offset < len(self._flat_chunks):
            self. collect(self._flat_chunks[self._read_offset])
            self._read_offset += 1
            if self.error_state or self.state == CollectorStates.Collected:
                break

        if self._read_offset >= len(self._flat_chunks):
            self._flat_chunks.clear()
            self._read_offset = 0

        return self.state

    def collect_chunk(self, bytes: bytearray) -> CollectorStates:
        if len(bytes) == 0:
            return self.state

        if len(self._flat_chunks) == 0:
            self._read_offset = 0

        self._flat_chunks.extend(bytes)
        return self.digest_chunk()
