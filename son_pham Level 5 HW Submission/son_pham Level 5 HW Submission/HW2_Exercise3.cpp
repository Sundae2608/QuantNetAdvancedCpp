/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 3: Regex Iterators, sregex_iterator 101
*/

#include <iostream>
#include <regex>
#include <set>
#include <string>

int main23() {
    std::string S2 = "1,1,2,3,5,8,13,21";
    std::regex myReg("(\\d+),?");

    std::set<std::string> result;

    // a) Create an instance it of sregex_iterator
    std::sregex_iterator it(S2.begin(), S2.end(), myReg);
    std::sregex_iterator end;

    // b) Iterate over , converting its dereferenced value and inserting it into
    // the output result.
    while (it != end) {
        result.insert((*it)[1]); // [1] represents the first capturing group in the
        // regular expression
        ++it;
    }

    // c) Print the result
    for (const std::string& value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Part d) Modify the program to use std::set<int> as output
    std::set<int> result2;
    std::sregex_iterator it2(S2.begin(), S2.end(), myReg);
    std::sregex_iterator end2;

    while (it2 != end2) {
        int value =
            std::stoi((*it2)[1]); // Convert the matched string to an integer
        result2.insert(value);
        ++it2;
    }

    for (int value : result2) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}