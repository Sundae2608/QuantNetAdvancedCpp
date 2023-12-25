/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 4: Token Iterator, std::sregex_token_iterator
*/

#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main24() {
    // a) Consider the regular expression and the target string:
    // std::regex myReg10("/");
    // std::string S3 = "2016/3/15";
    // Extract the data 2016, 3 and 15 from this string.
    std::regex myReg10("/");
    std::string S3 = "2016/3/15";

    std::vector<std::string> extractedData;

    std::sregex_token_iterator it(S3.begin(), S3.end(), myReg10, -1);
    std::sregex_token_iterator end;

    while (it != end) {
        extractedData.push_back(*it);
        ++it;
    }

    for (const std::string& data : extractedData) {
        std::cout << data << " ";
    }
    std::cout << std::endl;

    // b) Extract ‘/’ from this string.
    std::vector<std::size_t> extractedPositions;

    std::sregex_token_iterator it2(S3.begin(), S3.end(), myReg10, 0);
    std::sregex_token_iterator end2;

    while (it2 != end2) {
        extractedPositions.push_back(it2->first - S3.begin());
        ++it2;
    }

    for (std::size_t position : extractedPositions) {
        std::cout << "Position: " << position << std::endl;
    }

    return 0;
    // c) Choose appropriate data structures to contain the extracted data in both
    // cases.
    // For the first case, we return std::vector<std::string> since we are
    // interested in the actual information. For the second case, we return an
    // std::vector<size_t> since we are interested in the position in which the
    // match happens.
}