from __future__ import annotations
from dataclasses import dataclass, field
from scssdk_telemetry.scssdk_dataclasses import SCS_TELEMETRY_trailers_count
from truckconnect.value_storage import (
    SCSValueType,
    BufferType,
    value_storage_from_bytes,
    value_array_storage_from_bytes,
    value_vector_storage_from_bytes,
    is_value_storage,
    is_value_array_storage,
    is_value_vector_storage,
    SCSValueFVector,
    SCSValueFPlacement,
    SCSValueDPlacement
)


@dataclass
class GameplayPlayerUseTrainInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    pay_amount: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    source_name: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    target_name: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    source_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    target_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[GameplayPlayerUseTrainInfo, int]:
        gameplay_player_use_train_info: GameplayPlayerUseTrainInfo = GameplayPlayerUseTrainInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_use_train_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s64, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_use_train_info.pay_amount = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_train_info.source_name = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_train_info.target_name = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_train_info.source_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_train_info.target_id = deserialized
        total_read += read

        return gameplay_player_use_train_info, total_read

@dataclass
class GameplayPlayerUseFerryInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    pay_amount: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    source_name: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    target_name: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    source_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    target_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[GameplayPlayerUseFerryInfo, int]:
        gameplay_player_use_ferry_info: GameplayPlayerUseFerryInfo = GameplayPlayerUseFerryInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_use_ferry_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s64, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_use_ferry_info.pay_amount = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_ferry_info.source_name = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_ferry_info.target_name = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_ferry_info.source_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_use_ferry_info.target_id = deserialized
        total_read += read

        return gameplay_player_use_ferry_info, total_read

