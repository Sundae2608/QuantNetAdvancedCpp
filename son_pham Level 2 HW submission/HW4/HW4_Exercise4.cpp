/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 4, Exercise 4: Smart Pointers and STL Algorithms
*/

#include <iostream>
#include <list>
#include <memory>

namespace {
    // Base class
    class Base
    {
    public:
        Base() { }
        virtual void print() const = 0;
        virtual ~Base() { std::cout << "Base destructor" << std::endl; }
    };

    // Derived class
    class Derived : public Base
    {
    public:
        Derived() : Base() { }
        ~Derived() { std::cout << "Derived destructor" << std::endl; }
        void print() const { std::cout << "derived object" << std::endl; }
    };

    // Factory function for derive
    std::shared_ptr<Base> createSharedDerived() {
        return std::make_shared<Derived>();
    }
    std::unique_ptr<Base> createUniqueDerived() {
        return std::make_unique<Derived>();
    }
}

int main44() {

    // a) Create a list of smart pointers to Base. In particular, 
    // test the above code with both shared and unique pointers.
    // Which option compiles and why does unique pointer not compile?
    std::list<std::shared_ptr<Base>> shared_list;
    std::list<std::unique_ptr<Base>> unique_list;

    // Add shared pointers to the list
    shared_list.push_back(std::make_shared<Derived>());

    // Add unique pointer to the list
    unique_list.push_back(std::make_unique<Derived>());

    // This actually works for me. I am not sure why the exercise implies that
    // unique_list pushing back does not work.

    // b) Create a factory function to create instances of Derived and then add them to the list.
    shared_list.push_back(createSharedDerived());
    unique_list.push_back(createUniqueDerived());

    // This works and there are no memory leaks
    return 0;
}