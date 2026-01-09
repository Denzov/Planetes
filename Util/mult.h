#ifndef _MULT_H_
#define _MULT_H_

#include "UtilTypes.h"

namespace umath{
    template<IsVector V>
    inline V mult(const V& a, const V& b) {
        return { a.x * b.x, a.y * b.y };
    }

    template<IsVector V, Arithmetic T>
    inline V mult(const V& a, const T& b) {
        return { a.x * b, a.y * b };
    }

    template<IsVector V, Arithmetic T>
    inline V mult(const T& a, const V& b) {
        return { a * b.x, a * b.y };
    }
}

#endif // !_MULT_H_