/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 1, Exercise 2: Classification
*/

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <string>

namespace {
    bool is_digit_or_letter(char c) { return std::isalnum(c); }

    bool is_digit_and_not_letter(char c) {
        return std::isdigit(c) && !std::isalpha(c);
    }

    bool is_char_in_range(char c) {
        return std::islower(c) && c >= 'a' && c <= 'z';
    }

    std::pair<bool, std::string> is_valid_password(const std::string& password) {
        if (password.length() < 8) {
            return std::make_pair(false,
                "Password must contain at least 8 characters.");
        }

        bool has_digit = false;
        bool has_character = false;
        bool has_uppercase = false;

        for (char c : password) {
            if (std::iscntrl(c) || std::isspace(c)) {
                return std::make_pair(false, "No control characters or spaces allowed.");
            }

            if (std::isdigit(c)) {
                has_digit = true;
            }
            else if (std::isalpha(c)) {
                has_character = true;
                if (std::isupper(c)) {
                    has_uppercase = true;
                }
            }
        }

        if (!has_digit || !has_character || !has_uppercase) {
            return std::make_pair(false,
                "Password must contain a combination of digits, "
                "characters, and an uppercase letter.");
        }

        return std::make_pair(true, "Password is valid.");
    }

} // namespace

int main12() {
    // a) Consider the string std::string str1(" abd1 234\*"). Which predicates
    // will you use to test the following and what is the outcome (true or
    // false) (use function all())
    // P1 Recognize digits or letters.
    // P2 Recognize digits and not letters.
    // P3 Recognize characters from the range [‘a’,’z’].
    std::string str1(" abd1 234*");

    // P1: Recognize digits or letters.
    bool p1_result = std::all_of(str1.begin(), str1.end(), is_digit_or_letter);

    // P2: Recognize digits and not letters.
    bool p2_result =
        std::all_of(str1.begin(), str1.end(), is_digit_and_not_letter);

    // P3: Recognize characters from the range ['a', 'z'].
    bool p3_result = std::all_of(str1.begin(), str1.end(), is_char_in_range);

    std::cout << "P1 Result: " << std::boolalpha << p1_result << std::endl;
    std::cout << "P2 Result: " << std::boolalpha << p2_result << std::endl;
    std::cout << "P3 Result: " << std::boolalpha << p3_result << std::endl;

    // Create a simple password checker function that accepts a target string as
    // input and result type of (true or false) and a string stating the cause of
    // possible error or success. Requirements are:
    // - It must contain at least 8 characters.
    // - It must contain a combination of digits and characters.
    // - At least one character must be upper case.
    // - No control characters allowed.
    // - No spaces allowed.
    // What is the return type in these cases?
    // I think it is the most convenient to return a pair of value, a boolean
    // representing whether the password is valid, and a string to shows
    // the error of that password.
    std::string pwd1("DanielDuffy1952");
    std::string pwd2("DanielDuffy");
    std::string pwd3("U19520829");
    std::string pwd4("19520829U");

    auto result1 = is_valid_password(pwd1);
    std::cout << "Password 1: " << std::boolalpha << result1.first << " ("
        << result1.second << ")" << std::endl;

    auto result2 = is_valid_password(pwd2);
    std::cout << "Password 2: " << std::boolalpha << result2.first << " ("
        << result2.second << ")" << std::endl;

    auto result3 = is_valid_password(pwd3);
    std::cout << "Password 3: " << std::boolalpha << result3.first << " ("
        << result3.second << ")" << std::endl;

    auto result4 = is_valid_password(pwd4);
    std::cout << "Password 4: " << std::boolalpha << result4.first << " ("
        << result4.second << ")" << std::endl;

    return 0;
}