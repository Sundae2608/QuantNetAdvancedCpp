/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 4, Exercise 5
*/

#include <iostream>
#include <unordered_set>
#include <boost/functional/hash.hpp>

namespace {
    struct S {
        std::string f;
        std::string s;

        S(const std::string& s1, const std::string& s2) : f(s1), s(s2) {}
    };

    class SHash {
    public:
        std::size_t operator()(const S& s) const {
            std::size_t seed = 0;
            boost::hash_combine(seed, s.f);
            boost::hash_combine(seed, s.s);
            return seed;
        }
    };

    class SEqual {
    public:
        bool operator()(const S& lhs, const S& rhs) const {
            return (rhs.f == lhs.f && rhs.s == lhs.s);
        }
    };
}

int main46() {
    std::unordered_set<S, SHash, SEqual> mySet;

    // Add elements to the unordered set
    mySet.emplace("first", "one");
    mySet.emplace("second", "two");
    mySet.emplace("third", "three");

    // Examine the bucket information
    std::cout << "Bucket information:" << std::endl;
    for (std::size_t i = 0; i < mySet.bucket_count(); ++i) {
        std::cout << "Bucket " << i << ": " << mySet.bucket_size(i) << " elements" << std::endl;
    }

    return 0;
}