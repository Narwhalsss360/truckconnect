using System.Reflection;

namespace TruckConnect
{
	public struct MasterStorage()
	{
		public ConfigurationStorage Configuration = new();
		public struct ConfigurationStorage()
		{
			public ConfigurationSubstancesStorage ConfigurationSubstancesInfo = new();
			public struct ConfigurationSubstancesStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueListStorage<String> Id = new();
			}

			public ConfigurationControlsStorage ConfigurationControlsInfo = new();
			public struct ConfigurationControlsStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<String> ShifterType = new();
			}

			public ConfigurationHshifterStorage ConfigurationHshifterInfo = new();
			public struct ConfigurationHshifterStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<UInt32> SelectorCount = new();

				public ValueListStorage<Int32> SlotGear = new();

				public ValueListStorage<UInt32> SlotHandlePosition = new();

				public ValueListStorage<UInt32> SlotSelectors = new();
			}

			public ConfigurationTruckStorage ConfigurationTruckInfo = new();
			public struct ConfigurationTruckStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<String> BrandId = new();

				public ValueStorage<String> Brand = new();

				public ValueStorage<String> Id = new();

				public ValueStorage<String> Name = new();

				public ValueStorage<Single> FuelCapacity = new();

				public ValueStorage<Single> FuelWarningFactor = new();

				public ValueStorage<Single> AdblueCapacity = new();

				public ValueStorage<Single> AdblueWarningFactor = new();

				public ValueStorage<Single> AirPressureWarning = new();

				public ValueStorage<Single> AirPressureEmergency = new();

				public ValueStorage<Single> OilPressureWarning = new();

				public ValueStorage<Single> WaterTemperatureWarning = new();

				public ValueStorage<Single> BatteryVoltageWarning = new();

				public ValueStorage<Single> RpmLimit = new();

				public ValueStorage<UInt32> ForwardGearCount = new();

				public ValueStorage<UInt32> ReverseGearCount = new();

				public ValueStorage<Single> DifferentialRatio = new();

				public ValueStorage<UInt32> RetarderStepCount = new();

				public ValueStorage<SCSValueFVector> CabinPosition = new();

				public ValueListStorage<Single> ForwardRatio = new();

				public ValueListStorage<Single> ReverseRatio = new();

				public ValueStorage<SCSValueFVector> HeadPosition = new();

				public ValueStorage<SCSValueFVector> HookPosition = new();

				public ValueStorage<String> LicensePlate = new();

				public ValueStorage<String> LicensePlateCountry = new();

				public ValueStorage<String> LicensePlateCountryId = new();

				public ValueStorage<UInt32> WheelCount = new();

				public ValueListStorage<SCSValueFVector> WheelPosition = new();

				public ValueListStorage<Boolean> WheelSteerable = new();

				public ValueListStorage<Boolean> WheelSimulated = new();

				public ValueListStorage<Single> WheelRadius = new();

				public ValueListStorage<Boolean> WheelPowered = new();

				public ValueListStorage<Boolean> WheelLiftable = new();
			}

			public ConfigurationTrailerStorage[] ConfigurationTrailerInfo = new ConfigurationTrailerStorage[10];
			public struct ConfigurationTrailerStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<String> Id = new();

				public ValueStorage<String> CargoAccessoryId = new();

				public ValueStorage<SCSValueFVector> HookPosition = new();

				public ValueStorage<String> BrandId = new();

				public ValueStorage<String> Brand = new();

				public ValueStorage<String> Name = new();

				public ValueStorage<String> ChainType = new();

				public ValueStorage<String> BodyType = new();

				public ValueStorage<String> LicensePlate = new();

				public ValueStorage<String> LicensePlateCountry = new();

				public ValueStorage<String> LicensePlateCountryId = new();

				public ValueStorage<UInt32> WheelCount = new();

				public ValueListStorage<SCSValueFVector> WheelPosition = new();

				public ValueListStorage<Boolean> WheelSteerable = new();

				public ValueListStorage<Boolean> WheelSimulated = new();

				public ValueListStorage<Single> WheelRadius = new();

				public ValueListStorage<Boolean> WheelPowered = new();

				public ValueListStorage<Boolean> WheelLiftable = new();
			}

			public ConfigurationJobStorage ConfigurationJobInfo = new();
			public struct ConfigurationJobStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<String> CargoId = new();

				public ValueStorage<String> Cargo = new();

				public ValueStorage<Single> CargoMass = new();

				public ValueStorage<String> DestinationCityId = new();

				public ValueStorage<Single> CargoUnitMass = new();

				public ValueStorage<UInt32> CargoUnitCount = new();

				public ValueStorage<String> DestinationCity = new();

				public ValueStorage<String> SourceCityId = new();

				public ValueStorage<String> SourceCity = new();

				public ValueStorage<String> DestinationCompanyId = new();

				public ValueStorage<String> DestinationCompany = new();

				public ValueStorage<String> SourceCompanyId = new();

				public ValueStorage<String> SourceCompany = new();

				public ValueStorage<UInt64> Income = new();

				public ValueStorage<UInt32> DeliveryTime = new();

				public ValueStorage<Boolean> IsCargoLoaded = new();

				public ValueStorage<String> JobMarket = new();

				public ValueStorage<Boolean> SpecialJob = new();

				public ValueStorage<UInt32> PlannedDistanceKm = new();
			}
		}

		public GameplayStorage Gameplay = new();
		public struct GameplayStorage()
		{
			public GameplayJobCancelledStorage GameplayJobCancelledInfo = new();
			public struct GameplayJobCancelledStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<Int64> CancelPenalty = new();
			}

			public GameplayJobDeliveredStorage GameplayJobDeliveredInfo = new();
			public struct GameplayJobDeliveredStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<Int64> Revenue = new();

				public ValueStorage<Int32> EarnedXp = new();

				public ValueStorage<Single> CargoDamage = new();

				public ValueStorage<Single> DistanceKm = new();

				public ValueStorage<UInt32> DeliveryTime = new();

				public ValueStorage<Boolean> AutoParkUsed = new();

				public ValueStorage<Boolean> AutoLoadUsed = new();
			}

			public GameplayPlayerFinedStorage GameplayPlayerFinedInfo = new();
			public struct GameplayPlayerFinedStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<String> FineOffence = new();

				public ValueStorage<Int64> FineAmount = new();
			}

			public GameplayPlayerTollgatePaidStorage GameplayPlayerTollgatePaidInfo = new();
			public struct GameplayPlayerTollgatePaidStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<Int64> PayAmount = new();
			}

			public GameplayPlayerUseFerryStorage GameplayPlayerUseFerryInfo = new();
			public struct GameplayPlayerUseFerryStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<Int64> PayAmount = new();

				public ValueStorage<String> SourceName = new();

				public ValueStorage<String> TargetName = new();

				public ValueStorage<String> SourceId = new();

				public ValueStorage<String> TargetId = new();
			}

			public GameplayPlayerUseTrainStorage GameplayPlayerUseTrainInfo = new();
			public struct GameplayPlayerUseTrainStorage()
			{
				public ValueStorage<UInt32> Latest = new();

				public ValueStorage<Int64> PayAmount = new();

				public ValueStorage<String> SourceName = new();

				public ValueStorage<String> TargetName = new();

				public ValueStorage<String> SourceId = new();

				public ValueStorage<String> TargetId = new();
			}
		}

		public ChannelsStorage Channels = new();
		public struct ChannelsStorage()
		{
			public GeneralStorage General = new();
			public struct GeneralStorage()
			{
				public ValueStorage<Boolean> ChannelPaused = new();

				public ValueStorage<Single> ChannelLocalScale = new();

				public ValueStorage<UInt32> ChannelGameTime = new();

				public ValueStorage<Int32> ChannelMultiplayerTimeOffset = new();

				public ValueStorage<Int32> ChannelNextRestStop = new();

				public ValueStorage<Single> JobChannelCargoDamage = new();
			}

			public TruckStorage Truck = new();
			public struct TruckStorage()
			{
				public ValueStorage<SCSValueDPlacement> TruckChannelWorldPlacement = new();

				public ValueStorage<SCSValueFVector> TruckChannelLocalLinearVelocity = new();

				public ValueStorage<SCSValueFVector> TruckChannelLocalAngularVelocity = new();

				public ValueStorage<SCSValueFVector> TruckChannelLocalLinearAcceleration = new();

				public ValueStorage<SCSValueFVector> TruckChannelLocalAngularAcceleration = new();

				public ValueStorage<SCSValueFPlacement> TruckChannelCabinOffset = new();

				public ValueStorage<SCSValueFVector> TruckChannelCabinAngularVelocity = new();

				public ValueStorage<SCSValueFVector> TruckChannelCabinAngularAcceleration = new();

				public ValueStorage<SCSValueFPlacement> TruckChannelHeadOffset = new();

				public ValueStorage<Single> TruckChannelSpeed = new();

				public ValueStorage<Single> TruckChannelEngineRpm = new();

				public ValueStorage<Int32> TruckChannelEngineGear = new();

				public ValueStorage<Int32> TruckChannelDisplayedGear = new();

				public ValueStorage<Single> TruckChannelInputSteering = new();

				public ValueStorage<Single> TruckChannelInputThrottle = new();

				public ValueStorage<Single> TruckChannelInputBrake = new();

				public ValueStorage<Single> TruckChannelInputClutch = new();

				public ValueStorage<Single> TruckChannelEffectiveSteering = new();

				public ValueStorage<Single> TruckChannelEffectiveThrottle = new();

				public ValueStorage<Single> TruckChannelEffectiveBrake = new();

				public ValueStorage<Single> TruckChannelEffectiveClutch = new();

				public ValueStorage<Single> TruckChannelCruiseControl = new();

				public ValueStorage<UInt32> TruckChannelHshifterSlot = new();

				[StaticSize(2)]
				public ValueArrayStorage<Boolean> TruckChannelHshifterSelector = new(2);

				public ValueStorage<Boolean> TruckChannelParkingBrake = new();

				public ValueStorage<Boolean> TruckChannelMotorBrake = new();

				public ValueStorage<UInt32> TruckChannelRetarderLevel = new();

				public ValueStorage<Single> TruckChannelBrakeAirPressure = new();

				public ValueStorage<Boolean> TruckChannelBrakeAirPressureWarning = new();

				public ValueStorage<Boolean> TruckChannelBrakeAirPressureEmergency = new();

				public ValueStorage<Single> TruckChannelBrakeTemperature = new();

				public ValueStorage<Single> TruckChannelFuel = new();

				public ValueStorage<Boolean> TruckChannelFuelWarning = new();

				public ValueStorage<Single> TruckChannelFuelAverageConsumption = new();

				public ValueStorage<Single> TruckChannelFuelRange = new();

				public ValueStorage<Single> TruckChannelAdblue = new();

				public ValueStorage<Boolean> TruckChannelAdblueWarning = new();

				public ValueStorage<Single> TruckChannelOilPressure = new();

				public ValueStorage<Boolean> TruckChannelOilPressureWarning = new();

				public ValueStorage<Single> TruckChannelOilTemperature = new();

				public ValueStorage<Single> TruckChannelWaterTemperature = new();

				public ValueStorage<Boolean> TruckChannelWaterTemperatureWarning = new();

				public ValueStorage<Single> TruckChannelBatteryVoltage = new();

				public ValueStorage<Boolean> TruckChannelBatteryVoltageWarning = new();

				public ValueStorage<Boolean> TruckChannelElectricEnabled = new();

				public ValueStorage<Boolean> TruckChannelEngineEnabled = new();

				public ValueStorage<Boolean> TruckChannelLblinker = new();

				public ValueStorage<Boolean> TruckChannelRblinker = new();

				public ValueStorage<Boolean> TruckChannelHazardWarning = new();

				public ValueStorage<Boolean> TruckChannelLightLblinker = new();

				public ValueStorage<Boolean> TruckChannelLightRblinker = new();

				public ValueStorage<Boolean> TruckChannelLightParking = new();

				public ValueStorage<Boolean> TruckChannelLightLowBeam = new();

				public ValueStorage<Boolean> TruckChannelLightHighBeam = new();

				public ValueStorage<UInt32> TruckChannelLightAuxFront = new();

				public ValueStorage<UInt32> TruckChannelLightAuxRoof = new();

				public ValueStorage<Boolean> TruckChannelLightBeacon = new();

				public ValueStorage<Boolean> TruckChannelLightBrake = new();

				public ValueStorage<Boolean> TruckChannelLightReverse = new();

				public ValueStorage<Boolean> TruckChannelWipers = new();

				public ValueStorage<Single> TruckChannelDashboardBacklight = new();

				public ValueStorage<Boolean> TruckChannelDifferentialLock = new();

				public ValueStorage<Boolean> TruckChannelLiftAxle = new();

				public ValueStorage<Boolean> TruckChannelLiftAxleIndicator = new();

				public ValueStorage<Boolean> TruckChannelTrailerLiftAxle = new();

				public ValueStorage<Boolean> TruckChannelTrailerLiftAxleIndicator = new();

				public ValueStorage<Single> TruckChannelWearEngine = new();

				public ValueStorage<Single> TruckChannelWearTransmission = new();

				public ValueStorage<Single> TruckChannelWearCabin = new();

				public ValueStorage<Single> TruckChannelWearChassis = new();

				public ValueStorage<Single> TruckChannelWearWheels = new();

				public ValueStorage<Single> TruckChannelOdometer = new();

				public ValueStorage<Single> TruckChannelNavigationDistance = new();

				public ValueStorage<Single> TruckChannelNavigationTime = new();

				public ValueStorage<Single> TruckChannelNavigationSpeedLimit = new();

				[StaticSize(14)]
				public ValueArrayStorage<Single> TruckChannelWheelSuspDeflection = new(14);

				[StaticSize(14)]
				public ValueArrayStorage<Boolean> TruckChannelWheelOnGround = new(14);

				[StaticSize(14)]
				public ValueArrayStorage<UInt32> TruckChannelWheelSubstance = new(14);

				[StaticSize(14)]
				public ValueArrayStorage<Single> TruckChannelWheelVelocity = new(14);

				[StaticSize(14)]
				public ValueArrayStorage<Single> TruckChannelWheelSteering = new(14);

				[StaticSize(14)]
				public ValueArrayStorage<Single> TruckChannelWheelRotation = new(14);

				[StaticSize(14)]
				public ValueArrayStorage<Single> TruckChannelWheelLift = new(14);

				[StaticSize(14)]
				public ValueArrayStorage<Single> TruckChannelWheelLiftOffset = new(14);
			}

			public TrailerStorage[] Trailer = new TrailerStorage[10];
			public struct TrailerStorage()
			{
				public ValueStorage<Boolean> TrailerChannelConnected = new();

				public ValueStorage<Single> TrailerChannelCargoDamage = new();

				public ValueStorage<SCSValueDPlacement> TrailerChannelWorldPlacement = new();

				public ValueStorage<SCSValueFVector> TrailerChannelLocalLinearVelocity = new();

				public ValueStorage<SCSValueFVector> TrailerChannelLocalAngularVelocity = new();

				public ValueStorage<SCSValueFVector> TrailerChannelLocalLinearAcceleration = new();

				public ValueStorage<SCSValueFVector> TrailerChannelLocalAngularAcceleration = new();

				public ValueStorage<Single> TrailerChannelWearBody = new();

				public ValueStorage<Single> TrailerChannelWearChassis = new();

				public ValueStorage<Single> TrailerChannelWearWheels = new();

				[StaticSize(19)]
				public ValueArrayStorage<Single> TrailerChannelWheelSuspDeflection = new(19);

				[StaticSize(19)]
				public ValueArrayStorage<Boolean> TrailerChannelWheelOnGround = new(19);

				[StaticSize(19)]
				public ValueArrayStorage<UInt32> TrailerChannelWheelSubstance = new(19);

				[StaticSize(19)]
				public ValueArrayStorage<Single> TrailerChannelWheelVelocity = new(19);

				[StaticSize(19)]
				public ValueArrayStorage<Single> TrailerChannelWheelSteering = new(19);

				[StaticSize(19)]
				public ValueArrayStorage<Single> TrailerChannelWheelRotation = new(19);

				[StaticSize(19)]
				public ValueArrayStorage<Single> TrailerChannelWheelLift = new(19);

				[StaticSize(19)]
				public ValueArrayStorage<Single> TrailerChannelWheelLiftOffset = new(19);
			}
		}
	}

    public static class TelemetryStructureFunctions
    {
        public static bool IsTelemetryStructure(this Type? structType)
        {
            if (structType is null)
                return false;
            if (!structType.IsValueType || structType.Assembly != typeof(MasterStorage).Assembly)
                return false;

            return structType == typeof(MasterStorage) ? true : IsTelemetryStructure(structType.DeclaringType);
        }

        public static bool IsTelemetryStructure<T>() =>
            IsTelemetryStructure(typeof(T));

        public static bool IsTelemetryStructure(this object obj) =>
            IsTelemetryStructure(obj.GetType());

        public static int TelemetryStructureFromBytes(this byte[] bytes, object structure, int offset = 0)
        {
            if (!structure.IsTelemetryStructure())
                throw new NotImplementedException();
            int read = 0;

            void Value(object boxed, Action<object> setter, UInt32? staticSize)
            {
                read += boxed.StorageFromBytes(boxed.GetType().GetGenericArguments()[0].GetSCSValueTypeOf(), bytes, offset + read, staticSize);
                setter(boxed);
            }

            void Structure(object boxed, Action<object> setter)
            {
                read += bytes.TelemetryStructureFromBytes(boxed, offset + read);
                setter(boxed);
            }

            foreach (FieldInfo field in structure.GetType().GetFields())
            {
                if (field.FieldType.IsStorageType())
                    Value(field.GetValue(structure)!, result => field.SetValue(structure, result), field.GetCustomAttribute<StaticSizeAttribute>()?.StaticSize);
                else if (field.FieldType.IsTelemetryStructure())
                    Structure(field.GetValue(structure)!, result => field.SetValue(structure, result));
                else if (field.FieldType.IsArray)
                {
                    Array array = (Array)field.GetValue(structure)!;
                    if (field.FieldType.GetElementType()!.IsStorageType())
                        for (int i = 0; i < array.Length; i++)
                            Value(array.GetValue(i)!, result => array.SetValue(result, i), field.GetCustomAttribute<StaticSizeAttribute>()?.StaticSize);
                    else if (field.FieldType.GetElementType()!.IsTelemetryStructure())
                        for (int i = 0; i < array.Length; i++)
                            Structure(array.GetValue(i)!, result => array.SetValue(result, i));
                }
            }
            return read;
        }

        public static int TelemetryStructureArrayFromBytes(this byte[] bytes, object[] structures, int offset = 0)
        {
            int read = 0;
            foreach (object structure in structures)
                read += TelemetryStructureFromBytes(bytes, structure, offset + read);
            return read;
        }

        public static int TelemetryStructureFromBytes<T>(this ref T structure, byte[] bytes, int offset = 0) where T : struct
        {
            object boxed = structure;
            int read = bytes.TelemetryStructureFromBytes(boxed, offset);
            structure = (T)boxed;
            return read;
        }

        public static int TelemetryStructureArrayFromBytes<T>(this T[] structures, byte[] bytes, int offset = 0) where T : struct
        {
            int read = 0;
            for (int i = 0; i < structures.Length; i++)
                read += structures[i].TelemetryStructureFromBytes<T>(bytes, offset + read);
            return read;
        }

        public static T ConstructTelemetryStructure<T>(this byte[] bytes, int offset, out int read) where T : struct
        {
            object boxed = new T();
            read = bytes.TelemetryStructureFromBytes(boxed, offset);
            return (T)boxed;
        }

        public static T ConstructTelemetryStructure<T>(this byte[] bytes, int offset = 0) where T : struct =>
            ConstructTelemetryStructure<T>(bytes, offset, out int read);

        public static T[] ConstructTelemetryStructureArray<T>(this byte[] bytes, int count, int offset, out int read) where T : struct
        {
            T[] structures = new T[count];
            read = structures.TelemetryStructureArrayFromBytes(bytes, offset);
            return structures;
        }

        public static T[] ConstructTelemetryStructureArray<T>(this byte[] bytes, int count, int offset = 0) where T : struct =>
            ConstructTelemetryStructureArray<T>(bytes, count, offset, out int read);
    }
}
