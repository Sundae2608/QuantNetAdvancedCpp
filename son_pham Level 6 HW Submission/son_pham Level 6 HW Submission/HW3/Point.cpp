/*
* Advanced C++ and Modern Design
* Level 6 - Homework 3
* Author: Son Pham
* Point class header
*/

#include <cmath>
#include <iostream>

#include "OriginPoint.h"
#include "Point.h"
#include "Singleton.h"

Point::Point() : x_(0.0), y_(0.0) {}
Point::Point(double xs, double ys) : x_(xs), y_(ys) {}
Point::Point(const Point& pt) : x_(pt.x_), y_(pt.y_) {}
Point& Point::operator=(const Point& pt) {
    if (this != &pt) {
        x_ = pt.x_;
        y_ = pt.y_;
    }
    return *this;
}
double Point::Distance(const Point& p) const {
    double dx = p.x_ - x_;
    double dy = p.y_ - y_;
    return std::sqrt(dx * dx + dy * dy);
}
double Point::Distance() const {
    return Distance(Point()); // Distance to origin (0,0)
}
void Point::print(std::ostream& os) const {
    os << "Point: (" << x_ << ", " << y_ << ")";
}
double Point::x() const { return x_; }
double Point::y() const { return y_; }
void Point::x(double xs) { x_ = xs; }
void Point::y(double ys) { y_ = ys; }