/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 4, Exercise 3: Unordered Collections
*/

#include <iostream>
#include <unordered_set>
#include <set>
#include <chrono>
#include <functional>

namespace {
    struct Point {
        int x, y;

        // Comparison operator for strict weak ordering
        bool operator<(const Point& other) const {
            return x < other.x || (x == other.x && y < other.y);
        }

        // Equality operator
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct LineSegment {
        Point start, end;
    };

    struct PointHash2 {
        size_t operator()(const Point& pt) const {
            size_t hashX = std::hash<int>{}(pt.x);
            size_t hashY = std::hash<int>{}(pt.y);
            return hashX + 31 * hashY;
        }
    };
}

namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& pt) const {
            size_t hashX = std::hash<int>{}(pt.x);
            size_t hashY = std::hash<int>{}(pt.y);
            return hashX ^ (hashY + 0x9e3779b9 + (hashX << 6) + (hashX >> 2));
        }
    };
}

int main43() {
    // a) Create an unordered multiset of Point instances by creating a user - defined
    // hash for class Point based on std::hash.Add many points to this multiset using
    // insert() and emplace(); remove elements from the multiset using erase() and
    // clear(). Measure processing time using std::chrono.
    std::unordered_multiset<Point> pointSet;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        pointSet.emplace(Point{ i, i });
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time for inserting elements (Unordered Multiset): " << elapsed.count() << " seconds" << std::endl;

    pointSet.erase(Point{ 500000, 500000 });
    start = std::chrono::high_resolution_clock::now();
    pointSet.clear();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Elapsed time for clearing elements (Unordered Multiset): " << elapsed.count() << " seconds" << std::endl;

    // b) Now create your own hash functions and repeat part a) using multisets with 
    // these hashes as parameters. Measure processing time using std::chrono.
    std::unordered_multiset<Point, PointHash2> customPointSet;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        customPointSet.emplace(Point{ i, i });
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Elapsed time for inserting elements (Unordered multiset with custom function): " << elapsed.count() << " seconds" << std::endl;

    customPointSet.erase(Point{ 500000, 500000 });
    start = std::chrono::high_resolution_clock::now();
    customPointSet.clear();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Elapsed time for clearing elementss (Unordered multiset with custom function): " << elapsed.count() << " seconds" << std::endl;

    // c) Repeat part a) using ‘standard’ STL multisets. Measure processing time using std::chrono.
    std::multiset<Point> standardPointSet;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000000; ++i) {
        standardPointSet.emplace(Point{ i, i });
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Elapsed time for inserting elementss (Multiset): " << elapsed.count() << " seconds" << std::endl;

    standardPointSet.erase(Point{ 500000, 500000 });
    start = std::chrono::high_resolution_clock::now();
    standardPointSet.clear();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Elapsed time for clearing elements (Multiset): " << elapsed.count() << " seconds" << std::endl;

    // The print is as the following:
    // Elapsed time for inserting elements(Unordered Multiset) : 0.925357 seconds
    // Elapsed time for clearing elements(Unordered Multiset) : 0.189214 seconds
    // Elapsed time for inserting elements : 2.76644 seconds
    // Elapsed time for clearing elements : 0.228629 seconds
    // Elapsed time for inserting elements : 1.21584 seconds
    // Elapsed time for clearing elements : 0.145533 seconds
    //
    // Not much different between all set. It seems that the main efficiency is on
    // the hash function.
    return 0;
}