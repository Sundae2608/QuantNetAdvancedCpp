/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 7, Exercise 1: Boost and C++11 Error Condition
*/

#include <iostream>
#include <fstream>
#include <boost/system/error_code.hpp>

boost::system::error_condition OpenAndPrintFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return boost::system::error_condition(boost::system::errc::no_such_file_or_directory);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

    return boost::system::error_condition();
}

std::error_condition OpenAndPrintFileC11(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return std::make_error_condition(std::errc::no_such_file_or_directory);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();

    return {};
}

int main71() {
    // a) Write the code and test it using an existing file as input. The return type is boost::system::error condition.
    // b) We now need to check if the file exists. To this end, employ the function make_error_conditionand the scoped enumeration errc.
    // c) Test the code with an existing fileand a non - existing file.
    std::string filename = "example.txt"; 
    boost::system::error_condition result = OpenAndPrintFile(filename);
    if (result) {
        std::cout << "Error occurred: " << result.message() << std::endl;
    }
    else {
        std::cout << "File opened and printed successfully." << std::endl; // This file exists
    }


    std::string filename2 = "example5.txt";
    boost::system::error_condition result2 = OpenAndPrintFile(filename2);
    if (result2) {
        std::cout << "Error occurred: " << result2.message() << std::endl; // This file does not exist
    }
    else {
        std::cout << "File opened and printed successfully." << std::endl;
    }

    // d) Port the code to C++ 11 and test the program again.
    // To port the code to C++, we will use std::error_condition and std::make_error_condition instead
    std::error_condition c11_result1 = OpenAndPrintFileC11(filename);
    if (c11_result1) {
        std::cout << "Error occurred: " << c11_result1.message() << std::endl;
    }
    else {
        std::cout << "File opened and printed successfully." << std::endl; // This file exists
    }

    std::error_condition c11_result2 = OpenAndPrintFileC11(filename2);
    if (c11_result2) {
        std::cout << "Error occurred: " << c11_result2.message() << std::endl;
    }
    else {
        std::cout << "File opened and printed successfully." << std::endl; // This file exists
    }
    return 0;
}