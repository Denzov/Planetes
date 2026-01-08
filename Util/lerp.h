#pragma once 

namespace umath{
    template<typename T>
    inline float lerp(T&& a, T&& b, T&& t) {
        return a + (b - a) * t;
    }
}