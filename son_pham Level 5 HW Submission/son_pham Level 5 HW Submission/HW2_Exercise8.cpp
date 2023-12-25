/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2, Exercise 8: Time Series Data, mini-application
*/

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <string>
#include <vector>

 using namespace boost::gregorian;

 namespace {
     using Data = std::tuple<boost::gregorian::date, std::vector<double>>;
     using ResultSet = std::list<Data>;

     ResultSet processCSVFile(const std::string& filename) {
         ResultSet resultSet;

         std::ifstream inputFile(filename);
         if (!inputFile.is_open()) {
             throw std::runtime_error("Failed to open input file.");
         }

         std::string line;
         getline(inputFile, line);  // Read and discard the header line

         while (getline(inputFile, line)) {
             try {
                 boost::regex rowRegex(R"((\d{4}-\d{2}-\d{2}),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*),([^,]*))");
                 boost::smatch matches;
                 if (boost::regex_match(line, matches, rowRegex)) {
                     boost::gregorian::date date(boost::gregorian::from_simple_string(matches[1]));
                     std::vector<double> values;
                     for (size_t i = 2; i < matches.size(); ++i) {
                         values.push_back(boost::lexical_cast<double>(matches[i]));
                     }
                     resultSet.push_back(std::make_tuple(date, values));
                 }
                 else {
                     std::cerr << "Invalid CSV row format: " << line << std::endl;
                 }
             }
             catch (const std::exception& e) {
                 std::cerr << "Error processing row: " << e.what() << std::endl;
             }
         }

         inputFile.close();
         return resultSet;
     }

     void printResultSet(const ResultSet& resultSet) {
         for (const auto& data : resultSet) {
             boost::gregorian::date date = std::get<0>(data);
             const std::vector<double>& values = std::get<1>(data);

             std::cout << "Date: " << boost::gregorian::to_iso_extended_string(date) << std::endl;
             for (size_t i = 0; i < values.size(); ++i) {
                 std::cout << "Value " << i + 1 << ": " << values[i] << std::endl;
             }
             std::cout << "-----------------------" << std::endl;
         }
     }
 }

 int main28() {
     try {
         ResultSet resultSet = processCSVFile("data.csv");
         // ResultSet resultSet = processCSVFile("data2.csv");
         // The line below should return an error due to file not existing.

         // Print out the processed data
         printResultSet(resultSet);
         return 0;
     }
     catch (const std::exception& e) {
         std::cerr << "An error occurred: " << e.what() << std::endl;
         return 1;
     }

     // Some comments: I did try to actually create a far more generic version,
     // which is reading the file on its own and determine the type based
     // on some value data. In the end, I give up because it did turn out
     // to be way more complicated than I thought. I also think that in terms
     // of engineering principle, sending around a file with unknown column
     // signature across team is a pretty bad design and an organization problem.
     //
     // In the end, I write the file assuming that the columns and types
     // are already known before hand.
 }