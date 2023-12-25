#ifndef POINT_FACTORY_H
#define POINT_FACTORY_H

#include "Point.h"

template <typename PointType> class PointFactory {
public:
  static PointType CreatePoint(double x, double y);
};

#endif // POINT_FACTORY_H