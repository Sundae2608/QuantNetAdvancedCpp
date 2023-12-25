/*
* Advanced C++ and Modern Design
* Level 6 - Homework 10
* Author: Son Pham
* Approximate Distance
*/

#include "ApproximateDistance.h"
#include "Point.h"

double ApproximateDistance::CalculateDistance(const Point &p1,
                                              const Point &p2) const {
  double dx = std::abs(p2.x() - p1.x());
  double dy = std::abs(p2.y() - p1.y());
  return dx + dy;
}