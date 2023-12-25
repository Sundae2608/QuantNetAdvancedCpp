#include "Point.h"
#include "PointFactory.h"
#include "Polyline.h"

#include <iostream>

namespace {
// Sot this is for the requirement of "write the factory method for this class.
// The implementation should use template template parameter". This is
// interesting because it allows me to pass in any kind of Point class
// and any kind of ShapeFactory class. It is very interesting to see how it
// works out, though I am unsure what kind of use case that would make this
// decisively useful.
//
// Also, the exercise mentions this exercise in the context of reusing code.
// However, much of the code is quite new for this exercise.
template <template <typename> typename PointFactory, typename PointType>
class PolylineFactory {
public:
  Polyline<PointType> CreatePolyline() {
    Polyline<PointType> polyline;

    for (int i = 0; i < 5; ++i) {
      PointType point = PointFactory<PointType>::CreatePoint(i, i);
      polyline.AddPoint(point);
    }

    return polyline;
  }
};
} // namespace

int main() {
  PolylineFactory<PointFactory, Point> polylineFactory;

  Polyline<Point> polyline = polylineFactory.CreatePolyline();
  std::cout << polyline;

  return 0;
}