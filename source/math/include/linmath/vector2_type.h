/// vec2.h
#pragma once
#include "gen_type.h"
#include "swizzle_type.h"

namespace three {
namespace linmath {

template<typename T>
struct gen_type<VECTOR, 2, 1, T>
{
    union {
        struct { T x, y; };
        struct { T r, g; };
        struct { T witdh, height; };
        /// swizzle
#ifndef THREE_MATH_DISABLE_SWIZZLE
        swizzle_type<2, T, 0, 1> xy;
        swizzle_type<2, T, 1, 0> yx;
        swizzle_type<2, T, 0, 0, 0, 0> xxxx;
#endif // !THREE_MATH_DISABLE_SWIZZLE
    };

    /// default constructor
    constexpr gen_type() = default;
    constexpr gen_type(const vector2_type<T>&) = default;
    /// implicit constructor
    constexpr gen_type(T x, T y);
    /// explicit constructor
    constexpr explicit gen_type(T scalar);
    constexpr explicit gen_type(const vector3_type<T>& vec);
    constexpr explicit gen_type(const vector4_type<T>& vec);
    template<typename U>
    constexpr explicit gen_type(U x, U y);

    /// operator[]
    T& operator[](int i);
    const T& operator[](int i) const;

    static const vector2_type<T> Zero;
    static const vector2_type<T> One;
    static const vector2_type<T> UnitX;
    static const vector2_type<T> UnitY;
};

} // namespace linmath
} // namespace three

#include "vector2_type.inl"
#include "gen_type_math.inl"
#include "vector_math.inl"
