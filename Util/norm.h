#pragma once

#include "UtilTypes.h"

namespace umath{
    template<IsVector V>
    inline float norm(const V& v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

}