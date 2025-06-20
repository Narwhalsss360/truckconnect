using System.Collections;

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

        public UInt32 Count;

        public ValueArrayStorage(UInt32 maxCount = 0)
        {
            Initialized = false;
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Values = new T[maxCount];
            Count = 0;
        }

        public ValueArrayStorage(bool initialized, T[] values)
        {
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Initialized = initialized;
            Values = values;
            Count = 0;
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
            return metadata.Indexed ? typeof(ValueArrayStorage<>) : typeof(ValueStorage<>);
        }

        public static bool IsStorageType(this Type type) =>
            GetGenericStorageTypeDefinition(type) is not null;

        public static bool IsStorageType<T>() =>
            IsStorageType(typeof(T));

        public static void ThrowIfInvalidTypeForSCSValueType(this Type type, SCSValueType valueType)
        {
            if (type.GetGenericStorageTypeDefinition() is not Type genericType)
                throw new ArgumentException("Invalid type, all storage types are generic", nameof(type));

            if (genericType.MakeGenericType(valueType.GetTypeOfSCSValueType()) != type)
                throw new InvalidOperationException("This type is incorrect for the specified SCSValueType");
        }

        public static int StorageFromBytes(this object storage, SCSValueType valueType, byte[] bytes, int offset = 0, UInt32? staticSize = null)
        {
            if (bytes.Length <= offset)
                throw new InvalidDataException("Not enough bytes.");

            Type type = storage.GetType();
            Type? genericType = GetGenericStorageTypeDefinition(type);
            int read;

            if (genericType == typeof(ValueStorage<>))
            {
                type.GetField("Initialized")!.SetValue(storage, bytes[offset] > 0);

                object value;
                read = 1 + bytes.FromBytes(valueType, offset + 1, out value);
                type.GetField("Value")!.SetValue(storage, value);
            }
            else if (genericType == typeof(ValueArrayStorage<>))
            {
                type.GetField("Initialized")!.SetValue(storage, bytes[offset] > 0);
                read = 1;

                read += bytes.FromBytes(offset + read, out UInt32 count);
                type.GetField("Count")!.SetValue(storage, count);

                if (type.GetField("Values")!.GetValue(storage) is null)
                    type.GetField("Values")!.SetValue(
                        storage,
                        Array.CreateInstance(valueType.GetTypeOfSCSValueType(), count)
                    );

                Array array = (Array)type.GetField("Values")!.GetValue(storage)!;

                if (count > array.Length)
                    throw new NotImplementedException();

                UInt32 upperBound = staticSize ?? (UInt32)array.Length;
                for (int i = 0; i < upperBound; i++)
                {
                    read += bytes.FromBytes(valueType, offset + read, out object value);
                    array.SetValue(value, i);
                }
            }
            else if (genericType == typeof(ValueListStorage<>))
            {
                if (bytes.Length - offset < sizeof(UInt32))
                    throw new InvalidDataException("Not enough bytes.");

                if (type.GetField("Values")!.GetValue(storage) is null)
                    type.GetField("Values")!.SetValue(
                        storage,
                        Activator.CreateInstance(typeof(List<>).MakeGenericType(valueType.GetTypeOfSCSValueType()))
                    );

                IList list = (IList)type.GetField("Values")!.GetValue(storage)!;
                list.Clear();

                read = bytes.FromBytes(offset, out UInt32 count);
                for (int i = 0; i < count; i++)
                {
                    read += bytes.FromBytes(valueType, offset + read, out object value);
                    list.Add(value);
                }
            }
            else
                throw new ArgumentException("Type of was not a storage type.", nameof(storage));

            return read;
        }

        public static int StorageFromBytes<T>(this ref T storage, SCSValueType valueType, byte[] bytes, int offset = 0, UInt32? staticSize = null) where T : struct
        {
            ThrowIfInvalidTypeForSCSValueType(typeof(T), valueType);
            object boxed = storage;
            int read = boxed.StorageFromBytes(valueType, bytes, offset, staticSize);
            storage = (T)boxed;
            return read;
        }

        public static int StorageFromBytes<T>(this ref T storage, byte[] bytes, int offset = 0, UInt32? staticSize = null) where T : struct
        {
            if (GetGenericStorageTypeDefinition<T>() is not Type genericType)
                throw new ArgumentException("'storage' was a not a storage type", nameof(storage));

            object boxed = storage;
            int read = boxed.StorageFromBytes(typeof(T).GenericTypeArguments[0].GetSCSValueTypeOf(), bytes, offset);
            storage = (T)boxed;
            return read;
        }

        public static int StorageArrayFromBytes(this object[] storages, SCSValueType valueType, byte[] bytes, int offset = 0, UInt32? staticSize = null)
        {
            int totalRead = 0;
            for (int i = 0; i < storages.Length; i++)
                totalRead += storages[i].StorageFromBytes(valueType, bytes, offset + totalRead);
            return totalRead;
        }

        public static int StorageArrayFromBytes<T>(this T[] storages, SCSValueType valueType, byte[] bytes, int offset = 0) where T : struct
        {
            int totalRead = 0;
            for (int i = 0; i < storages.Length; i++)
                totalRead += storages[i].StorageFromBytes(valueType, bytes, offset + totalRead);
            return totalRead;
        }

        public static int StorageArrayFromBytes<T>(this T[] storages, byte[] bytes, int offset = 0) where T : struct
        {
            if (GetGenericStorageTypeDefinition<T>() is not Type)
                throw new ArgumentException("'storage' was a not a storage type", nameof(storages));
            return storages.StorageArrayFromBytes(typeof(T).GenericTypeArguments[0].GetSCSValueTypeOf(), bytes, offset);
        }

        public static object ConstructStorage(this Metadata metadata)
        {
            if (metadata.TelemetryType != TelemetryType.Channel)
                throw new NotImplementedException();
            if (Activator.CreateInstance(metadata.GetGenericStorageTypeDefinition().MakeGenericType(metadata.SCSValueType.GetTypeOfSCSValueType())) is not object storage)
                throw new NotImplementedException();
            return storage;
        }

        public static object ConstructStorage(this byte[] bytes, Metadata metadata, int offset, UInt32? staticSize, out int read)
        {
            if (metadata.TelemetryType != TelemetryType.Channel)
                throw new NotImplementedException();
            object storage = ConstructStorage(metadata);
            read = storage.StorageFromBytes(metadata.SCSValueType, bytes, offset);
            return storage;
        }

        public static object ConstructStorage(this byte[] bytes, Metadata metadata, int offset = 0, UInt32? staticSize = null) =>
            ConstructStorage(bytes, metadata, offset, staticSize, out int read);

        public static T ConstructStorage<T>(this byte[] bytes, Metadata metadata, int offset, UInt32? staticSize, out int read) where T : struct
        {
            if (metadata.TelemetryType != TelemetryType.Channel)
                throw new NotImplementedException();
            ThrowIfInvalidTypeForSCSValueType(typeof(T), metadata.SCSValueType);
            T storage = default;
            read = storage.StorageFromBytes(metadata.SCSValueType, bytes, offset);
            return storage;
        }

        public static T ConstructStorage<T>(this byte[] bytes, Metadata metadata, int offset = 0, UInt32? staticSize = null) where T : struct =>
            bytes.ConstructStorage<T>(metadata, offset, staticSize, out int read);

        public static object[] ConstructStorageArray(this byte[] bytes, int length, Metadata metadata, int offset, out int read)
        {
            object[] storages = new object[length];
            for (int i = 0; i < length; i++)
                storages[i] = ConstructStorage(metadata);
            read = storages.StorageArrayFromBytes(metadata.SCSValueType, bytes, offset);
            return storages;
        }

        public static object[] ConstructStorageArray(this byte[] bytes, int length, Metadata metadata, int offset = 0) =>
            bytes.ConstructStorageArray(length, metadata, offset, out int read);

        public static T[] ConstructStorageArray<T>(this byte[] bytes, int length, Metadata metadata, int offset, out int read) where T : struct
        {
            T[] storages = new T[length];
            read = storages.StorageArrayFromBytes(bytes, offset);
            return storages;
        }

        public static T[] ConstructStorageArray<T>(this byte[] bytes, int length, Metadata metadata, int offset = 0) where T : struct =>
            bytes.ConstructStorageArray<T>(length, metadata, offset, out int read);
    }
}
