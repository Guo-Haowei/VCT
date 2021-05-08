#pragma once
#include "gen_type.h"

namespace three {
namespace linmath {

///--------------------------------------------------------------------------///
/// comparison
///--------------------------------------------------------------------------///
template<type_info info, int M, int N, typename T>
bool operator==(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template<type_info info, int M, int N, typename T>
bool operator!=(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    return !(lhs == rhs);
}

template<type_info info, int M, int N, typename T>
bool operator>(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        if (lhs[i] <= rhs[i])
            return false;
    return true;
}

template<type_info info, int M, int N, typename T>
bool operator<(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        if (lhs[i] >= rhs[i])
            return false;
    return true;
}

template<type_info info, int M, int N, typename T>
bool operator>=(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        if (lhs[i] < rhs[i])
            return false;
    return true;
}

template<type_info info, int M, int N, typename T>
bool operator<=(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        if (lhs[i] > rhs[i])
            return false;
    return true;
}

///--------------------------------------------------------------------------///
/// addition
///--------------------------------------------------------------------------///
/// operator+
template<type_info info, int M, int N, typename T>
gen_type<info, M, N, T> operator+(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = lhs[i] + rhs[i];
    return ret;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator+(const gen_type<info, M, N, T>& lhs, U scalar)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = lhs[i] + static_cast<T>(scalar);
    return ret;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator+(U scalar, const gen_type<info, M, N, T>& rhs)
{
    return rhs + static_cast<T>(scalar);
}

/// operator+=
template<type_info info, int M, int N, typename T>
gen_type<info, M, N, T>& operator+=(gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        lhs[i] += rhs[i];
    return lhs;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T>& operator+=(gen_type<info, M, N, T>& lhs, U scalar)
{
    for (int i = 0; i < M * N; ++i)
        lhs[i] += static_cast<T>(scalar);
    return lhs;
}

///--------------------------------------------------------------------------///
/// negation
///--------------------------------------------------------------------------///
/// operator-
template<type_info info, int M, int N, typename T>
gen_type<info, M, N, T> operator-(const gen_type<info, M, N, T>& rhs)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = -rhs[i];
    return ret;
}

///--------------------------------------------------------------------------///
/// subtraction
///--------------------------------------------------------------------------///
/// operator-
template<type_info info, int M, int N, typename T>
gen_type<info, M, N, T> operator-(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = lhs[i] - rhs[i];
    return ret;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator-(const gen_type<info, M, N, T>& lhs, U scalar)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = lhs[i] - static_cast<T>(scalar);
    return ret;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator-(U scalar, const gen_type<info, M, N, T>& rhs)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = static_cast<T>(scalar) - rhs[i];
    return ret;
}

/// operator-=
template<type_info info, int M, int N, typename T>
gen_type<info, M, N, T>& operator-=(gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        lhs[i] -= rhs[i];
    return lhs;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T>& operator-=(gen_type<info, M, N, T>& lhs, U scalar)
{
    for (int i = 0; i < M * N; ++i)
        lhs[i] -= static_cast<T>(scalar);
    return lhs;
}

/// NOTE: matrix x matrix and vector x vector are different
///       but matrix x scalar and vector x scalar are the same
///--------------------------------------------------------------------------///
/// multiplication
///--------------------------------------------------------------------------///
/// operator*
template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator*(const gen_type<info, M, N, T>& lhs, U scalar)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = lhs[i] * static_cast<T>(scalar);
    return ret;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator*(U scalar, const gen_type<info, M, N, T>& rhs)
{
    return rhs * static_cast<T>(scalar);
}

/// operator*=
template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T>& operator*=(gen_type<info, M, N, T>& lhs, U scalar)
{
    for (int i = 0; i < M * N; ++i)
        lhs[i] *= static_cast<T>(scalar);
    return lhs;
}

///--------------------------------------------------------------------------///
/// division
///--------------------------------------------------------------------------///
/// operator/
template<type_info info, int M, int N, typename T>
gen_type<info, M, N, T> operator/(const gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = lhs[i] / rhs[i];
    return ret;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator/(const gen_type<info, M, N, T>& lhs, U scalar)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = lhs[i] / static_cast<T>(scalar);
    return ret;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T> operator/(U scalar, const gen_type<info, M, N, T>& rhs)
{
    gen_type<info, M, N, T> ret;
    for (int i = 0; i < M * N; ++i)
        ret[i] = static_cast<T>(scalar) / rhs[i];
    return ret;
}

/// operator/=
template<type_info info, int M, int N, typename T>
gen_type<info, M, N, T>& operator/=(gen_type<info, M, N, T>& lhs, const gen_type<info, M, N, T>& rhs)
{
    for (int i = 0; i < M * N; ++i)
        lhs[i] /= rhs[i];
    return lhs;
}

template<type_info info, int M, int N, typename T, typename U>
gen_type<info, M, N, T>& operator/=(gen_type<info, M, N, T>& lhs, U scalar)
{
    for (int i = 0; i < M * N; ++i)
        lhs[i] /= static_cast<T>(scalar);
    return lhs;
}

} // namespace linmath
} // namespace three
