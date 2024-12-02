#pragma once

#include "core.hpp"

#if defined(INTRIN_NO)

struct f32x16 { f32 data[16]; };
struct f32x8 { f32 data[8]; };
struct f32x4 { f32 data[4]; };

#elif defined(INTRIN_AVX512)

#include "immintrin.h"

using f32x16 = __m512;
using f32x8 = __m256;
using f32x4 = __m128;

#endif

