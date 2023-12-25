/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 2: Searching, regex_search()
*/

#include <iostream>
#include <regex>
#include <string>

int main22() {
    std::regex mySearchReg("(rain)|(Spain)");
    std::string myText("The rain in Spain stays mainly on the plain");
    std::smatch match;

    std::cout << myText << std::endl;
    if (std::regex_search(myText, match, mySearchReg)) {
        for (size_t i = 0; i < match.size(); ++i) {
            if (match[i].matched) {
                std::cout << "Submatch " << i << ": " << match[i].str() << std::endl;
            }
        }
    }
    else {
        std::cout << "No match found" << std::endl;
    }

    // This file prints the following:
    // Submatch 0: rain
    // Submatch 1: rain
    // Interestingly enough, only rain gets matched, but spain doesn't get matched
    // here. I wonder if it just means that once the first match is completed,
    // then the second matched never gets checked. Therefore, I tried changing the
    // string a little bit and see how it goes.
    std::smatch match2;
    std::string myText2("The rai in Spain stays mainly on the plain");
    std::cout << myText2 << std::endl;
    if (std::regex_search(myText2, match2, mySearchReg)) {
        for (size_t i = 0; i < match2.size(); ++i) {
            if (match2[i].matched) {
                std::cout << "Submatch " << i << ": " << match2[i].str() << std::endl;
            }
        }
    }
    else {
        std::cout << "No match found" << std::endl;
    }
    // This prints the following:
    // Submatch 0 : Spain
    // Submatch 2 : Spain
    // Hmm, interestingly, it seems that each of the matching index actually
    // refers to the permutation of the regex.
    // Match 0 is for: "(rain)|(Spain)"
    // Match 1 is for: "(rain)"
    // Match 2 is for: "(Spain)"
    return 0;
}