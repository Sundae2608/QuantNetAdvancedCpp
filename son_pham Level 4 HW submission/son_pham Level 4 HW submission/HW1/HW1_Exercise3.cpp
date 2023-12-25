/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 1, Exercise 3: Compile-Time Matrix Class
*/

#include <iostream>
#include <array>
#include <functional>

namespace {
	// For the data structure ADT to hold the data of the matrix, we can use a nested std::array to represent a 2D array.
	// This allows us to create a compile - time matrix class with fixed dimensions.The NestedMatrix<V, NR, NC> can be used 
	// to represent a matrix with NR rows and NC columns, where V is the type of the elements.
    template <typename V, int NR, int NC>
    using NestedMatrix = std::array<std::array<V, NC>, NR>;

    template <typename V, int NR, int NC>
    class Matrix
    {
    private:
        NestedMatrix<V, NR, NC> mat;

    public:
        // Constructors
        Matrix() = default;
        Matrix(const V& value)
        {
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    mat[i][j] = value;
        }
        Matrix(const Matrix<V, NR, NC>& other)
        {
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    mat[i][j] = other.mat[i][j];
        }

        // Constructor with initializer list
        Matrix(std::initializer_list<std::initializer_list<V>> initList)
        {
            int i = 0;
            for (const auto& row : initList)
            {
                int j = 0;
                for (const auto& val : row)
                {
                    if (i < NR && j < NC)
                        mat[i][j] = val;
                    ++j;
                }
                ++i;
            }
        }

        // Accessing elements using ()
        V& operator()(int row, int col) { return mat[row][col]; }
        const V& operator()(int row, int col) const { return mat[row][col]; }

        // Unary minus
        Matrix operator-() const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = -mat[i][j];
            return result;
        }

        // Scalar multiplication
        template <typename F>
        Matrix operator*(const F& a) const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = a * mat[i][j];
            return result;
        }

        // Matrix addition
        Matrix operator+(const Matrix<V, NR, NC>& other) const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = mat[i][j] + other.mat[i][j];
            return result;
        }

        // Matrix subtraction
        Matrix operator-(const Matrix<V, NR, NC>& other) const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = mat[i][j] - other.mat[i][j];
            return result;
        }

        // Matrix multiplication
        template <int RC>
        Matrix<V, NR, RC> operator*(const Matrix<V, NC, RC>& other) const
        {
            Matrix<V, NR, RC> result;
            for (int i = 0; i < NR; ++i)
            {
                for (int j = 0; j < RC; ++j)
                {
                    result(i, j) = V();
                    for (int k = 0; k < NC; ++k)
                    {
                        result(i, j) += mat[i][k] * other(k, j);
                    }
                }
            }
            return result;
        }

        // Output stream operator for Matrix (defined as a member function)
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
        {
            for (int i = 0; i < NR; ++i)
            {
                for (int j = 0; j < NC; ++j)
                    os << mat.mat[i][j] << " ";
                os << "\n";
            }
            return os;
        }
    };
}

int main13() {
    // b) Create some instances of Matrix and print them.
    Matrix<int, 2, 2> mat1(1);
    Matrix<int, 2, 2> mat2(2);
    Matrix<int, 2, 2> mat3 = { {1, 2}, {3, 4} };
    Matrix<int, 2, 4> mat4 = { {1, 2, 3, 4}, {5, 6, 7, 8} };

    Matrix<int, 2, 2> sum = mat1 + mat2;
    Matrix<int, 2, 2> diff = mat1 - mat2;
    Matrix<int, 2, 2> scaled = mat3 * 3;
    Matrix<int, 2, 4> mat_mul = mat3 * mat4;

    // c) Implement the above operation pertaining to the properties of a vector space as explained in the introduction.
    // The operations include: 
    // - Adding and subtraction; unary minus.
    // - Premultiplication by a scalar quantity.
    std::cout << "Matrix 1:\n" << mat1 << std::endl;
    std::cout << "Matrix 2:\n" << mat2 << std::endl;
    std::cout << "Matrix 3:\n" << mat3 << std::endl;
    std::cout << "Matrix 4:\n" << mat4 << std::endl;

    std::cout << "Matrix 1 + Matrix 2:\n" << sum << std::endl;
    std::cout << "Matrix 1 - Matrix 2:\n" << diff << std::endl;
    std::cout << "3 * Matrix 3:\n" << scaled << std::endl;
    std::cout << "Matrix 3 * Matrix 4:\n" << mat_mul << std::endl;

    // Unary minus example
    Matrix<int, 2, 4> negated = -mat4;

    std::cout << "Negated Matrix 4:\n" << negated << std::endl;
    return 0;
}