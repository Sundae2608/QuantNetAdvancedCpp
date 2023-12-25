/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 3, Exercise 5: Generating ‘random’ Bitsets
*/

#include <bitset>
#include <chrono>
#include <iostream>
#include <random>

namespace {

    static int64_t totalSetBits = 0;

    // Function to test independent_bits_engine functionality
    template <int NumBits>
    void testBitsEngine(int numTests) {

        std::mt19937 mt_eng(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());

        using BitsEngine = std::independent_bits_engine<std::mt19937, NumBits, unsigned long long>;
        BitsEngine bits_eng(mt_eng());

        int totalSetBits = 0;

        for (int i = 0; i < numTests; ++i) {
            unsigned long long randomValue = bits_eng();
            std::bitset<NumBits> bitset(randomValue);

            int setBitsCount = bitset.count();
            totalSetBits += setBitsCount;
        }

        double averageSetBits = static_cast<double>(totalSetBits) / numTests;
        std::cout << "Engine with " << NumBits << " bits:" << std::endl;
        std::cout << "Average number of set bits: " << averageSetBits << std::endl;
        std::cout << "Total set bits: " << totalSetBits << std::endl;
        std::cout << "Number of Runs: " << numTests << std::endl;
    }
} // namespace

int main35() {
    // a) Create an instance of independent_bits_engine with a given random number
    // engine, number of desired bits and integer types. Call the constructor with
    // a suitable seed as argument. For example, the seed could be user-defined or
    // from the std::chrono high-resolution clock. Display the generated value as
    // an integer and as a bitset.
    // Define the random number engine and seed it
    std::mt19937 mt_eng(
        std::chrono::high_resolution_clock::now().time_since_epoch().count());

    // Define the independent_bits_engine with width = 8
    using BitsEngine8 =
        std::independent_bits_engine<std::mt19937, 8, unsigned long long>;

    // Create an instance of the independent_bits_engine
    BitsEngine8 bits_eng(mt_eng());

    // Generate a random number and display it as an integer and bitset
    unsigned long long randomValue = bits_eng();
    std::cout << "Generated value: " << static_cast<int>(randomValue)
        << std::endl;
    std::cout << "Generated value as bitset: " << std::bitset<8>(randomValue)
        << std::endl;

    // b) Create a function to test this functionality in the following way; take
    // the width = 2, generate a random number using independent_bits_engine and
    // then use this number to create a bitset. Determine how many bits have been
    // set in this bitset (use member function count()) and add the number to a
    // running counter. Then call the function a large number of times. Do you get
    // a value in the region of 50%?
    int numTests = 1000000; // Large number of tests
    testBitsEngine<2>(numTests);

    double averageSetBits = static_cast<double>(totalSetBits) / numTests;
    std::cout << "Average number of set bits: " << averageSetBits << std::endl;

    // c) Experiment with width = 8, 16 and 64. How many trials are needed to
    // arrive at 50% of outcomes equal to 1?
    testBitsEngine<8>(numTests);
    testBitsEngine<16>(numTests);
    testBitsEngine<64>(numTests);

    // This program will print the following:
    // Generated value : 225
    // Generated value as bitset : 11100001
    // Engine with 2 bits :
    // Average number of set bits : 0.99949
    // Total set bits : 999490
    // Number of Runs : 1000000
    // Average number of set bits : 0
    // Engine with 8 bits :
    // Average number of set bits : 3.99834
    // Total set bits : 3998344
    // Number of Runs : 1000000
    // Engine with 16 bits :
    // Average number of set bits : 7.9995
    // Total set bits : 7999498
    // Number of Runs : 1000000
    // Engine with 64 bits :
    // Average number of set bits : 32.0024
    // Total set bits : 32002362
    // Number of Runs : 1000000
    //
    // In all 4 cases of 2 bits, 8 bits, 16 bits, 64 bits, the number of bits set
    // are very close to 50%.
    return 0;
}