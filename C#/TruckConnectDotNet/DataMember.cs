using System.Reflection;

namespace TruckConnect
{
    public class DataMember
    {
        public static readonly int SIZE_AS_BYTES = sizeof(byte) + sizeof(UInt32) + sizeof(byte);

        public readonly TelemetryID ID;

        public readonly MemberInfo? Member;

        public readonly TrailerIndexOrCount TrailerCount;

        public bool IsProperty
        {
            get => Member is PropertyInfo;
        }

        public bool IsField
        {
            get => Member is FieldInfo;
        }

        public PropertyInfo MemberAsProperty
        {
            get => Member is PropertyInfo propertyInfo ? propertyInfo : throw new InvalidOperationException("Member was not a PropertyInfo");
        }

        public FieldInfo MemberAsField
        {
            get => Member is FieldInfo fieldInfo ? fieldInfo : throw new InvalidOperationException("Member was not a FieldInfo");
        }

        public Metadata Metadata
        {
            get => Metadata.ByID(ID)!;
        }

        public DataMember(TelemetryID id, TrailerIndexOrCount? trailerCount = null, MemberInfo? member = null)
        {
            ID = id;
            if (Metadata.ByID(id) is null)
                throw new ArgumentException("TelemetryID was invalid", nameof(ID));

            Member = member;
            TrailerCount = trailerCount ?? new();
            EnsureWritable();
        }

        public void Assign(object obj, object value)
        {
            if (value is object[] array)
            {
                Array? member;
                if (IsProperty)
                    member = MemberAsProperty.GetValue(obj) as Array;
                else if (IsField)
                    member = MemberAsField.GetValue(obj) as Array;
                else
                    throw new InvalidOperationException("This DataMember is not associated with a field or a property");

                if (member is null)
                    throw new InvalidOperationException("This DataMember is not array");

                if (member.Length != array.Length)
                    throw new InvalidOperationException("The length of the arrays are not equal");

                for (int i = 0; i < member.Length; i++)
                    member.SetValue(array[i], i);
            }
            else
            {
                if (IsProperty)
                    MemberAsProperty.SetValue(obj, value);
                else if (IsField)
                    MemberAsField.SetValue(obj, value);
                else
                    throw new InvalidOperationException("This DataMember is not associated with a field or a property");
            }
        }

        public byte[] AsBytes()
        {
            return [
                (byte)ID,
                0, 0, 0, 0, //Unused offset
                TrailerCount.AsByteForDataDefinitionRegistration()
            ];
        }

        private void EnsureWritable()
        {
            if (Member is null)
                return;

            Type type;
            if (Member is FieldInfo field)
            {
                if (!field.IsPublic || field.IsInitOnly)
                    throw new ArgumentException("Member must be public", nameof(Member));
                type = field.FieldType;
            }
            else if (Member is PropertyInfo property)
            {
                if (!property.CanWrite)
                    throw new ArgumentException("Member must be public", nameof(Member));
                type = property.PropertyType;
            }
            else
            {
                throw new ArgumentException("Member must be either FieldInfo or PropertyInfo", nameof(Member));
            }

            if (Metadata.TelemetryType == TelemetryType.Channel)
            {
                if (type.IsArray)
                    type.GetElementType()!.ThrowIfInvalidTypeForSCSValueType(Metadata.SCSValueType);
                else
                    type.ThrowIfInvalidTypeForSCSValueType(Metadata.SCSValueType);
            }
            else
            {
                if (type.IsArray)
                    type.GetElementType()!.ThrowIfInvalidTypeForStructureID(Metadata.ID);
                else
                    type.ThrowIfInvalidTypeForStructureID(Metadata.ID);
            }
        }
    }
}

