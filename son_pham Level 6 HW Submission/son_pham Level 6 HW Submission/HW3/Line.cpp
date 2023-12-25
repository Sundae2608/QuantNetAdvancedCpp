/*
* Advanced C++ and Modern Design
* Level 6 - Homework 3
* Author: Son Pham
* Line class header
*/

#include "Line.h"
#include "Point.h"

Line::Line() {}
Line::Line(const Point& pt1s, const Point& pt2s) : p1_(pt1s), p2_(pt2s) {}
Line::Line(const Line& ln) : p1_(ln.p1_), p2_(ln.p2_) {}
Line& Line::operator=(const Line& ln) {
    if (this != &ln) {
        p1_ = ln.p1_;
        p2_ = ln.p2_;
    }
    return *this;
}
void Line::print(std::ostream& os) const {
    os << "Line: (" << p1_.x() << ", " << p1_.y() << ") to (" << p2_.x() << ", "
        << p2_.y() << ")";
}
Point Line::p1() const { return p1_; }
Point Line::p2() const { return p2_; }
double Line::Length() const { return p1_.Distance(p2_); }
void Line::p1(const Point& ps) { p1_ = ps; }
void Line::p2(const Point& ps) { p2_ = ps; }