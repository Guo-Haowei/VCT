#pragma once
#include "Types.h"
#include "linmath/quaternion_type.h"
#include <cmath>
#include <limits>

namespace three {

using Quaternion = linmath::quaternion_type<real>;

static Quaternion slerp(const Quaternion& x, const Quaternion& y, real a)
{
    Quaternion z = y;
    real cosine = dot(x, y);

    // If cosine < 0, the interpolation will take the long way around the sphere.
    // To fix this, one quat must be negated.
    if (cosine < real(0))
    {
        z = -y;
        cosine = -cosine;
    }

    // Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
    if (cosine > real(1) - std::numeric_limits<real>::epsilon())
        return lerp(x, z, a);

    real angle = std::acos(cosine);
    return (std::sin(angle - a * angle) * x + std::sin(a * angle) * z) / std::sin(angle);
}

} // namespace three
