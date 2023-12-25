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
	template <std::size_t N>
	void printBitset(const std::bitset<N>& bitset) {
		for (std::size_t i = N - 1; i < N; --i) {
			std::cout << bitset[i];
		}
	}
}

int main82() {
	// a) Creating two bitsets bs1 and bs2 of the same size:
	std::bitset<8> bs1("11001100");
	std::bitset<8> bs2("10101010");
	std::cout << "Bitset 1: ";
	printBitset(bs1);
	std::cout << std::endl << "Bitset 2: ";
	printBitset(bs1);
	std::cout << std::endl << std::endl;

	// b) Toggling all the bits of bs1 and bs2:
	bs1.flip();
	bs2.flip();
	std::cout << "Bitset 1: ";
	printBitset(bs1);
	std::cout << std::endl << "Bitset 2: ";
	printBitset(bs2);
	std::cout << std::endl << std::endl;

	// c) Performing bitwise XOR, OR, and AND operations on bs1 and bs2:
	std::bitset<8> resultXOR = bs1 ^ bs2;  // Bitwise XOR
	std::bitset<8> resultOR = bs1 | bs2;   // Bitwise OR
	std::bitset<8> resultAND = bs1 & bs2;  // Bitwise AND

	std::cout << "bs1 ^ bs2 = ";
	printBitset(resultXOR);
	std::cout << std::endl;
	std::cout << "bs1 | bs2 = ";
	printBitset(resultOR);
	std::cout << std::endl;
	std::cout << "bs1 & bs2 = ";
	printBitset(resultAND); 

	// d) Performing right and left shift operations on bs1 and bs2:
	std::bitset<8> resultRightShift = bs1 >> 2;  // Right shift by 2 positions
	std::bitset<8> resultLeftShift = bs2 << 3;   // Left shift by 3 positions
	std::cout << "bs1 >> 2 = ";
	printBitset(resultRightShift);
	std::cout << "bs1 << 3 = ";
	printBitset(resultLeftShift);

	// e) Creating hashed values for bs1 and bs2 using std::hash:
	int hashValue1 = std::hash<std::bitset<8>>{}(bs1);
	int hashValue2 = std::hash<std::bitset<8>>{}(bs2);
	std::cout << "Hash(bs1) = " << hashValue1 << std::endl;
	std::cout << "Hash(bs2) = " << hashValue2 << std::endl;

	// f) Binary literals and their relationship with bitsets:
	// Basically, you can represent binary literals are values that can represent binary directly in code.
	// Binary literals can be created like the following example. You can create a bitset from literals.
	auto blit = 0b0011;
	std::bitset<4> bs(blit);
	std::cout << "bitset: " << bs << '\n';

	// g) Create a byte in different ways: from a binary literal, from an integer,
	// as binary logical operators on existing bytes.
	std::byte b1 { 0b0011 };  // Create from a binary literal
	std::byte b2 = std::byte(0x12);  // Create from an integer (hexadecimal value)
	std::byte b3 = std::byte(0b1100) & std::byte(0b1010);  // Create using binary logical operators
	std::cout << "b1: " << std::to_integer<int>(b1) << std::endl;
	std::cout << "b2: " << std::to_integer<int>(b2) << std::endl;
	std::cout << "b3: " << std::to_integer<int>(b3) << std::endl;

	// h) Perform bitwise operations on bytes (AND, OR).
	std::byte result_and = b1 & b2;  // Bitwise AND
	std::cout << "b1 & b2: " << std::to_integer<int>(result_and) << std::endl;
	std::byte result_or = b1 | b2;   // Bitwise OR
	std::cout << "b1 | b2: " << std::to_integer<int>(result_or) << std::endl;
	
	// i) Left and right shift operations on bytes can be done using the shift operators (>> and <<):
	std::byte result_left_shift = b1 << 2;   // Left shift by 2 bits
	std::cout << "b1 << 2: " << std::to_integer<int>(result_left_shift) << std::endl;  // 12
	std::byte result_right_shift = b1 >> 1;  // Right shift by 1 bit
	std::cout << "b1 >> 1: " << std::to_integer<int>(result_right_shift) << std::endl;  // 1

	// When performing left shift or right shift operations on bytes, 
	// it's important to consider the "extreme cases" of shifting. 
	// Shifting a byte beyond its size will lead to undefined behavior. 
	// It's necessary to ensure that the shift amount is within the valid range
	// (0 to 7 for an 8-bit byte).
	std::byte result_left_shift_9 = b1 << 9;   // Left shift by 2 bits
	std::cout << "b1 << 9: " << std::to_integer<int>(result_left_shift_9) << std::endl;  // Shows as 0
	std::byte result_right_shift_9 = b1 >> 9;  // Right shift by 1 bit
	std::cout << "b1 >> 9: " << std::to_integer<int>(result_right_shift_9) << std::endl;  // Shows as 0

	// j) Some of the examples that I can think of using bitsets and bytes
	// Raw memory access: Bytes and bitsets are often used when working with 
	// low-level memory operations or when dealing with binary data at the byte level.
	// They allow you to manipulate individual bits and bytes directly, which can be
	// useful in tasks such as reading / writing data to / from specific memory
	// addresses or performing bitwise operations on memory - mapped hardware registers.

	// Storage and memory optimization : Bytes and bitsets can be utilized to represent
	// compact data structures where individual bits or bytes are important. They can be
	// used to efficiently store and manipulate flags, permissions, or other data that
	// can be represented by individual bits or groups of bits.

	// Performance optimizations: In certain scenarios, using bit-level operations can be more efficient.
	// For example, a left shift by 2 is a much quicker division by 2 than a division, at the cost of
	// code clarity.
	return 0;
}