/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 4, Exercise 4: Function Wrapper and Inheritance
Compiled in C++ 20
*/

#include <iostream>
#include <functional>

namespace {
    using VoidFunctionType = std::function<void(double)>;

    // Class hierarchy
    class Shape
    {
    public:
        Shape(VoidFunctionType input_f) : f_(input_f) {};
        virtual void rotate(double d) {
            f_(d);
        };
    protected:
        // Input rotate function
        VoidFunctionType f_;
    };

    class Circle : public Shape
    {
    public:
        Circle(VoidFunctionType input_f) : Shape(input_f) {};
        void rotate(double d) override { 
            std::cout << "Overriding method will call rotate twice" << std::endl;
            f_(d);
            f_(d);
        }
    };

    using VoidFunctionType = std::function<void(double)>;
}

int main44()
{
    auto func = [](double d) {
        std::cout << "Rotate " << d << std::endl;
    };

    auto func2 = [](double d) {
        std::cout << "Reverse rotate " << d << std::endl;
    };

    Shape s(func);
    Circle c(func);
    s.rotate(10.0); // Rotate once;
    c.rotate(10.0); // Rotate twice;

    Shape s2(func2);
    Circle c2(func2);
    s2.rotate(10.0); // Reverse rotate once;
    c2.rotate(10.0); // Reverse rotate twice;
    return 0;
}