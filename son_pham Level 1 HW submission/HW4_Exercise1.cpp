/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 4, Exercise 1: Function wrappers
Compiled in C++ 20
*/

#include <functional>
#include <iostream>

template <typename T>
using FunctionType = std::function<T(const T& t)>;

template <typename T>
void print(const FunctionType<T>& f, T t)
{
	std::cout << f(t) << '\n';
}

double foo(double x) {
	std::cout << "Free function foo" << std::endl;
	return x * 2;
}

struct FooObject {
	double operator()(double x) const {
		std::cout << "FooObject" << std::endl;
		return x * 2;
	}
};

int main41() {
	// Instance of a function wrapper
	FunctionType<double> f;

	// Assign a free function
	f = foo;
	print(f, 2.0);

	// Assign a function object
	FooObject foo_func;
	f = foo_func;
	print(f, 2.0);

	// Stored lambda function
	f = [](double x) {
		std::cout << "Lambda" << std::endl;
		return x * 2;
	};
	print(f, 2.0);
	return 0;
}