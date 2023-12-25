#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "ShapeFactory.h"
#include <iostream>

int main() {
  ShapeFactory factoryCreatePoint([](std::initializer_list<double> args) {
    auto it = args.begin();
    return new Point(*it++, *it++);
  });

  ShapeFactory factoryCreateLine([](std::initializer_list<double> args) {
    auto it = args.begin();
    return new Line(Point(*it++, *it++), Point(*it++, *it++));
  });

  ShapeFactory factoryCreateCircle([](std::initializer_list<double> args) {
    auto it = args.begin();
    return new Circle(Point(*it++, *it++), *it++);
  });

  Shape *point = factoryCreatePoint.CreateShape({2.0, 3.0});
  Shape *line = factoryCreateLine.CreateShape({1.0, 2.0, 3.0, 4.0});
  Shape *circle = factoryCreateCircle.CreateShape({0.0, 0.0, 5.0});

  std::cout << *point << std::endl;
  std::cout << *line << std::endl;
  std::cout << *circle << std::endl;

  // This is an interesting way to do things. It does allow a much more flexible
  // way to create the shape. Using these methods, it would be very easy to pass
  // any customer Shape creation function in. It would also be possible to pass
  // in even a ShapeComposite creator as well. The issue with this method comes
  // from the fact that we have to bend over backwards a little bit by allow the
  // addition of a method taking in an initializer list, meaning that we pass in
  // a list of arguments. This leads to a funny looking shape creation function
  // that uses it++.

  // c) Brainstorming question: consider the suitability of this design to other
  // pattern such as Strategy and Command? How does the new design compare with
  // the corresponding GOF design?
  // I am not sure if I agree with the premise of this question, because one
  // could argue that this is very similar to Strategy pattern, where a function
  // declaration common to all Shape creation is used, and that each lambda
  // function matches it.
  //
  // As for Command, I am not sure if a Command design ever makes sense for this
  // design. It would basically involve another object called "ShapeCommand",
  // which would basically implement the Shape creation method, and call
  // something in which ShapeFactory is passed in. The issue is that I don't see
  // that we ever needing more than 1 ShapeFactory for this kind of problems.
  //
  // Overall, even though this lambda method is slightly clunky, I do prefer it
  // compared to the GOF method. It helps us from having to create a giant
  // hierarchy of different ShapeFactory for different use cases. The creation
  // of different shapes are already different from each other, then if the
  // creation of shapes based on Console or Window are different, we might as
  // well just make every single creation custom.
  //
  // The second advantage of this is that in certain cases where certain Shape
  // factory does not have to create all types of shapes, we save ourself from
  // having to implement those shape creation functions just to match the
  // virtual function of the existing code base. For example, let's say a
  // "CircularMonitorShapeFactory" can only support Circle, then it does not
  // make sense to implement Line creation for this factory. This lambda design
  // is better in that regard.
  //
  // d) This pattern is very good if the decoration of the new object does not
  // care about which Factor the object comes from. For example, "Model_A" of
  // Shape requires an enlargement by 1.1x, but does not care whether the Shape
  // was typed in from console or initialized from code. In which case, the way
  // to do it would be to create a new base class called ModelFactory in which a
  // createShape std::function and a modifyShape std::function is passed in. And
  // then when createShape (of the model Factory is called), we simply calle
  // createShape and modifyShape continuously.
  return 0;
}