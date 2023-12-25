/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 8, Exercise 1: STL Bitset 101
*/

#include <bitset>
#include <iostream>
#include <string>
#include <stdexcept>

namespace {

	std::bitset<8> createBitsetFromPartialString(const std::string& partial_string, std::size_t start_index, std::size_t num_bits) {
		std::string substr = partial_string.substr(start_index, num_bits);
		if (substr.length() != num_bits) {
			throw std::out_of_range("Invalid substring length");
		}
		return std::bitset<8>(substr);
	}
}

int main81() {
	// a) Create bitsets from unsigned long and unsigned long long.
	unsigned long ul_value = 123456789UL;
	std::bitset<sizeof(unsigned long) * 8> bitset_from_ul(ul_value);

	unsigned long long ull_value = 987654321ULL;
	std::bitset<sizeof(unsigned long long) * 8> bitset_from_ull(ull_value);

	// b) Create bitsets from full strings (for example, “01010”). Create a bitset from parts of strings based on a start index and the number of bits to use.
	std::string full_string = "01010101";
	std::bitset<8> bitset_from_full_string(full_string);
	std::cout << "Bitset from full string: " << bitset_from_full_string << std::endl;

	std::string partial_string = "11001100";
	std::size_t start_index = 2;
	std::size_t num_bits = 4;
	std::bitset<8> bitset_from_partial_string;
	try {
		bitset_from_partial_string = createBitsetFromPartialString(partial_string, start_index, num_bits);
		std::cout << "Bitset from partial string: " << bitset_from_partial_string << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	// c) Using exception handling to check for out-of-range values and invalid arguments:
	// We include this as part of part b

	// d) Examples of different operations on bitsets:
	std::bitset<8> my_bit_set;

	// Set/reset all bits
	my_bit_set.set();    // Set all bits to 1
	my_bit_set.reset();  // Reset all bits to 0

	// Flip the bits
	my_bit_set.flip();   // Flip all the bits (1s become 0s, and 0s become 1s)

	// Test if none, all, or any bits are set
	bool none_set = my_bit_set.none();   // Check if no bits are set
	bool all_set = my_bit_set.all();     // Check if all bits are set
	bool any_set = my_bit_set.any();      // Check if any bit is set

	// Access the elements
	bool first_bit = my_bit_set[0];      // Access individual bits

	// Count the number of set bits
	std::size_t num_set_bits = my_bit_set.count();

	// e) Converting a bitset to std::string, unsigned long, and unsigned long long:
	std::bitset<8> my_bit_set_2("10101010");

	// Convert bitset to std::string
	std::string bitset_string = my_bit_set_2.to_string();

	// Convert bitset to unsigned long
	unsigned long ul = my_bit_set_2.to_ulong();

	// Convert bitset to unsigned long long
	unsigned long long ull = my_bit_set_2.to_ullong();

	std::cout << "Bitset as string: " << bitset_string << std::endl;
	std::cout << "Bitset as unsigned long: " << ul << std::endl;
	std::cout << "Bitset as unsigned long long: " << ull << std::endl;
	return 0;

}