@dataclass
class GameplayPlayerTollgatePaidInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    pay_amount: tuple[bool, int] = field(default_factory=lambda: (False, int()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[GameplayPlayerTollgatePaidInfo, int]:
        gameplay_player_tollgate_paid_info: GameplayPlayerTollgatePaidInfo = GameplayPlayerTollgatePaidInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_tollgate_paid_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s64, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_tollgate_paid_info.pay_amount = deserialized
        total_read += read

        return gameplay_player_tollgate_paid_info, total_read

@dataclass
class GameplayPlayerFinedInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    fine_offence: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    fine_amount: tuple[bool, int] = field(default_factory=lambda: (False, int()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[GameplayPlayerFinedInfo, int]:
        gameplay_player_fined_info: GameplayPlayerFinedInfo = GameplayPlayerFinedInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_fined_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        gameplay_player_fined_info.fine_offence = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s64, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_player_fined_info.fine_amount = deserialized
        total_read += read

        return gameplay_player_fined_info, total_read

@dataclass
class GameplayJobDeliveredInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    revenue: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    earned_xp: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    cargo_damage: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    distance_km: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    delivery_time: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    auto_park_used: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    auto_load_used: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[GameplayJobDeliveredInfo, int]:
        gameplay_job_delivered_info: GameplayJobDeliveredInfo = GameplayJobDeliveredInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_job_delivered_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s64, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_job_delivered_info.revenue = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_job_delivered_info.earned_xp = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        gameplay_job_delivered_info.cargo_damage = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        gameplay_job_delivered_info.distance_km = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_job_delivered_info.delivery_time = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        gameplay_job_delivered_info.auto_park_used = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        gameplay_job_delivered_info.auto_load_used = deserialized
        total_read += read

        return gameplay_job_delivered_info, total_read

@dataclass
class GameplayJobCancelledInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    cancel_penalty: tuple[bool, int] = field(default_factory=lambda: (False, int()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[GameplayJobCancelledInfo, int]:
        gameplay_job_cancelled_info: GameplayJobCancelledInfo = GameplayJobCancelledInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_job_cancelled_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s64, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        gameplay_job_cancelled_info.cancel_penalty = deserialized
        total_read += read

        return gameplay_job_cancelled_info, total_read

@dataclass
class ConfigurationJobInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    cargo_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    cargo: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    cargo_mass: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    destination_city_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    cargo_unit_mass: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    cargo_unit_count: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    destination_city: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    source_city_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    source_city: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    destination_company_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    destination_company: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    source_company_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    source_company: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    income: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    delivery_time: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    is_cargo_loaded: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    job_market: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    special_job: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    planned_distance_km: tuple[bool, int] = field(default_factory=lambda: (False, int()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[ConfigurationJobInfo, int]:
        configuration_job_info: ConfigurationJobInfo = ConfigurationJobInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_job_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.cargo_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.cargo = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_job_info.cargo_mass = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.destination_city_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_job_info.cargo_unit_mass = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_job_info.cargo_unit_count = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.destination_city = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.source_city_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.source_city = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.destination_company_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.destination_company = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.source_company_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.source_company = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u64, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_job_info.income = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_job_info.delivery_time = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        configuration_job_info.is_cargo_loaded = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_job_info.job_market = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        configuration_job_info.special_job = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_job_info.planned_distance_km = deserialized
        total_read += read

        return configuration_job_info, total_read

@dataclass
class ConfigurationTrailerInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    cargo_accessory_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    hook_position: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    brand_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    brand: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    name: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    chain_type: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    body_type: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    license_plate: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    license_plate_country: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    license_plate_country_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    wheel_count: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    wheel_position: list[SCSValueFVector] = field(default_factory=lambda: [])
    wheel_steerable: list[bool] = field(default_factory=lambda: [])
    wheel_simulated: list[bool] = field(default_factory=lambda: [])
    wheel_radius: list[float] = field(default_factory=lambda: [])
    wheel_powered: list[bool] = field(default_factory=lambda: [])
    wheel_liftable: list[bool] = field(default_factory=lambda: [])

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[ConfigurationTrailerInfo, int]:
        configuration_trailer_info: ConfigurationTrailerInfo = ConfigurationTrailerInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_trailer_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.cargo_accessory_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        configuration_trailer_info.hook_position = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.brand_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.brand = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.name = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.chain_type = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.body_type = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.license_plate = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.license_plate_country = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_trailer_info.license_plate_country_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_trailer_info.wheel_count = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, SCSValueFVector)
        configuration_trailer_info.wheel_position = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_trailer_info.wheel_steerable = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_trailer_info.wheel_simulated = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, float)
        configuration_trailer_info.wheel_radius = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_trailer_info.wheel_powered = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_trailer_info.wheel_liftable = deserialized
        total_read += read

        return configuration_trailer_info, total_read

@dataclass
class ConfigurationTruckInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    brand_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    brand: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    name: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    fuel_capacity: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    fuel_warning_factor: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    adblue_capacity: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    adblue_warning_factor: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    air_pressure_warning: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    air_pressure_emergency: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    oil_pressure_warning: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    water_temperature_warning: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    battery_voltage_warning: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    rpm_limit: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    forward_gear_count: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    reverse_gear_count: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    differential_ratio: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    retarder_step_count: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    cabin_position: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    forward_ratio: list[float] = field(default_factory=lambda: [])
    reverse_ratio: list[float] = field(default_factory=lambda: [])
    head_position: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    hook_position: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    license_plate: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    license_plate_country: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    license_plate_country_id: tuple[bool, str] = field(default_factory=lambda: (False, str()))
    wheel_count: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    wheel_position: list[SCSValueFVector] = field(default_factory=lambda: [])
    wheel_steerable: list[bool] = field(default_factory=lambda: [])
    wheel_simulated: list[bool] = field(default_factory=lambda: [])
    wheel_radius: list[float] = field(default_factory=lambda: [])
    wheel_powered: list[bool] = field(default_factory=lambda: [])
    wheel_liftable: list[bool] = field(default_factory=lambda: [])

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[ConfigurationTruckInfo, int]:
        configuration_truck_info: ConfigurationTruckInfo = ConfigurationTruckInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_truck_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_truck_info.brand_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_truck_info.brand = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_truck_info.id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_truck_info.name = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.fuel_capacity = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.fuel_warning_factor = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.adblue_capacity = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.adblue_warning_factor = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.air_pressure_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.air_pressure_emergency = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.oil_pressure_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.water_temperature_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.battery_voltage_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.rpm_limit = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_truck_info.forward_gear_count = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_truck_info.reverse_gear_count = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        configuration_truck_info.differential_ratio = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_truck_info.retarder_step_count = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        configuration_truck_info.cabin_position = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, float)
        configuration_truck_info.forward_ratio = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, float)
        configuration_truck_info.reverse_ratio = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        configuration_truck_info.head_position = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        configuration_truck_info.hook_position = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_truck_info.license_plate = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_truck_info.license_plate_country = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_truck_info.license_plate_country_id = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_truck_info.wheel_count = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, SCSValueFVector)
        configuration_truck_info.wheel_position = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_truck_info.wheel_steerable = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_truck_info.wheel_simulated = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, float)
        configuration_truck_info.wheel_radius = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_truck_info.wheel_powered = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, bool)
        configuration_truck_info.wheel_liftable = deserialized
        total_read += read

        return configuration_truck_info, total_read

@dataclass
class ConfigurationHshifterInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    selector_count: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    slot_gear: list[int] = field(default_factory=lambda: [])
    slot_handle_position: list[int] = field(default_factory=lambda: [])
    slot_selectors: list[int] = field(default_factory=lambda: [])

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[ConfigurationHshifterInfo, int]:
        configuration_hshifter_info: ConfigurationHshifterInfo = ConfigurationHshifterInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_hshifter_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_hshifter_info.selector_count = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s32, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, int)
        configuration_hshifter_info.slot_gear = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, int)
        configuration_hshifter_info.slot_handle_position = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, int)
        configuration_hshifter_info.slot_selectors = deserialized
        total_read += read

        return configuration_hshifter_info, total_read

