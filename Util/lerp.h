#ifndef _LERP_H_
#define _LERP_H_

namespace umath{
    template<typename T>
    inline T lerp(const T& a, const T& b, const T& t){
        return a + (b - a) * t;
    }
}

#endif // !_LERP_H_