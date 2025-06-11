#include "dynamic_store.h"

using std::string;
using std::to_string;
using namespace truckconnect;

template <>
void dynamic_store(const scs_value_t& value, truckconnect::value_storage<std::string>& destination) {
	destination.value = value.value_string.value;
	destination.initialized = true;
}

template <>
void dynamic_store(const scs_value_t& value, truckconnect::value_vector_storage<std::string>& destination, const uint32_t& index) {
	if (destination.values.size() <= index) {
		destination.values.resize(index + 1);
	}
	destination.values[index] = value.value_string.value;
}

void dynamic_store(const scs_value_t& value, void* const destination, const uint32_t& index) {
	switch (value.type)
	{
	case SCS_VALUE_TYPE_bool:
		if (index == SCS_U32_NIL) {
			dynamic_store<bool>(value, *reinterpret_cast<value_storage<bool>* const>(destination));
		} else {
			dynamic_store<bool>(value, *reinterpret_cast<value_vector_storage<bool>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_s32:
		if (index == SCS_U32_NIL) {
			dynamic_store<int32_t>(value, *reinterpret_cast<value_storage<int32_t>* const>(destination));
		} else {
			dynamic_store<int32_t>(value, *reinterpret_cast<value_vector_storage<int32_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_u32:
		if (index == SCS_U32_NIL) {
			dynamic_store<uint32_t>(value, *reinterpret_cast<value_storage<uint32_t>* const>(destination));
		} else {
			dynamic_store<uint32_t>(value, *reinterpret_cast<value_vector_storage<uint32_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_u64:
		if (index == SCS_U32_NIL) {
			dynamic_store<uint64_t>(value, *reinterpret_cast<value_storage<uint64_t>* const>(destination));
		} else {
			dynamic_store<uint64_t>(value, *reinterpret_cast<value_vector_storage<uint64_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_float:
		if (index == SCS_U32_NIL) {
			dynamic_store<float>(value, *reinterpret_cast<value_storage<float>* const>(destination));
		} else {
			dynamic_store<float>(value, *reinterpret_cast<value_vector_storage<float>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_double:
		if (index == SCS_U32_NIL) {
			dynamic_store<double>(value, *reinterpret_cast<value_storage<double>* const>(destination));
		} else {
			dynamic_store<double>(value, *reinterpret_cast<value_vector_storage<double>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_fvector:
		if (index == SCS_U32_NIL) {
			dynamic_store<scs_value_fvector_t>(value, *reinterpret_cast<value_storage<scs_value_fvector_t>* const>(destination));
		} else {
			dynamic_store<scs_value_fvector_t>(value, *reinterpret_cast<value_vector_storage<scs_value_fvector_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_dvector:
		if (index == SCS_U32_NIL) {
			dynamic_store<scs_value_dvector_t>(value, *reinterpret_cast<value_storage<scs_value_dvector_t>* const>(destination));
		} else {
			dynamic_store<scs_value_dvector_t>(value, *reinterpret_cast<value_vector_storage<scs_value_dvector_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_euler:
		if (index == SCS_U32_NIL) {
			dynamic_store<scs_value_euler_t>(value, *reinterpret_cast<value_storage<scs_value_euler_t>* const>(destination));
		} else {
			dynamic_store<scs_value_euler_t>(value, *reinterpret_cast<value_vector_storage<scs_value_euler_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_fplacement:
		if (index == SCS_U32_NIL) {
			dynamic_store<scs_value_fplacement_t>(value, *reinterpret_cast<value_storage<scs_value_fplacement_t>* const>(destination));
		} else {
			dynamic_store<scs_value_fplacement_t>(value, *reinterpret_cast<value_vector_storage<scs_value_fplacement_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_dplacement:
		if (index == SCS_U32_NIL) {
			dynamic_store<scs_value_dplacement_t>(value, *reinterpret_cast<value_storage<scs_value_dplacement_t>* const>(destination));
		} else {
			dynamic_store<scs_value_dplacement_t>(value, *reinterpret_cast<value_vector_storage<scs_value_dplacement_t>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_string:
		if (index == SCS_U32_NIL) {
			dynamic_store<string>(value, *reinterpret_cast<value_storage<string>* const>(destination));
		} else {
			dynamic_store<string>(value, *reinterpret_cast<value_vector_storage<string>* const>(destination), index);
		}
		break;
	case SCS_VALUE_TYPE_s64:
		if (index == SCS_U32_NIL) {
			dynamic_store<int64_t>(value, *reinterpret_cast<value_storage<int64_t>* const>(destination));
		} else {
			dynamic_store<int64_t>(value, *reinterpret_cast<value_vector_storage<int64_t>* const>(destination), index);
		}
		break;
	default:
		console_log(SCS_LOG_TYPE_error, IDENTSTR(dynamic_store), "Attempting to store and unknown type: " + to_string(value.type));
		break;
	}
}
