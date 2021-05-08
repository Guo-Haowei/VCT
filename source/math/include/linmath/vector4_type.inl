#pragma once
#include "vector4_type.h"

namespace three {
namespace linmath {

///--------------------------------------------------------------------------///
/// constructor
///--------------------------------------------------------------------------///
template<typename T>
constexpr vector4_type<T>::gen_type(T x, T y, T z, T w)
    : x(x), y(y), z(z), w(w)
{}

template<typename T>
constexpr vector4_type<T>::gen_type(T scalar)
    : x(scalar), y(scalar), z(scalar), w(scalar)
{}

template<typename T>
constexpr vector4_type<T>::gen_type(const vector2_type<T>& vec, T z, T w)
    : x(vec.x), y(vec.y), z(z), w(w)
{}

template<typename T>
constexpr vector4_type<T>::gen_type(const vector3_type<T>& vec, T w)
    : x(vec.x), y(vec.y), z(vec.z), w(w)
{}

template<typename T>
template<typename U>
constexpr vector4_type<T>::gen_type(U x, U y, U z, U w)
    : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z)), w(static_cast<T>(w))
{}

///--------------------------------------------------------------------------///
/// operator[]
///--------------------------------------------------------------------------///
template<typename T>
T& vector4_type<T>::operator[](int i)
{
    return reinterpret_cast<T*>(this)[i];
}

template<typename T>
const T& vector4_type<T>::operator[](int i) const
{
    return reinterpret_cast<const T*>(this)[i];
}

} // namespace linmath
} // namespace three
