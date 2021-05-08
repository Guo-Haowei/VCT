/// vec4.h
#pragma once
#include "gen_type.h"
#include "swizzle_type.h"

namespace three {
namespace linmath {

template<typename T>
struct gen_type<VECTOR, 4, 1, T>
{
    // info can be VECTOR or QUATERNION
    union {
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
#ifndef THREE_MATH_DISABLE_SWIZZLE
        /// swizzle
        swizzle_type<4, T, 0, 1> xy;
        swizzle_type<4, T, 1, 0> yx;
        swizzle_type<4, T, 0, 1, 2> xyz;
        swizzle_type<4, T, 2, 1, 0> zyx;
        swizzle_type<4, T, 0, 1, 2, 3> xyzw;
        swizzle_type<4, T, 3, 2, 1, 0> wzyx;
#endif // !THREE_MATH_DISABLE_SWIZZLE
    };

    /// default constructor
    constexpr gen_type() = default;
    constexpr gen_type(const vector4_type<T>&) = default;
    /// implicit constructor
    constexpr gen_type(T x, T y, T z, T w);
    constexpr gen_type(const vector2_type<T>& vec, T z, T w);
    constexpr gen_type(const vector3_type<T>& vec, T w);
    /// explicit constructor
    constexpr explicit gen_type(T scalar);
    template<typename U>
    constexpr explicit gen_type(U x, U y, U z, U w);

    /// operator[]
    T& operator[](int i);
    const T& operator[](int i) const;

    static const vector4_type<T> Zero;
    static const vector4_type<T> One;
    static const vector4_type<T> UnitX;
    static const vector4_type<T> UnitY;
    static const vector4_type<T> UnitZ;
    static const vector4_type<T> UnitW;
};

} // namespace linmath
} // namespace three

#include "vector4_type.inl"
#include "gen_type_math.inl"
#include "vector_math.inl"
