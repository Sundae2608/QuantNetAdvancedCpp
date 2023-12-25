#include "ApproximateDistance.h"
#include "Point.h"

double ApproximateDistance::CalculateDistance(const Point &p1,
                                              const Point &p2) const {
  double dx = std::abs(p2.x() - p1.x());
  double dy = std::abs(p2.y() - p1.y());
  return dx + dy;
}