/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 4, Exercise 1: Unique Pointers
*/

#include <iostream>
#include <memory>
#include <stdexcept>

namespace {
	class Point {
	public:
		Point(double x, double y) : x(x), y(y) {};
		void X(double new_x) {
			x = new_x;
		}
		void Y(double new_y) {
			y = new_y;
		}
		double x;
		double y;
	};

	// Template alias for part d
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;
}

int main41() {
	
	// a) Type, run and test the above code. Introduce a try-catch block in which memory is 
	// allocated and directly afterwards an exception is thrown. Since the code is not re-entrant
	// the memory is not reclaimed and hence introduces a memory leak (in more general cases it 
	// would be a resource leak).
	//double* d;
	//Point* pt;
	//try {

	//	// Block with raw pointer lifecycle
	//	double* d = new double(1.0);
	//	Point* pt = new Point(1.0, 2.0);// Two-d Point class
	//
	//	// Dereference and call member functions
	//	*d = 2.0;
	//	(*pt).X(3.0);// Modify x coordinate
	//	(*pt).Y(3.0);// Modify y coordinate

	//	// Can use operators for pointer operations
	//	pt->X(3.0);// Modify x coordinate
	//	pt->Y(3.0);// Modify y coordinate

	//	// Throw an artificial exception to introduce a memory leak here.
	//	throw std::exception();

	//	// Explicitly clean up memory (if you have not forgotten)
	//	delete d;
	//	delete pt;
	//}
	//catch (...) {
	//	std::cerr << "Exception caught" << std::endl;
	//}

	// b) Now port the above code by replacing raw pointers by std::unique_ptr. 
	// Run the code. There shouldn't be any leak now.
	std::unique_ptr<double> d2 = std::make_unique<double>(1.0);
	std::unique_ptr<Point> pt2 = std::make_unique<Point>(1.0, 2.0);// Two-d Point class

	// Dereference and call member functions
	*d2 = 2.0;
	(*pt2).X(3.0);// Modify x coordinate
	(*pt2).Y(3.0);// Modify y coordinate

	// Can use operators for pointer operations
	pt2->X(3.0);// Modify x coordinate
	pt2->Y(3.0);// Modify y coordinate

	// c) Experiment with the following: initializing two unique pointers to the
	// same pointer, assigning a unique pointer to another unique pointers and
	// transferring ownership from one unique pointer to another unique pointer.

	// Initialize two unique pointers to the same pointer
	double* x_ptr = new double(42.0);

	std::unique_ptr<double> unique_ptr1( x_ptr );
	// std::unique_ptr<double> unique_ptr2( x_ptr );  // This cause a run time error

	// Assigning a unique pointer to another unique pointer
	std::unique_ptr<int> int_ptr1 = std::make_unique<int>(42);
	//std::unique_ptr<int> int_ptr2 = int_ptr1;  // This cause a compile time error

	// Transferring ownership from one unique pointer to another unique pointer
	std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
	std::unique_ptr<int> ptr2;
	ptr2 = std::move(ptr1); // Ownership transferred from ptr1 to ptr2
	std::cout << "ptr2 value: " << *ptr2 << std::endl;

	// d) Use alias template (template typedef) to make the code more readable.
	// I am not sure about this. This code is just barely more readable than previously.
	// Furthermore, I can even use auto to imply the type. I don't think alias template
	// really helps here.
	UniquePtr<double> d = std::make_unique<double>(1.0);
	UniquePtr<Point> pt = std::make_unique<Point>(1.0, 2.0);
	return 0;
}