#include "PointFactory.h"

template <typename PointType>
PointType PointFactory<PointType>::CreatePoint(double x, double y) {
  return PointType(x, y);
}

template class PointFactory<Point>;