#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "Shape.h"

class Line : public Shape {
public:
  Line();
  template <typename PointType>
  Line(const PointType &pt1s, const PointType &pt2s);
  Line(const Line &ln);
  Line &operator=(const Line &ln);
  virtual void print(std::ostream &os) const override;

  Point p1() const;
  Point p2() const;
  double Length() const;
  void p1(const Point &ps);
  void p2(const Point &ps);
  virtual Line *Clone() const override;

private:
  Point p1_;
  Point p2_;
};

#endif // LINE_H