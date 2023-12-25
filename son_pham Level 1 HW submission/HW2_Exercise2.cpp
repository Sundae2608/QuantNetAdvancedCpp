/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 2, Exercise 2
Compiled in C++ 20
*/

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

template < typename T >
void SwapCopyStyle(T& a, T& b)
{
	// Swap a and b in copying way; temporary object needed
	T tmp(a); // Copy constructor
	a = b; // Copy all elements from b to a
	b = tmp; // Copy all elements from tmp to b
}

template < typename T >
void SwapMoveStyle(T& a, T& b)
{
	T tmp = std::move(a);
	a = std::move(b);
	b = std::move(tmp);
}

void print_vector(std::vector<int>& v) {
	std::for_each(v.begin(), v.end(), [](int& a) {std::cout << a << ", "; });
	std::cout << std::endl;
}

int main22() {

	// Exercise 2a
	std::string s = "Demo string";
	std::cout << "Initial string s: " << s << std::endl;
	std::string s2 = std::move(s);
	std::cout << "String s after move: " << s << std::endl;  // After move, string s seems empty
	std::cout << "String s2 after move: " << s2 << std::endl;

	// Exercise 2b
	auto time1 = std::chrono::system_clock::now();
	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto time2 = std::chrono::system_clock::now();
	std::vector<int> v2 = std::move(v);
	auto time3 = std::chrono::system_clock::now();
	std::vector<int> v3 = v2;
	auto time4 = std::chrono::system_clock::now();

	// Check content
	std::cout << "After all the moves and assignment, the following is the content of each vector: " << std::endl;
	std::cout << "v: ";
	print_vector(v);
	std::cout << "v2: ";
	print_vector(v2);
	std::cout << "v2 move time: " << time3 - time2 << std::endl;
	std::cout << "v3: ";
	print_vector(v3);
	std::cout << "v3 move time: " << time4 - time3 << std::endl;
	
	// Based on the time measured by chrono, it is clear that move semantics
	// is a lot faster than array copying

	// Exercise 2c;
	std::vector<int> vec1;
	std::vector<int> vec2;
	int num_nums = 100000;
	for (int i = 0; i < num_nums; i++) {
		(i % 2) == 0 ? vec1.push_back(i) : vec2.push_back(i);
	}
	auto time5 = std::chrono::system_clock::now();
	SwapCopyStyle(vec1, vec2);
	auto time6 = std::chrono::system_clock::now();
	std::cout << "Copy style time: " << time6 - time5 << std::endl;
	//std::cout << "Vec1 after copy style swap: ";
	//print_vector(vec1);
	//std::cout << "Vec2 after copy style swap: ";
	//print_vector(vec2);

	auto time7 = std::chrono::system_clock::now();
	SwapMoveStyle(vec1, vec2);
	auto time8 = std::chrono::system_clock::now();
	std::cout << "Move style time: " << time8 - time7 << std::endl;
	//std::cout << "Vec1 after move style swap: ";
	//print_vector(vec1);
	//std::cout << "Vec2 after move style swap: ";
	//print_vector(vec2);

	// Clearly move style swap is better that copy style swap.
	return 0;
}