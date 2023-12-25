/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 6, Exercise 2: Implementing the GOF Template Method Pattern (TMP)
Compiled in C++ 20
*/

#include <algorithm>
#include <functional>
#include <iostream>

using InputFunction = std::function<double()>;
using OutputFunction = std::function<void(const std::vector<double>&)>;

class TMPClass {
public:
	TMPClass(std::size_t n, double start_value, InputFunction i_func, OutputFunction o_func) :
		vec_(n, start_value), i_func_(i_func), o_func_(o_func) {
		
	};
	
	void process() {
		// Multiply each element by a given value from the abstract input source
		double value = i_func_();
		std::transform(vec_.begin(), vec_.end(), vec_.begin(), [value](double element) { return value * element; });

		// Send the data to output device
		o_func_(vec_);
	}
private:
	std::vector<double> vec_;
	InputFunction i_func_;
	OutputFunction o_func_;
};

double SampleInputDevice() {
	return 10.0;
}

void SampleOutputDevice(const std::vector<double>& vec) {
	std::for_each(vec.begin(), vec.end(), [](const double& element) { std::cout << element << " "; });
}

int main62() {
	TMPClass sample_tmp(10, 5.0, SampleInputDevice, SampleOutputDevice);
	sample_tmp.process();
	return 0;
}