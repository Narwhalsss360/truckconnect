using System.Collections.Generic;

namespace TruckConnect
{
    struct ValueStorage<T> where T : new()
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

    struct ValueArrayStorage<T> where T : new()
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

    struct ValueListStorage<T> where T : new()
    {
        public List<T> Values;

        public ValueListStorage()
        {
            SCSValueTypeFunctions.GetSCSValueTypeOf<T>();
            Values = new();
        }
    }
}
