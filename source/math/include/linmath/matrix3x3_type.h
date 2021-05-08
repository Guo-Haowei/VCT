#pragma once
#include "gen_type.h"
#include "vector3_type.h"

namespace three {
namespace linmath {

template<typename T>
struct gen_type<MATRIX, 3, 3, T>
{
    union
    {
        struct { vector3_type<T> cols[3]; };
        struct { T a11, a21, a31, a12, a22, a32, a13, a23, a33; };
    };

    /// default constructor
    constexpr gen_type() = default;
    constexpr gen_type(const matrix3x3_type<T>&) = default;
    /// implicit constructor
    constexpr gen_type(const vector3_type<T>& c1,
                       const vector3_type<T>& c2,
                       const vector3_type<T>& c3);
    constexpr gen_type(T a11, T a12, T a13,
                       T a21, T a22, T a23,
                       T a31, T a32, T a33);

    /// explicit constructor
    constexpr explicit gen_type(const matrix4x4_type<T>& mat4);
    constexpr explicit gen_type(const T* data);

    /// operator[]
    T& operator[](int i);
    const T& operator[](int i) const;

    static const matrix3x3_type<T> Zero;
    static const matrix3x3_type<T> Identity;
};

} // namespace linmath
} // namespace three

#include "matrix3x3_type.inl"
#include "matrix_math.inl"
#include "matrix_transform.inl"
