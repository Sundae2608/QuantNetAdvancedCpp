/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 5, Exercise 4:  Adapters for STL algorithms
Compiled in C++ 20
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <unordered_map>
#include <vector>

// Find index of the given target value x such that v[i] <= x < v[i + 1]
template <typename T>
int FindIndex(const std::vector<T>& vector, const T& value) {
    
    int left = 0;
    int right = vector.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (vector[mid] <= value && value < vector[mid + 1]) {
            return mid;
        }
        else if (vector[mid] > value) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1; // return -1 if target value is not found in the vector
}

// Maximum error between two vectors given the range i, j (inclusive of i and exclusive of j).
// I used some techniques like transform, next and max_element for this function.
template <typename T>
T MaximumErrorGivenTwoVectors(
    const std::vector<T>& v1, const std::vector<T>& v2, int i, int j) {

    std::vector<double> diff;
    diff.reserve(j - i + 1);
    std::transform(
        std::next(v1.begin(), i), 
        std::next(v1.begin(), j), 
        std::next(v2.begin(), i), std::back_inserter(diff), [](double a, double b) { return std::abs(a - b); });
    auto max_diff_it = std::max_element(diff.begin(), diff.end());
    return *max_diff_it;
}

// Print vector
template <typename T>
void PrintVector(const std::vector<T>& vector) {
    std::for_each(vector.begin(), vector.end(), [](const T& t) {
        std::cout << t << ", ";
        });
    std::cout << std::endl;
}

int main54() {
    std::vector<double> vector{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    std::cout << "4a. Vector content: ";
    PrintVector(vector);
    std::cout << "FindIndex(vector, 4.5) = " << FindIndex(vector, 4.5) << std::endl;

    std::cout << "4b. Maximum error between two vectors: " << std::endl;
    std::vector<double> v1 = { 1.0, 2.0, 3.0, 4.0, 5.0 };
    std::vector<double> v2 = { 1.5, 2.2, 2.8, 4.1, 5.2 };
    std::cout << "Vector 1: ";
    PrintVector(v1);
    std::cout << "Vector 2: ";
    PrintVector(v2);
    int i = 1;
    int j = 3;
    double max_err = MaximumErrorGivenTwoVectors(v1, v2, i, j);
    std::cout << "Maximum error between v1 and v2 from index " << i << " to " << j << " is " << max_err << std::endl;
    return 0;
}