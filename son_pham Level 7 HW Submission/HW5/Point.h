#ifndef POINT_H
#define POINT_H

#include "Shape.h"

#include <functional>
#include <iostream>

class Point;

using DistanceAlgorithm = std::function<double(const Point &, const Point &)>;

class Point : public Shape {
public:
  Point();
  Point(double xs, double ys);
  Point(const Point &pt);
  Point &operator=(const Point &pt);
  double Distance(const Point &p) const;
  double Distance() const; // Distance to origin
  static void SetDistanceAlgorithm(DistanceAlgorithm &algorithm);
  virtual void print(std::ostream &os) const override;
  virtual Point *Clone() const override;

  double x() const;
  double y() const;
  void x(double xs);
  void y(double ys);

private:
  double x_;
  double y_;
  static DistanceAlgorithm distanceAlgorithm;
};

#endif // POINT_H