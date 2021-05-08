#pragma once
#include "Types.h"
#include "Vector.h"
#include "Matrix.h"
#include <limits>
#include <assert.h>

namespace three {

template<int M, typename T> struct box_type;

using Box2  = box_type<2, real>;
using Box3  = box_type<3, real>;

template<int M, typename T> struct box_type
{
    using vec_type = linmath::vector_type<M, T>;
    using this_type = box_type<M, T>;

    vec_type min;
    vec_type max;

    constexpr box_type();

    constexpr box_type(const vec_type& min, const vec_type& max);

    void expandPoint(const vec_type& point);

    void expandPoints(size_t count, const vec_type* points);

    void unionBox(const box_type<M, T>& other);

    void mergeBox(const box_type<M, T>& other);

    void applyMatrix(const linmath::matrix4x4_type<T>& mat4);

    bool isValid() const;

    vec_type getCenter() const;

    vec_type getSize() const;

    void setFromCenterSize(const vec_type& center, const vec_type& size);
};

template<int M, typename T>
constexpr box_type<M, T>::box_type()
    : min { std::numeric_limits<T>::infinity() }, max { -std::numeric_limits<T>::infinity() }
{}

template<int M, typename T>
constexpr box_type<M, T>::box_type(const vec_type& _min, const vec_type& _max)
    : min(_min), max(_max)
{
    assert(_min <= _max);
}

template<int M, typename T>
void box_type<M, T>::expandPoint(const vec_type& point)
{
    min = linmath::min(min, point);
    max = linmath::max(max, point);
}

template<int M, typename T>
void box_type<M, T>::expandPoints(size_t count, const vec_type* points)
{
    for (size_t i = 0; i < count; ++i)
        expandPoint(points[i]);
}

template<int M, typename T>
void box_type<M, T>::unionBox(const box_type<M, T>& other)
{
    min = linmath::max(min, other.min);
    max = linmath::min(max, other.max);
}

template<int M, typename T>
void box_type<M, T>::mergeBox(const box_type<M, T>& other)
{
    min = linmath::min(min, other.min);
    max = linmath::max(max, other.max);
}

template<int M, typename T>
void box_type<M, T>::applyMatrix(const linmath::matrix4x4_type<T>& mat4)
{
    static_assert(M == 3);
    using linmath::vector4_type;
    vector4_type<T> points[8] = {
        vector4_type<T>(min.x, min.y, min.z, static_cast<T>(1)),
        vector4_type<T>(min.x, min.y, max.z, static_cast<T>(1)),
        vector4_type<T>(min.x, max.y, min.z, static_cast<T>(1)),
        vector4_type<T>(min.x, max.y, max.z, static_cast<T>(1)),
        vector4_type<T>(max.x, min.y, min.z, static_cast<T>(1)),
        vector4_type<T>(max.x, min.y, max.z, static_cast<T>(1)),
        vector4_type<T>(max.x, max.y, min.z, static_cast<T>(1)),
        vector4_type<T>(max.x, max.y, max.z, static_cast<T>(1))
    };

    this_type newBox;
    for (int i = 0; i < 8; ++i)
        newBox.expandPoint(vec_type(mat4 * points[i]));

    min = newBox.min;
    max = newBox.max;
}

template<int M, typename T>
bool box_type<M, T>::isValid() const
{
    return min < max;
}

template<int M, typename T>
linmath::vector_type<M, T> box_type<M, T>::getCenter() const
{
    return static_cast<T>(0.5) * (min + max);
}

template<int M, typename T>
linmath::vector_type<M, T> box_type<M, T>::getSize() const
{
    return max - min;
}

template<int M, typename T>
void box_type<M, T>::setFromCenterSize(const vec_type& center, const vec_type& size)
{
    vec_type sizeHalf = static_cast<T>(0.5) * size;
    min = center - sizeHalf;
    max = center + sizeHalf;
}

} // namespace three
