#include "log.hpp"

inline f32 _logarithm(const f32 x)
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
    // Taylor-series (not accurate enough)
    // x1 = x1 - 1.f;
    // f32 y1 = -x1 / 6.f + 1.f / 5.f;
    // y1 = y1 * x1 - 1.f / 4.f;
    // y1 = y1 * x1 + 1.f / 3.f;
    // y1 = y1 * x1 - 1.f / 2.f;
    // y1 = y1 * x1 + 1.f;
    // y1 = y1 * x1;

    // calculate the logarithm for the remaining ratio
    // approximation (https://stackoverflow.com/questions/9799041/efficient-implementation-of-natural-logarithm-ln-and-exponentiation)
    // -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x
    // with Remez-algorithm or similar, this can be even better
    f32 y1 = 0.44717955f - 0.056570851f * x1;
    y1 = -1.4699568f + y1 * x1;
    y1 = 2.8212026f + y1 * x1;
    y1 = -1.7417939f + y1 * x1;

    f32 y0 = static_cast<f32>(i32(log2_x_int >> 23) - 127);
    f32 y = y0 * C_LN_2 + y1;
    return y;
}

void logarithm(const i32 length, const f32* x, f32* y)
{
    for (int ix = 0; ix < length; ++ix)
    {
        y[ix] = _logarithm(x[ix]);
    }
}
