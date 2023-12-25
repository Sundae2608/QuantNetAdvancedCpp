/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 5, Exercise 1: Tuple / Span 101
Compiled in C++ 20
*/

#include <algorithm>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <string>
#include <span>
#include <tuple>
#include <vector>

// 1a. Create a tuple that models that person and create some attributes attached to them.
using Date = boost::gregorian::date;
using Person = std::tuple<std::string, std::string, Date>;

// 1b. Print function
void print(const Person& person) {
	std::cout << "Name: " << std::get<0>(person) << std::endl;
	std::cout << "Address: " << std::get<1>(person) << std::endl;
	std::cout << "Date of Birth: " << std::get<2>(person) << std::endl;
}

void print_span_range_based(std::span<int>& span) {
	std::for_each(span.begin(), span.end(), [](int& num) {
		std::cout << num << ", ";
		});
	std::cout << std::endl;
}

void print_span_iterator_loop(std::span<int>& span) {
	for (auto it = span.begin(); it != span.end(); it++) {
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}

void print_span_index_loop(std::span<int>& span) {
	for (int i = 0; i < span.size(); i++) {
		std::cout << span[i] << ", ";
	}
	std::cout << std::endl;
}

std::span<int> first_n_elements(std::span<int>& span, int n) {
	return span.subspan(0, n);
}

std::span<int> last_n_elements(std::span<int>& span, int n) {
	return span.subspan(span.size() - n, n); 
}

template <typename T>
void byte_view_of_span(std::span<T>& span)
{
	auto const const_bytes = std::as_bytes(span);
	for (auto const b : const_bytes)
	{
		std::cout << std::setw(2)
			<< std::hex
			<< std::uppercase
			<< std::setfill('0')
			<< std::to_integer<int>(b) << ' ';
	}
}

int main51() {
	// 1c. Create a vector of Person and add some instance of Person to it
	Person person1 = std::make_tuple("Son Pham", "Astoria NY 11105", Date(1995, 8, 26));
	Person person2 = std::make_tuple("Donal Trump", "Trump Tower NY", Date(1970, 1, 1));
	Person person3 = std::make_tuple("Barack Obama", "Obama Tower DC", Date(1970, 2, 2));

	std::vector<Person> people = { person1, person2, person3 };

	// 1d. Sort the person by name
	std::sort(people.begin(), people.end(), [](const Person& p1, const Person& p2) {
		return std::get<0>(p1) < std::get<0>(p2);
		});

	// 1e. Create a fixed size and variable size array and create a span view of them
	std::array<int, 5> fixed_array = { 1, 2, 3, 4, 5 };
	std::vector<int> variable_array = { 1, 2, 3, 4, 5 };
	std::span<int> fixed_span{ fixed_array };
	std::span<int> variable_span{ variable_array };

	// To see if they are read only, we can try to change the data through span.
	fixed_span[2] = 4;
	print_span_range_based(fixed_span);  // 1, 2, 4, 4, 5
	// This shows that the span is indeed mutable

	// 1f. Create 3 print functions for spans using range based loop, iterator 
	// loop and index loop
	print_span_range_based(fixed_span); // Range based for loop.
	print_span_iterator_loop(fixed_span); // Iterator loop
	print_span_index_loop(fixed_span); // Indexing loop

	// 1g. Write functions to return the first and last N elements of a span
	std::span<int> first_3_elements = first_n_elements(fixed_span, 3);
	std::cout << "First 3 elements: " << std::endl;
	print_span_range_based(first_3_elements);

	std::span<int> last_3_elements = last_n_elements(fixed_span, 3);
	std::cout << "Last 3 elements: " << std::endl;
	print_span_range_based(first_3_elements);

	// 1h. We already test the std::subspan within the implementation of
	// first_n_elements and last_n_elements;
	// 
	// 1i. Investigate and extend the following code to create “byte 
	// views of spans”.
	//
	// I am not quite sure what is the actual ask of the assignment here
	// but I do presume that the ask is about generalize this to
	// cover all kinds of data structure, and have a byte view of every
	// kind of span, not just the span of float.
	float data[3]{ 3.141592f, 3.141593f, 3.141594f };
	std::span<float> span_data{ data };
	byte_view_of_span(span_data);

	return 0;
}