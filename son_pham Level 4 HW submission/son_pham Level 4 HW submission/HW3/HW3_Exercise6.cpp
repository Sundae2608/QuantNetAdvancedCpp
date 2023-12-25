/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 3, Exercise 6: Boost Random 101
*/

#include <boost/random.hpp>
#include <iostream>
#include <random>

int main36() {
	// a) Create a variate of the triangle distribution with
	// lagged Fibonacci as
	// random number engine.
	typedef boost::random::lagged_fibonacci607 engine_type;
	engine_type engine;

	typedef boost::random::triangle_distribution<> triangle_dist_type;
	triangle_dist_type triangle_dist(0.0, 1.0); // Adjust parameters as needed

	boost::variate_generator<engine_type &, triangle_dist_type>
	triangle_variate(
		engine, triangle_dist);

	for (int i = 0; i < 10; ++i) {
		std::cout << "Triangle variate generation " << i << ": " << triangle_variate() << std::endl;
	}

	// b) Use Boost function template generate_canonical() to generate a value
	// uniformly in the range [0,1) with at least bits random bits:
	std::random_device rd;
	std::mt19937 gen(rd());

	// Experiment with various values of bits (for example, 8,16,32).
	double value;
	value = boost::random::generate_canonical<double, 8>(gen);
	std::cout << "Random double [0, 1) using 8 bits " << value << std::endl;
	value = boost::random::generate_canonical<double, 16>(gen);
	std::cout << "Random double [0, 1) using 16 bits " << value << std::endl;
	value = boost::random::generate_canonical<double, 64>(gen);
	std::cout << "Random double [0, 1) using 64 bits " << value << std::endl;

	return 0;
}