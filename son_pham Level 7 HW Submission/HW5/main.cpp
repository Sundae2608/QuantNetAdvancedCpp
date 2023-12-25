#include "Point.h"
#include <cmath>

namespace {
class PythagorasWithCounterAlgorithm {
private:
  int counter = 0;

public:
  double operator()(const Point &p1, const Point &p2) {
    counter++;
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) +
                     std::pow(p2.y() - p1.y(), 2));
  }
};

class TaxiManWithCounterAlgorithm {
private:
  int counter = 0;

public:
  double operator()(const Point &p1, const Point &p2) {
    counter++;
    return std::abs(p2.x() - p1.x()) + std::abs(p2.y() - p1.y());
  }
};
} // namespace

int main() {
  // Stateless strategy functions
  DistanceAlgorithm pythagoras = [](const Point &p1, const Point &p2) {
    return std::sqrt(std::pow(p2.x() - p1.x(), 2) +
                     std::pow(p2.y() - p1.y(), 2));
  };

  DistanceAlgorithm taxiMan = [](const Point &p1, const Point &p2) {
    return std::abs(p2.x() - p1.x()) + std::abs(p2.y() - p1.y());
  };

  Point p1(0.0, 0.0);
  Point p2(3.0, 4.0);

  Point::SetDistanceAlgorithm(pythagoras);
  double distancePythagoras = p1.Distance(p2);
  std::cout << "Distance using Pythagoras: " << distancePythagoras << std::endl;

  Point::SetDistanceAlgorithm(taxiMan);
  double distanceTaxiMan = p1.Distance(p2);
  std::cout << "Distance using TaxiMan: " << distanceTaxiMan << std::endl;

  // Stateful strategy functions
  // I simply use an outside counter and pass it in through Lambda.
  // I did try to have the function object to localize the count a bit,
  // but wasn't able to pass the algorithm into DistanceAlgorithm. The
  // objects are still in the namespace.
  int counterPythagoras = 0;
  DistanceAlgorithm pythagorasWithCounter =
      [&counterPythagoras](const Point &p1, const Point &p2) {
        counterPythagoras++;
        return std::sqrt(std::pow(p2.x() - p1.x(), 2) +
                         std::pow(p2.y() - p1.y(), 2));
      };
  int counterTaximan = 0;
  DistanceAlgorithm taximanWithCounter = [&counterTaximan](const Point &p1,
                                                           const Point &p2) {
    counterTaximan++;
    return std::abs(p2.x() - p1.x()) + std::abs(p2.y() - p1.y());
  };

  Point::SetDistanceAlgorithm(pythagorasWithCounter);
  Point::SetDistanceAlgorithm(pythagorasWithCounter);
  Point::SetDistanceAlgorithm(pythagorasWithCounter);
  distancePythagoras = p1.Distance(p2);
  std::cout << "Distance using Pythagoras (with counter): "
            << distancePythagoras << std::endl;
  std::cout << "Counter pythagoas: " << counterPythagoras << std::endl; // 3

  Point::SetDistanceAlgorithm(taximanWithCounter);
  distanceTaxiMan = p1.Distance(p2);
  distanceTaxiMan = p1.Distance(p2);
  std::cout << "Distance using TaxiMan (with counter): " << distanceTaxiMan
            << std::endl;
  std::cout << "Counter taximan: " << counterTaximan << std::endl; // 2

  return 0;
}