@dataclass
class ConfigurationControlsInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    shifter_type: tuple[bool, str] = field(default_factory=lambda: (False, str()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[ConfigurationControlsInfo, int]:
        configuration_controls_info: ConfigurationControlsInfo = ConfigurationControlsInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_controls_info.latest = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_storage(deserialized, str)
        configuration_controls_info.shifter_type = deserialized
        total_read += read

        return configuration_controls_info, total_read

@dataclass
class ConfigurationSubstancesInfo:
    latest: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    id: list[str] = field(default_factory=lambda: [])

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[ConfigurationSubstancesInfo, int]:
        configuration_substances_info: ConfigurationSubstancesInfo = ConfigurationSubstancesInfo()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        configuration_substances_info.latest = deserialized
        total_read += read

        deserialized, read = value_vector_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_string, buffer, offset + total_read)
        assert is_value_vector_storage(deserialized, str)
        configuration_substances_info.id = deserialized
        total_read += read

        return configuration_substances_info, total_read

@dataclass
class Trailer:
    trailer_channel_connected: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    trailer_channel_cargo_damage: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    trailer_channel_world_placement: tuple[bool, SCSValueDPlacement] = field(default_factory=lambda: (False, SCSValueDPlacement()))
    trailer_channel_local_linear_velocity: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    trailer_channel_local_angular_velocity: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    trailer_channel_local_linear_acceleration: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    trailer_channel_local_angular_acceleration: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    trailer_channel_wear_body: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    trailer_channel_wear_chassis: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    trailer_channel_wear_wheels: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    trailer_channel_wheel_susp_deflection: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(19)], 0))
    trailer_channel_wheel_on_ground: tuple[bool, list[bool], int] = field(default_factory=lambda: (False, [bool() for _ in range(19)], 0))
    trailer_channel_wheel_substance: tuple[bool, list[int], int] = field(default_factory=lambda: (False, [int() for _ in range(19)], 0))
    trailer_channel_wheel_velocity: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(19)], 0))
    trailer_channel_wheel_steering: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(19)], 0))
    trailer_channel_wheel_rotation: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(19)], 0))
    trailer_channel_wheel_lift: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(19)], 0))
    trailer_channel_wheel_lift_offset: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(19)], 0))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[Trailer, int]:
        trailer: Trailer = Trailer()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        trailer.trailer_channel_connected = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        trailer.trailer_channel_cargo_damage = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_dplacement, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueDPlacement)
        trailer.trailer_channel_world_placement = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        trailer.trailer_channel_local_linear_velocity = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        trailer.trailer_channel_local_angular_velocity = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        trailer.trailer_channel_local_linear_acceleration = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        trailer.trailer_channel_local_angular_acceleration = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        trailer.trailer_channel_wear_body = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        trailer.trailer_channel_wear_chassis = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        trailer.trailer_channel_wear_wheels = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        trailer.trailer_channel_wheel_susp_deflection = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, bool)
        trailer.trailer_channel_wheel_on_ground = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, int)
        trailer.trailer_channel_wheel_substance = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        trailer.trailer_channel_wheel_velocity = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        trailer.trailer_channel_wheel_steering = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        trailer.trailer_channel_wheel_rotation = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        trailer.trailer_channel_wheel_lift = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 19, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        trailer.trailer_channel_wheel_lift_offset = deserialized
        total_read += read

        return trailer, total_read

