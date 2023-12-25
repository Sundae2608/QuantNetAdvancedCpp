/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 3, Exercise 2: C++14: Using init Captures to move Objects into Closures
*/

#include <array>
#include <functional>
#include <iostream>
#include <vector>

int main32() {
    int size = 4;
    double val = 2.71;
    std::vector<double> data(size, val);

    // a) Move capture mode
    // Modify this code using move semantics, 
    // that is the vector data is moved into the lambda function.
    // Test the new code, including the values in data after the code has run.
    std::cout << "Part a) " << std::endl;
    auto fun = [data = std::move(data)]() mutable {
        for (std::size_t i = 0; i < data.size(); ++i) {
            data[i] = 3.14;
            std::cout << data[i] << ", ";
        }
        std::cout << '\n';
    };
    fun();

    // 'data' has been moved and is now empty
    std::cout << "Size of data after move: " << data.size() << std::endl;

    // b) Create the following code snippet
    std::cout << std::endl;
    std::cout << "Part b) " << std::endl;
    int x = 1'000'000; // This is a digit separator
    auto fun4 = [&r = x]()
    {
        r *= 2;
        std::cout << "r: " << r << std::endl;
    };
    fun4();

    // c) Migrate the following C++11 code that uses std::bind to emulate C++14 code that uses init capture:
    // I am not qure sure what I have to do here since the fun3 already uses std::bind. Is it considered migrated?
    // Though it is clear that this implementation is way more cumbersome than part a)
    std::cout << std::endl;
    std::cout << "Part c) " << std::endl;
    int size2 = 3; double val2 = 1.41;
    std::vector<double> data2(size2, val2);
    std::array<double, 3> data3 = { 1.2, 2.4, 4.7 };
    auto fun3 = std::bind( [] (std::vector<double>& array,
        std::array<double, 3> array2)
        {
            for (std::size_t i = 0; i < array.size(); ++i)
            {
                array[i] = 3.14; std::cout <<array[i]<<", ";
            }
            std::cout << '\n';
            for (std::size_t i = 0; i < array2.size(); ++i)
            {
                array2[i] = 2.71; std::cout <<array2[i]<<", ";
            }

        }, std::move(data2), std::move(data3));

    fun3();

    if (0 == data2.size() || 0 == data3.size())
    {
        std::cout <<"\nDouble arrays have no elements, OK\n";
    }
    else
    {
        std::cout <<"\n Ouch!\n";
        for (std::size_t i=0;i<data2.size(); ++i)
        {
            std::cout<<data2[i]<<"^"; 
        }
        for (std::size_t i = 0; i < data3.size(); ++i)
        {
            std::cout<<data3[i]<<"^";
        }
    }
    return 0;
}