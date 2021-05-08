#pragma once
#include "gen_type.h"
#include <cmath>
#include <algorithm>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace three {
namespace linmath {

///--------------------------------------------------------------------------///
/// multiplication
///--------------------------------------------------------------------------///
template<type_info info, int M, typename T>
gen_type<info, M, 1, T> operator*(const gen_type<info, M, 1, T>& lhs, const gen_type<info, M, 1, T>& rhs)
{
    gen_type<info, M, 1, T> ret;
    ret.x = lhs.x * rhs.x;
    ret.y = lhs.y * rhs.y;
    if constexpr(M >= 3) ret.z = lhs.z * rhs.z;
    if constexpr(M >= 4) ret.w = lhs.w * rhs.w;
    return ret;
}

template<type_info info, int M, typename T>
gen_type<info, M, 1, T>& operator*=(gen_type<info, M, 1, T>& lhs, const gen_type<info, M, 1, T>& rhs)
{
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    if constexpr(M >= 3) lhs.z *= rhs.z;
    if constexpr(M >= 4) lhs.w *= rhs.w;
    return lhs;
}

///--------------------------------------------------------------------------///
/// dot
template<type_info info, int M, typename T>
T dot(const gen_type<info, M, 1, T>& v1, const gen_type<info, M, 1, T>& v2)
{
    T ret = v1.x * v2.x + v1.y * v2.y;
    if constexpr (M >= 3) ret += v1.z * v2.z;
    if constexpr (M >= 4) ret += v1.w * v2.w;
    return ret;
}

///--------------------------------------------------------------------------///
/// length
template<type_info info, int M, typename T>
T lengthSqr(const gen_type<info, M, 1, T>& v)
{
    return dot(v, v);
}

template<type_info info, int M, typename T>
T length(const gen_type<info, M, 1, T>& v)
{
    return std::sqrt(lengthSqr(v));
}

///--------------------------------------------------------------------------///
/// normalize
template<type_info info, int M, typename T>
gen_type<info, M, 1, T> normalize(const gen_type<info, M, 1, T>& v)
{
    T len = length(v);
    // prevent len == 0, (0 / 0 == nan)
    len = len == static_cast<T>(0) ? static_cast<T>(1) : len;
    return v / len;
}

template<typename T>
vector3_type<T> cross(const vector3_type<T>& v1, const vector3_type<T>& v2)
{
    return vector3_type<T>
    {
        v1.y * v2.z - v2.y * v1.z,
        v1.z * v2.x - v2.z * v1.x,
        v1.x * v2.y - v2.x * v1.y
    };
}

///--------------------------------------------------------------------------///
/// mix
template<type_info info, int M, typename T, typename U>
gen_type<info, M, 1, T> lerp(const gen_type<info, M, 1, T>& a, const gen_type<info, M, 1, T>& b, const U& t)
{
    return (static_cast<T>(1) - t) * a + t * b;
}

///--------------------------------------------------------------------------///
/// min, max, clamp
///--------------------------------------------------------------------------///
template<type_info info, int M, typename T>
gen_type<info, M, 1, T> min(const gen_type<info, M, 1, T>& a, const gen_type<info, M, 1, T>& b)
{
    gen_type<info, M, 1, T> ret;
    ret.x = std::min(a.x, b.x);
    ret.y = std::min(a.y, b.y);
    if constexpr(M >= 3) ret.z = std::min(a.z, b.z);
    if constexpr(M >= 4) ret.w = std::min(a.w, b.w);
    return ret;
}

template<type_info info, int M, typename T>
gen_type<info, M, 1, T> max(const gen_type<info, M, 1, T>& a, const gen_type<info, M, 1, T>& b)
{
    gen_type<info, M, 1, T> ret;
    ret.x = std::max(a.x, b.x);
    ret.y = std::max(a.y, b.y);
    if constexpr(M >= 3) ret.z = std::max(a.z, b.z);
    if constexpr(M >= 4) ret.w = std::max(a.w, b.w);
    return ret;
}

template<type_info info, int M, typename T>
gen_type<info, M, 1, T> clamp(const gen_type<info, M, 1, T>& value, const gen_type<info, M, 1, T>& min, const gen_type<info, M, 1, T>& max)
{
    return three::min(three::max(value, min), max);
}


///--------------------------------------------------------------------------///
/// reflect
///--------------------------------------------------------------------------///
template<type_info info, int M, typename T>
gen_type<info, M, 1, T> reflect(const gen_type<info, M, 1, T>& I, const gen_type<info, M, 1, T>& N)
{
    return I - N * dot(N, I) * static_cast<T>(2);
}

} // namespace linmath
} // namespace three
