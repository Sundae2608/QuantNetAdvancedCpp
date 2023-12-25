/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 10, Exercise 1
*/

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace boost::numeric::ublas;

namespace {
    // Function to print a vector
    template<typename VectorType>
    void printVector(const VectorType& vector) {
        for (size_t i = 0; i < vector.size(); ++i) {
            std::cout << vector(i) << " ";
        }
        std::cout << std::endl;
    }
}

int main101() {
    // Exercise 1a: Creating a vector and accessing elements
    vector<double> v1(10);
    for (size_t i = 0; i < v1.size(); ++i) {
        v1(i) = i * 2.0;
    }

    std::cout << "Vector v1:" << std::endl;
    printVector(v1);

    // Exercise 1b: Vector operations
    vector<double> v2(10);

    // Initialize v2 with values
    for (size_t i = 0; i < v2.size(); ++i) {
        v2(i) = i * 1.5;
    }

    vector<double> v3(10); // Assuming v3 is another vector of the same size
    for (size_t i = 0; i < v3.size(); ++i) {
        v3(i) = i * 0.5;
    }

    v2 = v1;
    v1 += v2;
    v1 *= 2.5;
    v1 -= v3;

    std::cout << "Vector v1 after operations:" << std::endl;
    printVector(v1);

    // Exercise 1c: Using std::transform and std::multiplies
    vector<double> result(10);
    std::transform(v1.begin(), v1.end(), v2.begin(), result.begin(), std::multiplies<double>());

    std::cout << "Vector result (v1 * v2):" << std::endl;
    printVector(result);

    // Exercise 1d: Creating a scalar vector
    vector<double> scalarVector(100, 5.0);

    std::cout << "Scalar vector with all values as 5.0:" << std::endl;
    printVector(scalarVector);

    return 0;
}