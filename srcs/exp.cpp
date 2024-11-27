#include "exp.hpp"

f64 exponent(const f64 x)
{
    return 0.0;
}

f32 exponent(const f32 x)
{
    f32 z = x * C_LOG2_E * 0.25f;

    i32 is_z_neg = static_cast<i32>(z < 0);

    i32 zi0 = (static_cast<i32>(z) - is_z_neg);
    f32 z1 = (z - static_cast<f32>(zi0)) * 0.5f;
    zi0 = zi0 * (1 - 2 * is_z_neg);

    f32 y0 = static_cast<f32>(2 << (zi0 - 1));

    // taylor-series for the remainder
    f32 xln2 = z1 * C_LN_2;
    f32 y1 = xln2 / 5.f + 1.f;
    y1 = y1 * xln2 / 4.f + 1.f;
    y1 = y1 * xln2 / 3.f + 1.f;
    y1 = y1 * xln2 / 2.f + 1.f;
    y1 = y1 * xln2 + 1.f;

    // integer and remainder, to form the final res.
    y0 = y0 * (1.f - (f32)is_z_neg) + 1.f / y0 * (f32)is_z_neg;

    f32 y = y0 * y1 * y1;
    y = y * y;
    y = y * y;

    return y;
}
