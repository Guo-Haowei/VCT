#pragma once
#include <limits>

namespace three {

template<typename T>
inline constexpr T zero()
{
    return genType(0);
}
// radians
template<typename T>
inline constexpr T radians(T degrees)
{
    static_assert(std::numeric_limits<T>::is_iec559, "'radians' only accept floating-point input");
    return degrees * static_cast<T>(0.01745329251994329576923690768489);
}

// degrees
template<typename T>
inline constexpr T degrees(T radians)
{
    static_assert(std::numeric_limits<T>::is_iec559, "'degrees' only accept floating-point input");
    return radians * static_cast<T>(57.295779513082320876798154814105);
}

template<typename T>
inline constexpr T pi()
{
    return static_cast<T>(3.1415926535897932384626433832795028841971);
}

template<typename T>
inline constexpr T two_pi()
{
    return static_cast<T>(6.28318530717958647692528676655900576);
}

template<typename T>
inline constexpr T half_pi()
{
    return static_cast<T>(1.57079632679489661923132169163975144);
}

template<typename T>
inline constexpr T quarter_pi()
{
    return static_cast<T>(0.785398163397448309615660845819875721);
}

} // namespace three
