/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 4, Exercise 1: Hash 101
*/

#include <boost/functional/hash.hpp>
#include <functional>
#include <iostream>
#include <string>
#include <limits>

namespace {
    // a) Create two generic functions to hash arbitrary data types using Boost and C++11.
    template <typename T>
    std::size_t hashUsingBoost(const T& value) {
        boost::hash<T> hasher;
        return hasher(value);
    }

    template <typename T>
    std::size_t hashUsingCpp11(const T& value) {
        std::hash<T> hasher;
        return hasher(value);
    }
}

int main41() {
    // b) Test the functions using integers, strings, pointers, std::numeric_limits<long>::max().
    // Test with integers
    int intValue = 42;
    std::cout << "Hash using Boost: " << hashUsingBoost(intValue) << std::endl;
    std::cout << "Hash using C++11: " << hashUsingCpp11(intValue) << std::endl;

    // Test with strings
    std::string stringValue = "Hello, World!";
    std::cout << "Hash using Boost: " << hashUsingBoost(stringValue) << std::endl;
    std::cout << "Hash using C++11: " << hashUsingCpp11(stringValue) << std::endl;

    // Test with pointers
    int* ptrValue = &intValue;
    std::cout << "Hash using Boost: " << hashUsingBoost(ptrValue) << std::endl;
    std::cout << "Hash using C++11: " << hashUsingCpp11(ptrValue) << std::endl;

    // Test with std::numeric_limits<long>::max()
    long maxValue = std::numeric_limits<long>::max();
    std::cout << "Hash using Boost: " << hashUsingBoost(maxValue) << std::endl;
    std::cout << "Hash using C++11: " << hashUsingCpp11(maxValue) << std::endl;

    // c) Create two hashes h1 and h2 of two strings and then compute h1 ^ (h2 << 1).
    std::string str1 = "Hello";
    std::string str2 = "World";

    std::size_t h1 = hashUsingBoost(str1);
    std::size_t h2 = hashUsingBoost(str2);

    std::size_t result = h1 ^ (h2 << 1);

    std::cout << "h1: " << h1 << std::endl;
    std::cout << "h2: " << h2 << std::endl;
    std::cout << "Result: " << result << std::endl;

    // They are all different from eachother, which is the point of this.
    return 0;
}