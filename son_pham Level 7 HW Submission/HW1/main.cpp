#include <tuple>

#include "ConsoleShapeFactory.h"

int main() {
  ConsoleShapeFactory factory;
  std::tuple<Point *, Line *, Circle *> shapes = factory.CreateShapes();

  Point *point = std::get<0>(shapes);
  Line *line = std::get<1>(shapes);
  Circle *circle = std::get<2>(shapes);

  // Print some info about the shapes
  if (point != nullptr) {
    std::cout << *point;
  }
  if (line != nullptr) {
    std::cout << *line;
  }
  if (circle != nullptr) {
    std::cout << *circle;
  }

  // c) Compare the GOF solution with the new solution. For example, how much
  // effort is needed with both design if we wish to a new product (for example,
  // a class that models rectangles)?
  //
  // Honestly, I am not really a big fan of this new design due to the following
  // reason:
  // 1. In terms of the work, it is about the same work as before. Say we want
  // to add a rectangle class, we still have to create a new class called
  // Rectangle that inherit the shape. And then we add another Shape into the
  // tuple. This is equalling to the amount of work of just creating a new
  // Rectangle.
  // 2. This would lead to CreateShapes method eventually getting really
  // bloated. I also don't think there is much benefit of compressing all the
  // shape into a tuple, given that all the types are fixed.
  // 3. One could make an argument that CreateShapes can return an std::vector
  // of Shape, which is convenient and allow variable number of Shapes return.
  // But this doesn't have to be a function of ConsoleShape factory. Other code
  // from outside can call individual CreateCircle(), CreateLine() and
  // CreatePoint() function. This is a much cleaner design in my opinion, which
  // allows the functionality of ConsoleShapeFactory to stay very tight and
  // focused, and give flexibility to the users to implement the interface
  // however they see fit.

  return 0;
}