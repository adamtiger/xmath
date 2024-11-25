#include "math.hpp"
#include <cmath>

int main()
{
    std::cout << "XMath implementations with intrinsics." << std::endl;

    f32 x = 6.8f;
    f32 y = exponent(x);

    std::cout << "Expected: " << expf(x) << " - Actual: " << y << std::endl;

    return 0;
}
