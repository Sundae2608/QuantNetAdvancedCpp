/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 3, Exercise 4: C++14: Emulating deprecated C++ 98 STL Bind Code
*/

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

namespace {

    // Function maps Domain to Range
    template <typename R, typename D>
    using FunctionType = std::function<R(const D x)>;

    // Working function type
    using ScalarFunction = FunctionType<double, double>;

    // An fxy function that multiplies two number.
    double fxy(const double& x, const double& y)
    {
        return x * y;
    }

    // Bind first
    template <typename T>
    std::function<T(const T&)> bind1st(const std::function<T(const T& x, const T& y)>& f, const T& x_)
    {
        return [=](const T& y) {
            return f(x_, y);
        };
    }

    // Bind second
    template <typename T>
    std::function<T(const T&)> bind2nd(const std::function<T(const T& x, const T& y)>& f, const T& y_)
    {
        return [=](const T& x) {
            return f(x, y_);
        };
    }
}

int main34() {

    // Since yval = 10, fx effectively means return a value that is 10 times the input
    double yval = 10.0;
    ScalarFunction fx = bind2nd<double>(fxy, yval);
    std::cout << fx(3.0) << std::endl;  // 30.0

    // Test new bind code on STL algorithms
    std::vector<double> vec(10, 2.0);
    std::transform(vec.begin(), vec.end(), vec.begin(), fx);
    for (auto i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << ",";  // Ten values of 20.0 will be printed here.
    }
    return 0;
}