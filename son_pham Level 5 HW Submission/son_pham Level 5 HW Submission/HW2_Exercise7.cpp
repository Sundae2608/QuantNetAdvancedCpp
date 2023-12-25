/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 7: Replacing Regular Expressions
*/

#include <iostream>
#include <regex>
#include <string>

int main27() {
    std::string text("Quick brown fox");
    std::regex vowels("a|e|i|o|u");

    std::string replacedText = std::regex_replace(text, vowels, "*");

    std::cout << replacedText << std::endl;

    return 0;
}