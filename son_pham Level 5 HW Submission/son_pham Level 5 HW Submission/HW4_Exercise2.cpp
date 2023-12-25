/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 4, Exercise 2: Hash 101
*/

#include <iostream>
#include <list>
#include <boost/functional/hash.hpp>

namespace {
    struct Point {
        int x, y;
    };

    struct LineSegment {
        Point start, end;
    };

    struct PointHash : std::unary_function < Point, std::size_t> {
        std::size_t operator()(const Point& pt) const {
            // std::size_t seed = 0;
            // boost::hash_combine(seed, pt.x);
            // boost::hash_combine(seed, pt.y);
            // return seed;

            // My own version
            std::size_t hashX = std::hash<int>{}(pt.x);
            std::size_t hashY = std::hash<int>{}(pt.y);

            // Custom combining logic using bitwise XOR
            return hashX ^ (hashY + 0x9e3779b9 + (hashX << 6) + (hashX >> 2));
        }
    };
}

namespace boost {
    template <>
    struct hash<Point> {
        size_t operator()(const Point& pt) const {
            size_t seed = 0;
            boost::hash_combine(seed, pt.x);
            boost::hash_combine(seed, pt.y);
            return seed;
        }
    };

    template <>
    struct hash<LineSegment> {
        size_t operator()(const LineSegment& ls) const {
            size_t seed = 0;
            boost::hash_combine(seed, ls.start);
            boost::hash_combine(seed, ls.end);
            return seed;
        }
    };
}

int main42() {
    // a) Create hashes for Point and LineSegment using boost::hash_combine.
    // The functionality in LineSegment should delegate to the functionality in Point.
    Point p1 = { 1, 2 };
    Point p2 = { 3, 4 };

    LineSegment ls = { p1, p2 };

    std::size_t hashPoint = boost::hash<Point>{}(p1);
    std::size_t hashLineSegment = boost::hash<LineSegment>{}(ls);

    std::cout << "Hash of Point: " << hashPoint << std::endl;
    std::cout << "Hash of LineSegment: " << hashLineSegment << std::endl;

    // b) Create a list of Point instances and compute its hash using boost::hash_range().
    std::list<Point> points = { {1, 2}, {3, 4}, {5, 6} };
    std::size_t hashPoints = boost::hash_range(points.begin(), points.end());
    std::cout << "Hash of Points: " << hashPoints << std::endl;

    // c) Create a function object that represents a custom hash function for the Point class.    
    Point p = {1, 2};
    PointHash pointHashFunc;
    std::size_t customHashPoint = pointHashFunc(p);
    std::cout << "Hash of Point: " << customHashPoint << std::endl;
    return 0;
}