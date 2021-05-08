#pragma once
#include "Vector.h"

namespace three {

struct Ray
{
    Ray() {}
    Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction)
    {}

    Vector3 at(real t) const
    {
        return origin + t * direction;
    }

    Vector3 origin, direction;
};

} // namespace three
