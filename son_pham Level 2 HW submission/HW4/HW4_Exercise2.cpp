/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 4, Shared Pointers
*/

#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
    class C1 {
        private:
            std::shared_ptr<double> d;

        public:
            C1(std::shared_ptr<double> value) : d(value) {}
            virtual ~C1() { std::cout << "C1 destructor" << std::endl; }

            void print() const {
                std::cout << "C1 - Value: " << *d << std::endl;
            }
    };

    class C2 {
        private:
            std::shared_ptr<double> d;

        public:
            C2(std::shared_ptr<double> value) : d(value) {}
            virtual ~C2() { std::cout << "C2 destructor" << std::endl; }

            void print() const {
                std::cout << "C2 - Value: " << *d << std::endl;
            }
    };

    class Point {
    private:
        double x;
        double y;

    public:
        Point(double x, double y) : x(x), y(y) {}
        void X(double new_x) {
            x = new_x;
        }
        void Y(double new_y) {
            y = new_y;
        }
        double getX() const { return x; }
        double getY() const { return y; }
    };

    class CPoint1 {
        private:
            std::shared_ptr<Point> p;

        public:
            CPoint1(std::shared_ptr<Point> point) : p(point) {}
            virtual ~CPoint1() { std::cout << "CPoint1 destructor" << std::endl; }

            void print() const {
                std::cout << "C1 - Point: (" << p->getX() << ", " << p->getY() << ")" << std::endl;
            }
    };

    class CPoint2 {
    private:
        std::shared_ptr<Point> p;

    public:
        CPoint2(std::shared_ptr<Point> point) : p(point) {}
        virtual ~CPoint2() { std::cout << "CPoint2 destructor" << std::endl; }

        void print() const {
            std::cout << "C1 - Point: (" << p->getX() << ", " << p->getY() << ")" << std::endl;
        }
    };
}

