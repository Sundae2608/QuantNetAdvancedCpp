/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 2, Exercise 7: Mutating Algorithms
*/

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
    void printSubset(const std::vector<int>& subset) {
        std::cout << "{ ";
        for (int value : subset) {
            std::cout << value << " ";
        }
        std::cout << "}" << std::endl;
    }

    void powerSet(const std::vector<int>& S) {
        int n = S.size();
        int powerSetSize = 1 << n;

        for (int i = 0; i < powerSetSize; ++i) {
            std::vector<int> subset;
            for (int j = 0; j < n; ++j) {
                if ((i & (1 << j)) != 0) {
                    subset.push_back(S[j]);
                }
            }
            printSubset(subset);
        }
    }
} // namespace

int main27() {
    // a) Reverse S as a modifier option and copy to a second container.
    std::vector<int> S = { 1, -1, 7, 8, 9, 10 };
    std::vector<int> reversedCopy(S.rbegin(), S.rend());

    for (int value : reversedCopy) {
        std::cout << value << " ";
    }

    // b) Rotate S so that the value 8 is the beginning of the container.
    auto it = std::find(S.begin(), S.end(), 8);
    if (it != S.end()) {
        std::rotate(S.begin(), it, S.end());
    }

    for (int value : S) {
        std::cout << value << " ";
    }

    // c) Write a function to compute the power set of S (that is, the set of all
    // subsets of S containing elements). 26 = 64
    // Not sure what the 26 = 64 is really about here. Is it 2^6 = 64, as in the
    // number of sets in the power sets?
    powerSet(S);

    // d) Move the subset {8,9,10} to the front of the container.
    std::vector<int> subset = { 8, 9, 10 };
    it = std::search(S.begin(), S.end(), subset.begin(), subset.end());
    if (it != S.end()) {
        std::rotate(S.begin(), it, subset.end());
    }

    for (int value : S) {
        std::cout << value << " ";
    }
    return 0;
}