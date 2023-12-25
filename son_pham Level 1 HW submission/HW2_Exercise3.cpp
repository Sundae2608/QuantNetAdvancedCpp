/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 2, Exercise 3
Compiled in C++ 20
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class C {
public:
	C(std::vector<int>& input_v) : v_(input_v) {
		std::cout << "Default Constructor called." << std::endl;
	}
	~C() {
		std::cout << "Destructor called." << std::endl;
	}
	C(C& other_c) : v_(other_c.v_) {
		std::cout << "Copy constructor called." << std::endl;
	}
	C& operator=(const C& other_c) {
		this->v_ = other_c.v_;
		std::cout << "Assignment operator called." << std::endl;
		return *this;
	}
	// a) Create the move constructor and move assignment for class C
	C(C&& other_c) noexcept : v_(std::move(other_c.v_)) {
		std::cout << "Move Constructor called." << std::endl;
	}
	C& operator=(const C&& other_c) {
		this->v_ = other_c.v_;
		std::cout << "Move Assignment operator called." << std::endl;
		return *this;
	}
	void print() {
		std::cout << "This C class contains a vector of length " << v_.size() << std::endl;
		std::cout << "Content: ";
		std::for_each(v_.begin(), v_.end(), [](int& a) {
			std::cout << a << ", ";
			});
		std::cout << std::endl;
	}
	constexpr void scale(int s) {
		std::for_each(v_.begin(), v_.end(), [s](int& a) {
			a *= s;
			});
	}
	constexpr void divide(int s) {
		std::for_each(v_.begin(), v_.end(), [s](int& a) {
			a /= s;
			});
	}
private:
	std::vector<int> v_;
};

int main23() {
	// b) Test the new functions. I used std::move explicitly to make sure the move constructor
	// is called instead of a copy constructor. This can be confirmed by the print statement
	// showing that it was the move constructor which was called.
	std::vector<int> vec{ 1, 2, 3, 4, 5 };
	C c1(vec);
	C c2 = std::move(c1);
	C c3(vec);
	c3 = std::move(c2);
	std::cout << "C1: ";
	c1.print();
	std::cout << "C2: ";
	c2.print();
	std::cout << "C3: ";
	c3.print();
	
	// c) What if we use lvalue as the source of the move operation.
	std::cout << "Exercise 3c)";
	C c4(vec);
	C& c5 = c4;
	C C6 = std::move(c5);  // Original move constructor, which uses copy is used here.
	// When I used an lvalue as the source of the move operation, interestingly it basically
	// makes the compiler perform copy opeartion instead. I think this is because lvalue is
	// just a reference. There isn't really anything there to move from in c5. However, we didn't
	// actually tells c4 to be explicitly moved. Therefore, the compiler compromised by just copying
	// c5. I wonder why the compiler just didn't return an error though, since move semantics
	// only bring value in those cases.
	return 0;
}