#include "dot.hpp"

f32 dot_product(const i32 length, const f32* a, const f32* b)
{
    f32 acc = 0.f;
    for (i32 ix = 0; ix < length; ++ix)
    {
        acc += a[ix] * b[ix];
    }

    return acc;
}
