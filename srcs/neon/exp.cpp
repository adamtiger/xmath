#include "exp.hpp"
#include "arm_neon.h"

inline void _exponent(const f32* x, f32* y)
{
    f32 C_LOG2_EQ = C_LOG2_E * 0.25f;
    float32x4_t z = vmulq_f32(vld1q_f32(x), vdupq_n_f32(C_LOG2_EQ));

    int32x4_t is_z_neg = vreinterpretq_s32_u32(vcltq_f32(z, vdupq_n_f32(0)));

    int32x4_t zi0 = vsubq_s32(vcvtq_s32_f32(z), is_z_neg);
    float32x4_t z1 = vmulq_f32(vsubq_f32(z, vcvtq_f32_s32(zi0)), vdupq_n_f32(0.5f)); 

    zi0 = vmulq_s32(zi0, vsubq_s32(vdupq_n_s32(1), vmulq_s32(vdupq_n_s32(2), is_z_neg)));

    int32x4_t zi0_positive = vcgtq_s32(zi0, vdupq_n_s32(0));
    float32x4_t y0_pos = vcvtq_f32_s32(vshlq_s32(vdupq_n_s32(2), vsubq_s32(zi0, vdupq_n_s32(1))));
    float32x4_t y0 = vaddq_f32(
        vmulq_f32(y0_pos, vcvtq_f32_s32(zi0_positive)), 
        vsubq_f32(vdupq_n_f32(1.f), vcvtq_f32_s32(zi0_positive))
    );

    // taylor-series for the remainder
    float32x4_t xln2 = vmulq_f32(z1, vdupq_n_f32(C_LN_2));
    float32x4_t y1 = vaddq_f32(vmulq_f32(xln2, vdupq_n_f32(1.f / 5.f)), vdupq_n_f32(1.f));
    y1 = vaddq_f32(vmulq_f32(y1, vdupq_n_f32(1.f / 4.f)), vdupq_n_f32(1.f));
    y1 = vaddq_f32(vmulq_f32(y1, vdupq_n_f32(1.f / 3.f)), vdupq_n_f32(1.f));
    y1 = vaddq_f32(vmulq_f32(y1, vdupq_n_f32(1.f / 2.f)), vdupq_n_f32(1.f));
    y1 = vaddq_f32(vmulq_f32(y1, xln2), vdupq_n_f32(1.f));

    // integer and remainder, to form the final res.
    //y0 = y0 * (1.f - (f32)is_z_neg) + 1.f / y0 * (f32)is_z_neg;
    y0 = vaddq_f32(
        vmulq_f32(y0, vsubq_f32(vdupq_n_f32(1.f), vcvtq_f32_s32(is_z_neg))),
        vmulq_f32(vrecpeq_f32(y0), vcvtq_f32_s32(is_z_neg))
    );

    float32x4_t out = vmulq_f32(y0, vmulq_f32(y1, y1));
    out = vmulq_f32(out, out);
    out = vmulq_f32(out, out);

    vst1q_f32(y, out);
}

void exponent(const i32 length, const f32* x, f32* y)
{
    for (i32 ix = 0; ix < length; ix+=4)
    {
        _exponent(x + ix, y + ix);
    }
}
