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
            if (IsProperty)
                if (Metadata.TrailerChannel ?? false)
                    throw new NotImplementedException();
                else
                    MemberAsProperty.SetValue(obj, value);
            else if (IsField)
                if (Metadata.TrailerChannel ?? false)
                    throw new NotImplementedException();
                else
                    MemberAsField.SetValue(obj, value);
            else
                throw new InvalidOperationException("This DataMember is not associated with a field or a property");
        }

        public byte[] AsBytes()
        {
            return [
                (byte)ID,
                0, 0, 0, 0, //Unused offset
                TrailerCount.AsByte()
            ];
        }

        private void EnsureWritable()
        {
            if (Member is FieldInfo field)
            {
                if (!field.IsPublic || field.IsInitOnly)
                    throw new ArgumentException("Member must be public", nameof(Member));
                field.FieldType.GetSCSValueTypeOf();
            }
            else if (Member is PropertyInfo property)
            {
                if (!property.CanWrite)
                    throw new ArgumentException("Member must be public", nameof(Member));
                property.PropertyType.GetSCSValueTypeOf();
            }
            else if (Member is not null)
            {
                throw new ArgumentException("Member must be either FieldInfo or PropertyInfo", nameof(Member));
            }
        }
    }
}

