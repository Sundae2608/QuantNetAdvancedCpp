/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 7: Compile-Time Fractional Arithmetic 101
*/

#include <iostream>
#include <ratio>

int main() {
	// a) Create a number of instances of std::ratio and print them.
    using R1 = std::ratio<3, 4>;
    using R2 = std::ratio<4, 5>;
    using R3 = std::ratio<5, 9>;

    // Print the ratios
    std::cout << "R1: " << R1::num << "/" << R1::den << std::endl;
    std::cout << "R2: " << R2::num << "/" << R2::den << std::endl;
    std::cout << "R3: " << R3::num << "/" << R3::den << std::endl;

    // b) Create two std::ratio instances; add, subtract, multiply, and divide them:
    // Create instances of std::ratio with different numerator and denominator values
    using R4 = std::ratio<2, 3>;
    using R5 = std::ratio<4, 5>;
    std::cout << "R4: " << R4::num << "/" << R5::den << std::endl;
    std::cout << "R5: " << R4::num << "/" << R5::den << std::endl;

    // Add the ratios
    using AddResult = std::ratio_add<R4, R5>;
    std::cout << "R4 + R5: " << AddResult::num << "/" << AddResult::den << std::endl;

    // Subtract the ratios
    using SubResult = std::ratio_subtract<R4, R5>;
    std::cout << "R4 - R5: " << SubResult::num << "/" << SubResult::den << std::endl;

    // Multiply the ratios
    using MulResult = std::ratio_multiply<R4, R5>;
    std::cout << "R4 * R5: " << MulResult::num << "/" << MulResult::den << std::endl;

    // Divide the ratios
    using DivResult = std::ratio_divide<R4, R5>;
    std::cout << "R4 / R5: " << DivResult::num << "/" << DivResult::den << std::endl;

    // This is a very interesting arithmetic class.
    return 0;
}