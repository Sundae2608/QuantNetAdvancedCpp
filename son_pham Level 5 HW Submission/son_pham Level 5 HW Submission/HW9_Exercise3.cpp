/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 9, Exercise 3
*/

#include <iostream>
#include <boost/signals2.hpp>

namespace {
    struct BootstrapCheck {
        // a) Implement this signal and combiner.
        typedef bool result_type;

        template <typename InputIterator>
        bool operator()(InputIterator first, InputIterator last) const {
            while (first != last) {
                if (!(*first))
                    return false;
                ++first;
            }
            return true;
        }
    };


    bool SlotReturningTrue() {
        return true;
    }

    bool SlotReturningFalse() {
        return false;
    }
}

int main93() {
    boost::signals2::signal<bool(), BootstrapCheck> sig;

    // b) Create three slots each returning true with the exception of the second slot.
    // Create slots
    sig.connect(&SlotReturningTrue);
    sig.connect(&SlotReturningFalse);
    sig.connect(&SlotReturningTrue);

    // Call the signal and use the combiner
    bool result = sig();

    // Print the result
    std::cout << "Signal result: " << std::boolalpha << result << std::endl;

    // c)
    // Signal result is false, because the signal connect and returns the first false
    // when combined. It will return true if all slots return true.
    return 0;
}