@dataclass
class Truck:
    truck_channel_world_placement: tuple[bool, SCSValueDPlacement] = field(default_factory=lambda: (False, SCSValueDPlacement()))
    truck_channel_local_linear_velocity: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    truck_channel_local_angular_velocity: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    truck_channel_local_linear_acceleration: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    truck_channel_local_angular_acceleration: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    truck_channel_cabin_offset: tuple[bool, SCSValueFPlacement] = field(default_factory=lambda: (False, SCSValueFPlacement()))
    truck_channel_cabin_angular_velocity: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    truck_channel_cabin_angular_acceleration: tuple[bool, SCSValueFVector] = field(default_factory=lambda: (False, SCSValueFVector()))
    truck_channel_head_offset: tuple[bool, SCSValueFPlacement] = field(default_factory=lambda: (False, SCSValueFPlacement()))
    truck_channel_speed: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_engine_rpm: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_engine_gear: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    truck_channel_displayed_gear: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    truck_channel_input_steering: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_input_throttle: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_input_brake: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_input_clutch: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_effective_steering: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_effective_throttle: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_effective_brake: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_effective_clutch: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_cruise_control: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_hshifter_slot: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    truck_channel_hshifter_selector: tuple[bool, list[bool], int] = field(default_factory=lambda: (False, [bool() for _ in range(2)], 0))
    truck_channel_parking_brake: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_motor_brake: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_retarder_level: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    truck_channel_brake_air_pressure: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_brake_air_pressure_warning: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_brake_air_pressure_emergency: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_brake_temperature: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_fuel: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_fuel_warning: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_fuel_average_consumption: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_fuel_range: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_adblue: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_adblue_warning: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_oil_pressure: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_oil_pressure_warning: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_oil_temperature: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_water_temperature: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_water_temperature_warning: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_battery_voltage: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_battery_voltage_warning: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_electric_enabled: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_engine_enabled: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_lblinker: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_rblinker: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_hazard_warning: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_lblinker: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_rblinker: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_parking: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_low_beam: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_high_beam: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_aux_front: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    truck_channel_light_aux_roof: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    truck_channel_light_beacon: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_brake: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_light_reverse: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_wipers: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_dashboard_backlight: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_differential_lock: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_lift_axle: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_lift_axle_indicator: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_trailer_lift_axle: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_trailer_lift_axle_indicator: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    truck_channel_wear_engine: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_wear_transmission: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_wear_cabin: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_wear_chassis: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_wear_wheels: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_odometer: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_navigation_distance: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_navigation_time: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_navigation_speed_limit: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    truck_channel_wheel_susp_deflection: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(14)], 0))
    truck_channel_wheel_on_ground: tuple[bool, list[bool], int] = field(default_factory=lambda: (False, [bool() for _ in range(14)], 0))
    truck_channel_wheel_substance: tuple[bool, list[int], int] = field(default_factory=lambda: (False, [int() for _ in range(14)], 0))
    truck_channel_wheel_velocity: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(14)], 0))
    truck_channel_wheel_steering: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(14)], 0))
    truck_channel_wheel_rotation: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(14)], 0))
    truck_channel_wheel_lift: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(14)], 0))
    truck_channel_wheel_lift_offset: tuple[bool, list[float], int] = field(default_factory=lambda: (False, [float() for _ in range(14)], 0))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[Truck, int]:
        truck: Truck = Truck()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_dplacement, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueDPlacement)
        truck.truck_channel_world_placement = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        truck.truck_channel_local_linear_velocity = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        truck.truck_channel_local_angular_velocity = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        truck.truck_channel_local_linear_acceleration = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        truck.truck_channel_local_angular_acceleration = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fplacement, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFPlacement)
        truck.truck_channel_cabin_offset = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        truck.truck_channel_cabin_angular_velocity = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fvector, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFVector)
        truck.truck_channel_cabin_angular_acceleration = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_fplacement, buffer, offset + total_read)
        assert is_value_storage(deserialized, SCSValueFPlacement)
        truck.truck_channel_head_offset = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_speed = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_engine_rpm = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        truck.truck_channel_engine_gear = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        truck.truck_channel_displayed_gear = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_input_steering = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_input_throttle = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_input_brake = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_input_clutch = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_effective_steering = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_effective_throttle = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_effective_brake = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_effective_clutch = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_cruise_control = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        truck.truck_channel_hshifter_slot = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, 2, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, bool)
        truck.truck_channel_hshifter_selector = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_parking_brake = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_motor_brake = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        truck.truck_channel_retarder_level = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_brake_air_pressure = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_brake_air_pressure_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_brake_air_pressure_emergency = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_brake_temperature = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_fuel = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_fuel_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_fuel_average_consumption = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_fuel_range = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_adblue = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_adblue_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_oil_pressure = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_oil_pressure_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_oil_temperature = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_water_temperature = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_water_temperature_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_battery_voltage = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_battery_voltage_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_electric_enabled = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_engine_enabled = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_lblinker = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_rblinker = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_hazard_warning = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_lblinker = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_rblinker = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_parking = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_low_beam = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_high_beam = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        truck.truck_channel_light_aux_front = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        truck.truck_channel_light_aux_roof = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_beacon = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_brake = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_light_reverse = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_wipers = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_dashboard_backlight = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_differential_lock = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_lift_axle = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_lift_axle_indicator = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_trailer_lift_axle = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        truck.truck_channel_trailer_lift_axle_indicator = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_wear_engine = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_wear_transmission = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_wear_cabin = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_wear_chassis = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_wear_wheels = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_odometer = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_navigation_distance = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_navigation_time = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        truck.truck_channel_navigation_speed_limit = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        truck.truck_channel_wheel_susp_deflection = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, bool)
        truck.truck_channel_wheel_on_ground = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, int)
        truck.truck_channel_wheel_substance = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        truck.truck_channel_wheel_velocity = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        truck.truck_channel_wheel_steering = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        truck.truck_channel_wheel_rotation = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        truck.truck_channel_wheel_lift = deserialized
        total_read += read

        deserialized, read = value_array_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, 14, buffer, offset + total_read)
        assert is_value_array_storage(deserialized, float)
        truck.truck_channel_wheel_lift_offset = deserialized
        total_read += read

        return truck, total_read

