/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 5, Exercise 5: A simple next-Generation Builder Pattern
Currently doesnt work. This is some weird stuffs happening that only letter c got printed
Compiled in C++ 20
*/

#include <iostream>

namespace {

// This section decales the base interface of IODevice and Shape
// Forward declaration of Circle and Line to make IODevice legal
class Circle;
class Line;

class IODevice
{
    // Interface for displaying CAD objects
public:
    virtual void operator << (const Circle& c) = 0;
    virtual void operator << (const Line& c) = 0;
};

class Shape
{
public:
    virtual void display(IODevice& ioDevice) const = 0;
};

// This section defines the Circle class and the line class, which all inherit
// from the Shape class
class Circle : public Shape
{
public:
    void display(IODevice& ioDevice) const override {
        ioDevice << *this;
    }
 
    double radius;
    double cx;
    double cy;
};

// Line class deriving from shape
class Line : public Shape
{
public:
    void display(IODevice& ioDevice) const override {
        ioDevice << *this;
    }

    double x1;
    double y1;
    double x2;
    double y2;
};

// This section defines IODevice1 and IODevice2, all inheriting from IODevice to show the
// Shape class in different ways.
class IODevice1 : public IODevice
{
public:
    void operator << (const Circle& c) override {
        std::cout << "IO Device 1" << std::endl;
        std::cout << "circle cx=" << c.cx << " cy=" << c.cy << " r=" << c.radius << std::endl;
    }

    void operator << (const Line& l) override {
        std::cout << "IO Device 1" << std::endl;
        std::cout << "line x1=" << l.x1 << " y1=" << l.y1 << " x2=" << l.x2 << " y2= " << l.y2 << std::endl;
    }
};

// IO Device 2 inherting from IODevice
class IODevice2 : public IODevice
{
public:
    void operator << (const Circle& c) override {
        std::cout << "IO Device 2" << std::endl;
        std::cout << "circle cx=" << c.cx << " cy=" << c.cy << " r=" << c.radius << std::endl;
    }

    void operator << (const Line& l) override {
        std::cout << "IO Device 2" << std::endl;
        std::cout << "line x1=" << l.x1 << " y1=" << l.y1 << " x2=" << l.x2 << " y2= " << l.y2 << std::endl;
    }
};

using ShapePointer = std::shared_ptr<Shape>;
using IODevicePointer = std::shared_ptr<IODevice>;

// A Builder hierarchy that builds shapes and io devices
class Builder
{
public:
    std::tuple<ShapePointer, IODevicePointer> getProduct() {
        ShapePointer shape = getShape();
        IODevicePointer ioDevice = getIODevice();
        return std::make_tuple(shape, ioDevice);
    }

    // Hook functions that derived classes must implement
    virtual ShapePointer getShape() = 0;
    virtual IODevicePointer getIODevice() = 0;
};

class CircleIODevice1Builder : public Builder
{
public:
    ShapePointer getShape() override {
        auto circle = std::make_shared<Circle>();
        circle->radius = 5.0;
        circle->cx = 0.0;
        circle->cy = 0.0;

        return circle;
    }

    IODevicePointer getIODevice() override {
        return std::make_shared<IODevice1>();
    }
};
}

int main55()
{
    auto builder = std::make_unique<CircleIODevice1Builder>();
    auto [shape, ioDevice] = builder->getProduct();

    shape->display(*ioDevice);
    return 0;
}