/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 3, Exercise 2: Variadics and Polymorphic Behaviour
Compiled in C++ 20
*/

#include <array>
#include <iostream>

namespace {
	class Shape
	{
	public:
		virtual void rotate(double d) = 0;
	};

	class Circle : public Shape
	{
	public:
		void rotate(double d) override { std::cout << "c\n"; }
	};

	class Line : public Shape
	{
	public:
		void rotate(double d) override { std::cout << "l\n"; }
	};

	class Valve
	{
	public:
		void rotate(double d) { std::cout << "v\n"; }
	};

	template <typename T>
	void rotate(double factor, T& arg) {
		arg.rotate(factor);
	}

	template <typename T, typename... Types>
	void rotate(double factor, T& arg, Types&... args) {
		arg.rotate(factor);
		rotate(factor, args...);
	}
}

int main32() {

	// 2a. Creating variadic function that rotate each of these shapes.
	std::cout << "Exercise 2a";
	Circle circle;
	Line line;
	Valve valve;
	double factor = 2.0;
	rotate(factor, circle);
	rotate(factor, circle, line);
	rotate(factor, circle, valve);
	rotate(factor * 2, circle, valve, line);

	// 2b. We cannot include Valve in the array because Val does not inherit from Shape,
	// and is therefore not recognized as Shape, which is required to be added to an
	// array of Shape pointer.
	std::cout << "Exercise 2b";
	std::array<Shape*, 5> shapeList{ &circle, &line, &circle, &circle, &line };
	double factor2 = 20.0; 
	for (auto& elem : shapeList)
	{
		rotate(factor2, *elem);
	}
	return 0;
}