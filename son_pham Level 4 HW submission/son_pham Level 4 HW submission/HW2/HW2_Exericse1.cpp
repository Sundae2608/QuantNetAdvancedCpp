/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 1: Searching in Numeric Arrays
*/

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

namespace {
    using value_type = int; // Assuming int as the value type
    using Vector = std::vector<value_type>;
    using Range = std::tuple<std::size_t, std::size_t>;
    using Result = std::tuple<Range, bool>;

    // a) Reimplement find_sequential_greater using std::find_if.
    Result find_sequential_greater(const Vector& v, value_type x) {
        for (std::size_t j = 0; j < v.size(); ++j) {
            if (v[j] <= x && v[j + 1] > x) {
                return std::make_tuple(std::make_tuple(j, j + 1), true);
            }
        }
        return std::make_tuple(std::make_tuple(999, 999), false);
    }

    Result find_sequential_greater_find_if(const Vector& v, value_type x) {
        // Notice that find if treat val as the value, not the index itself.
        // Therefore, I can't implement both v[j] <= x && v[j + 1] > x
        // However, this shouldn't matter, as v[j] <= x should be sufficient
        // if we assume that the array is already sorted.
        auto it = std::find_if(v.begin(), v.end(),
            [x](value_type val) { return val <= x; });

        if (it != v.end() && std::next(it) != v.end()) {
            std::size_t index = std::distance(v.begin(), it);
            return std::make_tuple(std::make_tuple(index, index + 1), true);
        }

        return std::make_tuple(std::make_tuple(999, 999), false);
    }

    // b) Implement the O (log n) algorithms std::lower bound and std::upper bound
    // to effect the same functionality as in part a). Again, you need (as always)
    // to create a wrapper function.
    //
    // Basically, to reimplement find sequential greater, we can use the lowerbound
    // function.
    Result find_lower_bound(const Vector& v, value_type x) {
        auto it = std::lower_bound(v.begin(), v.end(), x);

        if (it != v.end() && it != v.begin()) {
            std::size_t index = std::distance(v.begin(), it) - 1;
            return std::make_tuple(std::make_tuple(index, index + 1), true);
        }

        return std::make_tuple(std::make_tuple(999, 999), false);
    }

    // c) Implement the O (log n) algorithm stud::equal range to effect the same
    // functionality as in part b). Again, you need (as always) to create a wrapper
    // function.
    Result find_equal_range(const Vector& v, value_type x) {
        auto range = std::equal_range(v.begin(), v.end(), x);

        if (range.first != range.second) {
            std::size_t firstIndex = std::distance(v.begin(), range.first);
            std::size_t lastIndex = std::distance(v.begin(), std::prev(range.second));
            return std::make_tuple(std::make_tuple(firstIndex, lastIndex + 1), true);
        }

        return std::make_tuple(std::make_tuple(999, 999), false);
    }

    // d) Reimplement the algorithm using find if not
    Result find_sequential_greater_find_if_not(const Vector& v, value_type x) {
        auto it =
            std::find_if(v.begin(), v.end(), [x](value_type val) { return val > x; });

        if (it != v.end() && std::next(it) != v.end()) {
            std::size_t index = std::distance(v.begin(), it);
            return std::make_tuple(std::make_tuple(index, index + 1), true);
        }

        return std::make_tuple(std::make_tuple(999, 999), false);
    }
} // namespace

int main21() {

    Vector v = { 1, 3, 5, 6, 7, 9 };
    value_type target = 5;

    // a) Reimplement find_sequential_greater with find_if
    Result result = find_sequential_greater(v, target);
    if (std::get<1>(result)) {
        std::cout << "Sequential greater range: ["
            << std::get<0>(std::get<0>(result)) << ", "
            << std::get<1>(std::get<0>(result)) << "]" << std::endl;
    }
    else {
        std::cout << "Target not found using sequential greater algorithm."
            << std::endl;
    }
    Result result_find_if = find_sequential_greater_find_if(v, target);
    if (std::get<1>(result_find_if)) {
        std::cout << "Sequential greater range (find if): ["
            << std::get<0>(std::get<0>(result)) << ", "
            << std::get<1>(std::get<0>(result)) << "]" << std::endl;
    }
    else {
        std::cout << "Target not found using sequential greater algorithm."
            << std::endl;
    }

    // b) Reimplement find_sequential greater with std::upperbound
    Result result_upper_bound = find_lower_bound(v, target);
    if (std::get<1>(result_upper_bound)) {
        std::cout << "Sequential greater range (lower bound): ["
            << std::get<0>(std::get<0>(result)) << ", "
            << std::get<1>(std::get<0>(result)) << "]" << std::endl;
    }
    else {
        std::cout << "Target not found using sequential greater algorithm."
            << std::endl;
    }

    // c) Reimplement find_sequential greater with std::equalrange
    Result result_equal_range = find_equal_range(v, target);
    if (std::get<1>(result_equal_range)) {
        std::cout << "Sequential greater range (equal range): ["
            << std::get<0>(std::get<0>(result)) << ", "
            << std::get<1>(std::get<0>(result)) << "]" << std::endl;
    }
    else {
        std::cout << "Target not found using sequential greater algorithm."
            << std::endl;
    }

    // d) find_if_not.
    // I am not quite sure what the algorithm is asking for here. I'll just opt
    // to do the reverse of a) and see what the behavior looks like
    Result result_find_if_not = find_sequential_greater_find_if_not(v, target);
    if (std::get<1>(result_find_if_not)) {
        std::cout << "Sequential greater range (find if not): ["
            << std::get<0>(std::get<0>(result)) << ", "
            << std::get<1>(std::get<0>(result)) << "]" << std::endl;
    }
    else {
        std::cout << "Target not found using sequential greater algorithm."
            << std::endl;
    }
    return 0;
}