#ifndef __DEVICE__
#define __DEVICE__

#include "core.hpp"

#if defined(INTRIN_NO)

struct f32x16 { f32 data[16]; };
struct f32x8 { f32 data[8]; };
struct f32x4 { f32 data[4]; };

#elif defined(INTRIN_NEON)

#include "arm_neon.h"

#elif defined(INTRIN_AVX512)

#include "immintrin.h"

#elif defined(INTRIN_NEON)

#include "arm_neon.h"

#else

// not used yet

#endif

#endif