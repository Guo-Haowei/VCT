#pragma once

namespace three {

using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using i8  = char;
using i16 = short;
using i32 = int;
using f32 = float;
using f64 = double;
#ifndef THREE_MATH_PRECISION_DOUBLE
using real = f32;
#else
using real = f64;
#endif // !THREE_MATH_PRECISION_DOUBLE

static_assert(sizeof(u8) == 1);
static_assert(sizeof(u16) == 2);
static_assert(sizeof(u32) == 4);
static_assert(sizeof(i8) == 1);
static_assert(sizeof(i16) == 2);
static_assert(sizeof(i32) == 4);
static_assert(sizeof(f32) == 4);
static_assert(sizeof(f64) == 8);

} // namespace three