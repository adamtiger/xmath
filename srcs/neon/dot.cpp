#include "dot.hpp"
#include "arm_neon.h"

f32 dot_product(const i32 length, const f32* a, const f32* b)
{
    float32x4_t out4 = vdupq_n_f32(0.f);
    for (i32 ix = 0; ix < length; ix+=4)
    {
        float32x4_t a4 = vld1q_f32(a + ix);
        float32x4_t b4 = vld1q_f32(b + ix);
        out4 = vfmaq_f32(out4, a4, b4);  // first argument is the accumulator
    }

    f32 y0 = vgetq_lane_f32(out4, 0);
    f32 y1 = vgetq_lane_f32(out4, 1);
    f32 y2 = vgetq_lane_f32(out4, 2);
    f32 y3 = vgetq_lane_f32(out4, 3);

    return (y0 + y1 + y2 + y3);
}
