#pragma once
#include "matrix3x3_type.h"
#include "matrix4x4_type.h"
#include "quaternion_type.h"
#include <cmath>
#include <assert.h>

namespace three {
namespace linmath {

/// transpose
template<int M, typename T>
static matrix_type<M, T> transpose(const matrix_type<M, T>& mat)
{
    matrix_type<M, T> ret;
    ret.a11 = mat.a11; ret.a12 = mat.a21;
    ret.a21 = mat.a12; ret.a22 = mat.a22;
    if constexpr(M >= 3)
    {
        ret.a13 = mat.a31; ret.a23 = mat.a32;
        ret.a31 = mat.a13; ret.a32 = mat.a23; ret.a33 = mat.a33;
    }
    if constexpr(M >= 4)
    {
        ret.a14 = mat.a41; ret.a24 = mat.a42; ret.a34 = mat.a43;
        ret.a41 = mat.a14; ret.a42 = mat.a24; ret.a43 = mat.a34; ret.a44 = mat.a44;
    }

    return ret;
}

/// translate
template<int M, typename T>
matrix4x4_type<T> translate(const vector_type<M, T>& t)
{
    matrix4x4_type<T> ret = matrix4x4_type<T>::Identity;
    ret.a14 = t.x;
    ret.a24 = t.y;
    ret.a34 = t.z;
    return ret;
}

/// scale
template<int M, typename T>
matrix4x4_type<T> scale(const vector_type<M, T>& s)
{
    matrix4x4_type<T> ret = matrix4x4_type<T>::Identity;
    ret.a11 = s.x;
    ret.a22 = s.y;
    ret.a33 = s.z;
    return ret;
}

template<typename T>
matrix4x4_type<T> rotateY(T rad)
{
    matrix4x4_type<T> ret = matrix4x4_type<T>::Identity;
    T sine = std::sin(rad);
    T cosine = std::cos(rad);
    ret.a11 = cosine;
    ret.a13 = sine;
    ret.a31 = -sine;
    ret.a33 = cosine;
    return ret;
}

template<int M, typename T>
matrix4x4_type<T> lookAt(const vector_type<M, T>& eye, const vector_type<M, T>& center, const vector_type<M, T>& up)
{
    const vector3_type<T> f(normalize(center - eye));
    const vector3_type<T> s(normalize(cross(f, vector3_type<T>(up))));
    const vector3_type<T> u(cross(s, f));

    matrix4x4_type<T> ret = matrix4x4_type<T>::Identity;
    ret.a11 = s.x; ret.a12 = s.y; ret.a13 = s.z; ret.a14 = -dot(s, eye);
    ret.a21 = u.x; ret.a22 = u.y; ret.a23 = u.z; ret.a24 = -dot(u, eye);
    ret.a31 = -f.x; ret.a32 = -f.y; ret.a33 = -f.z; ret.a34 = dot(f, eye);
    ret.a41 = T(0); ret.a42 = T(0); ret.a43 = T(0); ret.a44 = T(1);
    return ret;
}

// perspective matrix from one to negtive one (opengl NDC)
template <typename T>
matrix4x4_type<T> perspectiveRH_NO(T fovy, T aspect, T zNear, T zFar)
{
    assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > T(0));
    const T tanHalfFovy = std::tan(T(0.5) * fovy);
    matrix4x4_type<T> ret = matrix4x4_type<T>::Zero;
    ret.a11 = T(1) / (aspect * tanHalfFovy);
    ret.a22 = T(1) / tanHalfFovy;
    ret.a33 = -(zFar + zNear) / (zFar - zNear);
    ret.a43 = -T(1);
    ret.a34 = -(T(2) * zFar * zNear) / (zFar - zNear);
    return ret;
}

template <typename T>
matrix4x4_type<T> perspectiveTanHalfRH_NO(T tanHalf, T aspect, T zNear, T zFar)
{
    assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > T(0));
    matrix4x4_type<T> ret = matrix4x4_type<T>::Zero;
    ret.a11 = T(1) / (aspect * tanHalf);
    ret.a22 = T(1) / tanHalf;
    ret.a33 = -(zFar + zNear) / (zFar - zNear);
    ret.a43 = -T(1);
    ret.a34 = -(T(2) * zFar * zNear) / (zFar - zNear);
    return ret;
}

template<typename T>
matrix4x4_type<T> rotate(const quaternion_type<T>& q)
{
    T qx2(q.x * q.x);
    T qy2(q.y * q.y);
    T qz2(q.z * q.z);
    T qxz(q.x * q.z);
    T qxy(q.x * q.y);
    T qyz(q.y * q.z);
    T qwx(q.w * q.x);
    T qwy(q.w * q.y);
    T qwz(q.w * q.z);

    matrix4x4_type<T> ret = matrix4x4_type<T>::Identity;

    ret.a11 = T(1) - T(2) * (qy2 + qz2);
    ret.a12 = T(2) * (qxy - qwz);
    ret.a13 = T(2) * (qxz + qwy);

    ret.a21 = T(2) * (qxy + qwz);
    ret.a22 = T(1) - T(2) * (qx2 + qz2);
    ret.a23 = T(2) * (qyz - qwx);

    ret.a31 = T(2) * (qxz - qwy);
    ret.a32 = T(2) * (qyz + qwx);
    ret.a33 = T(1) - T(2) * (qx2 + qy2);

    return ret;
}

} // namespace linmath
} // namespace three
