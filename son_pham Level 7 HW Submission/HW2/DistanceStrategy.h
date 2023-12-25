#ifndef DISTANCESTRATEGY_H
#define DISTANCESTRATEGY_H

class Point;

class DistanceStrategy {
public:
  virtual double CalculateDistance(const Point &p1, const Point &p2) const = 0;
};

#endif // DISTANCESTRATEGY_H