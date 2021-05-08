#include "linmath/matrix4x4_type.h"
#include "Types.h"
using three::linmath::matrix4x4_type;

namespace three {

template<> constexpr matrix4x4_type<f32> matrix4x4_type<f32>::Zero     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
template<> constexpr matrix4x4_type<f32> matrix4x4_type<f32>::Identity { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

template<> constexpr matrix4x4_type<f64> matrix4x4_type<f64>::Zero     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
template<> constexpr matrix4x4_type<f64> matrix4x4_type<f64>::Identity { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

static_assert(sizeof(matrix4x4_type<f32>::Identity) == 16 * sizeof(f32));
static_assert(sizeof(matrix4x4_type<f64>::Identity) == 16 * sizeof(f64));

} // namespace three

