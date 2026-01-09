#ifndef _NORMALIZE_H_
#define _NORMALIZE_H_

#include "norm.h"
#include "mult.h"

namespace umath{
    template<IsVector V>
    inline V normalize(const V& v) {
        const float len = norm(v);

        if (len == 0.f)
            return { 0.f, 0.f };


        return mult(v, 1.f / len);  
    }

    template<IsVector V, Arithmetic T>
    inline V normalize(const V& v, const T& len) {
        return mult(v, (1 / len));
    }
}

#endif // !_NORMALIZE_H_