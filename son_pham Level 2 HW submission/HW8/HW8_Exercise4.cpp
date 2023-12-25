/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 8, Exercise 4: std::vector<bool> versus Bitset
*/

#include <bitset>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

namespace {
    std::vector<bool> intersect(const std::vector<bool>& vec1, const std::vector<bool>& vec2) {
        std::vector<bool> result;
        std::size_t size = std::min(vec1.size(), vec2.size());

        for (std::size_t i = 0; i < size; ++i) {
            result.push_back(vec1[i] && vec2[i]);
        }

        return result;
    }
}

int main84() {
    // a) Determine which functionalities that std::vector<bool> supports, compared to bitset
        // Flip operation
    std::vector<bool> vec{ true, false, true };
    vec.flip();
    std::cout << "Flipped vector: ";
    for (bool value : vec) {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    std::bitset<3> bs("101");
    bs.flip();
    std::cout << "Flipped bitset: " << bs << '\n';

    // XOR, OR, AND operations
    // std::vector<bool> does not support left shift or right shift

    // Construction from literals
    // std::vector<bool> does not support initialization directly from binary literals.
    // Though we can initialize from true and false value
    // std::vector<bool> vec4{ 0b101 };  // Doesn't work
    std::vector<bool> vec4{ true, false, true };
    std::cout << "Constructed vector from true and false values: ";
    for (bool value : vec4) {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    std::bitset<3> bs4(0b101);
    std::cout << "Constructed bitset from binary literal: " << bs4 << '\n';

    // In terms of general functionalities
    // * Size flexibility: std::vector<bool> allows dynamic resizing, meaning the size can be changed at runtime,
    //   while the size of a bitset is fixed at compile-time (though dynamic_bitset can vary in size).
    // * Contiguous storage: std::vector<bool> does not guarantee contiguous storage, which means the underlying
    //   storage can be fragmented. In contrast, bitsets store their bits in a contiguous block of memory.
    // * Iterators: std::vector<bool> provides standard iterators for iterating over its elements.
    //   Bitsets, on the other hand, do not have built-in iterators.

    // b) Create a function to compute the intersection of two instances std::vector<bool>.
    std::vector<bool> vec1{ true, false, true, true };
    std::vector<bool> vec2{ false, true, true, false };

    std::vector<bool> intersection = intersect(vec1, vec2);

    for (bool value : intersection) {
        std::cout << value << ' ';
    }

    // Yeah, bitset is overall superior to std::vector<bool>. The built iterator for std::vector<bool> is very
    // minimal in benefit because not many complicated storage and operation will be done with bools anyway.
    // The intersection implementation shows that mimicing bit set operations in std::vector<bool> is ugly
    // and inefficient.
    return 0;
}