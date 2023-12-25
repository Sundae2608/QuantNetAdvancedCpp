/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 5: Extracting name-value pairs, using Regex and String Algo
*/
/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 5: Extracting name-value pairs, using Regex and String Algo
*/

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

int main25() {
    // a) Consider string of the form std::string sA("a = 1, b = 2, c = 3").
    // Define a regular expression defined by the delimiter “,”. Use
    // std::sregex_token_iterator to extract strings of the form “a = 1” etc.
    std::string sA("a = 1, b = 2, c = 3");
    std::regex myReg(",");

    std::vector<std::string> extractedPairs;

    std::sregex_token_iterator it(sA.begin(), sA.end(), myReg, -1);
    std::sregex_token_iterator end;

    while (it != end) {
        extractedPairs.push_back(*it);
        ++it;
    }

    for (const std::string& pairStr : extractedPairs) {
        std::cout << "Pair: " << pairStr << std::endl;
    }

    // b) For each generated string from part a) use Boost Algo split() to extract
    // its left and right parts, which will become the map’s key and the value,
    // respectively.
    std::map<std::string, std::string> keyValueMap;
    for (const std::string &pairStr : extractedPairs) {
        std::vector<std::string> keyValue;
        boost::split(keyValue, pairStr, boost::is_any_of("="));
        if (keyValue.size() == 2) {
            boost::trim(keyValue[0]);
            boost::trim(keyValue[1]);
            keyValueMap[keyValue[0]] = keyValue[1];
        }
    }

    for (const auto &pair : keyValueMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second
                    << std::endl;
    }
    return 0;
}