int main42() {
    std::shared_ptr<double> d = std::make_shared<double>(3.14);

    // a) Create the code for the classes C1 and C2 each of which contains the
    // shared object from the value d above
    std::cout << "Part a)" << std::endl;
    C1 c1(d);
    C2 c2(d);
    c1.print();  // 3.14
    c2.print();  // 3.14
    *d = 42;
    c1.print();  // 42
    c2.print();  // 42
    std::cout << std::endl;

    // b) Create instances of these classes in scopes so that you can see that
    // resources are automatically released when no longer needed. To this end,
    // employ the member function use_count() to keep track of the number of shared
    // owners. This number should be equal to 0 when the program exits.
    std::cout << "Part b)" << std::endl;
    std::shared_ptr<double> d2;
    std::cout << "Current count: " << d2.use_count() << std::endl;  // 0
    {
        d2 = std::make_shared<double>(42);
        std::cout << "Current count: " << d2.use_count() << std::endl;  // 1
        C1 c1(d);
        std::cout << "Current count: " << d2.use_count() << std::endl;  // 1
        C2 c2(d);
        std::cout << "Current count: " << d2.use_count() << std::endl;  // 1
        std::shared_ptr<double> d3 = d2;
        std::cout << "Current count: " << d2.use_count() << std::endl;  // 2

        // It is quite interesting that:
        // 1. The shared pointer assignment inside the class did not increment the counter. Only a second
        // initialization of another shared pointer in which d2 was assigned to increases the count.
        c1.print();  // 3.14
        c2.print();  // 3.14
        *d = 42;
        c1.print();  // 42
        c2.print();  // 42

        // Transfer pointer ownernship
        std::shared_ptr<double> d4 = std::move(d3);
        if (d3 == nullptr) {
            std::cout << "d3 is empty after ownership transfer" << std::endl;
        }
        std::cout << "Current count: " << d2.use_count() << std::endl;  // Count is still 2 here.

        // Determine if shared ptr is the only owner of resource.
        // In this case, d2 is not the only owner since there is d4 existing, we can observe that by
        // count 2. However, out of this scope, d2 is the sole owner.

        // Swap 2 shared ptr
        std::shared_ptr<double> d5 = std::make_shared<double>(99);
        std::swap(d4, d5);
        std::cout << "d4 = " << *d4 << std::endl;  // 99
        std::cout << "d5 = " << *d5 << std::endl;  // 42
    }
    std::cout << "Current count: " << d2.use_count() << std::endl;  // 1
    // Give up ownership and reinitialise the shared pointer as being empty.
    d2.reset();
    std::cout << "Current count: " << d2.use_count() << std::endl;  // 0
    std::cout << std::endl;

    // c) Carry out the same exercise as in steps a) and b) but with a user-defined type as shared data:
    std::cout << "Part c) Repeat a for Class with Point" << std::endl;
    std::shared_ptr<Point> p = std::make_unique<Point>(2.0, 4.0);
    CPoint1 cpoint1(p);
    CPoint2 cpoint2(p);
    cpoint1.print();  // (2.0, 4.0)
    cpoint2.print();  // (2.0, 4.0)
    p->X(8.0);
    p->Y(16.0);
    cpoint1.print();  // (8.0, 16.0)
    cpoint2.print();  // (8.0, 16.0)
    std::cout << std::endl;

    std::cout << "Part c) Repeat b for Class with Point" << std::endl;
    std::shared_ptr<Point> p2;
    std::cout << "Current count: " << p2.use_count() << std::endl;  // 0
    {
        p2 = std::make_unique<Point>(2.0, 4.0);
        std::cout << "Current count: " << p2.use_count() << std::endl;  // 1
        CPoint1 cpoint1(p2);
        std::cout << "Current count: " << p2.use_count() << std::endl;  // 2
        CPoint2 cpoint2(p2);
        std::cout << "Current count: " << p2.use_count() << std::endl;  // 3
        cpoint1.print();  // (2.0, 4.0)
        cpoint2.print();  // (2.0, 4.0)
        p2->X(8.0);
        p2->Y(16.0);
        cpoint1.print();  // (8.0, 16.0)
        cpoint2.print();  // (8.0, 16.0)
        std::shared_ptr p3 = p2;
        std::cout << "Current count: " << p2.use_count() << std::endl;  // 4

        // Transfer pointer ownernship
        std::shared_ptr<Point> p4 = std::move(p3);
        if (p3 == nullptr) {
            std::cout << "p3 is empty after ownership transfer" << std::endl;
        }
        std::cout << "Current count: " << p2.use_count() << std::endl;  // Count is still 4 here.

        // Determine if shared ptr is the only owner of resource.
        // In this case, p2 is not the only owner since there is p4 existing, and that cpoint1 and cpoint2
        // contains internal pointer that shared the ownernship with p2.
        // However, out of this scope, p2 is the sole owner.

        // Swap 2 shared ptr
        std::shared_ptr<Point> p5 = std::make_shared<Point>(99, 99);
        std::swap(p4, p5);
        std::cout << "p4 = (" << p4->getX() << ", " << p4->getY() << ")" << std::endl;  // (99, 99)
        std::cout << "p5 = (" << p5->getX() << ", " << p5->getY() << ")" << std::endl;  // (8, 16)
    }
    std::cout << "Current count: " << p2.use_count() << std::endl;  // 1
    // Give up ownership and reinitialise the shared pointer as being empty.
    p2.reset();
    std::cout << "Current count: " << p2.use_count() << std::endl;  // 1
    std::cout << std::endl;

    // It is quite interesting that the class counter seems to be compiled different
    // compared to primitive pointer. There is an addition count of p2 for every CPoint
    // that additionally refers to p2. We can conclude that C++ 20 (or perhaps its compiler)
    // treat shared pointer for primitive and shared pointer for class differently.

    // d) Now extend the code in parts a) to c) to include the following operations on shared pointers: 
    // assigning, copy and compare two shared pointers sp1 and sp2. Furthermore, test the following features (some research needed here):
    // - Transfer ownership from sp1 to sp2.
    // - Determine if a shared pointer is the only owner of a resource.
    // - Swap sp1and sp2.
    //  - Give up ownershipand reinitialise the shared pointer as being empty.
    // For ease of management, I did it as part of each part above.
	return 0;
}