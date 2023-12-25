/*
* Advanced C++ and Modern Design
* Level 6 - Homework 2
* Author: Son Pham
* Main file to test the implementation
*/

#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "Shape.h"
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<Shape> point = std::make_unique<Point>(1.0, 2.0);
    std::unique_ptr<Shape> line =
        std::make_unique<Line>(Point(1.0, 2.0), Point(3.0, 4.0));
    std::unique_ptr<Shape> circle =
        std::make_unique<Circle>(Point(1.0, 2.0), 5.0);

    std::cout << *point << std::endl;
    std::cout << *line << std::endl;
    std::cout << *circle << std::endl;

    // New Point and Line object to test Distance() and Length()
    std::unique_ptr<Point> p1 = std::make_unique<Point>(1.0, 2.0);
    std::unique_ptr<Point> p2 = std::make_unique<Point>(4.0, 6.0);

    // Using std::make_unique for Line object
    std::unique_ptr<Line> line2 = std::make_unique<Line>(*p1, *p2);

    // Using the Distance() method in Point class
    std::cout << "Distance between p1 and p2: " << p1->Distance(*p2) << std::endl;

    // Using the Distance() to origin in Point class
    std::cout << "Distance from p1 to origin: " << p1->Distance() << std::endl;

    // Using the Length() method in Line class
    std::cout << "Length of the line: " << line2->Length() << std::endl;

    return 0;
}