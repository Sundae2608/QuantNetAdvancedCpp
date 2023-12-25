/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 2, Exercise 1: The beginning of Vector Space
*/

#include <complex>
#include <iostream>
#include <type_traits>
#include <array>
#include <vector>

namespace {
    // Printing function when value is non-compound
    template<typename T>
    void Print_tmpl(const T& t, std::false_type is_compound) {
        std::cout << t;
    }

    // Printing function when value is non-compound
    template<typename T>
    void Print_tmpl(const T& t, std::true_type is_compound) {
        for (const auto val : t) {
            std::cout << val << " ";
        }
    }

    template <typename T>
    void Print(const T& t)
    {
        Print_tmpl(t, std::is_compound<T>());
    }

    // Addition when is_compount<T> return false, meaning that
    // we are dealing with non-compounding type. Simply add
    // the two terms together when that is the cae
    template<typename T>
    T Addition_impl(const T& t1, const T& t2, std::false_type is_compound) {
        return t1 + t2;
    }

    // Addition when is_compound<T> return true, meaning that
    // we are dealing with compounding type. In that case, we have
    // to perform iteration and element-wise addition.
    template<typename T>
    T Addition_impl(const T& t1, const T& t2, std::true_type is_compound) {
        T result = t1;
        std::size_t size = t1.size();
        for (std::size_t i = 0; i < size; i++) {
            result[i] = t1[i] + t2[i];
        }
        return result;
    }

    template <typename T>
    T Addition(const T& t1, const T& t2)
    {
        return Addition_impl(t1, t2, std::is_compound<T>());
    }

    // AdditionInverse when is_compound<T> return false, meaning that
    // we are dealing with non-compounding type. Simply return the
    // negative of the value
    template<typename T>
    T AdditiveInverse_impl(const T& t, std::false_type) {
        return -t;
    }

    // AdditionInverse when is_compound<T> return true, meaning that
    // we are dealing with compounding type. In that case, simply add
    // 
    template<typename T>
    T AdditiveInverse_impl(const T& t, std::true_type) {
        T result = t;
        std::size_t size = t.size();
        for (std::size_t i = 0; i < size; ++i) {
            result[i] = -t[i];
        }
        return result;
    }

    template <typename T>
    T AdditiveInverse(T& val)
    {
        return AdditiveInverse_impl(val, std::is_compound<T>());
    }

    // Multiplication function for vector and scalar ordering
    template <typename T1, typename T2>
    auto Multiplication_impl(const T1& val1, const T2& val2,
        std::true_type is_val1_compound, std::false_type is_val2_compound)
    {
        T1 result = val1;
        std::size_t size = val1.size();
        for (std::size_t i = 0; i < size; ++i) {
            result[i] = val1[i] * val2;
        }
        return result;
    }

    // Multiplication function for scalar-vector multiplication
    template <typename T1, typename T2>
    auto Multiplication_impl(const T1& val1, const T2& val2,
        std::false_type is_val1_compound, std::true_type is_val2_compound)
    {
        return Multiplication_impl(val2, val1, std::true_type{}, std::false_type{});
    }

    // Multiplication function for scalar-scalar multiplication
    template <typename T1, typename T2>
    auto Multiplication_impl(const T1& val1, const T2& val2,
        std::false_type is_val1_compound, std::false_type is_val2_compound)
    {
        return val1 * val2;
    }

    // Multiplication base function. This will first checks the type, and then
    // call the implementation with the correct type
    template <typename T1, typename T2>
    auto Multiplication(const T1& val1, const T2& val2)
    {
        return Multiplication_impl(val1, val2, std::is_compound<T1>(), std::is_compound<T2>());
    }
}  // namespace

