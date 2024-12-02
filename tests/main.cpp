#include "math.hpp"
#include <cmath>

int main()
{
    std::cout << "XMath implementations with intrinsics." << std::endl;

    f32 x = 19.54f;
    f32 y = logarithm(x);

    std::cout << "Expected: " << logf(x) << " - Actual: " << y << std::endl;


    f32x16 z;
    z.data[0] = 2.89f;
    z.data[1] = 45.789f;
    f32x16 w = logarithm(z);

    std::cout << "Expected: " << logf(z.data[0]) << " - Actual: " << w.data[0] << std::endl;
    std::cout << "Expected: " << logf(z.data[1]) << " - Actual: " << w.data[1] << std::endl;

    return 0;
}
