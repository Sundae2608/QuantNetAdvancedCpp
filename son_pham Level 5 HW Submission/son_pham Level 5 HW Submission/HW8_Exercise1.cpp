/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 8, Exercise 1
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

namespace {
    template <typename Container>
    void printContainer(const std::string& description,
        const Container& container) {
        std::cout << description << ": ";
        for (const auto& item : container) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
} // namespace

int main81() {

    // a) Create a vector with the following elements:
    // C++:
    // vector<int> vec2{ 3,4,5,6,7,5,6,7,8,9,1,2,3,4 };
    std::vector<int> vec2{ 3, 4, 5, 6, 7, 5, 6,
                          7, 8, 9, 1, 2, 3, 4 }; // Will be changed
    printContainer("Exercise a - Original vector", vec2);

    // b) Call std::make_heap() on this vector and print the result. Draw the
    // corresponding binary tree by hand.
    std::make_heap(vec2.begin(), vec2.end());
    printContainer("Exercise b - After make_heap()", vec2);

    // c) Pop the root of the heap by calling pop_heap(). What are the effects of
    // calling this function (or not calling it) if the underlying container is
    // not a heap? And why do you need to call pop_back() after calling
    // pop_heap()?
    // We have to call pop_back() after calling pop_heap() to officially remove
    // the item from the array.
    // Basically, the pop_heap is really just an array organization function that
    // pushes the element to the end. But you actually need to pop it after
    // the reorganization.
    //
    // If we do this for a faulty heap, then the reorganization gets mangled
    // because it assumes that the ordering of the underlying function
    // matches what a heap would look like.
    std::pop_heap(vec2.begin(), vec2.end());
    vec2.pop_back();
    printContainer("Exercise c - After pop_heap()", vec2);

    // Pop a faulty heap
    std::vector<int> faulty_heap{ 3, 4, 5, 6, 7, 5, 6, 7, 8, 9, 1, 2, 3, 4 };
    printContainer("Exercise c - Faulty heap", faulty_heap);
    std::pop_heap(faulty_heap.begin(), faulty_heap.end());
    faulty_heap.pop_back();
    printContainer("Exercise c - After pop_heap() a faulty heap", faulty_heap);

    // d) Push a value onto the heap by calling push_heap(). What are the effects
    // of calling this function (or not calling it) if the underlying container is
    // not a heap? And why do you need to call push_back() before calling
    // push_heap()?
    // We have to call push_back() first so that the element is actually there
    // for the heap to reorganize.
    // Basically, the push_heap is really just an array organization function,
    // assuming that the element at the end has been pushed.
    //
    // If we do this for a faulty heap, then the reorganization gets mangled
    // because it assumes that the ordering of the underlying function
    // matches what a heap would look like.
    vec2.push_back(10);
    std::push_heap(vec2.begin(), vec2.end());
    printContainer("Exercise d - After push_heap()", vec2);

    // Push a faulty heap
    std::vector<int> faulty_heap2{ 3, 4, 5, 6, 7, 5, 6, 7, 8, 9, 1, 2, 3, 4 };
    printContainer("Exercise d - Faulty heap", faulty_heap2);
    faulty_heap.push_back(10);
    std::push_heap(faulty_heap2.begin(), faulty_heap2.end());
    printContainer("Exercise d - After push_heap() a faulty heap", faulty_heap2);

    // e) Sort the heap into a sorted collection.
    std::sort_heap(vec2.begin(), vec2.end());
    printContainer("Exercise e - After sort_heap()", vec2);

    // f) Find the largest element in a heap.
    int largest = vec2.front();
    std::cout << "Exercise f - Largest element: " << largest << std::endl;
    return 0;
}