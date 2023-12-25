/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 10, Exercise 4
*/

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <algorithm>
#include <iostream>
using namespace boost::numeric::ublas;

namespace {
    // Function to find the range of values greater than x
    template<typename Vector, typename T>
    std::tuple<std::size_t, std::size_t> find_sequential_greater(const Vector& v, T x) {
        for (std::size_t j = 0; j < v.size() - 1; ++j) {
            if (v(j) <= x && v(j + 1) > x)
                return std::make_tuple(j, j + 1);
        }
        return std::make_tuple(999, 999);
    }
}

int main() {
    // Creating a Boost uBLAS vector
    vector<double> v(10);
    for (std::size_t i = 0; i < v.size(); ++i) {
        v(i) = i * 1.5;
    }

    // Finding the range of values greater than 5.0
    auto range = find_sequential_greater(v, 5.0);
    std::cout << "Range of values greater than 5.0: (" << std::get<0>(range) << ", " << std::get<1>(range) << ")" << std::endl;

    // Part a: Using std::find_if
    auto it = std::find_if(v.begin(), v.end(), [](double value) { return value > 5.0; });
    if (it != v.end()) {
        std::size_t index = std::distance(v.begin(), it);
        std::cout << "Index of value greater than 5.0 (std::find_if): " << index << std::endl;
    }

    // Part b: Using std::lower_bound
    auto lower = std::lower_bound(v.begin(), v.end(), 5.0);
    if (lower != v.end()) {
        std::size_t lowerIndex = std::distance(v.begin(), lower);
        std::cout << "Index of lower bound value (std::lower_bound): " << lowerIndex << std::endl;
    }

    // Part c: Using std::equal_range
    auto equalRange = std::equal_range(v.begin(), v.end(), 5.0);
    if (equalRange.first != v.end()) {
        std::size_t equalLowerIndex = std::distance(v.begin(), equalRange.first);
        std::size_t equalUpperIndex = std::distance(v.begin(), equalRange.second);
        std::cout << "Indices of equal range values (std::equal_range): " << equalLowerIndex << ", " << equalUpperIndex << std::endl;
    }

    // Part d: Using std::find_if_not
    auto notGreater = std::find_if_not(v.begin(), v.end(), [](double value) { return value > 5.0; });
    if (notGreater != v.end()) {
        std::size_t notGreaterIndex = std::distance(v.begin(), notGreater);
        std::cout << "Index of first value not greater than 5.0 (std::find_if_not): " << notGreaterIndex << std::endl;
    }

    return 0;
}