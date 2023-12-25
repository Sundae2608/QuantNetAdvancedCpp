/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 10, Exercise 2
*/

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
using namespace boost::numeric::ublas;

namespace {
    // Function to print a matrix
    template<typename MatrixType>
    void printMatrix(const MatrixType& matrix) {
        for (size_t i = 0; i < matrix.size1(); ++i) {
            for (size_t j = 0; j < matrix.size2(); ++j) {
                std::cout << matrix(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
}

int main102() {
    // Exercise 2a: Creating matrices with different template parameters
    matrix<double, row_major> matrix1(3, 4); // Fixed-size matrix with double data type

    matrix<std::complex<double>, column_major, unbounded_array<std::complex<double>>> matrix2(2, 2); // Dynamic-size matrix with complex<double> data type

    // Exercise 2b: Accessing and modifying elements of matrices
    matrix<double> matrix3(3, 3);

    for (size_t i = 0; i < matrix3.size1(); ++i) {
        for (size_t j = 0; j < matrix3.size2(); ++j) {
            matrix3(i, j) = i * j * 1.5;
        }
    }

    std::cout << "Matrix matrix3:" << std::endl;
    printMatrix(matrix3);

    // Exercise 2c: Adding and subtracting matrices
    matrix<double> matrix4(2, 2);
    matrix<double> matrix5(2, 2);
    matrix<double> result(2, 2);

    // Initialize matrix4 and matrix5 with values
    for (size_t i = 0; i < matrix4.size1(); ++i) {
        for (size_t j = 0; j < matrix4.size2(); ++j) {
            matrix4(i, j) = i + j;
            matrix5(i, j) = i * j;
        }
    }

    result = matrix4 + matrix5;
    std::cout << "Matrix result (matrix4 + matrix5):" << std::endl;
    printMatrix(result);

    result = matrix4 - matrix5;
    std::cout << "Matrix result (matrix4 - matrix5):" << std::endl;
    printMatrix(result);

    // Exercise 2d: Resizing a matrix
    matrix<double> matrix6(2, 3);
    matrix6.resize(3, 4);

    // Fill matrix6 with values after resizing
    for (size_t i = 0; i < matrix6.size1(); ++i) {
        for (size_t j = 0; j < matrix6.size2(); ++j) {
            matrix6(i, j) = i * j * 2.0;
        }
    }

    std::cout << "Matrix matrix6 after resizing:" << std::endl;
    printMatrix(matrix6);

    // Exercise 2e: Creating zero and identity matrices
    matrix<double> zeroMatrix(2, 3, 0.0);
    identity_matrix<double> identityMatrix(4);

    std::cout << "Zero Matrix:" << std::endl;
    printMatrix(zeroMatrix);

    std::cout << "Identity Matrix:" << std::endl;
    printMatrix(identityMatrix);

    return 0;
}