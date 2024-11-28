#include "math.hpp"
#include <cmath>

int main()
{
    std::cout << "XMath implementations with intrinsics." << std::endl;

    f32 x = 15.48f;
    f32 y = logarithm(x);

    std::cout << "Expected: " << logf(x) << " - Actual: " << y << std::endl;

    return 0;
}
