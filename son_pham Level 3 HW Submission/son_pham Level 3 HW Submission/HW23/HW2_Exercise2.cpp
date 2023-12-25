/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 2, Exercise 2: Smart Races with Smart Pointers
*/

#include <chrono>
#include <random>
#include <thread>
#include <iostream>
#include <thread>

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

    void Modify(PointerType& p, double newVal) {
        // Wait a while, long enough to trigger the race
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(100, 1000); // Range for delay in milliseconds

        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen))); // Introduce random delay
        p->val = newVal;
        std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen))); // Introduce random delay between value and print
        std::cout << "New val: " << p->val << std::endl;
    }
}

int main22() {

    // b) Create an array of 100 threads, fire each one up (each one has thread function Modify() 
    // and a given value that will be the new value of the instance of PointerType).
    const int numThreads = 100;
    std::thread threads[numThreads];
    PointerType x = std::make_shared<X>();
    x->val = 1.0;

    for (int i = 0; i < numThreads; ++i) {
        double newValue = i; // Specify the new value for each thread. We we simply uses the i values.
        threads[i] = std::thread(Modify, std::ref(x), newValue);
    }

    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // c) The following is a copy results of one run
    // I notice that not only is the ordering of operation is undeterministic, sometimes they
    // even overlap each other. The value is sometimes modified by other thread even before
    // the next thread gets called. This is proven by the fact that "New val: 42" appears 
    // a lot at the end, which is basically a series of print statement got backlogged, and
    // that duplicated print also happens very occasionally, due to the value being modified
    // by other threads.
    //New val : 81
    //New val : 26
    //New val : 87
    //New val : 62
    //New val : 38
    //New val : 12
    //New val : 23
    //New val : 85
    //New val : 77
    //New val : 72
    //New val : 91
    //New val : 61
    //New val : 59
    //New val : 28
    //New val : 14
    //New val : 24
    //New val : 80
    //New val : 37
    //New val : 41
    //New val : 99
    //New val : 4
    //New val : 47
    //New val : 66
    //New val : 49
    //New val : 49
    //New val : 68
    //New val : 30
    //New val : 75
    //New val : 27
    //New val : 27
    //New val : 95
    //New val : 20
    //New val : 21
    //New val : 55
    //New val : 32
    //New val : 53
    //New val : 56
    //New val : 15
    //New val : 69
    //New val : 39
    //New val : 63
    //New val : 51
    //New val : 96
    //New val : 67
    //New val : 16
    //New val : 0
    //New val : 86
    //New val : 64
    //New val : 88
    //New val : 92
    //New val : 50
    //New val : 1
    //New val : 74
    //New val : 43
    //New val : 8
    //New val : 52
    //New val : 60
    //New val : 44
    //New val : 22
    //New val : 84
    //New val : 10
    //New val : 46
    //New val : 7
    //New val : 65
    //New val : 9
    //New val : 76
    //New val : 83
    //New val : 33
    //New val : 78
    //New val : 18
    //New val : 2
    //New val : 31
    //New val : 97
    //New val : 11
    //New val : 3
    //New val : 42
    //New val : 6
    //New val : 79
    //New val : 5
    //New val : 90
    //New val : 40
    //New val : 13
    //New val : 25
    //New val : 71
    //New val : 58
    //New val : 94
    //New val : 17
    //New val : 48
    //New val : 34
    //New val : 36
    //New val : 93
    //New val : 57
    //New val : 82
    //New val : 35
    //New val : 70
    //New val : 98
    //New val : 54
    //New val : 19
    //New val : 89
    //New val : 29
    return 0;
}