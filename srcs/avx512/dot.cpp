#include "dot.hpp"


f32 dot_product(const i32 length, const f32* a, const f32* b)
{
    __m512 out16 = _mm512_set1_ps(0.f);
    for (i32 ix = 0; ix < length; ix+=16)
    {
        __m512 a16 = _mm512_load_ps(a + ix);
        __m512 b16 = _mm512_load_ps(b + ix);
        out16 = _mm512_fmadd_ps(a16, b16, out16);
    }
    return _mm512_reduce_add_ps(out16);
}
