/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 2, Exercise 3: Conversions
*/

#include <iostream>
#include <type_traits>
#include <vector>

namespace {
    // Functions mapping integer to unsigned integers and vice versa
    int UnsignedIntToInt(unsigned int value) {
        return value;
    }

    unsigned int IntToUnsignedInt(int value) {
        return value;
    }

    // Functions that add const and then remove const
    template <typename T>
    struct AddConst {
        using Type = const T;
    };
    template <typename T>
    using AddConstT = typename AddConst<T>::Type;

    template <typename T>
    struct RemoveConst {
        using Type = std::remove_const_t<T>;
    };
    template <typename T>
    using RemoveConstT = typename RemoveConst<T>::Type;

    // Function template to add a pointer to a type, and remove pointer from a type
    template <typename T>
    T* AddPointer(T& value) {
        return &value;
    }
    template <typename T>
    T& RemovePointer(T* pointer) {
        return *pointer;
    }

    // Function template to add volatile to a type
    template <typename T>
    std::add_volatile_t<T> AddVolatile(const T& value) {
        return value;
    }

    // Function template to remove volatile from a type
    template <typename T>
    std::remove_volatile_t<T> RemoveVolatile(const T& value) {
        return value;
    }

    // Point class template that is defined by user
    template <typename T>
    struct Point {
        T x, y;

        Point(T x, T y) : x(x), y(y) {}
    };
}


int main23() {
    // 1) Mapping integer to unsigned integers and vice versa
    unsigned int u_integer = IntToUnsignedInt(-42);
    std::cout << "Convert -42 to unsgined int: " << u_integer << std::endl;  // Output: 4294967254

    int integer = UnsignedIntToInt(4294967254);
    std::cout << "Convert 4294967254 to unsgined int: " << integer << std::endl;  // Output: 42

    // 2) Add / remove the const specifier to or from a type
    // Adding const to the type
    using ConstInt = AddConstT<int>;
    ConstInt x = 42;
    const ConstInt& const_ref = x;
    // const_ref = 24;  This has compilation error because you cannot change const.

    // Remove const from a type
    using NonConstInt = RemoveConstT<ConstInt>;
    NonConstInt& non_const_ref = const_cast<NonConstInt&>(const_ref);
    non_const_ref = 24;
    std::cout << "New const_ref value" << const_ref << std::endl; // This prints 24 because x has changed.

    // 3) Add / remove the const specifier to or from a type
    // Adding a pointer to the int type
    int value = 42;
    int* pointer = AddPointer(value);
    std::cout << "Pointer value: " << *pointer << std::endl;  // Output: 42

    // Removing the pointer from the int* type
    int& reference = RemovePointer(pointer);
    reference = 24;
    std::cout << "Modified value: " << value << std::endl;  // Output: 24

    // 4) Add/remove the volatile specifier to or from a type.
    // Adding volatile to the int type
    volatile int volatile_var = AddVolatile(x);

    // Removing volatile from the volatile int type
    int non_volatile_var = RemoveVolatile(volatile_var);

    // Discuss the difference between direct list initialisation and copy list initialisation 
    // in C++17/20 compared to C++11. In which case does auto deduction reduce to std::initializer_list?
    // Give a code example. Under which circumstances can we get ill-formed expressions?

    // Direct list initialization
    // * In C++11: Direct list initialization initializes an object using a braced-init-list 
    //   (enclosed in curly braces) directly. It considers constructors that accept the 
    //   braced-init-list or compatible arguments for initialization.
    // * In C++17 / 20: Direct list initialization remains the same as in C++11. It initializes 
    //   an object directly using a braced - init - list.
    // Example code below:
    std::vector<int> vector{ 1, 2, 3 };

    // Copy list initialization
    // * In C++11: Copy list initialization considers constructors that can be invoked with a 
    //   single argumentfrom the brace - init - list.
    // * In C++17 / 20: Copy list initialization has a change in behavior. It is now equivalent to
    //   direct list initialization unless the target type is auto deduced or specifically
    //   std::initializer_list<T>.
    //
    //   In such cases, it constructs an std::initializer_list<T> object with the elements from the
    //   braced - init - list.
    std::vector<int> values1 = { 1, 2, 3 };  // Copy list initialization in C++11, this is *not* an initializer_list
    auto values2 = { 1, 2, 3 };              // Auto deduced to initializer list in C++ 17/20
    if (std::is_same<decltype(values1), std::initializer_list<int>>::value) {
        std::cout << "Type is std::initializer_list<int>" << std::endl;
    }
    else {
        std::cout << "Type is not std::initializer_list<int>" << std::endl;
    }
    if (std::is_same<decltype(values2), std::initializer_list<int>>::value) {
        std::cout << "Type is std::initializer_list<int>" << std::endl;
    }
    else {
        std::cout << "Type is not std::initializer_list<int>" << std::endl;
    }

    // Ill-formed Expressions:
    // * In C++11, if a constructor that accepts std::initializer_list and a compatible constructor
    //   both exist, direct list initialization would be ambiguous.
    // * In C++17/20, it will default to initializer list.
    struct Foo {
        Foo(std::initializer_list<int>) {
            std::cout << "Used the constructor with initializer list" << std::endl;
        }
        Foo(int) {
            std::cout << "Used the constructor with int" << std::endl;
        }
    };

    Foo foo{ 42 };  // Used the constructor with initializer list in C++17, ambiguous in C++11

    // Discuss how Class Template Argument Deduction (CTAD)) reduces code verbosity. Give a
    // non-trivial example using std::tuple and a user-defined class.
    // Class Template Argument Deduction(CTAD) is a feature introduced in C++17 that allows
    // the deduction of template arguments for class templates.It reduces code verbosity by
    // automatically deducing template arguments based on constructor arguments, eliminating
    // the need to explicitly specify the template arguments.

    // Explicit argument type specification
    std::tuple<int, float> t1(42, 3.14);
    // CTAD
    auto t2 = std::make_tuple(42, 3.14);

    // Creating a point using explicit template argument
    Point<double> p1(2.5, 3.5);
    // CTAD
    auto p2 = Point(2.5, 3.5);

    // Investigate the applicability of decltype and std::is_same when comparing the type of a
    // result with a “target” type.
    // Decltype is used to get the exact type, while is_same deduced whether they are the same typed.
    // When combined with each other, you can compare the type of a result to the target type. We
    // demonstrated this when we test the type of copy list initialization.
    return 0;
}