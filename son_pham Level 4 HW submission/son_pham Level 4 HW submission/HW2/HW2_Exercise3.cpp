/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 3: Classifying and Implementing Algorithms
*/

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

namespace {
    template <typename Container> void printContainer(const Container& container) {
        for (const auto& value : container) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
} // namespace

int main23() {

    std::vector<int> values = { 5, 10, 15, 20, 25 };

    // Classify each algorithm into one of the following category.
    // Non-modifying
    // Modifying
    // Removing
    // Mutating
    // Sorting
    // Sorted-Range
    // Numeric
    // Implement each algorithm given an std::vector of values.

    // a) Scale all values by a given factor.
    // Category: Modifying
    // Algorithm: std::transform
    int factor = 2;
    std::transform(values.begin(), values.end(), values.begin(),
        [factor](int value) { return value * factor; });
    std::cout << "Scaled values: ";
    printContainer(values);

    // b) Count the number of elements whose values are in a given range.
    // Category: Non-modifying
    // Algorithm: std::count_if
    int lower = 10, upper = 30;
    int count =
        std::count_if(values.begin(), values.end(), [lower, upper](int value) {
        return value >= lower && value <= upper;
            });
    std::cout << "Number of elements in range: " << count << std::endl;

    // c) Find the average, minimum, and maximum values in a container.
    // Category: Non-modifying, Numeric
    // Algorithm: std::accumulate, std::min_element, std::max_element.
    double average =
        static_cast<double>(std::accumulate(values.begin(), values.end(), 0)) /
        values.size();
    int min_value = *std::min_element(values.begin(), values.end());
    int max_value = *std::max_element(values.begin(), values.end());
    std::cout << "Average: " << average << ", Minimum: " << min_value
        << ", Maximum: " << max_value << std::endl;

    // d) Find the first element that is (not) in a range.
    // Category: Non-modifying
    // Algorithm: std::find_first_of
    std::vector<int> range = { 30, 40, 50 };
    auto result = std::find_first_of(values.begin(), values.end(), range.begin(),
        range.end());
    if (result != values.end()) {
        std::cout << "Found first matching value in range: " << *result
            << std::endl;
    }
    else {
        std::cout << "No matching value found in range." << std::endl;
    }

    // e) Search for all occurrences of ‘3456’ in the container.
    // Category: Non-modifying
    // Algorithm: std::search
    std::vector<int> pattern = { 3, 4, 5, 6 };
    auto search_result =
        std::search(values.begin(), values.end(), pattern.begin(), pattern.end());
    if (search_result != values.end()) {
        std::cout << "Pattern found starting at index "
            << std::distance(values.begin(), search_result) << std::endl;
    }
    else {
        std::cout << "Pattern not found." << std::endl;
    }

    // f) Determine if the elements in two ranges are equal.
    // Category: Non-modifying
    // Algorithm: std::equal
    std::vector<int> values2 = { 10, 20, 30, 40, 50 };
    bool equal = std::equal(values.begin(), values.end(), values2.begin());
    std::cout << "Ranges are " << (equal ? "equal." : "not equal.") << std::endl;

    // g) Determine if a set is some permutation of ‘12345’.
    // Category: Non-modifying
    // Algorithm: std::is_permutation
    std::vector<int> permutation = { 2, 4, 1, 3, 5 };
    std::vector<int> reference = { 1, 2, 3, 4, 5 };
    bool is_permutation = std::is_permutation(
        permutation.begin(), permutation.end(), reference.begin());
    std::cout << "Is a permutation: " << (is_permutation ? "yes" : "no")
        << std::endl;

    // h) Is a container already sorted?
    // Category: Non-modifying
    // Algorithm: std::is_sorted
    bool sorted = std::is_sorted(values.begin(), values.end());
    std::cout << "Is sorted: " << (sorted ? "yes" : "no") << std::endl;

    // i) Copy a container into another container.
    // Category: Modifying
    // Algorithm: std::copy
    std::vector<int> copied_values(values.size());
    std::copy(values.begin(), values.end(), copied_values.begin());
    std::cout << "Copied values: ";
    printContainer(copied_values);

    // j) Move the last 10 elements of a container to the front.
    // Category: Modifying
    // Algorithm: std::rotate
    std::rotate(values.begin(), values.end() - 10, values.end());
    std::cout << "Values after rotation: ";
    printContainer(values);

    // k) Swap two ranges at a given position.
    // Category: Modifying
    // Algorithm: std::swap_ranges
    std::vector<int> range1 = { 1, 2, 3 };
    std::vector<int> range2 = { 30, 40, 50 };
    auto swap_position = values.begin() + 1;
    std::swap_ranges(swap_position, swap_position + range1.size(),
        range2.begin());
    std::cout << "Values after swapping ranges: ";
    printContainer(values);

    // l) Generate values in a container based on some formula.
    // Category: Modifying, Numeric
    // Algorithm: std::generate
    std::generate(values.begin(), values.end(),
        [value = 0]() mutable { return value++; });
    std::cout << "Generated values: ";
    printContainer(values);

    // m) Replace all uneven numbers by zero.
    // Category: Modifying
    // Algorithm: std::replace_if
    std::replace_if(
        values.begin(), values.end(), [](int value) { return value % 2 != 0; },
        0);
    std::cout << "Values after replacing uneven numbers: ";
    printContainer(values);

    // n) Remove all elements whose value is less than 100.
    // Category: Removing
    // Algorithm: std::remove_if, followed by std::erase
    values.erase(std::remove_if(values.begin(), values.end(),
        [](int value) { return value < 100; }),
        values.end());
    std::cout << "Values after removing elements less than 100: ";
    printContainer(values);

    // o) Shuffle a container randomly (pre- and post-C++11 versions).
    // Category: Modifying
    // Algorithm: std::random_shuffle (pre-C++11), std::shuffle
    // (C++11 and later)
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(values.begin(), values.end(),
        std::mt19937(std::random_device()()));
    std::cout << "Values after shuffling: ";
    printContainer(values);

    // p) Compute one-sided divided differences of the values in a container.
    // Category: Numeric
    // Algorithm: This operation might not have a direct STL algorithm.
    // You would typically implement this using a loop.
    std::vector<double> divided_diff;
    std::adjacent_difference(values.begin(), values.end(),
        std::back_inserter(divided_diff));
    std::cout << "One-sided divided differences: ";
    printContainer(divided_diff);
    return 0;
}