@dataclass
class General:
    channel_paused: tuple[bool, bool] = field(default_factory=lambda: (False, bool()))
    channel_local_scale: tuple[bool, float] = field(default_factory=lambda: (False, float()))
    channel_game_time: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    channel_multiplayer_time_offset: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    channel_next_rest_stop: tuple[bool, int] = field(default_factory=lambda: (False, int()))
    job_channel_cargo_damage: tuple[bool, float] = field(default_factory=lambda: (False, float()))

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[General, int]:
        general: General = General()
        total_read: int = 0
        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_bool, buffer, offset + total_read)
        assert is_value_storage(deserialized, bool)
        general.channel_paused = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        general.channel_local_scale = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_u32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        general.channel_game_time = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        general.channel_multiplayer_time_offset = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_s32, buffer, offset + total_read)
        assert is_value_storage(deserialized, int)
        general.channel_next_rest_stop = deserialized
        total_read += read

        deserialized, read = value_storage_from_bytes(SCSValueType.SCS_VALUE_TYPE_float, buffer, offset + total_read)
        assert is_value_storage(deserialized, float)
        general.job_channel_cargo_damage = deserialized
        total_read += read

        return general, total_read

@dataclass
class Channels:
    general: General = field(default_factory=General)
    truck: Truck = field(default_factory=Truck)
    trailer: list[Trailer] = field(default_factory=lambda: [Trailer() for _ in range(SCS_TELEMETRY_trailers_count)])

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[Channels, int]:
        channels: Channels = Channels()
        total_read: int = 0
        deserialized, read = General.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, General)
        channels.general = deserialized
        total_read += read

        deserialized, read = Truck.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, Truck)
        channels.truck = deserialized
        total_read += read

        for _ in range(SCS_TELEMETRY_trailers_count):
            deserialized, read = Trailer.from_bytes(buffer, offset + total_read)
            channels.trailer.append(deserialized)
            total_read += read

        return channels, total_read

