#ifndef EXACTDISTANCE_H
#define EXACTDISTANCE_H

#include "DistanceStrategy.h"

class ExactDistance : public DistanceStrategy {
public:
  virtual double CalculateDistance(const Point &p1,
                                   const Point &p2) const override;
};

#endif // EXACTDISTANCE_H