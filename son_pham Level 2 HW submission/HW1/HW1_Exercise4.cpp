/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 1, Exercise 4: Supported Operations
*/

#include <iostream>
#include <type_traits>

namespace {
    class Shape
    {
    public:
        virtual void draw() = 0;
    };

    class Point : public Shape
    {
    public:
        Point() {}
        virtual void draw() override {}
    };

    class Point2 : public Shape
    {
    public:
        Point2() {}
        virtual void draw() override {}

        Point2(const Point2&) = delete;             // Deleting copy constructor
        Point2& operator=(const Point2&) = delete;  // Deleting copy assignment operator
    };

    class Point3 : public Shape
    {
    public:
        Point3() {}
        virtual void draw() override {}

        Point3(const Point3&) = delete;             // Deleting copy constructor
        Point3& operator=(const Point3&) = delete;  // Deleting copy assignment operator

        Point3(Point3&&) = default;                 // Explicitly defaulting move constructor
        Point3& operator=(Point3&&) = default;      // Explicitly defaulting move assignment operator
    };

}

int main14() {
    // a) Programmatically determine if type Point has a virtual destructor.
    std::cout << std::boolalpha;
    std::cout << "Point has a virtual destructor: " << std::has_virtual_destructor<Point>::value << std::endl;     // False
    std::cout << "Point has a default constructor: " << std::is_default_constructible<Point>::value << std::endl;  // True

    // b) Programmatically determine if type Point has the following constructors : default, copy, move.
    std::cout << "Point has a copy constructor: " << std::is_copy_constructible<Point>::value << std::endl;  // True
    std::cout << "Point has a move constructor: " << std::is_move_constructible<Point>::value << std::endl;  // True

    // c) Programmatically determine if type Point is copy assignable / move assignable.
    std::cout << "Point is copy assignable: " << std::is_copy_assignable<Point>::value << std::endl;  // True
    std::cout << "Point is move assignable: " << std::is_move_assignable<Point>::value << std::endl;  // True
    std::cout << std::endl;

    // d) Set the copy constructor and assignment operator as ‘deleted functions’ and
    // perform steps b)-c) again; do you get the same result?
    // For convenience, the changed function is in a separate class called Point2, which has the copy constructor
    // and assignment operator deleted.
    std::cout << "Point2 is similar to Point but has copy constructor and assignment operator deleted" << std::endl;
    std::cout << "Point2 has a copy constructor: " << std::is_copy_constructible<Point2>::value << std::endl;  // False
    std::cout << "Point2 has a move constructor: " << std::is_move_constructible<Point2>::value << std::endl;  // False
    std::cout << "Point2 is copy assignable: " << std::is_copy_assignable<Point2>::value << std::endl;         // False
    std::cout << "Point2 is move assignable: " << std::is_move_assignable<Point2>::value << std::endl;         // False
    std::cout << std::endl;

    // e) Add move semantics code (explicit move constructor and move assignment operator) and 
    // perform steps b)-c) again; do you get the same result?
    // Similarly, the changed code is now in class Point3
    std::cout << "Point3 is similar to Point but has copy constructor and assignment operator deleted" << std::endl;
    std::cout << "Point3 has a copy constructor: " << std::is_copy_constructible<Point3>::value << std::endl;  // False
    std::cout << "Point3 has a move constructor: " << std::is_move_constructible<Point3>::value << std::endl;  // True
    std::cout << "Point3 is copy assignable: " << std::is_copy_assignable<Point3>::value << std::endl;         // False
    std::cout << "Point3 is move assignable: " << std::is_move_assignable<Point3>::value << std::endl;         // True

    return 0;
}