#include "Frustum.h"

namespace three {

Frustum::Frustum()
{}

/// https://stackoverflow.com/questions/12836967/extracting-view-frustum-planes-hartmann-gribbs-method
void Frustum::setFromProjectionView(const Matrix4& PV)
{
    // Left clipping plane
    left.N.x    = PV.a41 + PV.a11;
    left.N.y    = PV.a42 + PV.a12;
    left.N.z    = PV.a43 + PV.a13;
    left.d      = PV.a44 + PV.a14;
    // Right clipping plane
    right.N.x   = PV.a41 - PV.a11;
    right.N.y   = PV.a42 - PV.a12;
    right.N.z   = PV.a43 - PV.a13;
    right.d     = PV.a44 - PV.a14;
    // Top clipping plane
    top.N.x     = PV.a41 - PV.a21;
    top.N.y     = PV.a42 - PV.a22;
    top.N.z     = PV.a43 - PV.a23;
    top.d       = PV.a44 - PV.a24;
    // Bottom clipping plane
    bottom.N.x  = PV.a41 + PV.a21;
    bottom.N.y  = PV.a42 + PV.a22;
    bottom.N.z  = PV.a43 + PV.a23;
    bottom.d    = PV.a44 + PV.a24;
    // Near clipping plane
    near.N.x    = PV.a41 + PV.a31;
    near.N.y    = PV.a42 + PV.a32;
    near.N.z    = PV.a43 + PV.a33;
    near.d      = PV.a44 + PV.a34;
    // Far clipping plane
    far.N.x     = PV.a41 - PV.a31;
    far.N.y     = PV.a42 - PV.a32;
    far.N.z     = PV.a43 - PV.a33;
    far.d       = PV.a44 - PV.a34;
}

bool Frustum::intersectsBox(const Box3& box)
{
    for (int i = 0; i < 6; ++i)
    {
        const Plane& plane = this->operator[](i);
        Vector3 p;
        p.x = plane.N.x > static_cast<real>(0) ? box.max.x : box.min.x;
        p.y = plane.N.y > static_cast<real>(0) ? box.max.y : box.min.y;
        p.z = plane.N.z > static_cast<real>(0) ? box.max.z : box.min.z;

        if (plane.distanceToPoint(p) < static_cast<real>(0))
            return false;
    }

    return true;
}

Plane& Frustum::operator[](int i)
{
    return reinterpret_cast<Plane*>(this)[i];
}

const Plane& Frustum::operator[](int i) const
{
    return reinterpret_cast<const Plane*>(this)[i];
}

} // namespace three

