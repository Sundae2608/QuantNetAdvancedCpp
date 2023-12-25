/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 1, Exercise 4: A Bitmap Class
*/

#include <iostream>
#include <bitset>
#include <array>
#include <functional>

namespace {
    //
    // Proposition copied from exercise 1
    //
    class Proposition
    {
    private:
        std::bitset<1> data;

    public:
        // a) Create the following constructors: default, bool as argument and a std::bitset<1> as argument.
        // These are the constructors required by the assignments.
        Proposition() : data(0) {}
        Proposition(bool value) : data(value) {}
        Proposition(std::bitset<1> value) : data(value) {}

        // Boolean operators as member functions
        Proposition operator==(const Proposition& other) const { return Proposition(data == other.data); }
        Proposition operator!=(const Proposition& other) const { return Proposition(data != other.data); }
        Proposition operator&(const Proposition& other) const { return Proposition(data & other.data); }
        Proposition operator|(const Proposition& other) const { return Proposition(data | other.data); }
        Proposition operator^(const Proposition& other) const { return Proposition(data ^ other.data); }
        Proposition operator!() const { return Proposition(~data); }

        // Friend functions for conditional and biconditional
        friend Proposition operator%(const Proposition& lhs, const Proposition& rhs); // Conditional
        friend Proposition operator<(const Proposition& lhs, const Proposition& rhs); // Biconditional

        // Conversion to bool
        operator bool() const { return data.test(0); }
    };

    // Conditional (->) as non-member friend function
    Proposition operator%(const Proposition& lhs, const Proposition& rhs)
    {
        return Proposition(!lhs.data.test(0) || rhs.data.test(0));
    }

    // Biconditional (<->) as non-member friend function
    Proposition operator<(const Proposition& lhs, const Proposition& rhs)
    {
        return Proposition((lhs % rhs).data.test(0) && (rhs % lhs).data.test(0));
    }

    //
    // Matrix code copied from exercise 3.
    //
    template <typename V, int NR, int NC>
    using NestedMatrix = std::array<std::array<V, NC>, NR>;

    template <typename V, int NR, int NC>
    class Matrix
    {
    private:
        NestedMatrix<V, NR, NC> mat;

    public:
        // Constructors
        Matrix() = default;
        Matrix(const V& value)
        {
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    mat[i][j] = value;
        }
        Matrix(const Matrix<V, NR, NC>& other)
        {
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    mat[i][j] = other.mat[i][j];
        }

        // Constructor with initializer list
        Matrix(std::initializer_list<std::initializer_list<V>> initList)
        {
            int i = 0;
            for (const auto& row : initList)
            {
                int j = 0;
                for (const auto& val : row)
                {
                    if (i < NR && j < NC)
                        mat[i][j] = val;
                    ++j;
                }
                ++i;
            }
        }

        // Accessing elements using ()
        V& operator()(int row, int col) { return mat[row][col]; }
        const V& operator()(int row, int col) const { return mat[row][col]; }

        // Unary minus
        Matrix operator-() const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = -mat[i][j];
            return result;
        }

