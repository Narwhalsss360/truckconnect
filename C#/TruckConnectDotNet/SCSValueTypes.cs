using System.Runtime.InteropServices;
using System.Collections.Generic;

namespace TruckConnect
{
    public enum SCSValueType
    {
        SCS_VALUE_TYPE_INVALID,
        SCS_VALUE_TYPE_bool,
        SCS_VALUE_TYPE_s32,
        SCS_VALUE_TYPE_u32,
        SCS_VALUE_TYPE_u64,
        SCS_VALUE_TYPE_float,
        SCS_VALUE_TYPE_double,
        SCS_VALUE_TYPE_fvector,
        SCS_VALUE_TYPE_dvector,
        SCS_VALUE_TYPE_euler,
        SCS_VALUE_TYPE_fplacement,
        SCS_VALUE_TYPE_dplacement,
        SCS_VALUE_TYPE_string,
        SCS_VALUE_TYPE_s64
    }

    [StructLayout(LayoutKind.Explicit, Size = 12)]
    public struct SCSValueFVector
    {
        [FieldOffset(0)]
        public float X;

        [FieldOffset(4)]
        public float Y;

        [FieldOffset(8)]
        public float Z;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct SCSValueDVector
    {
        [FieldOffset(0)]
        public double X;

        [FieldOffset(8)]
        public double Y;

        [FieldOffset(16)]
        public double Z;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct SCSValueEuler
    {
        [FieldOffset(0)]
        public float Heading;

        [FieldOffset(4)]
        public float Pitch;

        [FieldOffset(8)]
        public float Roll;
    }

    [StructLayout(LayoutKind.Explicit, Size = 24)]
    public struct SCSValueFPlacement
    {
        [FieldOffset(0)]
        public SCSValueFVector Position;

        [FieldOffset(12)]
        public SCSValueEuler Orientation;
    }

    [StructLayout(LayoutKind.Explicit, Size = 40)]
    public struct SCSValueDPlacement
    {
        [FieldOffset(0)]
        public SCSValueDVector Position;

        [FieldOffset(24)]
        public SCSValueEuler Orientation;
    }

    public static class SCSValueTypeFunctions
    {
        public static readonly Dictionary<SCSValueType, Type> VALUE_TYPE_MAPPING = new()
        {
            { SCSValueType.SCS_VALUE_TYPE_bool, typeof(Boolean) },
            { SCSValueType.SCS_VALUE_TYPE_s32, typeof(Int32) },
            { SCSValueType.SCS_VALUE_TYPE_u32, typeof(UInt32) },
            { SCSValueType.SCS_VALUE_TYPE_u64, typeof(UInt64) },
            { SCSValueType.SCS_VALUE_TYPE_float, typeof(Single) },
            { SCSValueType.SCS_VALUE_TYPE_double, typeof(Double) },
            { SCSValueType.SCS_VALUE_TYPE_fvector, typeof(SCSValueFVector) },
            { SCSValueType.SCS_VALUE_TYPE_dvector, typeof(SCSValueDVector) },
            { SCSValueType.SCS_VALUE_TYPE_euler, typeof(SCSValueEuler) },
            { SCSValueType.SCS_VALUE_TYPE_fplacement, typeof(SCSValueFPlacement) },
            { SCSValueType.SCS_VALUE_TYPE_dplacement, typeof(SCSValueDPlacement) },
            { SCSValueType.SCS_VALUE_TYPE_string, typeof(String) },
            { SCSValueType.SCS_VALUE_TYPE_s64, typeof(Int64) }
        };

        public static readonly Dictionary<Type, SCSValueType> TYPE_TO_VALUE_MAPPING = new()
        {
            { typeof(Boolean), SCSValueType.SCS_VALUE_TYPE_bool  },
            { typeof(Int32), SCSValueType.SCS_VALUE_TYPE_s32  },
            { typeof(UInt32), SCSValueType.SCS_VALUE_TYPE_u32  },
            { typeof(UInt64), SCSValueType.SCS_VALUE_TYPE_u64  },
            { typeof(Single), SCSValueType.SCS_VALUE_TYPE_float  },
            { typeof(Double), SCSValueType.SCS_VALUE_TYPE_double  },
            { typeof(SCSValueFVector), SCSValueType.SCS_VALUE_TYPE_fvector  },
            { typeof(SCSValueDVector), SCSValueType.SCS_VALUE_TYPE_dvector  },
            { typeof(SCSValueEuler), SCSValueType.SCS_VALUE_TYPE_euler  },
            { typeof(SCSValueFPlacement), SCSValueType.SCS_VALUE_TYPE_fplacement  },
            { typeof(SCSValueDPlacement), SCSValueType.SCS_VALUE_TYPE_dplacement  },
            { typeof(String), SCSValueType.SCS_VALUE_TYPE_string  },
            { typeof(Int64), SCSValueType.SCS_VALUE_TYPE_s64  }
        };

        public static SCSValueType GetSCSValueTypeOf(this Type type)
        {
            if (TYPE_TO_VALUE_MAPPING.ContainsKey(type))
                return TYPE_TO_VALUE_MAPPING[type];
            throw new ArgumentException(nameof(type), "Type was not a valid scs type");
        }

        public static SCSValueType GetSCSValueTypeOf<T>() => GetSCSValueTypeOf(typeof(T));

        public static Type GetTypeOfSCSValueType(this SCSValueType valueType)
        {
            if (VALUE_TYPE_MAPPING.ContainsKey(valueType))
                return VALUE_TYPE_MAPPING[valueType];
            throw new ArgumentException(nameof(valueType), "Type was not a valid scs type");
        }
    }
}
