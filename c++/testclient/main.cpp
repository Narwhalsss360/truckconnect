#include "tests.h"
#include <array>
#include <truckconnect>

int main() {
    /* Currently, truckconnect::metadata::... assumes that std::array<...> elements field has 0 offset */ {
        std::array<int, 1> array;
        truckconnect::platform::debug_assert(reinterpret_cast<const uint8_t* const>(&array) == reinterpret_cast<const uint8_t* const>(&array[0]));
    }
    return data_definition_test();
}
