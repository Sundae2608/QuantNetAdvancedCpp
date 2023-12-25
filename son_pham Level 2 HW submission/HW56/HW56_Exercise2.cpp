/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 5/6, Exercise 2: Machine epsilon
*/

#include <iostream>
#include <limits>
#include <cmath>

namespace {
    // Epsilon for double
    double double_epsilon() {
        double epsilon = 1.0;
        while ((1.0 + 0.5 * epsilon) != 1.0)
        {
            epsilon *= 0.5;
        }
        return epsilon;
    }

    // Epsilon for float
    float float_epsilon() {
        float epsilon = 1.0f;
        while ((1.0f + 0.5f * epsilon) != 1.0f)
        {
            epsilon *= 0.5f;
        }
        return epsilon;
    }
}

int main52() {
    // a) Generalize this function for other types.
    // I am not sure what is meant here as "other types". I can only think of float as the only other types
    std::cout << "Double epsilon: " << double_epsilon() << std::endl;  // 2.22045e-16
    std::cout << "Float epsilon: " << float_epsilon() << std::endl;    // 1.19209e-07

    // b) Compare with std::numeric_limits<double>::epsilon()
    std::cout << "std::numeric_limits<double>::epsilon() = " << std::numeric_limits<double>::epsilon() << std::endl;  // 2.22045e-16
    std::cout << "std::numeric_limits<float>::epsilon() = " << std::numeric_limits<float>::epsilon() << std::endl;    // 1.19209e-07
    // They are exactly the same!
    return 0;
}