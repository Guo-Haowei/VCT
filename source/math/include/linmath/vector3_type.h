/// vec3_type.h
#pragma once
#include "gen_type.h"
#include "swizzle_type.h"

namespace three {
namespace linmath {

template<typename T>
struct gen_type<VECTOR, 3, 1, T>
{
    union {
        struct { T x, y, z; };
        struct { T r, g, b; };
        /// swizzle
#ifndef THREE_MATH_DISABLE_SWIZZLE
        swizzle_type<3, T, 0, 1> xy;
        swizzle_type<3, T, 1, 0> yx;
        swizzle_type<3, T, 0, 1, 2> xyz;
        swizzle_type<3, T, 2, 1, 0> zyx;
        swizzle_type<3, T, 0, 0, 0, 0> xxxx;
#endif // !THREE_MATH_DISABLE_SWIZZLE
    };

    /// default constructor
    constexpr gen_type() = default;
    constexpr gen_type(const vector3_type<T>&) = default;
    /// implicit constructor
    constexpr gen_type(T x, T y, T z);
    constexpr gen_type(const vector2_type<T>& vec, T z);
    /// explicit constructor
    constexpr explicit gen_type(T scalar);
    constexpr explicit gen_type(const vector4_type<T>& vec);
    template<typename U>
    constexpr explicit gen_type(U x, U y, U z);

    /// operator[]
    T& operator[](int i);
    const T& operator[](int i) const;

    static const vector3_type<T> Zero;
    static const vector3_type<T> One;
    static const vector3_type<T> UnitX;
    static const vector3_type<T> UnitY;
    static const vector3_type<T> UnitZ;
};

} // namespace linmath
} // namespace three

#include "vector3_type.inl"
#include "gen_type_math.inl"
#include "vector_math.inl"