@dataclass
class Gameplay:
    gameplay_job_cancelled_info: GameplayJobCancelledInfo = field(default_factory=GameplayJobCancelledInfo)
    gameplay_job_delivered_info: GameplayJobDeliveredInfo = field(default_factory=GameplayJobDeliveredInfo)
    gameplay_player_fined_info: GameplayPlayerFinedInfo = field(default_factory=GameplayPlayerFinedInfo)
    gameplay_player_tollgate_paid_info: GameplayPlayerTollgatePaidInfo = field(default_factory=GameplayPlayerTollgatePaidInfo)
    gameplay_player_use_ferry_info: GameplayPlayerUseFerryInfo = field(default_factory=GameplayPlayerUseFerryInfo)
    gameplay_player_use_train_info: GameplayPlayerUseTrainInfo = field(default_factory=GameplayPlayerUseTrainInfo)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[Gameplay, int]:
        gameplay: Gameplay = Gameplay()
        total_read: int = 0
        deserialized, read = GameplayJobCancelledInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, GameplayJobCancelledInfo)
        gameplay.gameplay_job_cancelled_info = deserialized
        total_read += read

        deserialized, read = GameplayJobDeliveredInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, GameplayJobDeliveredInfo)
        gameplay.gameplay_job_delivered_info = deserialized
        total_read += read

        deserialized, read = GameplayPlayerFinedInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, GameplayPlayerFinedInfo)
        gameplay.gameplay_player_fined_info = deserialized
        total_read += read

        deserialized, read = GameplayPlayerTollgatePaidInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, GameplayPlayerTollgatePaidInfo)
        gameplay.gameplay_player_tollgate_paid_info = deserialized
        total_read += read

        deserialized, read = GameplayPlayerUseFerryInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, GameplayPlayerUseFerryInfo)
        gameplay.gameplay_player_use_ferry_info = deserialized
        total_read += read

        deserialized, read = GameplayPlayerUseTrainInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, GameplayPlayerUseTrainInfo)
        gameplay.gameplay_player_use_train_info = deserialized
        total_read += read

        return gameplay, total_read

@dataclass
class Configuration:
    configuration_substances_info: ConfigurationSubstancesInfo = field(default_factory=ConfigurationSubstancesInfo)
    configuration_controls_info: ConfigurationControlsInfo = field(default_factory=ConfigurationControlsInfo)
    configuration_hshifter_info: ConfigurationHshifterInfo = field(default_factory=ConfigurationHshifterInfo)
    configuration_truck_info: ConfigurationTruckInfo = field(default_factory=ConfigurationTruckInfo)
    configuration_trailer_info: list[ConfigurationTrailerInfo] = field(default_factory=lambda: [ConfigurationTrailerInfo() for _ in range(SCS_TELEMETRY_trailers_count)])
    configuration_job_info: ConfigurationJobInfo = field(default_factory=ConfigurationJobInfo)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[Configuration, int]:
        configuration: Configuration = Configuration()
        total_read: int = 0
        deserialized, read = ConfigurationSubstancesInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, ConfigurationSubstancesInfo)
        configuration.configuration_substances_info = deserialized
        total_read += read

        deserialized, read = ConfigurationControlsInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, ConfigurationControlsInfo)
        configuration.configuration_controls_info = deserialized
        total_read += read

        deserialized, read = ConfigurationHshifterInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, ConfigurationHshifterInfo)
        configuration.configuration_hshifter_info = deserialized
        total_read += read

        deserialized, read = ConfigurationTruckInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, ConfigurationTruckInfo)
        configuration.configuration_truck_info = deserialized
        total_read += read

        for _ in range(SCS_TELEMETRY_trailers_count):
            deserialized, read = ConfigurationTrailerInfo.from_bytes(buffer, offset + total_read)
            configuration.configuration_trailer_info.append(deserialized)
            total_read += read

        deserialized, read = ConfigurationJobInfo.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, ConfigurationJobInfo)
        configuration.configuration_job_info = deserialized
        total_read += read

        return configuration, total_read

@dataclass
class Master:
    configuration: Configuration = field(default_factory=Configuration)
    gameplay: Gameplay = field(default_factory=Gameplay)
    channels: Channels = field(default_factory=Channels)

    @staticmethod
    def from_bytes(buffer: BufferType, offset: int = 0) -> tuple[Master, int]:
        master: Master = Master()
        total_read: int = 0
        deserialized, read = Configuration.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, Configuration)
        master.configuration = deserialized
        total_read += read

        deserialized, read = Gameplay.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, Gameplay)
        master.gameplay = deserialized
        total_read += read

        deserialized, read = Channels.from_bytes(buffer, offset + total_read)
        assert isinstance(deserialized, Channels)
        master.channels = deserialized
        total_read += read

        return master, total_read
