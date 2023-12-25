/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 5/6, Exercise 2: Machine Precision Issues
*/

#include <iostream>
#include <cmath>
#include <limits>
#include <boost/math/special_functions/next.hpp>

int main53() {
    double x = 0.1;

    // Next representable value that is greater than x
    double nextGreater = std::nextafter(x, std::numeric_limits<double>::infinity());
    std::cout << "Next representable value greater than " << x << ": " << nextGreater << std::endl;  // 0.1;

    // Next representable value that is less than x
    double nextLess = std::nextafter(x, -std::numeric_limits<double>::infinity());
    std::cout << "Next representable value less than " << x << ": " << nextLess << std::endl;  // 0.1;

    // Advance x by a specified number of ULP
    double advanced = boost::math::float_advance(x, 2);
    std::cout << "Advanced value of " << x << " by 2 ULP: " << advanced << std::endl;  // 0.1

    // Find the number of gaps/bits/ULP between two floating-point values
    double a = 0.1;
    double b = a + std::numeric_limits<double>::min() * 4;
    double c = boost::math::float_advance(a, 4);
    std::cout << "Number of ULP between " << a << " and " << b << ": " << boost::math::float_distance(a, b) << std::endl;  // 0
    std::cout << "Number of ULP between " << a << " and " << c << ": " << boost::math::float_distance(a, c) << std::endl;  // 4
    // Looks like adding min numeric limits doesn't work, while float advance works better.

    a = 1.0;
    b = 0.0;
    std::cout << "Number of ULP between " << a << " and " << b << ": " << boost::math::float_distance(a, b) << std::endl;  // 1.0
    // -4.60718e+18 steps between the two numbers.
    return 0;
}