#pragma once
#include "gen_type.h"

namespace three {
namespace linmath {

/// matrix vector
template<typename T>
vector3_type<T> operator*(const matrix4x4_type<T>& lhs, const vector3_type<T>& rhs)
{
    vector3_type<T> ret;
    ret.x = lhs.a11 * rhs.x + lhs.a12 * rhs.y + lhs.a13 * rhs.z;
    ret.y = lhs.a21 * rhs.x + lhs.a22 * rhs.y + lhs.a23 * rhs.z;
    ret.z = lhs.a31 * rhs.x + lhs.a32 * rhs.y + lhs.a33 * rhs.z;
    return ret;
}

/// matrix vector
template<typename T>
vector4_type<T> operator*(const matrix4x4_type<T>& lhs, const vector4_type<T>& rhs)
{
    vector4_type<T> ret;
    ret.x = lhs.a11 * rhs.x + lhs.a12 * rhs.y + lhs.a13 * rhs.z + lhs.a14 * rhs.w;
    ret.y = lhs.a21 * rhs.x + lhs.a22 * rhs.y + lhs.a23 * rhs.z + lhs.a24 * rhs.w;
    ret.z = lhs.a31 * rhs.x + lhs.a32 * rhs.y + lhs.a33 * rhs.z + lhs.a34 * rhs.w;
    ret.w = lhs.a41 * rhs.x + lhs.a42 * rhs.y + lhs.a43 * rhs.z + lhs.a44 * rhs.w;
    return ret;
}

/// overload operator*
template<typename T>
matrix4x4_type<T> operator*(const matrix4x4_type<T>& lhs, const matrix4x4_type<T>& rhs)
{
    matrix4x4_type<T> ret;
    ret.a11 = lhs.a11 * rhs.a11 + lhs.a12 * rhs.a21 + lhs.a13 * rhs.a31 + lhs.a14 * rhs.a41;
    ret.a12 = lhs.a11 * rhs.a12 + lhs.a12 * rhs.a22 + lhs.a13 * rhs.a32 + lhs.a14 * rhs.a42;
    ret.a13 = lhs.a11 * rhs.a13 + lhs.a12 * rhs.a23 + lhs.a13 * rhs.a33 + lhs.a14 * rhs.a43;
    ret.a14 = lhs.a11 * rhs.a14 + lhs.a12 * rhs.a24 + lhs.a13 * rhs.a34 + lhs.a14 * rhs.a44;

    ret.a21 = lhs.a21 * rhs.a11 + lhs.a22 * rhs.a21 + lhs.a23 * rhs.a31 + lhs.a24 * rhs.a41;
    ret.a22 = lhs.a21 * rhs.a12 + lhs.a22 * rhs.a22 + lhs.a23 * rhs.a32 + lhs.a24 * rhs.a42;
    ret.a23 = lhs.a21 * rhs.a13 + lhs.a22 * rhs.a23 + lhs.a23 * rhs.a33 + lhs.a24 * rhs.a43;
    ret.a24 = lhs.a21 * rhs.a14 + lhs.a22 * rhs.a24 + lhs.a23 * rhs.a34 + lhs.a24 * rhs.a44;

    ret.a31 = lhs.a31 * rhs.a11 + lhs.a32 * rhs.a21 + lhs.a33 * rhs.a31 + lhs.a34 * rhs.a41;
    ret.a32 = lhs.a31 * rhs.a12 + lhs.a32 * rhs.a22 + lhs.a33 * rhs.a32 + lhs.a34 * rhs.a42;
    ret.a33 = lhs.a31 * rhs.a13 + lhs.a32 * rhs.a23 + lhs.a33 * rhs.a33 + lhs.a34 * rhs.a43;
    ret.a34 = lhs.a31 * rhs.a14 + lhs.a32 * rhs.a24 + lhs.a33 * rhs.a34 + lhs.a34 * rhs.a44;

    ret.a41 = lhs.a41 * rhs.a11 + lhs.a42 * rhs.a21 + lhs.a43 * rhs.a31 + lhs.a44 * rhs.a41;
    ret.a42 = lhs.a41 * rhs.a12 + lhs.a42 * rhs.a22 + lhs.a43 * rhs.a32 + lhs.a44 * rhs.a42;
    ret.a43 = lhs.a41 * rhs.a13 + lhs.a42 * rhs.a23 + lhs.a43 * rhs.a33 + lhs.a44 * rhs.a43;
    ret.a44 = lhs.a41 * rhs.a14 + lhs.a42 * rhs.a24 + lhs.a43 * rhs.a34 + lhs.a44 * rhs.a44;
    return ret;
}

} // namespace linmath
} // namespace three
