using System.Runtime.InteropServices;
using System.Text;

namespace TruckConnect
{
    public static class ByteConverters
    {
        public static int FromBytes(this byte[] bytes, int offset , out bool result)
        {
            if (bytes.Length - offset < sizeof(bool))
                throw new InvalidDataException("Not enough bytes.");

            result = bytes[offset] > 0;
            return 1;
        }

        public static int FromBytes(this byte[] bytes, int offset , out Int32 result)
        {
            if (bytes.Length - offset < sizeof(Int32))
                throw new InvalidDataException("Not enough bytes.");

            result = BitConverter.ToInt32(bytes, offset);
            return sizeof(Int32);
        }

        public static int FromBytes(this byte[] bytes, int offset , out UInt32 result)
        {
            if (bytes.Length - offset < sizeof(UInt32))
                throw new InvalidDataException("Not enough bytes.");

            result = BitConverter.ToUInt32(bytes, offset);
            return sizeof(UInt32);
        }

        public static int FromBytes(this byte[] bytes, int offset , out UInt64 result)
        {
            if (bytes.Length - offset < sizeof(UInt64))
                throw new InvalidDataException("Not enough bytes.");

            result = BitConverter.ToUInt64(bytes, offset);
            return sizeof(UInt64);
        }

        public static int FromBytes(this byte[] bytes, int offset , out float result)
        {
            if (bytes.Length - offset < sizeof(float))
                throw new InvalidDataException("Not enough bytes.");

            result = BitConverter.ToSingle(bytes, offset);
            return sizeof(float);
        }

        public static int FromBytes(this byte[] bytes, int offset , out double result)
        {
            if (bytes.Length - offset < sizeof(double))
                throw new InvalidDataException("Not enough bytes.");

            result = BitConverter.ToDouble(bytes, offset);
            return sizeof(double);
        }

        public static int FromBytes(this byte[] bytes, int offset , out SCSValueFVector result)
        {
            int size = Marshal.SizeOf<SCSValueFVector>();
            if (bytes.Length - offset < size)
                throw new InvalidDataException("Not enough bytes.");

            result = new(
                BitConverter.ToSingle(bytes, offset),
                BitConverter.ToSingle(bytes, offset + 4),
                BitConverter.ToSingle(bytes, offset + 8)
            );
            return size;
        }

        public static int FromBytes(this byte[] bytes, int offset , out SCSValueDVector result)
        {
            int size = Marshal.SizeOf<SCSValueDVector>();
            if (bytes.Length - offset < size)
                throw new InvalidDataException("Not enough bytes.");

            result = new(
                BitConverter.ToDouble(bytes, offset),
                BitConverter.ToDouble(bytes, offset + 8),
                BitConverter.ToDouble(bytes, offset + 16)
            );
            return size;
        }

        public static int FromBytes(this byte[] bytes, int offset , out SCSValueEuler result)
        {
            int size = Marshal.SizeOf<SCSValueEuler>();
            if (bytes.Length - offset < size)
                throw new InvalidDataException("Not enough bytes.");

            result = new(
                BitConverter.ToSingle(bytes, offset),
                BitConverter.ToSingle(bytes, offset + 4),
                BitConverter.ToSingle(bytes, offset + 8)
            );
            return size;
        }

        public static int FromBytes(this byte[] bytes, int offset , out SCSValueFPlacement result)
        {
            int size = Marshal.SizeOf<SCSValueFPlacement>();
            if (bytes.Length - offset < size)
                throw new InvalidDataException("Not enough bytes.");

            result = new();
            FromBytes(
                bytes,
                offset + FromBytes(bytes, offset, out result.Position),
                out result.Orientation
            );
            return size;
        }

        public static int FromBytes(this byte[] bytes, int offset , out SCSValueDPlacement result)
        {
            int size = Marshal.SizeOf<SCSValueDPlacement>();
            if (bytes.Length - offset < size)
                throw new InvalidDataException("Not enough bytes.");

            result = new();
            FromBytes(
                bytes,
                offset + FromBytes(bytes, offset, out result.Position),
                out result.Orientation
            );
            return size;
        }

