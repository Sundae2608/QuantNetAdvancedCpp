/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 5, Exercise 2: Application I, Numeric Algorithms with Tuples
Compiled in C++ 20
*/

#include <algorithm>
#include <complex>
#include <iostream>
#include <tuple>

template <typename T, typename Tuple, std::size_t N>
struct Calculator
{
    static T max(const Tuple& values)
    {   
        return maxHelper(values, std::make_index_sequence<N>{});
    }

    static T sum(const Tuple& values)
    {
        return sumHelper(values, std::make_index_sequence<N>{});
    }

    static double avg(const Tuple& values)
    {
        return static_cast<double>(sumHelper(values, std::make_index_sequence<N>{})) / static_cast<double>(N);
    }

private:

    template <std::size_t... Is>
    static T maxHelper(const Tuple& values, std::index_sequence<Is...>)
    {
        return std::max({ std::get<Is>(values)... });
    }

    template <std::size_t... Is>
    static T sumHelper(const Tuple& values, std::index_sequence<Is...>)
    {
        return (static_cast<T>(std::get<Is>(values)) + ...);
    }
};


int main52()
{
    // 2b. Test the code on tuples on elements whose underlying type is double
    std::cout << "2b. Double tuples" << std::endl;
    std::tuple<double, double, double, double> doubleTuple{ 1.0, 2.0, 3.0, 4.0 };
    double maxVal = Calculator<double, std::tuple<double, double, double, double>, 4>::max(doubleTuple);
    std::cout << "Max value: " << maxVal << std::endl;

    double sumVal = Calculator<double, std::tuple<double, double, double, double>, 4>::sum(doubleTuple);
    std::cout << "Sum value: " << sumVal << std::endl;

    double avgVal = Calculator<double, std::tuple<double, double, double, double>, 4>::avg(doubleTuple);
    std::cout << "Average value: " << avgVal << std::endl;

    // 2c. Test the code on tuples on elements whose underlying type is double
    // This returns a warning STL4037 saying that std::complex should only be defined
    // for float, double or long. Therefore, I will go with std::complex<double> for
    // the time being.
    std::cout << std::endl << "2c. Complex tuples" << std::endl;
    std::complex<double> c1(1, 1);
    std::complex<double> c2(2, 2);
    std::complex<double> c3(3, 3);
    std::tuple<std::complex<double>, std::complex<double>, std::complex<double>> complexTuple{ c1, c2, c3 };

    std::complex<double> sumC = Calculator<std::complex<double>, std::tuple<std::complex<double>, std::complex<double>, std::complex<double>>, 3>::sum(complexTuple);
    std::cout << "Sum value: " << sumC << std::endl;

    std::complex<double> avgC = Calculator<std::complex<double>, std::tuple<std::complex<double>, std::complex<double>, std::complex<double> >, 3>::sum(complexTuple);
    std::cout << "Avg value: " << sumC << std::endl;

    return 0;
}