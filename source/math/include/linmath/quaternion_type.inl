#pragma once
#include "quaternion_type.h"

namespace three {
namespace linmath {

///--------------------------------------------------------------------------///
/// constructor
///--------------------------------------------------------------------------///
template<typename T>
constexpr quaternion_type<T>::gen_type(T x, T y, T z, T w)
    : x(x), y(y), z(z), w(w)
{}

template<typename T>
template<typename U>
constexpr quaternion_type<T>::gen_type(U x, U y, U z, U w)
    : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)), w(static_cast<T>(w))
{}

///--------------------------------------------------------------------------///
/// operator[]
///--------------------------------------------------------------------------///
template<typename T>
T& quaternion_type<T>::operator[](int i)
{
    return reinterpret_cast<T*>(this)[i];
}

template<typename T>
const T& quaternion_type<T>::operator[](int i) const
{
    return reinterpret_cast<const T*>(this)[i];
}

} // namespace linmath
} // namespace three

