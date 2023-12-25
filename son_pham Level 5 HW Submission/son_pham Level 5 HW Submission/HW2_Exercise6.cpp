/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 6: ECMAScript Grammar Example
*/

#include <iostream>
#include <regex>
#include <string>

int main26() {
    // a) What kinds of numbers does this regular expression subsume?
    //
    // This regular expression represents a pattern for recognizing
    // floating-point numbers in scientific notation. Specifically, it can match
    // numbers that have an optional sign (+ or -), an integer or decimal part,
    // an optional fractional part, and an optional exponent part in the form of
    // e or E followed by another optional sign and an integer exponent value.
    // In other words, this pattern matches numbers in various formats, such as:

    // 123
    // -45.67
    // 0.123
    // 1.0e6
    // -2.5E-3

    // b) Create a program to test valid and invalid numbers.
    std::regex ecmaReg("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|"
        "-)?)[[:digit:]]+)?");

    std::string numberStrings[] = {// Valid
                                   "123", "-45.67", "0.123", "1.0e6", "-2.5E-3",
                                   // Invalid
                                   "abc", "12.34.56", "1.2e3.4", "-1.2E-", "+" };

    for (const std::string& num : numberStrings) {
        if (std::regex_match(num, ecmaReg)) {
            std::cout << num << " is a valid number." << std::endl;
        }
        else {
            std::cout << num << " is NOT a valid number." << std::endl;
        }
    }

    // c) For valid numbers, convert them to double.
    for (const std::string& num : numberStrings) {
        if (std::regex_match(num, ecmaReg)) {
            double convertedNumber = std::stod(num);
            std::cout << "Original: " << num << ", Converted: " << convertedNumber
                << std::endl;
        }
        else {
            std::cout << num << " is NOT a valid number." << std::endl;
        }
    }

    return 0;
}