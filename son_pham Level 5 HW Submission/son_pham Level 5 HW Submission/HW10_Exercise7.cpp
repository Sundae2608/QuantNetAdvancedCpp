/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 10, Exercise 7
*/

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <iostream>
using namespace boost::numeric::ublas;

namespace {
    // Generic print function for vectors
    template <typename VectorType>
    void printVector(const VectorType& vec) {
        std::cout << "[ ";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec(i);
            if (i != vec.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " ]" << std::endl;
    }

    // Generic print function for matrices
    template <typename MatrixType>
    void printMatrix(const MatrixType& matrix) {
        for (size_t i = 0; i < matrix.size1(); ++i) {
            for (size_t j = 0; j < matrix.size2(); ++j) {
                std::cout << std::setw(8) << std::left << matrix(i, j);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

int main107() {
    // Creating vectors
    vector<double> v1(3);
    v1(0) = 1.0; v1(1) = 2.0; v1(2) = 3.0;

    vector<double> v2(3);
    v2(0) = 4.0; v2(1) = 5.0; v2(2) = 6.0;

    // Inner product of two vectors
    double innerProduct = inner_prod(v1, v2);
    std::cout << "Inner Product of v1 and v2: " << innerProduct << std::endl;

    // Outer product of two vectors
    matrix<double> outerProduct = outer_prod(v1, v2);
    std::cout << "Outer Product of v1 and v2:" << std::endl;
    printMatrix(outerProduct);

    // Adding and subtracting two vectors
    vector<double> additionResult = v1 + v2;
    vector<double> subtractionResult = v1 - v2;

    std::cout << "v1 + v2: ";
    printVector(additionResult);

    std::cout << "v1 - v2: ";
    printVector(subtractionResult);

    // Euclidean norm of a vector
    double euclideanNorm = norm_2(v1);
    std::cout << "Euclidean Norm of v1: " << euclideanNorm << std::endl;

    // L1 norm of a vector
    double l1Norm = norm_1(v1);
    std::cout << "L1 Norm of v1: " << l1Norm << std::endl;

    // Max norm of a vector
    double maxNorm = norm_inf(v1);
    std::cout << "Max Norm of v1: " << maxNorm << std::endl;

    // Creating a matrix
    matrix<double> A(2, 3);
    A(0, 0) = 1.0; A(0, 1) = 2.0; A(0, 2) = 3.0;
    A(1, 0) = 4.0; A(1, 1) = 5.0; A(1, 2) = 6.0;

    // L1 norm of a matrix
    double l1NormMatrix = norm_1(A);
    std::cout << "L1 Norm of Matrix A: " << l1NormMatrix << std::endl;

    // Max norm of a matrix
    double maxNormMatrix = norm_inf(A);
    std::cout << "Max Norm of Matrix A: " << maxNormMatrix << std::endl;

    // Matrix-vector product
    vector<double> result = prod(A, v1);
    std::cout << "Matrix-Vector Product A * v1: ";
    printVector(result);

    return 0;
}