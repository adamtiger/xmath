#include "exp.hpp"

f64 exponent(const f64 x)
{
    return 0.0;
}

f32 exponent(const f32 x)
{
    f32 z = x * C_LOG2_E;

    i32 zi0 = static_cast<i32>(z);
    f32 z1 = (z - static_cast<f32>(zi0)) * 0.5f;

    f32 y0 = static_cast<f32>(2 << (zi0 - 1));

    // taylor-series for the remainder
    f32 xln2 = z1 * C_LN_2;
    f32 y1 = xln2 / 5.f + 1.f;
    y1 = y1 * xln2 / 4.f + 1.f;
    y1 = y1 * xln2 / 3.f + 1.f;
    y1 = y1 * xln2 / 2.f + 1.f;
    y1 = y1 * xln2 + 1.f;

    // integer and remainder, to form the final res.
    f32 y = y0 * y1 * y1;

    return y;
}
