/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 4, Exercise 3: Function Wrapper and Bind
Compiled in C++ 20
*/

#include <iostream>
#include <functional>

template <typename T>
using FunctionType = std::function<T(const T& t)>;

template <typename T>
void print(const FunctionType<T>& f, T t)
{
    std::cout << f(t) << '\n';
}

class C
{
    // Function object with extra member functions
private:
    double _data;
public:
    C(double data) : _data(data) {}
    double operator () (double factor) {
        return _data + factor;
    }

    double translate(double factor) {
        return _data + factor;
    }

    double translate2(double factor1, double factor2) {
        return _data + factor1 + factor2;
    }

    static double Square(double x) {
        return x * x;
    }
};

int main43()
{
    // Create an instance of C
    C c(10.0);

    // Bind the function wrapper to C’s static member function.
    FunctionType<double> squareFunc = std::bind(& C::Square, std::placeholders::_1);
    std::cout << "SquareFunc: " << squareFunc(5.0) << std::endl;

    // Bind the function wrapper to C's member function using std::bind and placeholders
    auto translate = std::bind(&C::translate, c, std::placeholders::_1);
    auto translate2 = std::bind(&C::translate2, c, std::placeholders::_1, std::placeholders::_2);
    std::cout << "translate: " << translate(5.0) << std::endl;
    std::cout << "translate2: " << translate2(5.0, 6.0) << std::endl;

    // Bind the function operator() to C's member function using std::bind and placeholders
    auto opeartor = std::bind(&C::operator(), c, std::placeholders::_1);
    std::cout << "operator(): " << translate(5.0) << std::endl;
    return 0;
}