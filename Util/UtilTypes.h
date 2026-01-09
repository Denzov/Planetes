#ifndef _UTIL_TYPES_H_
#define _UTIL_TYPES_H_

#include <concepts>
#include <type_traits>

namespace umath
{
    template<typename T>
    concept IsVector = requires(T v) {
        v.x; v.y;
    };

    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T>; 
} 

#endif // !_UTIL_TYPES_H_