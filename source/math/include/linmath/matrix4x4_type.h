#pragma once
#include "gen_type.h"
#include "vector4_type.h"

namespace three {
namespace linmath {

template<typename T>
struct gen_type<MATRIX, 4, 4, T>
{
    union {
        struct { vector4_type<T> cols[4]; };
        struct { T a11, a21, a31, a41, a12, a22, a32, a42, a13, a23, a33, a43, a14, a24, a34, a44; };
    };

    /// default constructor
    constexpr gen_type() = default;
    constexpr gen_type(const matrix4x4_type<T>&) = default;
    /// implicit constructor
    constexpr gen_type(const vector4_type<T>& c1,
                       const vector4_type<T>& c2,
                       const vector4_type<T>& c3,
                       const vector4_type<T>& c4);
    constexpr gen_type(T a11, T a12, T a13, T a14,
                       T a21, T a22, T a23, T a24,
                       T a31, T a32, T a33, T a34,
                       T a41, T a42, T a43, T a44);

    /// explicit constructor
    constexpr explicit gen_type(const matrix3x3_type<T>& mat3);
    constexpr explicit gen_type(const T* data);

    /// operator[]
    T& operator[](int i);
    const T& operator[](int i) const;

    static const matrix4x4_type<T> Zero;
    static const matrix4x4_type<T> Identity;
};

} // namespace linmath
} // namespace three

#include "matrix4x4_type.inl"
#include "matrix_math.inl"
#include "matrix_transform.inl"
