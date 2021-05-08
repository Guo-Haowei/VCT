#pragma once
#include "vector2_type.h"

namespace three {
namespace linmath {

///--------------------------------------------------------------------------///
/// constructor
///--------------------------------------------------------------------------///
template<typename T>
constexpr vector2_type<T>::gen_type(T x, T y)
    : x(x), y(y)
{}

template<typename T>
constexpr vector2_type<T>::gen_type(T scalar)
    : x(scalar), y(scalar)
{}

template<typename T>
constexpr vector2_type<T>::gen_type(const vector3_type<T>& vec)
    : x(vec.x), y(vec.y)
{}

template<typename T>
constexpr vector2_type<T>::gen_type(const vector4_type<T>& vec)
    : x(vec.x), y(vec.y)
{}

template<typename T>
template<typename U>
constexpr vector2_type<T>::gen_type(U x, U y)
    : x(static_cast<T>(x)), y(static_cast<T>(y))
{}

///--------------------------------------------------------------------------///
/// operator[]
///--------------------------------------------------------------------------///
template<typename T>
T& vector2_type<T>::operator[](int i)
{
    return reinterpret_cast<T*>(this)[i];
}

template<typename T>
const T& vector2_type<T>::operator[](int i) const
{
    return reinterpret_cast<const T*>(this)[i];
}

} // namespace linmath
} // namespace three
