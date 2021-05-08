#pragma once
#include "vector3_type.h"

namespace three {
namespace linmath {

///--------------------------------------------------------------------------///
/// constructor
///--------------------------------------------------------------------------///
template<typename T>
constexpr vector3_type<T>::gen_type(T x, T y, T z)
    : x(x), y(y), z(z)
{}

template<typename T>
constexpr vector3_type<T>::gen_type(const vector2_type<T>& vec, T z)
    : x(vec.x), y(vec.y), z(z)
{}

template<typename T>
constexpr vector3_type<T>::gen_type(T scalar)
    : x(scalar), y(scalar), z(scalar)
{}

template<typename T>
constexpr vector3_type<T>::gen_type(const vector4_type<T>& vec)
    : x(vec.x), y(vec.y), z(vec.z)
{}

template<typename T>
template<typename U>
constexpr vector3_type<T>::gen_type(U x, U y, U z)
    : x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z))
{}

///--------------------------------------------------------------------------///
/// operator[]
///--------------------------------------------------------------------------///
template<typename T>
T& vector3_type<T>::operator[](int i)
{
    return reinterpret_cast<T*>(this)[i];
}

template<typename T>
const T& vector3_type<T>::operator[](int i) const
{
    return reinterpret_cast<const T*>(this)[i];
}

} // namespace linmath
} // namespace three
