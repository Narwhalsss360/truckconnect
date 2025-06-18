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
}
