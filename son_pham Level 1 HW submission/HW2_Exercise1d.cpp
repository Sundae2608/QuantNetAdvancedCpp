/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 2, Exercise 1d, Adding noexcept
Compiled in C++ 20
*/

#include <algorithm>
#include <iostream>
#include <vector>

class C {
public:
	C(std::vector<int>& input_v) noexcept : v_(input_v) {
		std::cout << "Constructor called." << std::endl;
	}
	~C() noexcept {
		std::cout << "Destructor called." << std::endl;
	}
	C(C& other_c) noexcept : v_(other_c.v_) {
		std::cout << "Copy constructor called." << std::endl;
	}
	C& operator=(const C& other_c) noexcept {
		this->v_ = other_c.v_;
		std::cout << "Assignment operator called." << std::endl;
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
	constexpr void scale(int s) noexcept {
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

int main21d() {
	std::vector<int> vec{ 1, 2, 3, 4, 5 };
	C c(vec);
	C c2 = c;
	c2 = c2;
	c.print();
	std::cout << "Doubling each element" << std::endl;
	c.scale(2);
	c.print();
	return 0;
}