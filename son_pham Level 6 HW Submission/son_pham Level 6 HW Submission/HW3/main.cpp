/*
* Advanced C++ and Modern Design
* Level 6 - Homework 3
* Author: Son Pham
* Main class testing implementations
*/

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
    nestedComposite.AddShape(&Point(0.0, 0.0));
    nestedComposite.AddShape(&Line(Point(0.0, 0.0), Point(2.0, 2.0)));
    nestedComposite.AddShape(&Circle(Point(0.0, 0.0), 3.0));

    rootComposite.AddShape(&nestedComposite);

    std::cout << "Number of shapes in rootComposite: " << rootComposite.Count()
        << std::endl;

    std::cout << rootComposite;

    return 0;
}