int main21() {
    // a) Define addition of two vectors
    // Test for scalar type
    // This should returns 8.0
    double scalar1 = 5.0;
    double scalar2 = 3.0;
    double scalarSum = Addition(scalar1, scalar2);
    std::cout << "Scalar Addition: ";
    Print(scalarSum);  // 8.0
    std::cout << std::endl;

    // Test for std::array
    // This should print out 5.0, 7.0, 9.0.
    std::array<double, 3> arr1 = { 1.0, 2.0, 3.0 };
    std::array<double, 3> arr2 = { 4.0, 5.0, 6.0 };
    std::array<double, 3> arrSum = Addition(arr1, arr2);
    std::cout << "Array Addition: ";
    Print(arrSum);  // 5.0, 7.0, 9.0
    std::cout << std::endl;

    // Test for std::vector
    // This should print out 5.0, 7.0, 9.0.
    std::vector<double> vec1 = { 1.0, 2.0, 3.0 };
    std::vector<double> vec2 = { 4.0, 5.0, 6.0 };
    std::vector<double> vecSum = Addition(vec1, vec2);
    std::cout << "Vector Addition: ";
    Print(vecSum);  // 5.0, 7.0, 9.0
    std::cout << std::endl;

    // Test for std::vector<std::complex<double>>
    // This should print out 5.0, 7.0, 9.0.
    std::vector<std::complex<double>> complexVec1 = { {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0} };
    std::vector<std::complex<double>> complexVec2 = { {4.0, 4.0}, {5.0, 5.0}, {6.0, 6.0} };
    std::vector<std::complex<double>> complexVecSum = Addition(complexVec1, complexVec2);
    std::cout << "Complex vector Addition: ";
    Print(vecSum);  // 5.0 + 5.0i, 7.0 + 7.0i, 9.0 + 9.0i
    std::cout << std::endl;


    // b) Define additive inverse
    std::cout << "Scalar Additiive Inverse: ";
    double scalarInverse = AdditiveInverse(scalarSum);  // -8.0
    Print(scalarInverse);
    std::cout << std::endl;

    std::cout << "Array Additiive Inverse: ";
    std::array<double, 3> arrInverse = AdditiveInverse(arrSum);  // -5.0, -7.0, -9.0
    Print(arrInverse);
    std::cout << std::endl;

    std::cout << "Vector Additiive Inverse: ";
    std::vector<double> vecInverse = AdditiveInverse(vecSum);  // -5.0, -7.0, -9.0
    Print(vecInverse);
    std::cout << std::endl;

    std::cout << "Complex Vector Additiive Inverse: ";
   std::vector<std::complex<double>> complexVecInverse = AdditiveInverse(complexVecSum);  // -5.0, -7.0, -9.0
    Print(complexVecInverse);
    std::cout << std::endl;

    // c) Define a function for scalar multiplication of a scalar and an array
    // producing a new array. Determine the signature of this function.
    // We will reuse scalarSum and arrSum. This should create the following multiplication
    // 8 * (5, 7, 9) and returns 40, 56, 72
    std::vector<double> vecMult1 = Multiplication(scalarSum, vecSum);  // 40, 56, 72
    std::cout << "ScalarSum x arraySum ";
    Print(vecMult1);
    std::cout << std::endl;

    std::vector<double> vecMult2 = Multiplication(vecSum, scalarSum);  // 40, 56, 72
    std::cout << "arraySum x scalarSum ";
    Print(vecMult2);
    std::cout << std::endl;

    int scalarMult = Multiplication(scalarSum, scalarSum);          // 64
    std::cout << "scalarSum x scalarSum ";
    Print(scalarMult);
    std::cout << std::endl;

    std::vector<std::complex<double>> complexVecMult = Multiplication(complexVecSum, scalarSum);          // 64
    std::cout << "complexVecSum x scalarSum ";
    Print(complexVecMult);  // 40 + 40i, 56 + 56i, 72 + 72i
    std::cout << std::endl;

    // d) Test these three functions for double, std::array<double, N>and std::vector<double>.
    // Each test was included above.

    // e) Test the functions on containers whose underlying type is std::complex<double>.
    // Again, already tested above.
    return 0;
}