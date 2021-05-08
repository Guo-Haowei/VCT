#pragma once
#include "../Vector.h"
#include <vector>

namespace three {
namespace geometry {

extern void boxWireframe(std::vector<Vector3>& outPoints, std::vector<u32>& outIndices, float size = 0.5f);
extern void box(std::vector<Vector3>& outPoints, std::vector<u32>& outIndices, float size = 0.5f);
extern void boxWithNormal(std::vector<Vector3>& outPoints, std::vector<Vector3>& outNomrals, std::vector<u32>& outIndices, float size = 0.5f);

} // namespace geometry
} // namespace three
