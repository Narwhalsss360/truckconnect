using System.Collections.Generic;

namespace TruckConnect
{
    public struct ValueStorage<T> where T : new()
    {
        public bool Initialized;

        public T Value;

        public ValueStorage()
        {
            Initialized = false;
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Value = new();
        }
    }

    public struct ValueArrayStorage<T> where T : new()
    {
        public bool Initialized;

        public T[] Values;

        public ValueArrayStorage(UInt32 maxCount)
        {
            Initialized = false;
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Values = new T[maxCount];
        }
    }

    public struct ValueListStorage<T> where T : new()
    {
        public List<T> Values;

        public ValueListStorage()
        {
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Values = new();
        }
    }
}
