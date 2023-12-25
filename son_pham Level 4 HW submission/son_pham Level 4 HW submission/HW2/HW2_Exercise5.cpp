/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 5: Which Style to use?
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <functional>

namespace {
    struct GreaterThanThreshold {
        int threshold;
        GreaterThanThreshold(int thresh) : threshold(thresh) {}

        bool operator()(int value) const { return std::abs(value) > threshold; }
    };

} // namespace

int main25() {
    // Compare these three solutions against each other with regard to quality
    // issues such as readability, understandability and maintainability.
    // User-defined function objects: These can be more verbose as you need to
    // define a separate functor class or struct. However, they can be very clear
    // and maintainable if we give them meaningful names and follow a consistent
    // naming convention.

    // Predefined STL function objects: Using predefined function objects like
    // std::multiplies or std::less can improve code readability when the
    // intention is clear. However, their usage might not be as intuitive for
    // complex predicates or when dealing with non-standard comparisons. Also,
    // function objects are hard to combined.

    // Lambda functions: Lambdas can provide concise and localized code,
    // especially for simple predicates. They can capture variables from the
    // surrounding scope, which can make them more flexible. However, complex
    // lambdas might reduce readability if they are too compact or involve
    // multiple nested conditions.

    // b) Consider the case of transforming a vector of integers into a set of
    // integers. Only those elements whose absolute value is strictly greater than
    // a given threshold value. An example is the vector {1,2,1,4,5,5,-1} . If the
    // threshold value is 2 then the output set will be {4,5}. Implement this
    // problems using the three bespoke methods.
    std::vector<int> input = { 1, 2, 1, 4, 5, 5, -1 };
    int threshold = 2;
    std::set<int> output;

    // User-defined function object
    std::remove_copy_if(input.begin(), input.end(),
        std::inserter(output, output.begin()),
        GreaterThanThreshold(threshold));

    for (int value : output) {
        std::cout << value << " ";
    }

    // Predefined STL function object
    input = { 1, 2, 1, 4, 5, 5, -1 };
    threshold = 2;
    output = {};
    std::remove_copy_if(input.begin(), input.end(),
        std::inserter(output, output.begin()),
        std::bind2nd(std::greater<int>(), threshold));

    for (int value : output) {
        std::cout << value << " ";
    }

    // Lambda function
    input = { 1, 2, 1, 4, 5, 5, -1 };
    threshold = 2;
    output = {};
    std::remove_copy_if(
        input.begin(), input.end(), std::inserter(output, output.begin()),
        [threshold](int value) { return std::abs(value) > threshold; });

    for (int value : output) {
        std::cout << value << " ";
    }

    // c) I think this example is a little bit too simple to clearly
    // deomonstrate the value of each method. However, in my opinion, the
    // user-defined approach has the best understability. You can literally read:
    // Remove and copy to new array if the threshold greater than 2, which is very
    // English-like and very easy to understand.

    // The use of function object is a little bit unclear in this case. Notice
    // that there is no function object that allow us to convert to absolute value
    // and then bind, so this clearly shows that STL function objects are very
    // limited in functionality. Once we start chaining multiple function objects,
    // we start to defeat the readability benefit.

    // Lambda is a good compromise. It does not have the named function, but it
    // does allow the reader to see the implementation of the absolute greater
    // comparison right away The naming problem can easily be resolved with a line
    // of comment. I think Lambda is the best approach out of the 3.
    return 0;
}