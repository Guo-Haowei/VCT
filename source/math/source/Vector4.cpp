#include "linmath/vector4_type.h"
#include "Types.h"
using three::linmath::vector4_type;

namespace three {

template<> constexpr vector4_type<i32> vector4_type<i32>::Zero  { 0 };
template<> constexpr vector4_type<i32> vector4_type<i32>::One   { 1 };
template<> constexpr vector4_type<i32> vector4_type<i32>::UnitX { 1, 0, 0, 0 };
template<> constexpr vector4_type<i32> vector4_type<i32>::UnitY { 0, 1, 0, 0 };
template<> constexpr vector4_type<i32> vector4_type<i32>::UnitZ { 0, 0, 1, 0 };
template<> constexpr vector4_type<i32> vector4_type<i32>::UnitW { 0, 0, 0, 1 };

template<> constexpr vector4_type<f32> vector4_type<f32>::Zero  { 0 };
template<> constexpr vector4_type<f32> vector4_type<f32>::One   { 1 };
template<> constexpr vector4_type<f32> vector4_type<f32>::UnitX { 1, 0, 0, 0 };
template<> constexpr vector4_type<f32> vector4_type<f32>::UnitY { 0, 1, 0, 0 };
template<> constexpr vector4_type<f32> vector4_type<f32>::UnitZ { 0, 0, 1, 0 };
template<> constexpr vector4_type<f32> vector4_type<f32>::UnitW { 0, 0, 0, 1 };

template<> constexpr vector4_type<f64> vector4_type<f64>::Zero  { 0 };
template<> constexpr vector4_type<f64> vector4_type<f64>::One   { 1 };
template<> constexpr vector4_type<f64> vector4_type<f64>::UnitX { 1, 0, 0, 0 };
template<> constexpr vector4_type<f64> vector4_type<f64>::UnitY { 0, 1, 0, 0 };
template<> constexpr vector4_type<f64> vector4_type<f64>::UnitZ { 0, 0, 1, 0 };
template<> constexpr vector4_type<f64> vector4_type<f64>::UnitW { 0, 0, 0, 1 };

static_assert(sizeof(vector4_type<f32>::Zero) == 4 * sizeof(f32));
static_assert(sizeof(vector4_type<f64>::Zero) == 4 * sizeof(f64));

} // namespace three


