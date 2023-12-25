/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 3, Exercise 3: Do the STL Shuffle
*/

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

namespace {
    // Function to print the order (original or shuffled)
    void PrintOrder(const std::vector<int>& nums, const std::string& orderType) {
        std::cout << orderType << " order: ";
        for (int num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

} // namespace

int main33() {
    // a) Create a large vector of integers. Shuffle the order of elements using
    // random_shuffle() which has two forms; the first shuffles the elements using
    // an implementation-dependent random-number generator (typically rand()) ;
    // the second form has an extra argument that is a function (with a single
    // input parameter) that returns a random number, using rand() or one of C++11
    // random number engine such as:
    // User-defined random number generator
    // mt19937
    // default_random_engine
    // linear_congruential_engine.
    // Implement the second form using rand() and each of these generators.
    // TODO: This might need a rdo, as there is still a bug involved in
    // the linear_congruential_engine. It kind of doesn't make sense that there is
    // a bug here.
    std::vector<int> nums(20);
    for (int i = 0; i < 10; ++i) {
        nums[i] = i + 1;
    }

    PrintOrder(nums, "Original");

    // Random device for seed
    std::random_device rd;

    // // Shuffling using rand()
    // std::random_shuffle(nums.begin(), nums.end());
    // PrintOrder(nums, "Random Shuffled");

    // // Shuffling using mt19937 engine (std::random_shuffle)
    std::mt19937 mt_eng(rd());
    // std::random_shuffle(nums.begin(), nums.end(), mt_eng);
    // PrintOrder(nums, "Random Shuffled (mt19937)");

    // // Shuffling using default_random_engine (std::random_shuffle)
    std::default_random_engine def_eng(rd());
    // std::random_shuffle(nums.begin(), nums.end(), def_eng);
    // PrintOrder(nums, "Random Shuffled (default_random_engine)");

    // // Shuffling using linear_congruential_engine (std::random_shuffle)
    std::linear_congruential_engine<uint32_t, 16807, 0, 2147483647> lc_eng;
    // std::random_shuffle(nums.begin(), nums.end(), lc_eng);
    // PrintOrder(nums, "Random Shuffled (linear_congruential_engine)");

    // b) Use std::shuffle
    // Shuffling using mt19937 engine (std::shuffle)
    std::shuffle(nums.begin(), nums.end(), mt_eng);
    PrintOrder(nums, "Shuffled (mt19937)");

    // Shuffling using default_random_engine (std::shuffle)
    std::shuffle(nums.begin(), nums.end(), def_eng);
    PrintOrder(nums, "Shuffled (default_random_engine)");

    // Shuffling using linear_congruential_engine (std::shuffle)
    std::shuffle(nums.begin(), nums.end(), lc_eng);
    PrintOrder(nums, "Shuffled (linear_congruential_engine)");
    return 0;
}