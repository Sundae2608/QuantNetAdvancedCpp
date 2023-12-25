/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Point
*/

#include <cmath>
#include <iostream>

#include "OriginPoint.h"
#include "Point.h"
#include "Singleton.h"

DistanceStrategy *Point::distanceStrategy_ = nullptr;

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
  if (distanceStrategy_) {
    return distanceStrategy_->CalculateDistance(*this, p);
  } else {
    return 0.0; // Default behavior when no strategy is set
  }
}
double Point::Distance() const {
  return Distance(Point()); // Distance to origin (0,0)
}
double Point::Distance(const Point &p, const DistanceStrategy &strategy) const {
  return strategy.CalculateDistance(*this, p);
}
void Point::print(std::ostream &os) const {
  os << "Point: (" << x_ << ", " << y_ << ")";
}
double Point::x() const { return x_; }
double Point::y() const { return y_; }
void Point::x(double xs) { x_ = xs; }
void Point::y(double ys) { y_ = ys; }
Point *Point::Clone() const { return new Point(*this); }
void Point::SetDistanceStrategy(DistanceStrategy *strategy) {
  distanceStrategy_ = strategy;
}
void Point::Accept(ShapeVisitor &visitor) { visitor.Visit(*this); }