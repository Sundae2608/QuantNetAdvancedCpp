/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 7, Exercise 3: Boost Bimap
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

namespace bimaps = boost::bimaps;

// Define tags for improved readability
struct Title {};
struct Author {};

int main73() {
    using AuthorBookMultimap = std::multimap<std::string, std::string>;
    using BookPriceBimap = bimaps::bimap<
        bimaps::tagged<std::string, Title>,
        bimaps::tagged<double, bimaps::unordered_set_of<double>>
    >;

    AuthorBookMultimap authorBookAssociation;
    BookPriceBimap bookPriceBimap;

    // a) Create a 1 N association between book title and author (choose the appropriate STL data structures). Model book price in Bimap.
    // Create 1:N association between authors and books using multimap. Multimap
    // Make sense because you can have the same author (same key) having muiltiple entries.
    authorBookAssociation.insert({ "Author 1", "Book A" });
    authorBookAssociation.insert({ "Author 1", "Book B" });
    authorBookAssociation.insert({ "Author 2", "Book C" });
    authorBookAssociation.insert({ "Author 3", "Book D" });

    // Create book prices using Boost.Bimap
    bookPriceBimap.insert({ "Book A", 10.99 });
    bookPriceBimap.insert({ "Book B", 15.99 });
    bookPriceBimap.insert({ "Book C", 20.49 });
    bookPriceBimap.insert({ "Book D", 12.75 });

    // b) Print the price of a book from a given author.
    std::string searchAuthor = "Author 1"; // Change this to the author you want to search
    auto authorRange = authorBookAssociation.equal_range(searchAuthor);

    std::cout << "Books and Prices by Author: " << searchAuthor << std::endl;
    for (auto it = authorRange.first; it != authorRange.second; ++it) {
        auto title = it->second;
        auto priceIter = bookPriceBimap.left.find(title);
        if (priceIter != bookPriceBimap.left.end()) {
            std::cout << "Book: " << title << ", Price: " << priceIter->second << std::endl;
        }
    }

    // c) Now create an association attribute containing a tuple consisting of book abstractand its price.
    using BookAttributeBimap = bimaps::bimap<
        bimaps::tagged<std::string, Title>,
        bimaps::tagged<std::tuple<std::string, double>, Author>
    >;

    BookAttributeBimap bookAttributeBimap;

    bookAttributeBimap.insert({ "Book A", {"Abstract for Book A", 10.99} });
    bookAttributeBimap.insert({ "Book B", {"Abstract for Book B", 15.99} });
    bookAttributeBimap.insert({ "Book C", {"Abstract for Book C", 20.49} });
    bookAttributeBimap.insert({ "Book D", {"Abstract for Book D", 12.75} });

    // Print the author, price, and abstract of each book
    std::cout << "Author, Price, and Abstract of Each Book:" << std::endl;
    for (const auto& entry : bookAttributeBimap) {
        const auto& bookTitle = entry.left;
        const auto& attributeTuple = entry.right;

        std::cout << "Book: " << bookTitle
            << ", Author: " << std::get<1>(attributeTuple)
            << ", Price: " << std::get<0>(attributeTuple)
            << ", Abstract: " << std::get<1>(attributeTuple) << std::endl;
    }
    return 0;
}