#ifndef __DEVICE__
#define __DEVICE__

#include "core.hpp"

#if defined(INTRIN_AVX512)

#include "immintrin.h"

#elif defined(INTRIN_NEON)

#include "arm_neon.h"

#else

// default

#endif

#endif  // __DEVICE__
