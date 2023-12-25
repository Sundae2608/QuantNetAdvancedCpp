/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 4, Exercise 3: The deprecated Smart Pointer std::auto_ptr
*/

#include <iostream>
#include <memory>

int main43() {
    //// Define auto_ptr pointers instead of raw pointers
    //std::auto_ptr <double> d(new double(1.0));

    //// Dereference
    //*d = 2.0;

    //// Change ownership of auto_ptr
    //// (after assignment, d is undefined)
    //std::auto_ptr<double>d2 = d;
    //*d2 = 3.0;

    //std::cout << "Auto values: " << *d.get() << ", " << *d2.get();  
    
    // This code freezes for a bit before giving me runtime error
    // t gives a runtime error because after the ownership is transferred
    // from d to d2 using assignment (auto_ptr<double> d2 = d;), both d and d2
    // end up owning the same pointer. This violates the ownership semantics
    // of unique ownership that should be maintained by smart pointers
    // Accessing the pointer through either d or d2 results in undefined behavior.

    std::unique_ptr<double> d = std::make_unique<double>(1.0);

    *d = 2.0;

    std::unique_ptr<double> d2 = std::move(d);
    *d2 = 3.0;

    std::cout << "Unique pointer values: " << *d2 << std::endl;  // 3
    return 0;
}