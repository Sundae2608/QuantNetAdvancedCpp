/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 1, Exercise 3: Type Properties and Type Relationships
*/

#include <iostream>
#include <type_traits>

namespace {
    class Shape
    {
    public:
        virtual void draw() = 0;
    };

    class Base
    {
    private:
        int y;
    public:
        Base() {}
        void draw() {}
    };

    class Point : public Shape
    {
    public:
        Point() {}
        virtual void draw() override {}
    };
}

int main13() {
    // a) Which classes/types are empty, polymorphic or abstract?
    std::cout << std::boolalpha;
    std::cout << "Empty classes:" << std::endl;
    std::cout << "Shape: " << std::is_empty<Shape>::value << std::endl;  // False
    std::cout << "Base: " << std::is_empty<Base>::value << std::endl;    // False
    std::cout << "Point: " << std::is_empty<Point>::value << std::endl;  // False

    std::cout << "\nPolymorphic classes:" << std::endl;
    std::cout << "Shape: " << std::is_polymorphic<Shape>::value << std::endl;  // True
    std::cout << "Base: " << std::is_polymorphic<Base>::value << std::endl;    // False
    std::cout << "Point: " << std::is_polymorphic<Point>::value << std::endl;  // True

    std::cout << "\nAbstract classes:" << std::endl;
    std::cout << "Shape: " << std::is_abstract<Shape>::value << std::endl;  // True
    std::cout << "Base: " << std::is_abstract<Base>::value << std::endl;    // False
    std::cout << "Point: " << std::is_abstract<Point>::value << std::endl;  // False

    // b) Which classes are the same?
    // None of the classes are the same
    std::cout << "\nType equality:" << std::endl;
    std::cout << "Shape and Base: " << std::is_same<Shape, Base>::value << std::endl;   // False 
    std::cout << "Shape and Point: " << std::is_same<Shape, Point>::value << std::endl; // False
    std::cout << "Base and Point: " << std::is_same<Base, Point>::value << std::endl;   // False

    // c) Which classes have a gen/spec (base/derived) relationship?
    // The only class that has a base/derived relation ship is Shape and Point, where Shape is base of Point
    // and Point is derived of Shape
    std::cout << "\nGeneralization/Speciation relationship:" << std::endl;
    std::cout << "Shape is base of Base: " << std::is_base_of<Shape, Base>::value << std::endl;    // False
    std::cout << "Shape is base of Point: " << std::is_base_of<Shape, Point>::value << std::endl;  // True
    std::cout << "Base is base of Point: " << std::is_base_of<Base, Point>::value << std::endl;    // False
    std::cout << "Base is base of Shape: " << std::is_base_of<Base, Shape>::value << std::endl;    // False
    std::cout << "Point is base of Shape: " << std::is_base_of<Point, Shape>::value << std::endl;  // False
    std::cout << "Point is base of Base: " << std::is_base_of<Point, Base>::value << std::endl;    // False

    // d) Which types can be converted to each other?
    // When I do raw type, it seems that none of them can be converted to each other.
    std::cout << "\nType convertibility:" << std::endl;
    std::cout << "Shape is convertible to Point: " << std::is_convertible<Shape, Point>::value << std::endl;  // False
    std::cout << "Shape is convertible to Base: " << std::is_convertible<Shape, Base>::value << std::endl;    // False
    std::cout << "Base is convertible to Point: " << std::is_convertible<Base, Point>::value << std::endl;    // False
    std::cout << "Base is convertible to Shape: " << std::is_convertible<Base, Shape>::value << std::endl;    // False
    std::cout << "Point is convertible to Shape: " << std::is_convertible<Point, Shape>::value << std::endl;  // False
    std::cout << "Point is convertible to Base: " << std::is_convertible<Point, Base>::value << std::endl;    // False
    // However, if I do pointer, then Point can be converted to Shape. Unsurprising given they have base derived relationship
    std::cout << "\nPointer type convertibility:" << std::endl;
    std::cout << "Shape is convertible to Base: " << std::is_convertible<Shape*, Base*>::value << std::endl;    // False
    std::cout << "Shape is convertible to Point: " << std::is_convertible<Shape*, Point*>::value << std::endl;  // False
    std::cout << "Base is convertible to Point: " << std::is_convertible<Base*, Point*>::value << std::endl;    // False
    std::cout << "Base is convertible to Shape: " << std::is_convertible<Base*, Shape*>::value << std::endl;    // False
    std::cout << "Point is convertible to Shape: " << std::is_convertible<Point*, Shape*>::value << std::endl;  // True
    std::cout << "Point is convertible to Base: " << std::is_convertible<Point*, Base*>::value << std::endl;    // False

    return 0;
}