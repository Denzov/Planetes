#pragma once

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
