#include "log.hpp"
#include "arm_neon.h"


inline void _logarithm(const f32* x, f32* y)
{
    // load the next 16 elements
    float32x4_t x4 = vld1q_f32(x);

    // calculate the highest log2 integer part
    // and the multiplier
    i32 exp_mask = 255;
    exp_mask = exp_mask << 23;

    int32x4_t emi4 = vld1q_dup_s32(&exp_mask);
    int32x4_t xi4 = vreinterpretq_s32_f32(x4);

    int32x4_t log2_xi4 = vandq_s32(xi4, emi4);
    float32x4_t log2_x4 = vreinterpretq_f32_s32(log2_xi4);

    float32x4_t x1 = vmulq_f32(x4, vrecpeq_f32(log2_x4));

    // calculate the logarithm for the remaining ratio
    // approximation (https://stackoverflow.com/questions/9799041/efficient-implementation-of-natural-logarithm-ln-and-exponentiation)
    // -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x
    // with Remez-algorithm or similar, this can be even better
    f32 e0 = -1.7417939f;
    f32 e1 = 2.8212026f;
    f32 e2 = -1.4699568f;
    f32 e3 = 0.44717955f;
    f32 e4 = 0.056570851f;

    float32x4_t y1 = vsubq_f32(vld1q_dup_f32(&e3), vmulq_f32(vld1q_dup_f32(&e4), x1));
    y1 = vaddq_f32(vld1q_dup_f32(&e2), vmulq_f32(y1, x1));
    y1 = vaddq_f32(vld1q_dup_f32(&e1), vmulq_f32(y1, x1));
    y1 = vaddq_f32(vld1q_dup_f32(&e0), vmulq_f32(y1, x1));
    
    float32x4_t y0 = vcvtq_f32_s32(
        vsubq_s32(
            vshrq_n_s32(log2_xi4, 23), vld1q_dup_s32(&C_F32_BIAS)
        )
    );

    float32x4_t y4 = vaddq_f32(vmulq_f32(y0, vld1q_dup_f32(&C_LN_2)), y1);

    // __m512 y16 = _mm512_add_ps(_mm512_mul_ps(y0, _mm512_set1_ps(C_LN_2)), y1);
    
    vst1q_f32(y, y4);
}

void logarithm(const i32 length, const f32* x, f32* y)
{
    for (int ix = 0; ix < length; ix+=4)
    {
        _logarithm(x + ix, y + ix);
    }
}
