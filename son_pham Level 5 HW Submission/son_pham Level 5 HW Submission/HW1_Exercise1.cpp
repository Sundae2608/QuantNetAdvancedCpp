/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 1, Exercise 1: String Algorithms Library
*/

#include <algorithm>
#include <iostream>
#include <string>

int main11() {
    // a) Trim leading and trailing blanks. Use two versions in which the input
    // string is modified and in which a copy of the input string is created. Use
    // the default character separator (blank space).
    std::cout << std::boolalpha;
    std::string input_string = "  hello world  ";

    // Modify the input string
    input_string.erase(input_string.begin(),
        std::find_if(input_string.begin(), input_string.end(),
            [](char c) { return !std::isspace(c); }));
    input_string.erase(std::find_if(input_string.rbegin(), input_string.rend(),
        [](char c) { return !std::isspace(c); })
        .base(),
        input_string.end());

    // Create a copy of the input string
    std::string copied_string = input_string;

    std::cout << "Modified: " << input_string << std::endl;
    std::cout << "Copied: " << copied_string << std::endl;

    // b) Perform the operations in part a) by trimming the string using different
    // predicates, for example trimming leading and trailing characters such as
    // “AAA”, for example. You can use Boolean operator such as OR and AND.
    input_string = "AAAhello worldAAA";

    // Trim leading and trailing "AAA"
    size_t start = input_string.find_first_not_of("A");
    size_t end = input_string.find_last_not_of("A");
    std::string modified_string = input_string.substr(start, end - start + 1);

    std::cout << "Modified: " << modified_string << std::endl;

    // c) Test if a string starts or ends with a given string. Consider both
    // case-sensitive and case-insensitive variants.
    input_string = "Hello World";

    bool starts_with_hello = input_string.rfind("Hello", 0) == 0;
    bool ends_with_world = input_string.size() >= 5 &&
        input_string.rfind("World") == input_string.size() - 5;

    std::cout << "Starts with Hello: " << starts_with_hello << std::endl;
    std::cout << "Ends with World: " << ends_with_world << std::endl;

    // Case-insensitive variants
    // We achieve this basically by transform both the input string and the
    // checking string to lower-case.
    std::string lower_input = input_string;
    std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(),
        ::tolower);

    bool starts_with_hello_insensitive = lower_input.rfind("hello", 0) == 0;
    bool ends_with_world_insensitive =
        lower_input.size() >= 5 &&
        lower_input.rfind("world") == lower_input.size() - 5;

    std::cout << "Starts with Hello (case-insensitive): "
        << starts_with_hello_insensitive << std::endl;
    std::cout << "Ends with World (case-insensitive): "
        << ends_with_world_insensitive << std::endl;

    // d) Test if a string contains another string. Consider both case-sensitive
    // and case-insensitive variants. Test if two strings are equal.
    input_string = "Hello World";
    std::string contains_string = "Hello";

    bool contains_hello = input_string.find(contains_string) != std::string::npos;

    // Case-insensitive variant
    lower_input = input_string;
    std::transform(lower_input.begin(), lower_input.end(), lower_input.begin(),
        ::tolower);
    std::string lower_contains = contains_string;
    std::transform(lower_contains.begin(), lower_contains.end(),
        lower_contains.begin(), ::tolower);

    bool contains_hello_insensitive =
        lower_input.find(lower_contains) != std::string::npos;

    std::cout << "Contains Hello: " << contains_hello << std::endl;
    std::cout << "Contains Hello (case-insensitive): "
        << contains_hello_insensitive << std::endl;

    // Test if two strings are equal
    std::string string1 = "Hello";
    std::string string2 = "hello";

    bool are_equal_case_sensitive = string1 == string2;

    std::string lower_string1 = string1;
    std::transform(lower_string1.begin(), lower_string1.end(),
        lower_string1.begin(), ::tolower);
    std::string lower_string2 = string2;
    std::transform(lower_string2.begin(), lower_string2.end(),
        lower_string2.begin(), ::tolower);

    bool are_equal_case_insensitive = lower_string1 == lower_string2;

    std::cout << "Equal strings (case-sensitive): " << are_equal_case_sensitive
        << std::endl;
    std::cout << "Equal strings (case-insensitive): "
        << are_equal_case_insensitive << std::endl;

    return 0;
}