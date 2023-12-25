/*
* Advanced C++ and Modern Design
* Level 6 - Homework 7
* Author: Son Pham
* Exact Distance
*/

#include "ExactDistance.h"
#include "Point.h"

#include <cmath>

double ExactDistance::CalculateDistance(const Point& p1,
    const Point& p2) const {
    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    return std::sqrt(dx * dx + dy * dy);
}