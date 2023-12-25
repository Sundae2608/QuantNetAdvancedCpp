/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 9, Exercise 4
*/

#include <iostream>
#include <boost/signals2.hpp>

namespace {
    double SlotMultiply(double x, double y) {
        return x * y;
    }

    double SlotAdd(double x, double y) {
        return x + y;
    }

    double SlotSubtract(double x, double y) {
        return x - y;
    }

    template <typename T>
    struct SumCombiner {
        typedef T result_type;

        template <typename InputIterator>
        T operator()(InputIterator first, InputIterator last) const {
            T sum = 0;
            while (first != last) {
                sum += *first;
                ++first;
            }
            return sum;
        }
    };
}

int main94() {
    boost::signals2::signal<double(double x, double y), SumCombiner<double>> sig;

    // Create slots
    sig.connect(&SlotMultiply);
    sig.connect(&SlotAdd);
    sig.connect(&SlotSubtract);

    // Call the signal and use the combiner
    double result = sig(5.0, 3.0);

    // Print the result
    std::cout << "Signal result: " << result << std::endl;

    // Signal result is 25
    // This is correct.
    // 5 * 3 = 15
    // 5 + 3 = 8
    // 5 - 3 = 2
    // The sum is 25

    return 0;
}