/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 10, Exercise 5
*/

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace boost::numeric::ublas;

// Generic print function for general containers
template <typename T, template <typename S, typename Alloc>
class Container, typename TAlloc>
void print(const std::string& comment, const Container<T, TAlloc>& container) {
    std::cout << comment << ": ";

    auto f = [](const T& t) { std::cout << t << ", "; };
    std::for_each(container.begin(), container.end(), f);
    std::cout << std::endl;

    for (std::size_t i = 0; i < container.size(); ++i) {
        std::cout << container[i] << ",";
    }
    std::cout << std::endl;
}

// Generic find_sequential_greater function using template template parameters
template <template <typename, typename> class Container, typename T, typename Alloc>
std::tuple<std::size_t, std::size_t> find_sequential_greater(const Container<T, Alloc>& v, T x) {
    for (std::size_t j = 0; j < v.size() - 1; ++j) {
        if (v(j) <= x && v(j + 1) > x)
            return std::make_tuple(j, j + 1);
    }
    return std::make_tuple(999, 999);
}

int main() {
    // Using STL vector
    std::vector<double> v1{ 2.0, 3.0, 4.0, -6.0 };
    print(std::string("STL"), v1);

    auto stl_range = find_sequential_greater(v1, 3.0);
    std::cout << "STL: Range of values greater than 3.0: (" << std::get<0>(stl_range) << ", " << std::get<1>(stl_range) << ")" << std::endl;

    // Using Boost uBLAS vector
    vector<double> v2(4);
    v2(0) = 2.0; v2(1) = 3.0; v2(2) = 4.0; v2(3) = -6.0;
    print(std::string("Boost"), v2);

    auto boost_range = find_sequential_greater(v2, 3.0);
    std::cout << "Boost: Range of values greater than 3.0: (" << std::get<0>(boost_range) << ", " << std::get<1>(boost_range) << ")" << std::endl;

    return 0;
}