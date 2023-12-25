#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 10, Exercise 3
*/

#include <complex>
#include <iostream>
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

int main103() {
    // Exercise 3a: Creating a sparse matrix with complex numbers
    compressed_matrix<std::complex<double>> sparseMatrix(3, 3);

    sparseMatrix(0, 1) = std::complex<double>(1.0, 2.0);
    sparseMatrix(2, 2) = std::complex<double>(-3.0, 0.0);

    std::cout << "Sparse Matrix:" << std::endl;
    printMatrix(sparseMatrix);

    sparseMatrix.clear();

    // Exercise 3b: Creating upper and lower triangular matrices
    triangular_matrix<double, upper> upperTriangular(3, 3);
    triangular_matrix<double, lower> lowerTriangular(3, 3);

    std::cout << "Upper Triangular Matrix:" << std::endl;
    printMatrix(upperTriangular);

    std::cout << "Lower Triangular Matrix:" << std::endl;
    printMatrix(lowerTriangular);

    // Exercise 3c: Creating upper and lower triangular matrix views from a dense matrix
    matrix<double> denseMatrix(3, 3);

    // Filling the dense matrix with values
    for (size_t i = 0; i < denseMatrix.size1(); ++i) {
        for (size_t j = 0; j < denseMatrix.size2(); ++j) {
            denseMatrix(i, j) = i * j * 1.5;
        }
    }

    triangular_adaptor<matrix<double>, lower> lowerTriangularView(denseMatrix);
    triangular_adaptor<matrix<double>, upper> upperTriangularView(denseMatrix);

    std::cout << "Dense Matrix:" << std::endl;
    printMatrix(denseMatrix);

    std::cout << "Lower Triangular View of Dense Matrix:" << std::endl;
    printMatrix(lowerTriangularView);

    std::cout << "Upper Triangular View of Dense Matrix:" << std::endl;
    printMatrix(upperTriangularView);

    return 0;
}