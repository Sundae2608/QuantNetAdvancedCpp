/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 2, Exercise 1a, default and delete
Compiled in C++ 20
*/

#include <algorithm>
#include <iostream>
#include <vector>

// In this exercise. We have to:
// 1. Delete the default construct.
// 2. Make the assignment operator and the copy constructor private;
class C {
public:
	C() = default;
	C(std::vector<int>& input_v) : v_(input_v) {
		std::cout << "Constructor called." << std::endl;
	}
	~C() {
		std::cout << "Destructor called." << std::endl;
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
	C(C& other_c) = delete;
	C& operator=(const C& other_c) = delete;

	friend class CFriend;
};

// Define a friend class to show that the method can't be used.
class CFriend {
public:
	void doSomethingToFriend(C& c) {
		// These still failed to compiled.
		// C c(c);
		// c = c;
	}
};

int main21a() {
	std::vector<int> vec{ 1, 2, 3, 4, 5 };
	C c(vec);
	c.print();
	std::cout << "Doubling each element" << std::endl;
	c.scale(2);
	c.print();
	// These two lines now failed to compile because the function is
	// already deleted.
	// C c2 = c;
	// c2 = c2;
	return 0;
}