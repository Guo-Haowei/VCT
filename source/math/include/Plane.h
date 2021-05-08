#pragma once
#include "Vector.h"

namespace three {

struct Plane
{
    Vector3 N;
    real    d;

    Plane();

    Plane(const Vector3& N, real d);

    real distanceToPoint(const Vector3& point) const;
};

} // namespace three
