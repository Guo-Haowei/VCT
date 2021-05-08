#pragma once
#include "Plane.h"
#include "Matrix.h"
#include "Box.h"

#ifdef near
#   undef near
#endif
#ifdef far
#   undef far
#endif

namespace three {

struct Frustum
{
    Plane left;
    Plane right;
    Plane top;
    Plane bottom;
    Plane near;
    Plane far;

    Plane& operator[](int i);

    const Plane& operator[](int i) const;

    Frustum();

    void setFromProjectionView(const Matrix4& PV);

    bool intersectsBox(const Box3& box);
};

} // namespace three
