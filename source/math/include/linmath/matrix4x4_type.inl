#pragma once
#include "matrix4x4_type.h"

namespace three {
namespace linmath {

///--------------------------------------------------------------------------///
/// constructor
///--------------------------------------------------------------------------///
template<typename T>
constexpr matrix4x4_type<T>::gen_type(const vector4_type<T>& c1,
                                      const vector4_type<T>& c2,
                                      const vector4_type<T>& c3,
                                      const vector4_type<T>& c4)
    : cols { c1, c2, c3, c4 }
{}

template<typename T>
constexpr matrix4x4_type<T>::gen_type(T a11, T a12, T a13, T a14,
                                      T a21, T a22, T a23, T a24,
                                      T a31, T a32, T a33, T a34,
                                      T a41, T a42, T a43, T a44)
    : a11(a11), a12(a12), a13(a13), a14(a14)
    , a21(a21), a22(a22), a23(a23), a24(a24)
    , a31(a31), a32(a32), a33(a33), a34(a34)
    , a41(a41), a42(a42), a43(a43), a44(a44)
{}

template<typename T>
constexpr matrix4x4_type<T>::gen_type(const matrix3x3_type<T>& mat3)
    : a11(mat3.a11), a12(mat3.a12), a13(mat3.a13), a14(0)
    , a21(mat3.a21), a22(mat3.a22), a23(mat3.a23), a24(0)
    , a31(mat3.a31), a32(mat3.a32), a33(mat3.a33), a34(0)
    , a41(0), a42(0), a43(0), a44(1)
{}

template<typename T>
constexpr matrix4x4_type<T>::gen_type(const T* data)
    : a11(data[0]), a12(data[4]), a13(data[8]), a14(data[12])
    , a21(data[1]), a22(data[5]), a23(data[9]), a24(data[13])
    , a31(data[2]), a32(data[6]), a33(data[10]), a34(data[14])
    , a41(data[3]), a42(data[7]), a43(data[11]), a44(data[15])
{}

///--------------------------------------------------------------------------///
/// operator[]
///--------------------------------------------------------------------------///
template<typename T>
T& matrix4x4_type<T>::operator[](int i)
{
    return reinterpret_cast<T*>(this)[i];
}

template<typename T>
const T& matrix4x4_type<T>::operator[](int i) const
{
    return reinterpret_cast<const T*>(this)[i];
}

} // namespace linmath
} // namespace three
