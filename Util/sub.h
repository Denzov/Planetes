#pragma once

#include "UtilTypes.h"

namespace umath{
    template<IsVector V>
    inline V sub(const V& a, const V& b) {
        return { a.x - b.x, a.y - b.y };
    }

    template<IsVector V, Arithmetic T>
    inline V sub(const V& a, const T& b) {
        return { a.x - b, a.y - b };
    }

    template<IsVector V, Arithmetic T>
    inline V sub(const T& a, const V& b) {
        return { a - b.x, a - b.y };
    }
}