        public static int FromBytes(this byte[] bytes, int offset , out string result)
        {
            if (bytes.Length <= offset)
                throw new InvalidDataException("Not enough bytes.");

            if (bytes[offset] == '\0')
            {
                result = "";
                return 1;
            }

            int end = offset;
            for (int i = offset; i < bytes.Length; i++)
            {
                if (bytes[i] == '\0')
                {
                    end = i;
                    break;
                }
            }

            if (end == offset)
                throw new InvalidDataException("No '\\0' character");

            int szLength = end - offset + 1;
            result = Encoding.UTF8.GetString(bytes[offset..(offset + szLength - 1)]);
            return szLength;
        }

        public static int FromBytes(this byte[] bytes, int offset , out Int64 result)
        {
            if (bytes.Length - offset < sizeof(Int64))
                throw new InvalidDataException("Not enough bytes.");

            result = BitConverter.ToInt64(bytes, offset);
            return sizeof(Int64);
        }

        public static int FromBytes(this byte[] bytes, int offset, int count, List<bool> bools)
        {
            const int BOOL_INT_SIZE = sizeof(UInt32);
            const int BOOL_INT_BIT_COUNT = 32;
            int boolIntCount = (count + BOOL_INT_BIT_COUNT - 1) / BOOL_INT_BIT_COUNT;

            bools.Clear();

            for (
                int i = 0, iint = offset, bit = 0;
                i < count;
                i++, iint = bit == BOOL_INT_BIT_COUNT - 1 ? iint + 1 : iint, bit = bit == BOOL_INT_BIT_COUNT - 1 ? 0 : bit + 1
            )
                bools.Add((bytes[iint] & (1 << bit)) > 0);

            return (boolIntCount + 7) / 8;//boolIntCount * BOOL_INT_SIZE;
        }

        public static int FromBytes(this byte[] bytes, SCSValueType valueType, int offset, out object result)
        {
            switch (valueType)
            {
                case SCSValueType.SCS_VALUE_TYPE_bool:
                {
                    bool asBool;
                    int read = FromBytes(bytes, offset, out asBool);
                    result = asBool;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_s32:
                {
                    Int32 asInt32;
                    int read = FromBytes(bytes, offset, out asInt32);
                    result = asInt32;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_u32:
                {
                    UInt32 asUInt32;
                    int read = FromBytes(bytes, offset, out asUInt32);
                    result = asUInt32;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_u64:
                {
                    UInt64 asUInt64;
                    int read = FromBytes(bytes, offset, out asUInt64);
                    result = asUInt64;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_float:
                {
                    float asFloat;
                    int read = FromBytes(bytes, offset, out asFloat);
                    result = asFloat;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_double:
                {
                    double asDouble;
                    int read = FromBytes(bytes, offset, out asDouble);
                    result = asDouble;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_fvector:
                {
                    SCSValueFVector asSCSValueFVector;
                    int read = FromBytes(bytes, offset, out asSCSValueFVector);
                    result = asSCSValueFVector;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_dvector:
                {
                    SCSValueDVector asSCSValueDVector;
                    int read = FromBytes(bytes, offset, out asSCSValueDVector);
                    result = asSCSValueDVector;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_euler:
                {
                    SCSValueEuler asSCSValueEuler;
                    int read = FromBytes(bytes, offset, out asSCSValueEuler);
                    result = asSCSValueEuler;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_fplacement:
                {
                    SCSValueFPlacement asSCSValueFPlacement;
                    int read = FromBytes(bytes, offset, out asSCSValueFPlacement);
                    result = asSCSValueFPlacement;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_dplacement:
                {
                    SCSValueDPlacement asSCSValueDPlacement;
                    int read = FromBytes(bytes, offset, out asSCSValueDPlacement);
                    result = asSCSValueDPlacement;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_string:
                {
                    string asString;
                    int read = FromBytes(bytes, offset, out asString);
                    result = asString;
                    return read;
                }
                case SCSValueType.SCS_VALUE_TYPE_s64:
                {
                    Int64 asInt64;
                    int read = FromBytes(bytes, offset, out asInt64);
                    result = asInt64;
                    return read;
                }
                default:
                    throw new ArgumentException("Unknown SCSValueType", nameof(valueType));
            }
        }
    }
}

