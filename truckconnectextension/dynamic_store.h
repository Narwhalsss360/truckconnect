#pragma once
#include "truckconnectextension.h"

template <typename T>
void dynamic_store(const scs_value_t& value, truckconnect::value_storage<T>& destination) {
	destination.value = *reinterpret_cast<const T* const>(&value.value_bool.value);
	destination.initialized = true;
}

template <>
void dynamic_store(const scs_value_t& value, truckconnect::value_storage<std::string>& destination);

template <typename T>
void dynamic_store(const scs_value_t& value, truckconnect::value_vector_storage<T>& destination, const uint32_t& index) {
	if (destination.values.size() <= index) {
		destination.values.resize(index + 1);
	}
	destination.values[index] = *reinterpret_cast<const T* const>(&value.value_bool.value);
}

template <>
void dynamic_store(const scs_value_t& value, truckconnect::value_vector_storage<std::string>& destination, const uint32_t& index);

void dynamic_store(const scs_value_t& value, void* const destination, const uint32_t& index = 0);
