#include <cmath>
#include <iostream>

#include "OriginPoint.h"
#include "Point.h"
#include "Singleton.h"

DistanceAlgorithm Point::distanceAlgorithm = nullptr;

Point::Point() : x_(0.0), y_(0.0) {}
Point::Point(double xs, double ys) : x_(xs), y_(ys) {}
Point::Point(const Point &pt) : x_(pt.x_), y_(pt.y_) {}
Point &Point::operator=(const Point &pt) {
  if (this != &pt) {
    x_ = pt.x_;
    y_ = pt.y_;
  }
  return *this;
}
double Point::Distance(const Point &p) const {
  return Point::distanceAlgorithm(*this, p);
}
double Point::Distance() const {
  return Point::distanceAlgorithm(*this, Point());
}
void Point::print(std::ostream &os) const {
  os << "Point: (" << x_ << ", " << y_ << ")";
}
double Point::x() const { return x_; }
double Point::y() const { return y_; }
void Point::x(double xs) { x_ = xs; }
void Point::y(double ys) { y_ = ys; }
Point *Point::Clone() const { return new Point(*this); }
void Point::SetDistanceAlgorithm(DistanceAlgorithm &algorithm) {
  Point::distanceAlgorithm = algorithm;
}