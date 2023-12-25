/* 
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 1, Exercise 1
Compiled in C++ 20
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <utility>

constexpr float kMinFloat = std::numeric_limits<float>::min();
constexpr float kMaxFloat = std::numeric_limits<float>::max();

// b) Print the values of the modified array using auto to inialize
// of declaring it explicity
//
// Since the assignment asked me to use an iterator, I decided to do
// it this way.
void print_array(const std::vector<float>& arr) {
	for (auto it = arr.begin(); it != arr.end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << "\n";
}

// Exercise 1: First Encounters with Lambda Functions
int main11() {

	// a) Create a lambda function multiplies each element of an array
	// by a number.
	float i = 2;
	float* ptr_i = &i;
	std::vector<float> arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
	std::cout << "Before\n";
	print_array(arr);
	std::for_each(arr.begin(), arr.end(), [i](float& x) {
		return x * i;
		});
	std::cout << "After multiplied by 2 (passed by value)\n";
	print_array(arr);

	std::for_each(arr.begin(), arr.end(), [&ptr_i](float& x) {
		return x * (*ptr_i);
		});
	std::cout << "After multiplied by 2 (passed by reference)\n";
	print_array(arr);

	// c) Write a lambda function to compute both the minimum and maximum of the array
	// Since we use lambda to compute min and max, this implies the use of mutable labmda
	auto findMindMax = [](std::vector<float>& arr) -> std::pair<float, float> {
		float min = kMaxFloat;
		float max = kMinFloat;
		std::for_each(arr.begin(), arr.end(), [&min](float x) mutable {
			min = (x < min) ? x : min;
			});
		std::for_each(arr.begin(), arr.end(), [&max](float x) mutable {
			max = (x > max) ? x : max;
			});
		return { min, max };
	};
	const auto [min_num, max_num] = findMindMax(arr);
	std::cout << "Min: " << min_num << ", Max: " << max_num << "\n";

	// d) Compare the approach taken in part c) by calling std::minmax_element. 
	// For example, do you get the same output? How easy is to understand and
	// reuse the code?
	std::cout << "Using std::minmax_element\n";
	const auto [min_num2, max_num2] = std::minmax_element(arr.begin(), arr.end());
	std::cout << "Min: " << *min_num2 << ", Max: " << *max_num2;

	// The output is not quite teh same. std::minmax_element seems to return a
	// pair of pointer instead of a pair of value. But since we have to dereference
	// the ointer, it is pretty easy overall.
	return 0;
}