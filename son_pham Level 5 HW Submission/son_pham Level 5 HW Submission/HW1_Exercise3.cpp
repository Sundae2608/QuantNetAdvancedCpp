/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 1, Exercise 3: Splitting and Joining of Strings
*/

#include <algorithm>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

namespace {
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream iss(str);
        std::string token;
        while (std::getline(iss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::string join(const std::vector<std::string>& strings, char delimiter) {
        std::ostringstream oss;
        for (size_t i = 0; i < strings.size(); ++i) {
            oss << strings[i];
            if (i < strings.size() - 1) {
                oss << delimiter;
            }
        }
        return oss.str();
    }

     boost::gregorian::date convertToDate(const std::string &dateString) {
       try {
         int year = boost::lexical_cast<int>(dateString.substr(0, 4));
         int month = boost::lexical_cast<int>(dateString.substr(5, 2));
         int day = boost::lexical_cast<int>(dateString.substr(8, 2));
         return boost::gregorian::date(year, month, day);
       } catch (const boost::bad_lexical_cast &) {
         throw std::runtime_error("Invalid date format");
       }
     }

    std::map<std::string, double> convertToMap(const std::string& input) {
        std::map<std::string, double> result;
        std::istringstream iss(input);
        std::string pair;
        while (std::getline(iss, pair, ',')) {
            size_t equalsPos = pair.find('=');
            if (equalsPos != std::string::npos) {
                std::string key = pair.substr(0, equalsPos);
                double value = std::stod(pair.substr(equalsPos + 1));
                result[key] = value;
            }
        }
        return result;
    }
} // namespace

int main13() {
    // a) Consider the string std::string sA("1,2,3,4/5/9*56"). It has
    // delimiters / and *. Split this string into a vector of strings and then
    // join them to form the string std::string sA("1/2/3/4/5/9/56").
    std::string sA("1,2,3,4/5/9*56");
    std::vector<std::string> parts = split(sA, ',');
    std::string joined = join(parts, '/');

    std::cout << "Joined string: " << joined << std::endl;

    // b) Consider a string that models dates, for example “2015-12-31”. Write a
    // function that converts strings having this format into a Boost date. You
    // will need to use Boost lexical_cast to convert strings to integers.
    std::string dateString("2015-12-31");
    boost::gregorian::date date = convertToDate(dateString);
    std::cout << "Converted date: " << date << std::endl;

    // c) Consider a string consisting of string pairs of the form key = value
    // (for example, port = 23, pin = 87, value = 34.4). Write a function to
    // convert the string to an instance of std::map<std::string, double>. In
    // other words, we create name-value maps.
    std::string input("port=23,pin=87,value=34.4");
    std::map<std::string, double> resultMap = convertToMap(input);

    for (const auto& pair : resultMap) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }

    return 0;
}
