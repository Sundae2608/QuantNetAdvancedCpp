/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 8: Classifying Algorithms
*/

#include <algorithm>
#include <iostream>
#include <stack>

namespace {

    class CustomStack {
    public:
        void push(int value) { data_.push(value); }

        int pop() {
            int topValue = data_.top();
            data_.pop();
            return topValue;
        }

        void max() {
            if (data_.size() >= 2) {
                int first = data_.top();
                data_.pop();
                int second = data_.top();
                data_.pop();
                data_.push(std::max(first, second));
                data_.push(std::min(first, second));
                data_.push(first);
            }
        }

        void min() {
            if (data_.size() >= 2) {
                int first = data_.top();
                data_.pop();
                int second = data_.top();
                data_.pop();
                data_.push(std::min(first, second));
                data_.push(std::max(first, second));
                data_.push(first);
            }
        }

        void over() {
            if (data_.size() >= 2) {
                int topValue = data_.top();
                data_.pop();
                int secondValue = data_.top();
                data_.push(topValue);
                data_.push(secondValue);
                data_.push(topValue);
            }
        }

        void rot() {
            if (data_.size() >= 3) {
                int topValue = data_.top();
                data_.pop();
                int secondValue = data_.top();
                data_.pop();
                int thirdValue = data_.top();
                data_.pop();
                data_.push(secondValue);
                data_.push(topValue);
                data_.push(thirdValue);
            }
        }

        void swap() {
            if (data_.size() >= 2) {
                int first = data_.top();
                data_.pop();
                int second = data_.top();
                data_.pop();
                data_.push(first);
                data_.push(second);
            }
        }

        void drop() {
            if (!data_.empty()) {
                data_.pop();
            }
        }

    private:
        std::stack<int> data_;
    };
} // namespace

int main28() {
    // Consider a stack ADT (Last-In-First-Out) and a selection of its operations:
    // max(), min() : leaves on the stack the larger and lesser of the two top
    // values, respectively. over() : duplicates the second stack value on top of
    // the stack. rot() : rotate the stack's third data value to the top of the
    // stack. swap() : interchange the top two values on the stack. drop() :
    // discard the value on the top of the stack.

    // The naming of these algorithms is a little strange since they don't match
    // the conventional meaning of these methods. However, if we strictly consider
    // the actual meanings of the operations, then the classification of each
    // algorithm would be the following
    //
    // max(), min(), over(), rotate(), swap() : Modifying
    // drop() : Removing

    // Implementation
    CustomStack stack;
    stack.push(5);
    stack.push(8);

    stack.max(); // Larger of 5 and 8 (8) becomes the top element
    stack.min(); // Lesser of 5 and 8 (5) becomes the top element

    stack.push(3);
    stack
        .over(); // Duplicates the second element (3), so stack becomes 5, 3, 8, 3

    stack.push(2);
    stack.rot(); // Rotates the third value (8) to the top, so stack becomes 8, 5,
    // 3, 2

    stack
        .swap(); // Interchanges the top two elements, so stack becomes 5, 8, 3, 2

    stack.drop(); // Removes the top element, so stack becomes 8, 3, 2
    return 0;
}