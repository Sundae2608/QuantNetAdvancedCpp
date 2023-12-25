/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 4, Exercise 5: Function Wrapper and Composition
Compiled in C++ 20
*/

#include <iostream>
#include <functional>

namespace {
    // Example code from the exercise
    template <typename T>
    using FunctionType = std::function<T(T)>;

    template <typename T>
    class NextGenPolymorphism
    {
    private:
        FunctionType<T> _func;
        T _fac;
    public:
        NextGenPolymorphism(const FunctionType<T>& function,
            const T& factor) : _fac(factor)
        {
            _func = function;
        }

        T execute(T d) { return _func(d) * _fac; }

        void switchFunction(const FunctionType<T>& function)
        {
            _func = function;
        }
    };

    // Rotate function type
    template <typename T>
    using RotateFunctionType = std::function<T(T)>;

    // Shape with a customized rotate function
    class Shape {

    public:
        Shape(double angle, const RotateFunctionType<double>& rotate_func) : angle_(angle), rotate_func_(rotate_func) { };

        void rotate(double angle) {
            angle_ += rotate_func_(angle);
        }

        double get_angle() {
            return angle_;
        }
    private:
        double angle_;
        RotateFunctionType<double> rotate_func_;
    };
}

int main45() {
    // Next gen stuff
    auto square = [](double d) {return d * d; };
    auto expo = [](double d) {return std::exp(d); };
    NextGenPolymorphism<double> ng(square, 1.0);
    std::cout << "Square: " << ng.execute(2.0) << std::endl; // 4

    // square is not cool, switch to expo
    ng.switchFunction(expo);
    std::cout << "Exponential: " << ng.execute(5.0) << std::endl;; // 148.413

    // Exercise call to the new Shape
    auto rotate_func = [](double angle) {
        std::cout << "Rotate angle " << angle << std::endl;
        return angle;
    };
    
    auto reverse_rotate_func = [](double angle) {
        std::cout << "Reverse rotate angle " << angle << std::endl;
        return -angle;
    };

    // Shape using normal rotate function
    Shape shape1(0, rotate_func);
    std::cout << "Old angle of shape 1: " << shape1.get_angle() << std::endl;
    shape1.rotate(10.0);
    std::cout << "New angle of shape 1: " << shape1.get_angle() << std::endl;

    Shape shape2(0, reverse_rotate_func);
    std::cout << "Old angle of shape 2: " << shape2.get_angle() << std::endl;
    shape2.rotate(10.0);
    std::cout << "New angle of shape 2: " << shape2.get_angle() << std::endl;

    return 0;
}