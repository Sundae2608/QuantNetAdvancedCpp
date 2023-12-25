/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 3, Exercise 2: C++14: Using init Captures to move Objects into Closures
*/

#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

namespace {
    // Function maps Domain to Range
    template <typename R, typename D>
    using FunctionType = std::function<R(const D x)>;

    // Working function type
    using ScalarFunction = FunctionType<double, double>;

    // a) Create functions to add, multiply and subtract two functions. Create unary additive inverse of a 
    // function and a function representing scalar multiplication.

    // Addition of function
    template <typename R, typename D>
    FunctionType<R, D> operator + (const FunctionType<R, D>& f,
        const FunctionType<R, D>& g)
    {
        return [=](const D& x)
        {
            return f(x) + g(x);
        };
    }

    // Subtracting of functions
    template <typename R, typename D>
    FunctionType<R, D> operator - (const FunctionType<R, D>& f,
        const FunctionType<R, D>& g)
    {
        return [=](const D& x)
        {
            return f(x) - g(x);
        };
    }

    // Multiplication of functions
    template <typename R, typename D>
    FunctionType<R, D> operator * (const FunctionType<R, D>& f,
        const FunctionType<R, D>& g)
    {
        return [=](const D& x)
        {
            return f(x) * g(x);
        };
    }

    // Division of functions
    template <typename R, typename D>
    FunctionType<R, D> operator / (const FunctionType<R, D>& f,
        const FunctionType<R, D>& g)
    {
        return [=](const D& x)
        {
            return f(x) / g(x);
        };
    }

    // Additive inverse of function
    template <typename R, typename D>
    FunctionType<R, D> operator -(const FunctionType<R, D>& f)
    {
        // Unary additive inverse of a function
        return [=](const D& x) {
            return -f(x);
        };
    }

    // Composition of function
    template <typename R, typename D>
    FunctionType<R, D> operator << (const FunctionType<R, D>& f,
        const FunctionType<R, D>& g)
    {
        return [=](const D& x)
        {
            return f(g(x));
        };
    }
    template <typename R, typename D>
    FunctionType<R, D> operator*(double scalar, const FunctionType<R, D>& f)
    {
        // Scalar multiplication of a function
        return [=](const D& x) {
            return scalar * f(x);
        };
    }

    // b) Implement the following functions: cos, sin, tan, exp, log, abs and sqrt.
    template <typename R, typename D>
    FunctionType<R, D> cos(const FunctionType<R, D>& f)
    {
        return [=](const D& x) {
            return std::cos(f(x));
        };
    }

    template <typename R, typename D>
    FunctionType<R, D> sin(const FunctionType<R, D>& f)
    {
        return [=](const D& x) {
            return std::sin(f(x));
        };
    }

    template <typename R, typename D>
    FunctionType<R, D> tan(const FunctionType<R, D>& f)
    {
        return [=](const D& x) {
            return std::tan(f(x));
        };
    }

    template <typename R, typename D>
    FunctionType<R, D> exp(const FunctionType<R, D>& f)
    {
        return [=](const D& x) {
            return std::exp(f(x));
        };
    }

    template <typename R, typename D>
    FunctionType<R, D> log(const FunctionType<R, D>& f)
    {
        return [=](const D& x) {
            return std::log(f(x));
        };
    }

    template <typename R, typename D>
    FunctionType<R, D> abs(const FunctionType<R, D>& f)
    {
        return [=](const D& x) {
            return std::abs(f(x));
        };
    }

    template <typename R, typename D>
    FunctionType<R, D> sqrt(const FunctionType<R, D>& f)
    {
        return [=](const D& x) {
            return std::sqrt(f(x));
        };
    }

    // c) Finally, produce code that allows you to do the code given in the exericse.
    // This basically ask me to produce the min and max function
    template <typename R, typename D>
    FunctionType<R, D> min(const FunctionType<R, D>& f, const FunctionType<R, D>& g)
    {
        return [=](const D& x) {
            R f_x = f(x);
            R g_x = g(x);
            return f_x < g_x ? f_x : g_x;
        };
    }

    template <typename R, typename D>
    FunctionType<R, D> max(const FunctionType<R, D>& f, const FunctionType<R, D>& g)
    {
        return [=](const D& x) {
            R f_x = f(x);
            R g_x = g(x);
            return f_x > g_x ? f_x : g_x;
        };
    }
}  // namespace

int main33() {
    // Scalar functions: double to double
    std::cout << "Part 0: Scalar functions" << std::endl;
    ScalarFunction f = [](double x) {return x * x; };
    ScalarFunction g = [=](double x) { return x; };
    std::cout << g(2) << ", " << g(8) << std::endl;
    std::cout << std::endl;

    // Set a: Arithmetic functions
    std::cout << "Part a: Arithmetic functions" << std::endl;
    double scale = 2.0;
    auto fA = 2.0 * (f + g);
    auto fM = f - g;
    auto fD = f / g;
    auto fMul = f * g;
    auto fC = g << g << 4.0 * g; // Compose
    auto fMinus = -(f + g);

    double x = 5.0;

    std::cout << fA(x) << ", " << fM(x) << ", " << fD(x) << ", "
        << fMul(x) << ", compose: " << fC(x) << ", " << fMinus(x) << std::endl; // 2, 8*60, 20, 5, 125, compose: 20, -30
    std::cout << std::endl;

    // Set b: Triggonometric functions
    std::cout << "Part b: Trigonometric functions" << std::endl;
    auto ftmp = log(g);
    auto ftmp2 = cos(f);
    auto f2 = (abs(exp(g)) * log(g) + sqrt(ftmp)) / ftmp2;
    std::cout << f2(x) << std::endl;  // 242.262
    std::cout << std::endl;

    // Set b: Min and max
    std::cout << "Part c" << std::endl;
    auto h1 = min(f, g);
    auto h2 = max(f, g);
    std::cout << "min(f,g): " << h1(2.0) << std::endl;  // min(f,g): 2
    std::cout << "max(f,g): " << h2(2.0) << std::endl;  // max(f,g): 2
    auto h3 = min(h1, max(2 * f, 3 * g));
    auto h4 = max(h2, max(-2 * f, 3 * g));
    std::cout << "h3(2.0) " << h3(2.0) << std::endl;   // min(f,g): 2
    std::cout << "h4(2.0): " << h4(2.0) << std::endl;  // max(f,g): 6
    std::cout << std::endl;
    return 0;
}