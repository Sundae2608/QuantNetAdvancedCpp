/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 4, Exercise 4: Variadic Hash
*/
#include <iostream>
#include <boost/functional/hash.hpp>

namespace {
    template <typename T>
    void hash_value(std::size_t& seed, const T& val)
    {
        boost::hash_combine(seed, val);
    }

    template <typename T, typename... Types>
    void hash_value(std::size_t& seed, const T& val, const Types&... args)
    {
        boost::hash_combine(seed, val);
        hash_value(seed, args...);
    }

    template <typename... Types>
    std::size_t hash_value(const Types&... args)
    {
        std::size_t seed = 0;
        hash_value(seed, args...);
        return seed;
    }

    struct Point {
        double x;
        double y;

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };
}

namespace boost {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& pt) const {
            size_t seed = 0;
            boost::hash_combine(seed, pt.x);
            boost::hash_combine(seed, pt.y);
            return seed;
        }
    };
}

int main44() {
    // a) Create a hash function using a seed
    std::size_t seed = 0;
    hash_value(seed, 42, "Hello, World!", 3.14);

    std::cout << "Hash value: " << seed << std::endl;


    // b) Create a generic auxiliary function to create a hash value from a
    // heterogeneous list of arguments (in this case the seed is initialised to zero)
    Point p = { 1.0, 2.0 };
    std::string str = "Hello, World!";
    int intValue = 42;

    std::size_t hash1 = hash_value(p, str, intValue);
    std::size_t hash2 = hash_value(3.14, p, str);

    std::cout << "Hash 1: " << hash1 << std::endl;
    std::cout << "Hash 2: " << hash2 << std::endl;
    return 0;
}