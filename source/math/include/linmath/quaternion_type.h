/// vec4.h
#pragma once
#include "gen_type.h"

namespace three {
namespace linmath {

template<typename T>
struct gen_type<QUATERNION, 4, 1, T>
{
    // info can be VECTOR or QUATERNION
    T x, y, z, w;

    /// default constructor
    constexpr gen_type() = default;
    constexpr gen_type(const quaternion_type<T>&) = default;
    /// implicit constructor
    constexpr gen_type(T x, T y, T z, T w);
    /// explicit constructor
    template<typename U>
    constexpr explicit gen_type(U x, U y, U z, U w);

    /// operator[]
    T& operator[](int i);
    const T& operator[](int i) const;
};

} // namespace linmath
} // namespace three

#include "quaternion_type.inl"
#include "gen_type_math.inl"
#include "vector_math.inl"
