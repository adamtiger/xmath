#include "log.hpp"
#include "device.hpp"

inline void _logarithm(const f32* x, f32* y)
{
    // load the next 16 elements
    __m512 x16 = _mm512_load_ps(x);

    // calculate the highest log2 integer part
    // and the multiplier
    i32 exp_mask = 255;
    exp_mask = exp_mask << 23;
    __m512i emi16 = _mm512_set1_epi32(exp_mask);
    __m512i xi16 = _mm512_castps_si512(x16);

    __m512i log2_xi16 = _mm512_and_epi32(xi16, emi16);
    __m512 log2_x16 = _mm512_castsi512_ps(log2_xi16);

    __m512 x1 = _mm512_div_ps(x16, log2_x16);  // [1, 2)

    // calculate the logarithm for the remaining ratio
    // approximation (https://stackoverflow.com/questions/9799041/efficient-implementation-of-natural-logarithm-ln-and-exponentiation)
    // -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x
    // with Remez-algorithm or similar, this can be even better
    __m512 y1 = _mm512_sub_ps(_mm512_set1_ps(0.44717955f), _mm512_mul_ps(_mm512_set1_ps(0.056570851f), x1));
    y1 = _mm512_add_ps(_mm512_set1_ps(-1.4699568f), _mm512_mul_ps(y1, x1));
    y1 = _mm512_add_ps(_mm512_set1_ps(2.8212026f), _mm512_mul_ps(y1, x1));
    y1 = _mm512_add_ps(_mm512_set1_ps(-1.7417939f), _mm512_mul_ps(y1, x1));

    __m512 y0 = _mm512_cvt_roundepi32_ps(
        _mm512_sub_epi32(
            _mm512_srli_epi32(log2_xi16, 23), 
            _mm512_set1_epi32(C_F32_BIAS)
        ), (_MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC)
    ); 

    __m512 y16 = _mm512_add_ps(_mm512_mul_ps(y0, _mm512_set1_ps(C_LN_2)), y1);
    
    _mm512_store_ps(y, y16);
}

void logarithm(const i32 length, const f32* x, f32* y)
{
    for (int ix = 0; ix < length; ix+=16)
    {
        _logarithm(x + ix, y + ix);
    }
}
