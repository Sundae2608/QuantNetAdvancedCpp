/*
* Advanced C++ and Modern Design
* Level 6 - Homework 6
* Author: Son Pham
* Main file testing functionality. As well as answers on advantages
* and disadvantages of two methods.
*/

#include "ApproximateDistance.h"
#include "ExactDistance.h"
#include "Point.h"
#include <iostream>

int main() {
    Point p1(1.0, 2.0);
    Point p2(4.0, 6.0);

    ExactDistance exactStrategy;
    ApproximateDistance approxStrategy;

    Point::SetDistanceStrategy(&exactStrategy);
    std::cout << "Exact Distance: " << p1.Distance(p2) << std::endl;

    Point::SetDistanceStrategy(&approxStrategy);
    std::cout << "Approximate Distance: " << p1.Distance(p2) << std::endl;

    std::cout << "Exact Distance (strategy inside function argument): "
        << p1.Distance(p2, exactStrategy) << std::endl;
    std::cout << "Approximate Distance (strategy inside function argument): "
        << p1.Distance(p2, approxStrategy) << std::endl;

    // Storing Strategy in Static Variable (Previous Method):
    // Advantages:
    // - Once set, the strategy remains consistent for all distance calculations.
    // - No need to pass the strategy as an argument to each distance calculation.
    // Disadvantages:
    // - Global state can be challenging to manage, especially in multi-threaded
    // environments and especially when the calculation has to juggle back and
    // forth between different types of calculation. (However, if that is the case,
    // then it is simply better to just have two different functions)
    // 
    // Passing Strategy as Method Argument
    // Advantages:
    // - Flexibility to use different strategies for different distance
    // calculations.
    // - No global state; each calculation can have its strategy.
    // Disadvantages:
    // - Requires passing the strategy explicitly each time, which can be
    // cumbersome. This leads to cumbersome duplication if the class is used multiple
    // times
    return 0;
}