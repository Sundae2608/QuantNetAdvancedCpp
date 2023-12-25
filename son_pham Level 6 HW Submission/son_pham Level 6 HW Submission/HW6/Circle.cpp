/*
* Advanced C++ and Modern Design
* Level 6 - Homework 6
* Author: Son Pham
* Circle header file
*/

#include "Circle.h"
#include "Point.h"

Circle::Circle() {}
Circle::Circle(const Point& c, double r) : center_(c), radius_(r) {}
Circle::Circle(const Circle& c) : center_(c.center_), radius_(c.radius_) {}
Circle& Circle::operator=(const Circle& c) {
    if (this != &c) {
        center_ = c.center_;
        radius_ = c.radius_;
    }
    return *this;
}
Circle::~Circle() {}
void Circle::print(std::ostream& os) const {
    os << "Circle: Center (" << center_.x() << ", " << center_.y() << "), Radius "
        << radius_;
}
Point Circle::CenterPoint() const { return center_; }
double Circle::Radius() const { return radius_; }
void Circle::CenterPoint(const Point& centre) { center_ = centre; }
void Circle::Radius(double radius) { radius_ = radius; }
Circle* Circle::Clone() const { return new Circle(*this); }