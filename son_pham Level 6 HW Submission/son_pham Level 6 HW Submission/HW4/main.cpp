/*
* Advanced C++ and Modern Design
* Level 6 - Homework 4
* Author: Son Pham
* Main file testing implementations
*/

#include <iostream>

#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "ShapeComposite.h"
#include <iostream>

int main() {
    ShapeComposite rootComposite;

    Point p1(1.0, 2.0);
    Line line(p1, Point(4.0, 6.0));
    Circle circle(p1, 5.0);

    rootComposite.AddShape(&p1);
    rootComposite.AddShape(&line);
    rootComposite.AddShape(&circle);

    ShapeComposite nestedComposite;
    nestedComposite.AddShape(&rootComposite);
    std::cout << "Number of shapes in rootComposite: " << rootComposite.Count()
        << std::endl;
    std::cout << "Composition of rootComposite: " << std::endl;
    std::cout << rootComposite;
    std::cout << "Number of shapes in nestedComposite: " << nestedComposite.Count()
        << std::endl;
    std::cout << "Composition of nestedComposite: " << std::endl;
    std::cout << nestedComposite;


    std::cout << "Composition of copied rootComposite: " << std::endl;
    ShapeComposite copiedComposite(rootComposite);
    std::cout << copiedComposite;

    std::cout << "Composition of copied nestedComposite: " << std::endl;
    ShapeComposite copiedNestedComposite(nestedComposite);
    std::cout << copiedNestedComposite;

    return 0;
}