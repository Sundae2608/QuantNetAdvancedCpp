/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 1, Exercise 2: Simple switchable Bridge Functionality
*/

#include <iostream>
#include <type_traits>

namespace {
    // Helper function to determine if a type is a pointer
    template<typename T>
    constexpr bool is_pointer() {
        return std::is_pointer<T>::value;
    }

    // Helper function to determine if a type is a reference
    template<typename T>
    constexpr bool is_reference() {
        return std::is_reference<T>::value;
    }

    // Helper function to remove reference and cv qualifiers
    template<typename T>
    using decay_t = typename std::decay<T>::type;

    // Print value for non-pointer reference types
    template<typename T>
    void printValueImpl(T value, std::false_type) {
        std::cout << value << std::endl;
    }

    // Print value for pointer types
    template<typename T>
    void printValueImpl(T value, std::true_type) {
        std::cout << *value << std::endl;
    }

    // Template function to print values, handles pointers and reference types separately
    template<typename T>
    void printValue(T&& value) {
        if constexpr (is_pointer<std::decay_t<T>>()) {
            printValueImpl(value, std::true_type{});
        }
        else {
            printValueImpl(value, std::false_type{});
        }
    }
}

int main12() {
    int x = 5;
    int* ptr = &x;
    int& ref = x;

    printValue(ptr);  // Dereferences and prints the value: 5
    printValue(&x);   // Dereferences and prints the value: 5
    printValue(ref);  // Prints the value directly: 5

    return 0;
}