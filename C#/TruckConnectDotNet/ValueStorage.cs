namespace TruckConnect
{
    public struct ValueStorage<T>
    {
        public bool Initialized;

        public T Value;

        public ValueStorage()
        {
            Initialized = false;
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            if (typeof(T) == typeof(String))
            {
                Value = (T)("" as object);
            }
            else
            {
                if (Activator.CreateInstance(typeof(T)) is not T value)
                    throw new NotImplementedException();
                Value = value;
            }
        }

        public ValueStorage(bool initialized, T value)
        {
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Initialized = initialized;
            Value = value;
        }
    }

    public struct ValueArrayStorage<T>
    {
        public bool Initialized;

        public T[] Values;

        public ValueArrayStorage(UInt32 maxCount)
        {
            Initialized = false;
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Values = new T[maxCount];
        }

        public ValueArrayStorage(bool initialized, T[] values)
        {
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Initialized = initialized;
            Values = values;
        }
    }

    public struct ValueListStorage<T>
    {
        public List<T> Values;

        public ValueListStorage()
        {
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Values = new();
        }

        public ValueListStorage(List<T> values)
        {
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Values = values;
        }
    }

    public static class ValueStorageFunctions
    {
        public static Type? GetGenericStorageTypeDefinition(this Type type)
        {
             if (!type.IsGenericType)
                return null;

            Type genericDefinition = type.GetGenericTypeDefinition();
            if (genericDefinition == typeof(ValueStorage<>))
                return typeof(ValueStorage<>);
            else if (genericDefinition == typeof(ValueArrayStorage<>))
                return typeof(ValueArrayStorage<>);
            else if (genericDefinition == typeof(ValueListStorage<>))
                return typeof(ValueListStorage<>);

            return null;
        }

        public static Type? GetGenericStorageTypeDefinition<T>()
            => GetGenericStorageTypeDefinition(typeof(T));

        public static Type GetGenericStorageTypeDefinition(this Metadata metadata)
        {
            if (metadata.TelemetryType != TelemetryType.Channel)
                throw new NotImplementedException("Only channels are impleneted");
            return metadata.Indexed ?? false ? typeof(ValueArrayStorage<>) : typeof(ValueStorage<>);
        }

        public static bool IsStorageType(this Type type) =>
            GetGenericStorageTypeDefinition(type) is not null;

        public static bool IsStorageType<T>() =>
            IsStorageType(typeof(T));

        public static void ThrowIfInvalidTypeForID(this Type type, TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = null)
        {
            trailerIndexOrCount ??= new(false, 1);
            if (!type.IsGenericType)
                throw new ArgumentException("Invalid type, all storage types are generic", nameof(type));

            if (Metadata.ByID(id) is not Metadata metadata)
                throw new ArgumentException("Invalid TelemetryID", nameof(id));

            if (metadata.TelemetryType != TelemetryType.Channel)
                throw new NotImplementedException("Only channel TelemetryTypes are implemented.");

            if ((metadata.TrailerChannel ?? false) && trailerIndexOrCount.Value.IsCount)
            {
                if (!type.IsArray)
                    throw new ArgumentException("Type must be an array for requesting trailer channel for multiple trailers.", nameof(type));
                type = type.GetElementType() ?? throw new InvalidProgramException();
            }

            Type? storageType = type.GetGenericStorageTypeDefinition();
            if ((metadata.Indexed ?? true) && storageType != typeof(ValueArrayStorage<>))
                throw new ArgumentException($"Value storage for {id} must be a {typeof(ValueArrayStorage<>)}");
            else if (!(metadata.Indexed ?? true) && storageType != typeof(ValueStorage<>))
                throw new ArgumentException($"Value storage for {id} must be a {typeof(ValueStorage<>)}");
        }

        public static void ThrowIfInvalidTypeForID<T>(this TelemetryID id, TrailerIndexOrCount? trailerIndexOrCount = null) =>
            ThrowIfInvalidTypeForID(typeof(T), id, trailerIndexOrCount);

        public static int StorageFromBytes<T>(this ref T storage, SCSValueType valueType, byte[] bytes, int offset = 0) where T : struct
        {
            if (bytes.Length <= offset)
                throw new NotImplementedException();

            object boxed = storage;
            int read;
            Type? definingType = GetGenericStorageTypeDefinition<T>();

            if (definingType == typeof(ValueStorage<>))
            {
                typeof(T).GetField("Initialized")!.SetValue(boxed, bytes[offset] > 0);

                object value;
                read = 1 + bytes.FromBytes(valueType, offset + 1, out value);
                typeof(T).GetField("Value")!.SetValue(boxed, value);
            }
            else
            {
                throw new NotImplementedException();
            }

            storage = (T)boxed;
            return 1 + read;
        }
    }
}
