/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 1, Exercise 2
Compiled in C++ 20
*/

#include <algorithm>
#include <complex>
#include <iostream>
#include <numeric>
#include <vector>

struct FOMultiply
{
    template <typename T>
    T operator () (const T& x, const T& y)
    {
        return x * y;
    }
};

template <typename T>
T MyMultiply2(const T& x, const T& y) { return x * y; };

using Complex = std::complex<double>;

// b) Implement the accumulation algorithm using an ebemdded lambda function in
// combination with std::for_each and captured variables.
//
// I first define a function, and then
template<typename T, typename Func>
T MyAccumulate(const std::vector<T>& arr, T& init_value, Func func) {
    std::for_each(arr.begin(), arr.end(), [&init_value, &func](T a) {
        init_value = func(init_value, a);
        });
    return init_value;
};


int main12() {
    std::vector<int> vec{ 1,2,3,4,5 };

    int value1 = 1;
    int acc1 = std::accumulate(vec.begin(), vec.end(), value1,
        std::multiplies<int>());

    int value2 = 1;
    int acc2 = std::accumulate(vec.begin(), vec.end(),
        value2, FOMultiply());

    int value3 = 1;
    auto MyMultiply = [](auto x, auto y) { return x * y; };
    int acc3 = std::accumulate(vec.begin(), vec.end(),
        value3, MyMultiply);


    // a) Implement and test the algorithm using the genetic lambda
    // I am not sure what we actually have to test here to be honest
    // since the code was already given. Therefore, I will simply
    // just printing out the results here
    std::cout << "Using std::multiplies<int>() gives: " << acc1 << std::endl;
    std::cout << "Using FOMultiply() gives: " << acc2 << std::endl;
    std::cout << "Using MyMultiply gives: " << acc3 << std::endl;

    // We will now use this with complex numbers to see if the code works.
    std::vector<Complex>
        complex_array{ Complex(1.0, 1.0), Complex(2.0, 2.0) };
    Complex init_value1(1.0, 1.0);

    Complex acc_comp = std::accumulate(complex_array.begin(),
        complex_array.end(), init_value1, MyMultiply2<Complex>);
    std::cout << "Multiply complex numbers: " << acc_comp << std::endl;
 
    // b) Implement the accumulation algorithm using an ebemdded lambda function in
    // combination with std::for_each and captured variables.
    //
    // The implementation of the template function was done outside of the main block.
    // This will test the call
    int value_int = 1;
    Complex value_complex(1.0, 1.0);
    MyAccumulate(vec, value_int, MyMultiply);
    std::cout << "Multiply integer with customer made MyAccumulate: " << value_int << std::endl;
    MyAccumulate(complex_array, value_complex, MyMultiply);
    std::cout << "Multiply integer with customer made MyAccumulate: " << value_complex << std::endl;

    // c) Give an example of a stored lambda function that may be called from an 
    // STL algorithm (may be any relevant STL algorithm). Demonstrate using the STL 
    // algorithm with your stored lambda.
    //
    // I am not sure about this exercise. It seems that we already kind of demonstrated this
    // with so many examples and the use of accumulate above. Therefore, I will demonstrate a
    // new example with the use of std::sort()
    std::vector<int> v = { 2, 4, 7, 1, 0, 6, 8, 9, 3, 5 };

    auto reverse_sort_func = [](int a, int b) -> bool {
        return a >= b;
    };
    std::sort(v.begin(), v.end(), reverse_sort_func);

    for (const auto& num : v) {
        std::cout << num << ", "; // prints "9, 8, 7, 6, 5, 4, 3, 2, 1, 0"
    }
    std::cout << std::endl;
    return 0;
}