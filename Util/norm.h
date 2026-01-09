#ifndef _NORM_H_
#define _NORM_H_

#include "UtilTypes.h"

namespace umath{
    template<IsVector V>
    inline auto norm(const V& v) -> decltype(v.x){
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

}

#endif // !_NORM_H_