/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 2: Predicates for Ranges
*/

#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <ranges> // Required for C++20 range algorithms
#include <vector>
#include <random>

namespace {
    void part_a() {
        std::vector<int> vec1 = { 1, 3, 5, 7, 9 };
        std::vector<int> vec2 = { 1, 3, 2, 7, 9 };

        // a)
        // std::is_sorted Algorithm
        bool sorted1 = std::is_sorted(vec1.begin(), vec1.end());
        if (sorted1) {
            std::cout << "vec1 is sorted." << std::endl;
        }
        else {
            std::cout << "vec1 is not sorted." << std::endl;
        }

        // std::ranges::is_sorted Algorithm (C++20)
        // bool sorted2 = std::ranges::is_sorted(vec1);
        // if (sorted2) {
        //     std::cout << "vec1 is sorted using ranges::is_sorted." << std::endl;
        // } else {
        //     std::cout << "vec1 is not sorted using ranges::is_sorted." <<
        //     std::endl;
        // }

        // std::is_sorted_until Algorithm
        auto pos1 = std::is_sorted_until(vec2.begin(), vec2.end());
        if (pos1 == vec2.end()) {
            std::cout << "vec2 is completely sorted." << std::endl;
        }
        else {
            std::cout << "vec2 is not sorted at position "
                << std::distance(vec2.begin(), pos1) << std::endl;
        }

        // std::ranges::is_sorted_until Algorithm (C++20)
        // auto pos2 = std::ranges::is_sorted_until(vec2);
        // if (pos2 == vec2.end()) {
        //     std::cout << "vec2 is completely sorted using ranges::is_sorted_until."
        //     << std::endl;
        // } else {
        //     std::cout << "vec2 is not sorted at position " <<
        //     std::distance(vec2.begin(), pos2) << " using ranges::is_sorted_until."
        //     << std::endl;
        // }
    }

    void part_b() {
        // b) Test the efficiency of the above code:
        const int size = 1000000; // Size of the container

        std::vector<int> sortedVec(size);
        std::iota(sortedVec.begin(), sortedVec.end(),
            0); // Fill with consecutive numbers

        std::vector<int> unsortedVec(size);
        std::iota(unsortedVec.begin(), unsortedVec.end(), 0);
        // std::random_shuffle(unsortedVec.begin(),
        //     unsortedVec.end()); // Shuffle the elements

        // Measure execution time for std::is_sorted
        auto start1 = std::chrono::high_resolution_clock::now();
        bool sorted1 = std::is_sorted(sortedVec.begin(), sortedVec.end());
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration1 =
            std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
        std::cout << "std::is_sorted time: " << duration1.count() << " microseconds"
            << std::endl;

        // Measure execution time for std::ranges::is_sorted
        // auto start2 = std::chrono::high_resolution_clock::now();
        // bool sorted2 = std::ranges::is_sorted(sortedVec);
        // auto end2 = std::chrono::high_resolution_clock::now();
        // auto duration2 =
        //     std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
        // std::cout << "std::ranges::is_sorted time: " << duration2.count()
        //           << " microseconds" << std::endl;

        // Measure execution time for std::is_sorted_until
        auto start3 = std::chrono::high_resolution_clock::now();
        auto pos1 = std::is_sorted_until(unsortedVec.begin(), unsortedVec.end());
        auto end3 = std::chrono::high_resolution_clock::now();
        auto duration3 =
            std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);
        std::cout << "std::is_sorted_until time: " << duration3.count()
            << " microseconds" << std::endl;

        // Measure execution time for std::ranges::is_sorted_until
        // auto start4 = std::chrono::high_resolution_clock::now();
        // auto pos2 = std::ranges::is_sorted_until(unsortedVec);
        // auto end4 = std::chrono::high_resolution_clock::now();
        // auto duration4 =
        //     std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4);
        // std::cout << "std::ranges::is_sorted_until time: " << duration4.count()
        //           << " microseconds" << std::endl;
        // 
        // I commented this out because this doesn't work in C++14. meanwhile,
        // random_shuffle is deprecated in C++ 20, simply uncommenet this code to
        // run them
    }
} // namespace
// TODO: Run with C++ 20.
int main22() {
    part_a();
    part_b();
    return 0;
}