/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 4, Exercise 2: std::placeholders and std::bind
Compiled in C++ 20
*/

#include <iostream>
#include <functional>

double freeFunction3(double x, double y, double z)
{
    return x + y + z;
}

// Function of arity 2
auto function2 = std::bind(freeFunction3, std::placeholders::_1, std::placeholders::_2, 0.0);

// Function of arity 1
auto function1 = std::bind(freeFunction3, std::placeholders::_1, 0.0, 0.0);

// Function of arity 0
auto function0 = std::bind(freeFunction3, 0.0, 0.0, 0.0);

int main42()
{
    // Test function2 with appropriate variables
    double result2 = function2(1.0, 2.0);
    std::cout << "Result2: " << result2 << std::endl;

    // Test function1 with appropriate variables
    double result1 = function1(1.0);
    std::cout << "Result1: " << result1 << std::endl;

    // Test function0
    double result0 = function0();
    std::cout << "Result0: " << result0 << std::endl;
    return 0;
}