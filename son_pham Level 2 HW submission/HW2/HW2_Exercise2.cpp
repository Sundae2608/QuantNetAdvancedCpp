/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 2, Exercise 2: Arrays Categories
*/

#include <iostream>
#include <type_traits>
#include <vector>

int main22() {
    // a) Test std::is_array() on a range of fundamental, scalar, object, arithmetic and compound types.
    std::cout << std::boolalpha;

    // Fundamental types
    std::cout << "int: " << std::is_array<int>::value << std::endl;
    std::cout << "char: " << std::is_array<char>::value << std::endl;
    std::cout << "bool: " << std::is_array<bool>::value << std::endl;

    // Scalar types
    std::cout << "float: " << std::is_array<float>::value << std::endl;
    std::cout << "double: " << std::is_array<double>::value << std::endl;

    // Object types
    std::cout << "std::string: " << std::is_array<std::string>::value << std::endl;
    std::cout << "std::vector<int>: " << std::is_array<std::vector<int>>::value << std::endl;

    // Arithmetic types
    std::cout << "int*: " << std::is_array<int*>::value << std::endl;
    std::cout << "float&: " << std::is_array<float&>::value << std::endl;

    // Compound types
    std::cout << "int[5]: " << std::is_array<int[5]>::value << std::endl;
    std::cout << "float[][3]: " << std::is_array<float[][3]>::value << std::endl;
    std::cout << std::endl;
    
    // b) Create an array int [][3][4][5]. Find its rank and extent.
    using ArrayType = int[][3][4][5];

    std::cout << "Rank: " << std::rank<ArrayType>::value << std::endl;
    std::cout << "Extent of dimension 0: " << std::extent<ArrayType, 0>::value << std::endl;
    std::cout << "Extent of dimension 1: " << std::extent<ArrayType, 1>::value << std::endl;
    std::cout << "Extent of dimension 2: " << std::extent<ArrayType, 2>::value << std::endl;
    std::cout << "Extent of dimension 3: " << std::extent<ArrayType, 3>::value << std::endl;
    std::cout << std::endl;

    // c) Call std::remove_extent() and std::remove_all_extent() on the array in question b).
    // What is happening?
    std::cout << "std::remove_extent result: ";
    using RemoveExtentType = std::remove_extent<ArrayType>::type;
    std::cout << "Rank after remove_extent: " << std::rank<RemoveExtentType>::value << std::endl;  // 3
    std::cout << "Extent of dimension 0: " << std::extent<RemoveExtentType, 0>::value << std::endl;  // 3
    std::cout << "Extent of dimension 1: " << std::extent<RemoveExtentType, 1>::value << std::endl;  // 4
    std::cout << "Extent of dimension 2: " << std::extent<RemoveExtentType, 2>::value << std::endl;  // 5
    // This function seems to remove the first extent in the type.

    std::cout << "std::remove_all_extent result: ";
    using RemoveAllExtentType = std::remove_all_extents<ArrayType>::type;
    std::cout << std::rank<RemoveAllExtentType>::value << std::endl;
    std::cout << "Rank after remove_all_extents: " << std::rank<RemoveAllExtentType>::value << std::endl;
    // This function seems to remove the all extents in the type.
    return 0;
}