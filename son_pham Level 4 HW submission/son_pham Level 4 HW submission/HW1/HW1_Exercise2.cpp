/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 1, Exercise 2: Adapter Classes for Bitsets
*/

#include <algorithm>
#include <functional>
#include <iostream>

namespace {
    // Vector class of fized size N and can hold any template type T
    template<typename T, int N>
    class Vector
    {
    private:
        T arr[N];

    public:
        // Constructors
        Vector() = default;

        // Same value constructor
        Vector(const T& value)
        {
            for (int i = 0; i < N; ++i)
                arr[i] = value;
        }

        // Copy constructor
        Vector(const Vector<T, N>& other)
        {
            for (int i = 0; i < N; ++i)
                arr[i] = other.arr[i];
        }

        // Initializer list constructor
        Vector(std::initializer_list<T> initList)
        {
            if (initList.size() != N)
            {
                std::cerr << "Error: Invalid initializer list size for Vector<" << N << ">.\n";
                return;
            }
            std::copy(initList.begin(), initList.end(), arr);
        }

        // Accessing elements using []
        T& operator[](int index) { return arr[index]; }
        const T& operator[](int index) const { return arr[index]; }

        // Unary minus
        Vector operator-() const
        {
            Vector result;
            for (int i = 0; i < N; ++i)
                result.arr[i] = -arr[i];
            return result;
        }

        // Member function to modify elements of the vector
        void modify(const std::function<T(T&)>& f)
        {
            std::transform(arr, arr + N, arr, f);
        }
    };

    // Output stream operator for Vector
    template<typename T, int N>
    std::ostream& operator<<(std::ostream& os, const Vector<T, N>& vec)
    {
        os << "[ ";
        for (int i = 0; i < N; ++i)
        {
            os << vec[i];
            if (i < N - 1)
                os << ", ";
        }
        os << " ]";
        return os;
    }

    // Addition
    template<typename T, int N>
    Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (int i = 0; i < N; ++i)
            result[i] = lhs[i] + rhs[i];
        return result;
    }

    // Subtraction
    template<typename T, int N>
    Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs)
    {
        Vector<T, N> result;
        for (int i = 0; i < N; ++i)
            result[i] = lhs[i] - rhs[i];
        return result;
    }

    // Scalar multiplication
    template<typename T, int N, typename F>
    Vector<T, N> operator*(const F& a, const Vector<T, N>& vec)
    {
        Vector<T, N> result;
        for (int i = 0; i < N; ++i)
            result[i] = a * vec[i];
        return result;
    }
}

int main12() {
	// a) Given the above operations to be implemented you need to choose a suitable data structure ADT to hold the data, for example:
	// For the data structure ADT to hold the data of the vector, we can use a simple C-style array Type arr[N];. 
	// Since the vector has a fixed size N, using a fixed-size array is a suitable and efficient choice. 
	// This allows us to access elements using [] and perform various vector operations efficiently.
	//
	// std::vector is okay, but we don't really the extra overhead of creating the vector, and all the push and pop functionalities
	// as the ADT is already fixed sized.

	// b) Create some instances of Vector and print them.
    Vector<int, 3> vec1(1);
    Vector<double, 4> vec2(2.5);
    Vector<char, 5> vec3('A');

    std::cout << "vec1: " << vec1 << std::endl;
    std::cout << "vec2: " << vec2 << std::endl;
    std::cout << "vec3: " << vec3 << std::endl;

    // c) Implement the above operation pertaining to the properties of a vector space as explained in the introduction.
    // The operations include: 
    // - Adding and subtraction; unary minus.
    // - Premultiplication by a scalar quantity.
    Vector<int, 3> v1 = { 1, 2, 3 };
    Vector<int, 3> v2 = { 4, 5, 6 };
    Vector<int, 3> v3 = { 2, 2, 2 };

    Vector<int, 3> sum = v1 + v2;
    Vector<int, 3> diff = v1 - v2;
    Vector<int, 3> scaled = 2 * v3;

    std::cout << "v1 + v2: " << sum << std::endl;
    std::cout << "v1 - v2: " << diff << std::endl;
    std::cout << "2 * v3: " << scaled << std::endl;

    // d) Implement the scalar multiplication operation as a template member function having an extra template parameter.
    Vector<double, 4> vec = { 1.5, 2.5, 3.5, 4.5 };
    Vector<double, 4> scaledDouble = 1.5 * vec;

    std::cout << "1.5 * vec: " << scaledDouble << std::endl;

    // e) Create a member function that modifies all the elements of a vector using std::function <T (const T&)>. 
    // Internally, the member function should call std::transform or use the internal array directly. 
    // Be careful: data is on the stack and not on the heap. The signature of the function is:
    // void modify(const std::function<Type (Type&)>& f);

    // Example for part e (using modify to scale and offset the vector)
    Vector<double, 4> v = { 1, 2, 3, 4 };
    v.modify([](double& x) { return x * 2; }); // Scale the vector by 2
    std::cout << "Scaled by 2 vector: " << v << std::endl;

    v.modify([](double& x) { return x + 3; }); // Offset the vector by 3
    std::cout << "Offset by 3 vector: " << v << std::endl;

    v.modify([](double& x) { return x / 4; }); // Divide the vector by 4
    std::cout << "Divided by 4 vector: " << v << std::endl;
    return 0;
}