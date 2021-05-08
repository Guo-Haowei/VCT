#pragma once
#include "gen_type.h"
#include <type_traits>
/// TODO: move implementation to inl file

namespace three {
namespace linmath {

constexpr bool swizzle_valid(int N, int A, int B, int C, int D)
{
    return (A >= 0 && A < N) &&                       // validate A
           (B >= 0 && B < N) &&                       // validate B
           ((C >= 0 && C < N) || C == -1) &&          // validate C
           ((D >= 0 && D < N && C != -1) || D == -1); // validate D
}

constexpr int swizzle_vector_size(int A, int B, int C, int D)
{
    return 2 + (C != -1) + (D != -1);
}

constexpr bool swizzle_assignable(int N, int A, int B, int C, int D)
{
    return swizzle_valid(N, A, B, C, D) &&
           (A >= 0) &&
           (B > A) &&
           ((C > B) || (C == -1)) &&
           ((D > C) || (D == -1));
}

template <int N, typename T, int A, int B, int C = -1, int D = -1,
          std::enable_if_t<linmath::swizzle_valid(N, A, B, C, D), bool> = 0>
struct swizzle_type
{
    static constexpr int vector_size = swizzle_vector_size(A, B, C, D);
    static constexpr int assignable = swizzle_assignable(N, A, B, C, D);
    static constexpr int indices[4] = {A, B, C, D};
    using this_vector = vector_type<vector_size, T>;
    T data[N];

    // assignment
    this_vector operator=(const this_vector &rhs)
    {
        static_assert(assignable);
        auto copy = rhs;
        for (int i = 0; i < vector_size; ++i)
            at(i) = copy[i];
        return copy;
    }

    // equality
    bool operator==(const this_vector &rhs) const
    {
        for (int i = 0; i < vector_size; ++i)
            if (at(i) != rhs[i])
                return false;
        return true;
    }

    template <int N2, int A2, int B2, int C2, int D2>
    bool operator==(const swizzle_type<N2, T, A2, B2, C2, D2> &rhs) const
    {
        using other_t = swizzle_type<N2, T, A2, B2, C2, D2>;
        static_assert(other_t::vector_size == vector_size);
        for (int i = 0; i < vector_size; ++i)
            if (at(i) != rhs.at(i))
                return false;
        return true;
    }

    template <int N2, int A2, int B2, int C2, int D2>
    bool operator!=(const swizzle_type<N2, T, A2, B2, C2, D2> &rhs) const
    {
        return !(*this == rhs);
    }

    T &at(int i) { return data[indices[i]]; }
    const T &at(int i) const { return data[indices[i]]; }

    operator this_vector() const
    {
        this_vector ret;
        for (int i = 0; i < vector_size; ++i)
            ret[i] = at(i);
        return ret;
    }
};

} // namespace linmath
} // namespace three
