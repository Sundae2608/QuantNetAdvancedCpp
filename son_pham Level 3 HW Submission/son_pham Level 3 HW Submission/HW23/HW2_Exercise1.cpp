/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 2, Exercise 1: Atomic Operations on Shared Pointers
*/

#include <iostream>

namespace {
    struct X
    {
        double val;

        X() : val(0.0) {}
        void operator ()() {
            std::cout << "An X " << val << std::endl;
        }
    };

    // C++11
    template <typename T>
    using GenericPointerType = std::shared_ptr<T>;
    using PointerType = GenericPointerType<X>;
}

int main21() {
    // a) Create an instance x of class PointerType and give it a value.
    PointerType x = std::make_shared<X>();
    x->val = 3.14;

    // b) Create a second instance x2 and atomically store it value in x.
    PointerType x2 = std::make_shared<X>();
    x2->val = 2.71;

    // std::atomic_store(&x, x2);  // This seems to be deprecated in C++ 20

    // c) Create an instance x3and exchange it with both xand x2.
    PointerType x3 = std::make_shared<X>();
    x3->val = 1.23;

    // PointerType oldX = std::atomic_exchange(&x, x3);   // Deprecated in C++ 20
    // PointerType oldX2 = std::atomic_exchange(&x2, x3); // Deprecated in C++ 20

    // d) Keep tabs on the use count of these instances.
    std::cout << "x use count: " << x.use_count() << std::endl;
    std::cout << "x2 use count: " << x2.use_count() << std::endl;
    std::cout << "x3 use count: " << x3.use_count() << std::endl;

    // e) Why is atomic<std::shared_ptr> not possible ?
    // I am not sure what the exercise means by this. My following code clearly shows that it is possible.
    // Perhaps this is implying that this intiialiation is moot and it won't work in a way that std::atomic
    // expects.
    // For this, I theorize that this is because shared_ptr is not a pointer, but actually has a memory
    // operation which keeps track of the count. Because of this, the operations on shared_ptr is not atomic.
    // Threads accessing shared ptr can mangle the shared count if order of operations overlap in undesirable
    // way.
    //
    // Though it seems that C++ has now supported it.
    std::atomic<std::shared_ptr<X>> atomic_shared_ptr(std::make_shared<X>());

    // f) Are shared pointers lock - free ?
    std::cout << std::boolalpha;
    std::cout << "Atomic int is lock-free: " << atomic_shared_ptr.is_lock_free() << std::endl;
    return 0;
}