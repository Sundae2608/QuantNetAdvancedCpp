/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 7, Exercise 1: Boost and C++11 Error Condition
*/

#include <iostream>
#include <fstream>
#include <boost/system/error_code.hpp>

std::tuple<std::string, int, std::string> GetErrorConditionInfo(const std::error_condition& errorCondition) {
    std::string categoryName = errorCondition.category().name();
    int errorCodeValue = errorCondition.value();
    std::string errorMessage = errorCondition.message();

    return std::make_tuple(categoryName, errorCodeValue, errorMessage);
}

int main72() {
    // a) Create instances of std::error_condition based on the following requirements:
    // Default constructor
    std::error_condition default_error_condition;

    // Value and error category
    std::error_code error_code = std::make_error_code(std::errc::no_such_file_or_directory);
    std::error_condition error_condition(error_code.default_error_condition());

    // Based on std::errc code
    std::error_condition errc_error_condition = std::make_error_condition(std::errc::argument_out_of_domain);

    // b) Create a function that returns the following information pertaining to instances of std::error_condition:
    std::tuple<std::string, int, std::string> error_info = GetErrorConditionInfo(error_condition);

    std::cout << "Category: " << std::get<0>(error_info) << std::endl;    // Category: generic
    std::cout << "Error Code: " << std::get<1>(error_info) << std::endl;  // Error Code: 2
    std::cout << "Message: " << std::get<2>(error_info) << std::endl;     // Message: no such file or directory
    return 0;
}