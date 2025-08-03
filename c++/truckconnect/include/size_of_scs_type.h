#include "scssdk/scssdk_value.h"
#include <cstdint>

namespace truckconnect {
    namespace metadata {
        constexpr const uint32_t sizeof_scs_type(const scs_value_type_t& type_id) {
            switch (type_id) {
            case SCS_VALUE_TYPE_INVALID:
                return 0;
            case SCS_VALUE_TYPE_bool:
                return sizeof(bool);
            case SCS_VALUE_TYPE_s32:
                return sizeof(int32_t);
            case SCS_VALUE_TYPE_u32:
                return sizeof(uint32_t);
            case SCS_VALUE_TYPE_u64:
                return sizeof(uint64_t);
            case SCS_VALUE_TYPE_float:
                return sizeof(float);
            case SCS_VALUE_TYPE_double:
                return sizeof(double);
            case SCS_VALUE_TYPE_fvector:
                return sizeof(scs_value_fvector_t);
            case SCS_VALUE_TYPE_dvector:
                return sizeof(scs_value_dvector_t);
            case SCS_VALUE_TYPE_euler:
                return sizeof(scs_value_euler_t);
            case SCS_VALUE_TYPE_fplacement:
                return sizeof(scs_value_fplacement_t);
            case SCS_VALUE_TYPE_dplacement:
                return sizeof(scs_value_dplacement_t);
            case SCS_VALUE_TYPE_string:
                return 0;
            case SCS_VALUE_TYPE_s64:
                return sizeof(int64_t);
            default:
                return 0;
            }
        }
    }
}

