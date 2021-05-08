#pragma once
#include "Plane.h"

namespace three {


Plane::Plane() {}

Plane::Plane(const Vector3& N, real d)
    : N(N), d(d)
{}

real Plane::distanceToPoint(const Vector3& point) const
{
    return dot(point, N) + d;
}

} // namespace three
