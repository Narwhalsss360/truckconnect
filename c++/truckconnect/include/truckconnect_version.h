#pragma once
#include <cstdint>
#include <string>

#define TRUCKCONNECT_MAKE_VERSION(major, minor, patch) (patch | minor << 8 | major << 16)
#define TRUCKCONNECT TRUCKCONNECT_MAKE_VERSION(0, 1, 0)
#define TRUCKCONNECT_MAJOR (TRUCKCONNECT & 0xFF)
#define TRUCKCONNECT_MINOR ((TRUCKCONNECT >> 8) & 0xFF)
#define TRUCKCONNECT_PATCH ((TRUCKCONNECT >> 16) & 0xFF)
#define TRUCKCONNECT_VERSION_STR ("0.1.0")
#define TRUCKCONNECT_NAMESPACE truckconnect

namespace truckconnect {
    struct version_t {
        uint8_t
            patch : 8,
            minor : 8,
            major : 8;

        constexpr version_t()
            : patch(0), minor(0), major(0) {}

        constexpr version_t(const uint8_t& major, const uint8_t& minor, const uint8_t& patch)
            : patch(patch), minor(minor), major(major) {}

        version_t(const uint32_t& version)
            : patch(version & 0xFF), minor((version >> 8) & 0xFF), major((version >> 16) & 0xFF) {}

        constexpr operator const uint32_t() const {
            return TRUCKCONNECT_MAKE_VERSION(major, minor, patch);
        }

        operator const std::string() const {
            return std::to_string(major) + '.' + std::to_string(minor) + '.' + std::to_string(patch);
        }
    };

    constexpr const version_t version = version_t(TRUCKCONNECT_MAJOR, TRUCKCONNECT_MINOR, TRUCKCONNECT_PATCH);
}

namespace std {
    static string to_string(const truckconnect::version_t& version) {
        return (string)version;
    }
}
