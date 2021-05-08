#pragma once
#include "Types.h"
#include "linmath/vector2_type.h"
#include "linmath/vector3_type.h"
#include "linmath/vector4_type.h"

namespace three {

// type alias
using Vector2i = linmath::vector2_type<i32>;
using Vector2u = linmath::vector2_type<u32>;
using Vector2  = linmath::vector2_type<real>;

using Vector3i = linmath::vector3_type<i32>;
using Vector3u = linmath::vector3_type<u32>;
using Vector3  = linmath::vector3_type<real>;

using Vector4i = linmath::vector4_type<i32>;
using Vector4u = linmath::vector4_type<u32>;
using Vector4 =  linmath::vector4_type<real>;

// using
using linmath::dot;
using linmath::lengthSqr;
using linmath::length;
using linmath::normalize;
using linmath::cross;
using linmath::min;
using linmath::max;
// using linmath::abs;
using linmath::lerp;
using linmath::reflect;

} // namespace three
