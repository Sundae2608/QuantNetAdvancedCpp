/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 7, Exercise 4
*/

#include <boost/bimap.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <functional> // for std::greater
#include <iostream>

int main() {
    using namespace boost::bimaps;

    // Bimap with Set domain and List range
    typedef bimap<set_of<std::string>, list_of<int>> SetToListBimap;

    // Bimap with Multiset domain and Set range
    typedef bimap<multiset_of<int>, set_of<std::string>> MultisetToSetBimap;

    // Bimap with Unordered set domain and Unordered set range
    typedef bimap<unordered_set_of<std::string>, unordered_set_of<int>> UnorderedSetToUnorderedSetBimap;

    // Uncomment the following for part c)
    // Bimap with Set domain and List range, using std::greater as comparator
    // typedef bimap<set_of<std::string>, list_of<int, std::greater<int>>> SetToListBimapWithCompare;

    // Bimap with Multiset domain and Set range, using std::greater as comparator
    // typedef bimap<multiset_of<int, std::greater<int>>, set_of<std::string>> MultisetToSetBimapWithCompare;

    // Bimap with Unordered set domain and Unordered set range, using std::greater as comparator
    // typedef bimap<unordered_set_of<std::string>, unordered_set_of<int, std::greater<int>>> UnorderedSetToUnorderedSetBimapWithCompare;

    // Create instances of bimaps
    SetToListBimap setToList;
    setToList.insert(SetToListBimap::value_type("apple", 1));
    setToList.insert(SetToListBimap::value_type("banana", 2));

    MultisetToSetBimap multisetToSet;
    multisetToSet.insert(MultisetToSetBimap::value_type(1, "one"));
    multisetToSet.insert(MultisetToSetBimap::value_type(1, "uno"));

    UnorderedSetToUnorderedSetBimap unorderedSetToUnorderedSet;
    unorderedSetToUnorderedSet.insert(UnorderedSetToUnorderedSetBimap::value_type("first", 1));
    unorderedSetToUnorderedSet.insert(UnorderedSetToUnorderedSetBimap::value_type("second", 2));

    // Print the values
    std::cout << "Set to List Bimap:" << std::endl;
    for (const auto& pair : setToList) {
        std::cout << pair.left << " <-> " << pair.right << std::endl;
    }

    std::cout << "Multiset to Set Bimap:" << std::endl;
    for (const auto& pair : multisetToSet) {
        std::cout << pair.left << " <-> " << pair.right << std::endl;
    }

    std::cout << "Unordered Set to Unordered Set Bimap:" << std::endl;
    for (const auto& pair : unorderedSetToUnorderedSet) {
        std::cout << pair.left << " <-> " << pair.right << std::endl;
    }

    return 0;
}