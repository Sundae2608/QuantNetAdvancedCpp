/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 7, Exercise 1: Boost Bimap
*/
#include <iostream>
#include <string>
#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>

int main71() {

    // a) Populate the bimap with some names using insert().
    using namespace boost::bimaps;
    typedef bimap<set_of<std::string>, multiset_of<int>> BimapType;
    BimapType people;
    people.insert({ "Alice", 25 });
    people.insert({ "Son", 25 });
    people.insert({ "Daniel", 27 });
    people.insert({ "Daniel", 30 });
    people.insert({ "Bob", 30 });
    people.insert({ "Charlie", 28 });

    // Does C++11 emplace() work with Bimap?
    // C++11 emplace() does not work directly with Boost.Bimap
    
    // people.emplace({"David", 35}); // This will not work

    for (const auto& person : people) {
        std::cout << "Name: " << person.left << ", Age: " << person.right << std::endl;
    }

    // b) Print the left and right maps of the bimap (first and second views).
    std::cout << "Left view (Names):" << std::endl;
    for (const auto& person : people.left) {
        std::cout << person.first << ": " << person.second << std::endl;
    }

    std::cout << "Right view (Ages):" << std::endl;
    for (const auto& person : people.right) {
        std::cout << person.second << ": " << person.first << std::endl;
    }

    // c) Search for age based on name and search for name based on age. Use function at().Take exception handling into consideration.
    try {
        std::cout << "age of alice: " << people.left.at("Alice") << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "entry not found." << std::endl;
    }

    // Right does not have "at". We need to use "find"
    auto it = people.right.find(30);
    if (it != people.right.end()) {
        std::cout << "name of person with age 30: " << it->first << std::endl;
    }
    else {
        std::cout << "entry not found." << std::endl;
    }

    // d) Iterate in the bimap using the third view(that is, a set of relations).
    for (const auto& relation : people) {
        std::cout << "Name: " << relation.left << ", Age: " << relation.right << std::endl;
    }
    return 0;
}