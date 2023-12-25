/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 3, Exercise 1: User-defined deprecated Entities
*/

#include <iostream>
#include <iostream>

// Deprecated free/global function
[[deprecated("This function is deprecated")]]
void DeprecatedFunc() {
    std::cout << "This function is deprecated." << std::endl;
}

void NormalFunc() {
    std::cout << "This function is not deprecated." << std::endl;
}

// Non-deprecated class with deprecated member function
class NormalClass {
public:
    [[deprecated("This member function is deprecated")]]
    void DeprecatedMemberFunc() {
        std::cout << "This member function is deprecated." << std::endl;
    }

    void NormalFunc() {
        std::cout << "This member function is not deprecated." << std::endl;
    }
};

// Deprecated class
class [[deprecated("This member function is deprecated")]] DeprecatedClass {
};

// Deprecated global variable
[[deprecated("This global variable is deprecated")]]
int DeprecatedGlobalVar = 42;

// Deprecated enum
enum [[deprecated("This enum is deprecated")]] DeprecatedEnum {
    VALUE1,
    VALUE2
};

// Deprecated enum class
enum class [[deprecated("This enum class is deprecated")]] DeprecatedEnumClass {
    VALUE1,
    VALUE2
};

template <typename T>
class TemplateClass {};

template <>
class [[deprecated("This template specialization is deprecated")]] TemplateClass<int> {};

int main31() {
    // Call the deprecated and non-deprecated entities
    DeprecatedFunc();  // Compiler warning about deprecated function
    NormalFunc();

    // Deprecated class
    DeprecatedClass depre_obj;  // Compiler warning about deprecated class

    // Normal class with deprecated functions
    NormalClass obj;
    obj.DeprecatedMemberFunc();  // Compiler warning about deprecated member function
    obj.NormalFunc();

    // Deprecated global variable
    std::cout << DeprecatedGlobalVar << std::endl;  // Compiler warning about deprecated variable

    // Deprecated enum
    DeprecatedEnum enum_var = VALUE1; // Compiler warning about deprecated enum

    // Deprecated enum class
    DeprecatedEnumClass deprecatedEnumClassValue = DeprecatedEnumClass::VALUE2;  // Compiler warning about deprecated enum class

    // Deprecated template specialization
    TemplateClass<int> deprecatedTemplateInstance;  // Compiler warning about deprecated template specialization

    // Deprecated lambda function
    auto [[deprecated("This lambda function is deprecated")]] deprecatedLambda = []() {
        std::cout << "This lambda function is deprecated." << std::endl;
    };  // Compiler warning about deprecated lambda

    // Call the deprecated lambda function
    deprecatedLambda();  // Compiler warning about deprecated lambda
    return 0;
}