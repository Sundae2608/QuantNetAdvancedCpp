/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Exercise 5: Creating Object Adapters for Bitset, Compile-Time
*/

#include <array>
#include <bitset>
#include <iostream>
#include <boost/dynamic_bitset.hpp>

namespace {
	template <size_t N, size_t M>
	class BitMatrix {
	public:
		BitMatrix() = default;

		template <typename... Args>
		BitMatrix(Args... args) : data{ std::bitset<M>(args)... } {}

        // Set all rows
        void set() {
            for (auto& row : data) {
                row.set();
            }
        }

        // Set a specific rows
        void set(size_t row) {
            data[row].set();
        }

        // Reset all rows
        void reset() {
            for (auto& row : data) {
                row.reset();
            }
        }

        // Reset a specific row
        void reset(size_t row) {
            data[row].reset();
        }

        // Flip all bits in all rows
        void flip() {
            for (auto& row : data) {
                row.flip();
            }
        }

        // Flip a specific rows
        void flip(size_t row) {
            data[row].flip();
        }

        // Test if none of the bit is set for the entire matrix
        bool none() const {
            for (const auto& row : data) {
                if (!row.none()) {
                    return false;
                }
            }
            return true;
        }

        // Test if none of the bits in a specific row are set
        bool none(size_t row) const {
            return data[row].none();
        }

        // Test if all bits are set
        bool all() const {
            for (const auto& row : data) {
                if (!row.all()) {
                    return false;
                }
            }
            return true;
        }

        // Test if all of the bits in a specific row are set 
        bool all(size_t row) const {
            return data[row].all();
        }

        // Test if any bit in the entire matrix is set
        bool any() const {
            for (const auto& row : data) {
                if (row.any()) {
                    return true;
                }
            }
            return false;
        }


        // Test if any of the bits in a specific row are set
        bool any(size_t row) const {
            return data[row].any();
        }

        // Access elements in the matrix
        std::bitset<M>& operator()(size_t index) {
            return data[index];
        }

        // Access a specific element in the matrix
        bool& operator()(size_t row, size_t col) {
            return data[row][col];
        }

        // Count the number of set bits
        size_t count() const {
            size_t total = 0;
            for (const auto& row : data) {
                total += row.count();
            }
            return total;
        }

        // Matrix printer function
        void print() const {
            for (const auto& row : data) {
                std::cout << row << '\n';
            }
            std::cout << '\n';
        }

        // OR operation on two matrices
        BitMatrix<N, M> operator|(const BitMatrix<N, M>& other) const {
            BitMatrix<N, M> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] | other.data[i];
            }
            return result;
        }

        // XOR operation on two matrices
        BitMatrix<N, M> operator^(const BitMatrix<N, M>& other) const {
            BitMatrix<N, M> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] ^ other.data[i];
            }
            return result;
        }

        // AND operation on two matrices
        BitMatrix<N, M> operator&(const BitMatrix<N, M>& other) const {
            BitMatrix<N, M> result;
            for (size_t i = 0; i < N; ++i) {
                result.data[i] = data[i] & other.data[i];
            }
            return result;
        }

	private:
		std::array<std::bitset<M>, N> data;
	};
}

int main85() {
	// a) I think I will go with an std::array<std::bitset<M>, N>.
	// M and N are template argument, so we should prefer fixed representation like array and bitset combination
	// or raw bitset instead of vector or dynamic_bitset.
	// As for between std::array<std::bitset<M>, N> and std::bitset<N * M>. I will go with std::array<std::bitset<M>, N>
	// because using array to iterate is just more convenient. If we using bitset<N*M>, then all bit is organized linearly
	// meaning that each bit has to be accessed with i * M + j indexing, which is slightly unintuitive. Furthermore,
    // some upcoming operations in the 

	// b) Constructors need to be created. Use the same defaults as with std::bitset<M>.
	BitMatrix<2, 3> matrix1;  // Default constructor
	BitMatrix<2, 3> matrix2(0b110, 0b011);  // Constructor with bitset literals

    // c) Implement the following for all rows in the matrix and for a given row in the matrix:
    // * Set / reset all bits.
    // * Flip the bits.
    // * Test if none, all or any bits are set.
    // * Access the elements.
    // * Count the number of set bits.
    BitMatrix<3, 4> matrix(0b1100, 0b0110, 0b1010);

    // Set/reset all bits in all rows
    matrix.set();
    std::cout << "Matrix after set():\n";
    matrix.print();

    matrix.reset();
    std::cout << "Matrix after reset():\n";
    matrix.print();

    // Set/reset all bits in a specific row
    matrix.set(1);
    std::cout << "Matrix after set(1):\n";
    matrix.print();

    matrix.reset(1);
    std::cout << "Matrix after reset(1):\n";
    matrix.print();

    // Flip all bits in all rows
    matrix.flip();
    std::cout << "Matrix after flip():\n";
    matrix.print();

    // Flip all bits in a specific row
    matrix.flip(2);
    std::cout << "Matrix after flip(2):\n";
    matrix.print();

    // Test if none, all, or any bits are set in all rows
    bool noneAllRows = matrix.none();
    bool allAllRows = matrix.all();
    bool anyAllRows = matrix.any();
    std::cout << "none(): " << noneAllRows << '\n';
    std::cout << "all(): " << allAllRows << '\n';
    std::cout << "any(): " << anyAllRows << '\n';
    std::cout << '\n';

    // Test if none, all, or any bits are set in a specific row
    bool noneRow2 = matrix.none(2);
    bool allRow1 = matrix.all(1);
    bool anyRow0 = matrix.any(0);
    std::cout << "none(2): " << noneRow2 << '\n';
    std::cout << "all(1): " << allRow1 << '\n';
    std::cout << "any(0): " << anyRow0 << '\n';
    std::cout << '\n';

    // Count the number of set bits in all rows
    size_t countAllRows = matrix.count();
    std::cout << "count(): " << countAllRows << '\n';
    std::cout << '\n';

    // d) Create member functions for OR, XORand AND Boolean operations on bit matrices.
    BitMatrix<3, 4> matrix3(0b1100, 0b0110, 0b1010);
    BitMatrix<3, 4> matrix4(0b1010, 0b0101, 0b1100);

    // OR operation
    BitMatrix<3, 4> resultOR = matrix3 | matrix4;
    std::cout << "OR Result:\n";
    resultOR.print();

    // XOR operation
    BitMatrix<3, 4> resultXOR = matrix3 ^ matrix4;
    std::cout << "XOR Result:\n";
    resultXOR.print();

    // AND operation
    BitMatrix<3, 4> resultAND = matrix3 & matrix4;
    std::cout << "AND Result:\n";
    resultAND.print();
	return 0;
}