        // Scalar multiplication
        template <typename F>
        Matrix operator*(const F& a) const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = a * mat[i][j];
            return result;
        }

        // Matrix addition
        Matrix operator+(const Matrix<V, NR, NC>& other) const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = mat[i][j] + other.mat[i][j];
            return result;
        }

        // Matrix subtraction
        Matrix operator-(const Matrix<V, NR, NC>& other) const
        {
            Matrix result;
            for (int i = 0; i < NR; ++i)
                for (int j = 0; j < NC; ++j)
                    result.mat[i][j] = mat[i][j] - other.mat[i][j];
            return result;
        }

        // Matrix multiplication
        template <int RC>
        Matrix<V, NR, RC> operator*(const Matrix<V, NC, RC>& other) const
        {
            Matrix<V, NR, RC> result;
            for (int i = 0; i < NR; ++i)
            {
                for (int j = 0; j < RC; ++j)
                {
                    result(i, j) = V();
                    for (int k = 0; k < NC; ++k)
                    {
                        result(i, j) += mat[i][k] * other(k, j);
                    }
                }
            }
            return result;
        }

        // Output stream operator for Matrix (defined as a member function)
        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
        {
            for (int i = 0; i < NR; ++i)
            {
                for (int j = 0; j < NC; ++j)
                    os << mat.mat[i][j] << " ";
                os << "\n";
            }
            return os;
        }
    };

	using value_type = Proposition;

	template <int NR, int NC>
	using BitMap = Matrix<value_type, NR, NC>;

	template <int NR, int NC>
	using BitMap2 = std::array<std::bitset<NC>, NR>;

    // Print function for BitMap
    template <int NR, int NC>
    void printBitMap(const BitMap<NR, NC>& bm)
    {
        for (int i = 0; i < NR; ++i)
        {
            for (int j = 0; j < NC; ++j)
                std::cout << bm(i, j) << " ";
            std::cout << "\n";
        }
    }

    // Print function for BitMap2
    template <int NR, int NC>
    void printBitMap2(const BitMap2<NR, NC>& bm)
    {
        for (int i = 0; i < NR; ++i)
            std::cout << bm[i] << "\n";
    }

    // BitFunction type definition
    using BitFunction = std::function<Proposition(const Proposition&, const Proposition&)>;

    // mask function to merge two bitmaps using a BitFunction
    template <int NR, int NC>
    BitMap<NR, NC> mask(const BitMap<NR, NC>& bm1, const BitMap<NR, NC>& bm2, const BitFunction& masker) {
        BitMap<NR, NC> result;
        for (int i = 0; i < NR; ++i) {
            for (int j = 0; j < NC; ++j) {
                result(i, j) = masker(bm1(i, j), bm2(i, j));
            }
        }
        return result;
    }
}

int main14() {
	// a) Create instances of BitMapand of BitMap2 as well as the corresponding print functions.
    // c) We can clearly see part c here as well when comparing between BitMap1 and BitMap2. Bitmap1 initialization
    // clearly has a lot of drudgery. On the other hand, BitMap2 is clearly better.
    // Example for BitMap
    BitMap<4, 4> bm;
    bm(1, 2) = true;
    bm(2, 3) = true;

    // Example for BitMap2
    BitMap2<3, 8> bm2 = {
        std::bitset<8>("10101010"),
        std::bitset<8>("10101010"),
        std::bitset<8>("11110000")
    };

    // Print the bitmaps
    std::cout << "BitMap:\n";
    printBitMap(bm);

    std::cout << "\nBitMap2:\n";
    printBitMap2(bm2);

    // Example BitMap and BitMap2 instances

    // b) We wish to superimpose two bitmaps on top of each other in some way in order to 
    // create a third bitmap. For each, we could AND the individual cells of the bitmaps. 
    const int NR = 4;
    const int NC = 4;
    BitMap<NR, NC> bitmap1(false);
    BitMap<NR, NC> bitmap2(false);
    bitmap1(0, 0) = true;
    bitmap1(0, 1) = true;
    bitmap1(0, 2) = true;
    bitmap1(0, 3) = true;
    bitmap1(1, 0) = true;

    bitmap2(2, 0) = true;
    bitmap2(2, 1) = true;
    bitmap2(2, 2) = true;
    bitmap2(2, 3) = true;
    bitmap2(3, 0) = true;

    // Define BitFunction for XOR
    auto XOR = [](const Proposition& p1, const Proposition& p2) {
        return p1 ^ p2;
    };

    // Merge the bitmaps using XOR operator
    BitMap<NR, NC> bmA = mask(bitmap1, bitmap2, XOR);

    // Print the result
    std::cout << "\nMerged BitMap:\n";
    printBitMap(bmA);

    return 0;
}