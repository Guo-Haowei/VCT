#pragma once
#include "linmath/gen_type.h"
#include "linmath/swizzle_type.h"
#include <iostream>

namespace three {
namespace linmath {

/// Vector
template<int M, typename T>
std::ostream& operator<<(std::ostream& os, const vector_type<M, T>& vec)
{
    os << " [ ";
    for (int i = 0; i < M; ++i)
        os << vec[i] << ' ';
    os << ']';
    return os;
}

/// Matrix
// template<int M, int N, typename T>
// std::ostream& operator<<(std::ostream& os, const gen_type<M, N, T>& mat)
// {
//     os << "Matrix" << M << 'x' << N;
//     for (int r = 0; r < M; ++r)
//     {
//         os << "\n[ ";
//         for (int c = 0; c < N; ++c)
//             os << mat.cols[c][r] << ' ';
//         os << ']';
//     }
//     return os;
// }

/// Swizzle
// template<int N, typename T, int A, int B, int C, int D>
// std::ostream& operator<<(std::ostream& os, const swizzle_type<N, T, A, B, C, D>& swizzle)
// {
//     os << " [ " << swizzle.at(0) << " " << swizzle.at(1);
//     if constexpr(C != -1) os << " " << swizzle.at(2);
//     if constexpr(D != -1) os << " " << swizzle.at(3);
//     os << " ]";
//     return os;
// }

} // namespace linmath
} // namespace three
