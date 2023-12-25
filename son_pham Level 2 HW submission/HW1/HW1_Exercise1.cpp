/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 1, Exercise 1: Type traits
*/

#include <iostream>
#include <type_traits>

namespace {
    // Helper function to determine if a type is a pointer
    template<typename T>
    constexpr bool is_pointer() {
        return std::is_pointer<T>::value;
    }

    // Helper function to determine if a type is a null pointer
    template<typename T>
    constexpr bool is_null_pointer() {
        return std::is_null_pointer<T>::value;
    }

    // Helper function to determine if a type is an lvalue reference
    template<typename T>
    constexpr bool is_lvalue_reference() {
        return std::is_lvalue_reference<T>::value;
    }

    // Helper function to determine if a type is an rvalue reference
    template<typename T>
    constexpr bool is_rvalue_reference() {
        return std::is_rvalue_reference<T>::value;
    }

    // Main function to determine the type of a given value. I combined
    // them together like this for convenience in testing.
    template<typename T>
    void determineType(T&& value) {
        std::cout << "This is of type: ";

        if (is_pointer<T>()) {
            std::cout << "Pointer";
        }
        else if (is_null_pointer<T>()) {
            std::cout << "Null Pointer";
        }
        else if (is_lvalue_reference<T>()) {
            std::cout << "Lvalue Reference";
        }
        else if (is_rvalue_reference<T>()) {
            std::cout << "Rvalue Reference";
        }
        else {
            std::cout << "Other";
        }

        std::cout << std::endl;
    }

    // Function to determine if a type is a member function pointer
    // or a pointer to a non-static member object.
    template <typename T>
    void determineMemberType(T) {
        std::cout << "This is of type: ";
        if (std::is_member_function_pointer<T>::value) {
            std::cout << "Member function pointer";
        }
        else if (std::is_member_object_pointer<T>::value) {
            std::cout << "Member function object pointer";
        }
        else {
            std::cout << "Other";
        }
        std::cout << std::endl;
    }

    template <typename T>
    void determinePointerType(const T& t) {
        if (std::is_pointer<T>::value)
        {
            std::cout << "This is a pointer type argument\n";
        }
        else
        {
            std::cout << "_not_ a pointer type argument\n";
        }
    }

}

int main11() {
    // a) Write a function to determine if a type is a pointer, null pointer, lvalue reference
    // or rvalue reference.
    int x = 42;
    int* ptr = &x;
    int& ref = x;
    int&& rref = 10;

    determineType(ptr);     // Type: Pointer
    determineType(nullptr); // Type: Null Pointer
    determineType(ref);     // Type: Lvalue Reference
    determineType(rref);    // Type: Rvalue Reference

    // b) Determine if a type is a member function pointer or if it is a pointer to 
    // a non-static member object.
    class MyClass {
    public:
        int memberObject;
        void memberFunction() {}
    };

    determineMemberType(&MyClass::memberFunction); // Member function type
    determineMemberType(&MyClass::memberObject);   // Member object type

    // c) Is a shared pointer a pointer type ? Is it a pointer type when 
    // converted to a raw pointer ?
    std::shared_ptr<MyClass> shared_ptr;
    determinePointerType(shared_ptr);        // Not a pointer type
    determinePointerType(shared_ptr.get());  // Is a pointer type
    return 0;
}