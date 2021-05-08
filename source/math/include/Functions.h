#pragma once

namespace three {

template<typename T>
T clamp(const T& value, const T& min, const T& max)
{
    return std::min(std::max(value, min), max);
}

} // namespace three
