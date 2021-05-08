#pragma once
#include "Types.h"
#include "linmath/matrix3x3_type.h"
#include "linmath/matrix4x4_type.h"
// #include "Quaternion.h"

namespace three {

/// type alias
using Matrix3 = linmath::matrix3x3_type<real>;
using Matrix4 = linmath::matrix4x4_type<real>;

using linmath::transpose;
using linmath::translate;
using linmath::scale;
using linmath::rotateY;
using linmath::rotate;
using linmath::lookAt;
using linmath::perspectiveRH_NO;
using linmath::perspectiveTanHalfRH_NO;

} // namespace three
