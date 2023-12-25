#ifndef POLYLINE_H
#define POLYLINE_H

#include "Shape.h"

#include <iostream>
#include <vector>

template <typename PointType> class Polyline : public Shape {
public:
  Polyline();

  void AddPoint(const PointType &point);

  virtual void print(std::ostream &os) const override;
  virtual Polyline *Clone() const override;

private:
  std::vector<PointType> points;
};

#endif // POLYLINE_H