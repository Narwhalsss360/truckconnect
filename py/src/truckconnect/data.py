from dataclasses import dataclass, field
from .telemetry_id import TelemetryID


@dataclass
class DataMember:
    id: TelemetryID
    trailer_count: int = field(default=0)

    def to_bytes(self) -> bytearray:
        return bytearray([
            self.id.value,
            0, 0, 0, 0,
            self.trailer_count
        ])


@dataclass
class DataDefinition:
    INVALID_DATA_DEFINITION_ID = 255

    id: int
    members: list[DataMember]

    def to_bytes(self) -> bytearray:
        as_bytes: bytearray = bytearray()
        as_bytes.append(self.id)
        for member in self.members:
            as_bytes.extend(member.to_bytes())
        return as_bytes
