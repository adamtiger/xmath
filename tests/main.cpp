#include "math.hpp"
#include <cmath>

static void fill_array(const f32 vmin, const f32 vmax, const i32 length, f32* arr)
{
    std::default_random_engine eng;
    std::uniform_real_distribution<f32> uni_distr(vmin, vmax);

    for (i32 ix = 0; ix < length; ++ix)
    {
        arr[ix] = uni_distr(eng);
    }
}

void test_logarithm()
{
    constexpr i32 length = 64;
    f512 x_aligned[length / 16];
    f512 y_aligned[length / 16];
    f32* x = reinterpret_cast<f32*>(x_aligned);
    f32* y = reinterpret_cast<f32*>(y_aligned);
    fill_array(0.7f, 50.f, length, x);

    logarithm(length, x, y);

    for (i32 ix = 0; ix < length; ++ix)
    {
        std::cout << "Index: " << ix << " - Expected: " << logf(x[ix]) << " - Actual: " << y[ix] << " - Value: " << x[ix] << std::endl;
    }
}


void test_dotproduct()
{
    constexpr i32 length = 64;
    f512 a_aligned[length / 16];
    f512 b_aligned[length / 16];
    f32* a = reinterpret_cast<f32*>(a_aligned);
    f32* b = reinterpret_cast<f32*>(b_aligned);
    fill_array(-50.f, 50.f, length, a);
    fill_array(-50.f, 50.f, length, b);

    f32 actual = dot_product(length, a, b);

    f32 expected = 0.f;
    for (i32 ix = 0; ix < length; ++ix)
    {
        expected += a[ix] * b[ix];
    }

    std::cout << "Expected: " << expected << " - Actual: " << actual << std::endl;
}


int main()
{
    std::cout << "XMath implementations with intrinsics." << std::endl;

    test_dotproduct();
    
    return 0;
}
