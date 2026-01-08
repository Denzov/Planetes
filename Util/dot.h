#pragma once

#include "UtilTypes.h"

namespace umath{
    template<IsVector V>
    inline float dot(const V& a, const V& b) {
        return a.x * b.x + a.y * b.y;
    }
}