/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 10, Exercise 6
*/

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

int main() {
    // Creating a matrix
    matrix<double> m(3, 4);
    for (size_t i = 0; i < m.size1(); ++i) {
        for (size_t j = 0; j < m.size2(); ++j) {
            m(i, j) = i * j * 1.5;
        }
    }

    // a) Creating and printing matrix_row, matrix_column, and matrix_range
    matrix_row<matrix<double>> row_proxy(m, 1);
    matrix_column<matrix<double>> column_proxy(m, 2);
    matrix_range<matrix<double>> range_proxy(m, range(1, 3), range(0, 3));

    std::cout << "Matrix Row Proxy:" << std::endl;
    std::cout << row_proxy << std::endl;

    std::cout << "Matrix Column Proxy:" << std::endl;
    std::cout << column_proxy << std::endl;

    std::cout << "Matrix Range Proxy:" << std::endl;
    std::cout << range_proxy << std::endl;

    // b) Creating and printing matrix_slice
    matrix_slice<matrix<double>> ms(m, slice(0, 1, 3), slice(0, 1, 3));

    std::cout << "Matrix Slice:" << std::endl;
    std::cout << ms << std::endl;

    return 0;
}