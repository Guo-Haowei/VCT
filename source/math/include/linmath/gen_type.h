#pragma once

namespace three {
namespace linmath {

enum type_info
{
    SCALAR,
    VECTOR,
    MATRIX,
    QUATERNION
};

/**
 * @brief general type for vector, matrix and quaternion
 *
 * @tparam M, M rows
 * @tparam N, N cols
 * @tparam T, data type
 */
template<type_info info, int M, int N, typename T>
struct gen_type;

/// scalar_type
template<typename T>
struct gen_type<SCALAR, 1, 1, T>;

/// vector_type
template<int M, typename T>
struct gen_type<VECTOR, M, 1, T>;
template<int M, typename T>
using vector_type = gen_type<VECTOR, M, 1, T>;

/// vector2_type
template<typename T>
struct gen_type<VECTOR, 2, 1, T>;
template<typename T>
using vector2_type = gen_type<VECTOR, 2, 1, T>;

/// vector3_type
template<typename T>
struct gen_type<VECTOR, 3, 1, T>;
template<typename T>
using vector3_type = gen_type<VECTOR, 3, 1, T>;

// vector4_type
template<typename T>
struct gen_type<VECTOR, 4, 1, T>;
template<typename T>
using vector4_type = gen_type<VECTOR, 4, 1, T>;

// quaternion_type
template<typename T>
struct gen_type<QUATERNION, 4, 1, T>;
template<typename T>
using quaternion_type = gen_type<QUATERNION, 4, 1, T>;

// matrix_type
template<int M, typename T>
struct gen_type<MATRIX, M, M, T>;
template<int M, typename T>
using matrix_type = gen_type<MATRIX, M, M, T>;

// matrix3x3_type
template<typename T>
struct gen_type<MATRIX, 3, 3, T>;
template<typename T>
using matrix3x3_type = gen_type<MATRIX, 3, 3, T>;

// matrix4x4_type
template<typename T>
struct gen_type<MATRIX, 4, 4, T>;
template<typename T>
using matrix4x4_type = gen_type<MATRIX, 4, 4, T>;

} // namespace linmath
} // namespace three
