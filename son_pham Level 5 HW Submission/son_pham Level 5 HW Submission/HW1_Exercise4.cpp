/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 1, Exercise 4:Time Series Data, mini-application
*/

#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <vector>

namespace {
    using Data = std::tuple<boost::gregorian::date, std::vector<double>>;
    using ResultSet = std::list<Data>;

    ResultSet readCSVFile(const std::string& filename) {
        ResultSet resultSet;

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file." << std::endl;
            return resultSet;
        }

        // Skip the header line
        std::string header;
        std::getline(file, header);

        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> tokens;
            boost::split(tokens, line, boost::is_any_of(","));

            if (tokens.size() >= 7) {
                std::string dateString = tokens[0];
                boost::gregorian::date date = boost::gregorian::from_string(dateString);

                std::vector<double> values;
                for (size_t i = 1; i < tokens.size(); ++i) {
                    double value = boost::lexical_cast<double>(tokens[i]);
                    values.push_back(value);
                }

                Data data = std::make_tuple(date, values);
                resultSet.push_back(data);
            }
        }

        return resultSet;
    }
}

int main14() {
    ResultSet resultSet = readCSVFile("data.csv");

    // Print the result set
    for (const Data& data : resultSet) {
        boost::gregorian::date date;
        std::vector<double> values;
        std::tie(date, values) = data;

        std::cout << "Date: " << date << std::endl;
        for (double value : values) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}