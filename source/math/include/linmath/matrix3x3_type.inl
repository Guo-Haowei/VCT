#pragma once
#include "matrix3x3_type.h"

namespace three {
namespace linmath {

template<typename T>
constexpr matrix3x3_type<T>::gen_type(const vector3_type<T>& c1, const vector3_type<T>& c2, const vector3_type<T>& c3)
    : cols { c1, c2, c3 }
{}

template<typename T>
constexpr matrix3x3_type<T>::gen_type(T a11, T a12, T a13,
                                      T a21, T a22, T a23,
                                      T a31, T a32, T a33)
    : a11(a11), a12(a12), a13(a13)
    , a21(a21), a22(a22), a23(a23)
    , a31(a31), a32(a32), a33(a33)
{}

template<typename T>
constexpr matrix3x3_type<T>::gen_type(const matrix4x4_type<T>& mat4)
    : a11(mat4.a11), a12(mat4.a12), a13(mat4.a13)
    , a21(mat4.a21), a22(mat4.a22), a23(mat4.a23)
    , a31(mat4.a31), a32(mat4.a32), a33(mat4.a33)
{}

template<typename T>
constexpr matrix3x3_type<T>::gen_type(const T* data)
    : a11(data[0]), a12(data[3]), a13(data[6])
    , a21(data[1]), a22(data[4]), a23(data[7])
    , a31(data[2]), a32(data[5]), a33(data[8])
{}

///--------------------------------------------------------------------------///
/// operator[]
///--------------------------------------------------------------------------///
template<typename T>
T& matrix3x3_type<T>::operator[](int i)
{
    return reinterpret_cast<T*>(this)[i];
}

template<typename T>
const T& matrix3x3_type<T>::operator[](int i) const
{
    return reinterpret_cast<const T*>(this)[i];
}
} // namespace linmath
} // namespace three
