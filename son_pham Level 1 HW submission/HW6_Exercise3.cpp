/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 6, Exercise 3: Implementing the GOF Template Method Pattern (TMP)
Compiled in C++ 20
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

// This is reused class from Exercise 3
class C {
public:
	C() {
		std::cout << "Default constructor with no argument called" << std::endl;
	};
	C(std::vector<int>& input_v) : v_(input_v) {
		std::cout << "Default constructor called." << std::endl;
	}
	C(std::initializer_list<int> list) : v_(list) {
		std::cout << "Default constructor with list initialization" << std::endl;
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

struct CAggregate {
	int i1;
	int i2;
	int i3;
};

struct S
{
	int x;
	struct Foo
	{
		int i; int j; int a[3];
	} b;
};

int main63() {
	// Part 1: Example of initializations
	// Default initialisation : object is constructed without an initializer.
	C c1;

	// Value initialisation : object is constructed with an empty initializer.
	C c2{};

	// Direct initialisation : object is initialised from an explicit set of constructor arguments.
	std::vector<int> vec_arg{ 1, 2, 3 };
	C c3(vec_arg);

	// Copy initialisation : object is initialised from another object.
	C c4 = c3;

	// List initialisation : object is initialised from braced - init - list.
	C c5{ 1, 2, 3, 4 };

	// Aggregate initialisation : initialise an aggregate from a braced - init - list.
	CAggregate c6{ 1, 2, 3 };

	// Reference initialisation : bind a reference to an object.
	C& c7 = c1;

	// Part 2: I am not sure what does ill-formed case mean here. I presumed that this is when it doesn't
	// compile. One thing that I did try and not compile was wheN I tried to initialize C6 using aggregate
	// initialization. This doesn't seem to work
	// C c6 { 1, 2, 3 };

	// Part 3: Apply aggregate initialisation to the following class.
	S s1{ 1, {2, 3, {4, 5, 6}} };
	S s2{ 1, {2, 3} };
	S s3{ 1, {2} };
	S s4{ 1 };

	// One thing interesting to me is that I don't have to really initialize every argument. The compiler
	// simply takes argument in 1-by-1. The only one case where it doesn't compile is when it is out of
	// order. Something like:
	// S s5 {1, {4, 5, 6}};
	return 0;
}