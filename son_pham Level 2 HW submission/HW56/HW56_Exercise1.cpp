/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
*  Exercise 5/6, Exercise 1: Classifying Numbers
*/

#include <iostream>
#include <limits>
#include <cmath>

template <typename T>
const char* Classify(T t)
{
    switch (std::fpclassify(t))
    {
    case FP_INFINITE:  return "Inf";
    case FP_NAN: return "NaN";
    case FP_NORMAL:    return "normal";
    case FP_SUBNORMAL: return "subnormal";
    case FP_ZERO: return "zero";
    default:  return "unknown";
    }
}

int main51() {
    // a) Test this function for the following values
    constexpr double val = std::numeric_limits<double>::max();
    std::cout << "Category of " << val << ": " << Classify(val) << std::endl;  // Normal (1.79769e+308)
    std::cout << "Category of " << 2.0 * val << ": " << Classify(2.0 * val) << std::endl;  // Inf (Inf)
    std::cout << "Category of " << 3.1415 + val << ": " << Classify(3.1415 + val) << std::endl;  // Normal (1.79769e+308)
    // One intresting thing is that the addition to max double did not push the val to infinity, yet a multiplication did.

    constexpr double val2 = std::numeric_limits<double>::min() - 3.1415;
    std::cout << "Category of " << val2 << ": " << Classify(val2) << std::endl;  // Normal (-3.1415)
    std::cout << "Category of " << val2 / 2.0 << ": " << Classify(val2 / 2.0) << std::endl;  // Normal (-1.57075)

    constexpr double val3 = DBL_MIN / 2.0;
    std::cout << "Category of " << val3 << ": " << Classify(val3) << std::endl;  // subnormal (1.11254e-308)

    // b) Apply the functions std::isfinite, std::isinf, std::isnan, std::isnormal to the following values:
    double factor = 2.0;
    double val4 = factor * std::numeric_limits<double>::max();
    std::cout << std::boolalpha;
    std::cout << val4 << std::endl;  // Inf
    std::cout << "Is finite? " << std::isfinite(val4) << std::endl;  // false
    std::cout << "Is infinite? " << std::isinf(val4) << std::endl;   // true
    std::cout << "Is NaN? " << std::isnan(val4) << std::endl;        // false
    std::cout << "Is normal? " << std::isnormal(val4) << std::endl;  // false

    double val5 = val4 - val4;
    std::cout << val5 << std::endl;  // -nan(ind)  -> Very interesting. 
    // C++ cannot deduce that this would equal 0. Instead, it treats this as an Inf operations.
    std::cout << "Is finite? " << std::isfinite(val5) << std::endl;  // false
    std::cout << "Is infinite? " << std::isinf(val5) << std::endl;   // false
    std::cout << "Is NaN? " << std::isnan(val5) << std::endl;        // true
    std::cout << "Is normal? " << std::isnormal(val5) << std::endl;  // false

    double val6 = std::sqrt(-1.0);  // -nan(ind)
    std::cout << val6 << std::endl;
    std::cout << "Is finite? " << std::isfinite(val6) << std::endl;  // false
    std::cout << "Is infinite? " << std::isinf(val6) << std::endl;   // false
    std::cout << "Is NaN? " << std::isnan(val6) << std::endl;        // true
    std::cout << "Is normal? " << std::isnormal(val6) << std::endl;  // false

    double val7 = std::log(0.0);  // -inf
    std::cout << val7 << std::endl;
    std::cout << "Is finite? " << std::isfinite(val7) << std::endl;  // false
    std::cout << "Is infinite? " << std::isinf(val7) << std::endl;   // true
    std::cout << "Is NaN? " << std::isnan(val7) << std::endl;        // false
    std::cout << "Is normal? " << std::isnormal(val7) << std::endl;  // false

    double val8 = std::exp(factor * std::numeric_limits<double>::max());
    std::cout << val8 << std::endl;  // inf
    std::cout << "Is finite? " << std::isfinite(val8) << std::endl;  // false
    std::cout << "Is infinite? " << std::isinf(val8) << std::endl;   // true
    std::cout << "Is NaN? " << std::isnan(val8) << std::endl;        // false
    std::cout << "Is normal? " << std::isnormal(val8) << std::endl;  // false
    return 0;
}