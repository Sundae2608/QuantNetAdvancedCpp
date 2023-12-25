/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 1: Non-modifying Algorithms
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>

namespace {

    std::map<int, int> countFrequency(const std::vector<int>& container) {
        std::map<int, int> frequencyMap;

        for (int value : container) {
            frequencyMap[value]++;
        }

        return frequencyMap;
    }

    std::tuple<int, int, int, double>
        computeStatistics(const std::vector<int>& container) {
        int min = *std::min_element(container.begin(), container.end());
        int max = *std::max_element(container.begin(), container.end());
        int sum = std::accumulate(container.begin(), container.end(), 0);
        double average = static_cast<double>(sum) / container.size();

        return std::make_tuple(min, max, sum, average);
    }
} // namespace

int main24() {
    // a) Count the frequency of each value in a container:
    std::vector<int> input = { 1, 2, 4, 5, 4, 1 };
    std::map<int, int> frequencyMap = countFrequency(input);

    for (const auto& entry : frequencyMap) {
        std::cout << "{" << entry.first << ": " << entry.second << " times} ";
    }

    // b) Write a function to compute the minimum, maximum, sum and average of the
    // values of the elements in a container with numeric values. The output is a
    // tuple with four fields.
    auto statistics = computeStatistics(input);

    std::cout << "Min: " << std::get<0>(statistics) << std::endl;
    std::cout << "Max: " << std::get<1>(statistics) << std::endl;
    std::cout << "Sum: " << std::get<2>(statistics) << std::endl;
    std::cout << "Average: " << std::get<3>(statistics) << std::endl;

    // c) Consider the container S = {1,2,-3,4,5,5,5,6}. Use an STL algorithm to
    // find the first occurrence of the value 5. Now use: std::bind2nd()
    // std::bind() Lambda expression to find the position of the first even number
    // in S.
    std::vector<int> S = { 1, 2, -3, 4, 5, 5, 5, 6 };

    // Finding the first occurrence of 5
    auto firstFive = std::find(S.begin(), S.end(), 5);
    std::cout << "First occurrence of 5: " << std::distance(S.begin(), firstFive)
        << std::endl;

    // Finding the position of the first even number using bind2nd
    auto firstEven =
        std::find_if(S.begin(), S.end(), std::bind2nd(std::modulus<int>(), 2));
    std::cout << "Position of first even number: "
        << std::distance(S.begin(), firstEven) << std::endl;

    // Finding the position of the first even number using bind
    auto firstEvenBind =
        std::find_if(S.begin(), S.end(),
            std::bind(std::modulus<int>(), std::placeholders::_1, 2));
    std::cout << "Position of first even number using bind: "
        << std::distance(S.begin(), firstEvenBind) << std::endl;

    // Finding the position of the first even number using lambda expression
    auto firstEvenLambda =
        std::find_if(S.begin(), S.end(), [](int num) { return num % 2 == 0; });
    std::cout << "Position of first even number using lambda: "
        << std::distance(S.begin(), firstEvenLambda) << std::endl;

    // d) Consider the container S = {1,2,5,5,-3,4,5,5,5,6,3,4,5}. Determine how
    // to do the following:
    // - Return the position of the first three consecutive elements having the
    // value 5.
    // - Return the position of the first element of the first subrange matching
    // {3,4,5}.
    // - Return the position of the first element of the last subrange matching
    // {3,4,5}.
    std::vector<int> S2 = { 1, 2, 5, 5, -3, 4, 5, 5, 5, 6, 3, 4, 5 };

    // Finding the position of the first three consecutive elements with value 5
    auto threeConsecutive5 = std::search_n(S2.begin(), S2.end(), 3, 5);
    std::cout << "Position of first three consecutive 5's: "
        << std::distance(S.begin(), threeConsecutive5) << std::endl;

    // Finding the position of the first element of the first subrange matching
    // {3, 4, 5}
    std::vector<int> subrange = { 3, 4, 5 };
    auto firstSubrange =
        std::search(S2.begin(), S2.end(), subrange.begin(), subrange.end());
    std::cout << "Position of first element of first subrange: "
        << std::distance(S2.begin(), firstSubrange) << std::endl;

    // Finding the position of the first element of the last subrange matching {3,
    // 4, 5}
    auto lastSubrange =
        std::find_end(S2.begin(), S2.end(), subrange.begin(), subrange.end());
    std::cout << "Position of first element of last subrange: "
        << std::distance(S2.begin(), lastSubrange) << std::endl;

    // e) Consider the container S = {1,2,5,5,-3,4,5,5,5,6,3,4,5}. Find the first
    // element in S that has a value equal to the value of the following element.
    std::vector<int> S3 = { 1, 2, 5, 5, -3, 4, 5, 5, 5, 6, 3, 4, 5 };

    for (auto it = S3.begin(); it != S3.end() - 1; ++it) {
        if (*it == *(it + 1)) {
            std::cout << "First element with value equal to the next: " << *it
                << std::endl;
            break;
        }
    }

    // f) Consider the container S = {1,2,5,5,-3,4,5,5,5,6,3,4,5} and S1 =
    // {1,2,5}. Determine whether the elements in S1 are equal to the elements in
    // S.
    std::vector<int> S4 = { 1, 2, 5, 5, -3, 4, 5, 5, 5, 6, 3, 4, 5 };
    std::vector<int> S5 = { 1, 2, 5 };

    bool areEqual = std::equal(S4.begin(), S4.end(), S5.begin(), S5.end());

    if (areEqual) {
        std::cout << "S5 is equal to the corresponding elements in S4."
            << std::endl;
    }
    else {
        std::cout << "S5 is not equal to the corresponding elements in S4."
            << std::endl;
    }
    return 0;
}