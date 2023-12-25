/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 8, Exercise 3: Boost Dynamic Bitset 101
*/

#include <iostream>
#include <boost/dynamic_bitset.hpp>

int main83() {
    // a) Port the code that you created in questions 1 and 2 to boost::dynamic_bitset<T>. Test your code.
    boost::dynamic_bitset<> bs1(8, 0b10101010);
    boost::dynamic_bitset<> bs2(8, 0b11001100);

    std::cout << "bs1: " << bs1 << '\n';
    std::cout << "bs2: " << bs2 << '\n';

    bs1.flip();
    bs2.flip();

    std::cout << "bs1 (toggled): " << bs1 << '\n';
    std::cout << "bs2 (toggled): " << bs2 << '\n';

    boost::dynamic_bitset<> result_xor = bs1 ^ bs2;
    boost::dynamic_bitset<> result_or = bs1 | bs2;
    boost::dynamic_bitset<> result_and = bs1 & bs2;

    std::cout << "XOR: " << result_xor << '\n';
    std::cout << "OR: " << result_or << '\n';
    std::cout << "AND: " << result_and << '\n';

    bs1 >>= 1;
    bs2 <<= 2;

    std::cout << "bs1 (right shift): " << bs1 << '\n';
    std::cout << "bs2 (left shift): " << bs2 << '\n';

    // b) (Changing the size of a bitset at run-time). Apply resize(), clear(), 
    // push_back(), pop_back() and append() to bitset instances.
    boost::dynamic_bitset<> bs(8);

    std::cout << "Initial bitset: " << bs << '\n';

    bs.resize(12);          // Resize to 12 bits
    bs.clear();             // Clear all bits
    bs.push_back(true);     // Append a bit with value true
    bs.pop_back();          // Remove the last bit
    bs.append(0b1010);      // Append the binary value 1010 (4 bits)

    std::cout << "Final bitset: " << bs << '\n';

    // c) (Set operations). Test the functionality to test if a bitset is a subset (or proper subset) of another bitset.
    // To test if one boost::dynamic_bitset<T> is a subset or proper subset of another, you can use the is_subset_of 
    // and is_proper_subset_of member functions. Here's an example:
    boost::dynamic_bitset<> bs3(8, 0b11110000);
    boost::dynamic_bitset<> bs4(8, 0b11110000);

    bool isSubset = bs3.is_subset_of(bs4);
    bool isProperSubset = bs3.is_proper_subset_of(bs4);

    std::cout << std::boolalpha;
    std::cout << "bs3: " << bs3 << '\n';
    std::cout << "bs4: " << bs4 << '\n';
    std::cout << "Is bs3 a subset of bs4? " << isSubset << '\n';
    std::cout << "Is bs3 a proper subset of bs4? " << isProperSubset << '\n';

    // d) (Searching in bitsets). Use find_first() and find_next() to search for bits in bitsets.
    boost::dynamic_bitset<> bs5(8, 0b10101010);
    std::cout << "Bitset: " << bs5 << '\n';

    std::size_t firstSetBit = bs5.find_first();
    std::cout << "First set bit at index: " << firstSetBit << '\n';

    std::size_t nextSetBit = bs5.find_next(firstSetBit);
    std::cout << "Next set bit at index: " << nextSetBit << '\n';
    return 0;
}