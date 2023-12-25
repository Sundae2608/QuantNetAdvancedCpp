/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 1, Exercise 5: Numeric Algorithms for Vectors and Matrices
*/

#include <array>
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
#include <complex>

namespace {
    // Vector class of fized size N and can hold any template type T
    template<typename T, int N>
    class Vector
    {
    private:
        T arr[N];

    public:
        // Constructors
        Vector() = default;

        // Same value constructor
        Vector(const T& value)
        {
            for (int i = 0; i < N; ++i)
                arr[i] = value;
        }

        // Copy constructor
        Vector(const Vector<T, N>& other)
        {
            for (int i = 0; i < N; ++i)
                arr[i] = other.arr[i];
        }

        // Initializer list constructor
        Vector(std::initializer_list<T> initList)
        {
            if (initList.size() != N)
            {
                std::cerr << "Error: Invalid initializer list size for Vector<" << N << ">.\n";
                return;
            }
            std::copy(initList.begin(), initList.end(), arr);
        }

        // Accessing elements using []
        T& operator[](int index) { return arr[index]; }
        const T& operator[](int index) const { return arr[index]; }

        // Unary minus
        Vector operator-() const
        {
            Vector result;
            for (int i = 0; i < N; ++i)
                result.arr[i] = -arr[i];
            return result;
        }

        // Member function to modify elements of the vector
        void modify(const std::function<T(T&)>& f)
        {
            std::transform(arr, arr + N, arr, f);
        }

        // Iterator functionality
        T* begin() { return arr; }
        const T* begin() const { return arr; }
        T* end() { return arr + N; }
        const T* end() const { return arr + N; }
    };

    // Output stream operator for Vector
    template<typename T, int N>
    std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec)
    {
        os << "[ ";
        for (int i = 0; i < N; ++i)
        {
            os << vec[i];
            if (i < N - 1)
                os << ", ";
        }
        os << " ]";
        return os;
    }

    // Addition
    template<typename T, int N>
    Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (int i = 0; i < N; ++i)
            result[i] = lhs[i] + rhs[i];
        return result;
    }

    // Subtraction
    template<typename T, int N>
    Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (int i = 0; i < N; ++i)
            result[i] = lhs[i] - rhs[i];
        return result;
    }

    // Scalar multiplication
    template<typename T, int N, typename F>
    Vector<T, N> operator*(const F& a, const Vector<T, N>& vec)
    {
        Vector<T, N> result;
        for (int i = 0; i < N; ++i)
            result[i] = a * vec[i];
        return result;
    }

    // a) Create user-friendly wrappers for the STL inner_product functions. 
    // In both cases you use instances of Vector as arguments. You will need
    // to add iterator functionality to Vector.
    //
    // THis is a bit perplexing to me. It doesn't look like the refactored
    // wrappers are majorly more convenient than the std::inner_product.
    // We avoid those .begin() and .end() basically.
    template <typename T, int N>
    T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue) {
        return std::inner_product(v1.begin(), v1.end(), v2.begin(), initValue);
    }

    template <typename T>
    using BinaryFunction = std::function<T(const T&, const T&)>;

    template <typename T, int N>
    T inner_product(const Vector<T, N>& v1, const Vector<T, N>& v2, T initValue,
        const BinaryFunction<T>& op1, const BinaryFunction<T>& op2) {
        return std::inner_product(v1.begin(), v1.end(), v2.begin(), initValue, op1, op2);
    }

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

    template <typename T, int N>
    Matrix<T, N, N> outer_product(const Vector<T, N>& v1, const Vector<T, N>& v2) {
        Matrix<T, N, N> result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result(i, j) = v1[i] * v2[j];
            }
        }
        return result;
    }

    template <typename T, int N>
    Matrix<std::complex<T>, N, N> outer_product(const Vector<std::complex<T>, N>& v1,
        const Vector<std::complex<T>, N>& v2) {
        Matrix<std::complex<T>, N, N> result;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                result(i, j) = std::conj(v1[i]) * v2[j];
            }
        }
        return result;
    }
}

int main() {
    // b) Test the first variant.
    Vector<int, 3> v1 = { 1, 2, 3 };
    Vector<int, 3> v2 = { 4, 5, 6 };

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;

    int result = inner_product(v1, v2, 0);
    std::cout << "Inner product: " << result << std::endl;

    // c) For the second variant, test it using addition and multiplication operators 
    // (you get 4 options for lambda binary functions ADD and MUL)
    BinaryFunction<int> ADD = [](const int& a, const int& b) { return a + b; };
    BinaryFunction<int> MUL = [](const int& a, const int& b) { return a * b; };
    int resultAddMul = inner_product(v1, v2, 0, ADD, MUL);

    std::cout << "inner product with custom operators: " << resultAddMul << std::endl;

    // d) Outer product
    Matrix<int, 3, 3> outerProductInt = outer_product(v1, v2);
    std::cout << "Outer product (int):\n" << outerProductInt << std::endl;

    // e) Outer product with complex conjugate
    Vector<std::complex<double>, 3> cv1 = {
        std::complex<double>(1.0, 2.0),
        std::complex<double>(2.0, -1.0),
        std::complex<double>(-1.0, 0.5)
    };

    Vector<std::complex<double>, 3> cv2 = {
        std::complex<double>(0.5, 1.0),
        std::complex<double>(-1.0, 2.0),
        std::complex<double>(2.0, 0.5)
    };

    std::cout << "cv1: " << cv1 << std::endl;
    std::cout << "cv2: " << cv2 << std::endl;

    Matrix<std::complex<double>, 3, 3> outerProductComplex = outer_product(cv1, cv2);

    std::cout << "Outer product of complex vectors:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << outerProductComplex(i, j) << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}