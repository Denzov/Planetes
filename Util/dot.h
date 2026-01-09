#ifndef _DOT_H_
#define _DOT_H_

#include "UtilTypes.h"

namespace umath{
    template<IsVector V>
    inline auto dot(const V& a, const V& b) -> decltype(a.x){
        return a.x * b.x + a.y * b.y;
    }
}

#endif // !_DOT_H_