#ifndef APPROXIMATEDISTANCE_H
#define APPROXIMATEDISTANCE_H

#include "DistanceStrategy.h"

class ApproximateDistance : public DistanceStrategy {
public:
  virtual double CalculateDistance(const Point &p1,
                                   const Point &p2) const override;
};

#endif // APPROXIMATEDISTANCE_H