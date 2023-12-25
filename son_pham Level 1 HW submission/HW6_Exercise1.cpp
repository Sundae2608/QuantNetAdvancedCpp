/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 6, Exercise 1: Using Sealed Classes and Sealed Member Functions
Compiled in C++ 20
*/

#include <iostream>
#include <memory>

struct Base
{
    virtual void draw() { std::cout << "print a base\n"; }
    virtual void print() {}
    ~Base() { std::cout << "bye base\n"; }
};

struct Derived final : public Base
{
    Derived() {}
    void draw() override { std::cout << "print a derived\n"; }
    void print() override { std::cout << "print function\n"; }
    ~Derived() { std::cout << "bye derived\n"; }
};

int main61() {
    
    std::unique_ptr<Derived> ptr = std::make_unique<Derived>();
    ptr->draw();
    ptr->print();
    return 0;
}