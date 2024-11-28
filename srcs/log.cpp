#include "log.hpp"

f64 logarithm(const f64 x)
{
    return 0.0;
}

f32 logarithm(const f32 x)
{
    // calculate the highest log2 integer part
    // and the multiplier
    u32 exp_mask = 255;
    exp_mask = exp_mask << 23;
    const u32 x_u32 = *reinterpret_cast<const u32*>(&x); 

    u32 log2_x_int = x_u32 & exp_mask;
    f32 log2_x_float = *reinterpret_cast<f32*>(&log2_x_int);

    f32 x1 = x / log2_x_float;  // [1, 2)

    // calculate the logarithm for the remaining ratio
    x1 = x1 - 1.f;
    f32 y1 = -x1 / 6.f + 1.f / 5.f;
    y1 = y1 * x1 - 1.f / 4.f;
    y1 = y1 * x1 + 1.f / 3.f;
    y1 = y1 * x1 - 1.f / 2.f;
    y1 = y1 * x1 + 1.f;
    y1 = y1 * x1;

    f32 y0 = static_cast<f32>(i32(log2_x_int >> 23) - 127);
    f32 y = y0 * C_LN_2 + y1;
    return y;
}
