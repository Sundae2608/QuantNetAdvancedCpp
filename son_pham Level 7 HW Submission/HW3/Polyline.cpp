#include "Polyline.h"
#include "Point.h"

template <typename PointType> Polyline<PointType>::Polyline() {}

template <typename PointType>
void Polyline<PointType>::AddPoint(const PointType &point) {
  points.push_back(point);
}

template <typename PointType>
void Polyline<PointType>::print(std::ostream &os) const {
  // Print implementation for the Polyline class
  os << "Polyline: ";
  for (const auto &point : points) {
    os << "(" << point << ") ";
  }
}

template <typename PointType>
Polyline<PointType> *Polyline<PointType>::Clone() const {
  // Create a new Polyline object and copy points
  Polyline<PointType> *newPolyline = new Polyline<PointType>();

  for (const auto &point : points) {
    newPolyline->points.push_back(point);
  }

  return newPolyline;
}

template class Polyline<Point>;