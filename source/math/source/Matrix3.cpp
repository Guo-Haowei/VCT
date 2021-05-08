#include "linmath/matrix3x3_type.h"
#include "Types.h"
using three::linmath::matrix3x3_type;

namespace three {

template<> constexpr matrix3x3_type<f32> matrix3x3_type<f32>::Zero     { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
template<> constexpr matrix3x3_type<f32> matrix3x3_type<f32>::Identity { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

template<> constexpr matrix3x3_type<f64> matrix3x3_type<f64>::Zero     { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
template<> constexpr matrix3x3_type<f64> matrix3x3_type<f64>::Identity { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

static_assert(sizeof(matrix3x3_type<f32>::Identity) == 9 * sizeof(f32));
static_assert(sizeof(matrix3x3_type<f64>::Identity) == 9 * sizeof(f64));

} // namespace three

