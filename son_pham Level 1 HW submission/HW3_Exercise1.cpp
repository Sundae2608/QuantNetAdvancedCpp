/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 3, Exercise 1: Fundamentals of Variadics
Compiled in C++ 20
*/

#include <bitset>
#include <iostream>

template <typename T>
void print(const T& arg) {
	std::cout << arg;
}

template <typename T, typename... Types>
void print(const T& arg, const Types&... args) {
	std::cout << arg << ", ";
	print(args...);
}

int main31() {
	// Variadic function templates
	int j = 1; double d = 2.0;
	print(j); print(d); print(j, d); print(d, j);
	std::cout << "\n3 params \n";
	print(d, j, std::bitset<8>(233));
	return 0;
}