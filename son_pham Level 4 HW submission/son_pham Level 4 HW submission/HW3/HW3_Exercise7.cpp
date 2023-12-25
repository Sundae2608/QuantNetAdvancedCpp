/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 3, Exercise 7: The Chi-Squared Test
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <random>
#include <vector>

namespace {
    // Function to compute the chi-squared statistic
    double computeChiSquared(const std::vector<int>& observed,
        const std::vector<double>& expected) {
        double chiSquared = 0.0;
        for (size_t i = 0; i < observed.size(); ++i) {
            chiSquared += pow(observed[i] - expected[i], 2) / expected[i];
        }
        return chiSquared;
    }

} // namespace

int main37() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    const int numRolls = 1000;
    std::vector<int> observed(6, 0);
    std::vector<double> expected(6, numRolls / 6.0);

    for (int i = 0; i < numRolls; ++i) {
        int roll = dis(gen);
        observed[roll - 1]++;
    }

    double chiSquared = computeChiSquared(observed, expected);

    // c) Now choose an integer and create uniform integers in the range .
    // Generate draws and count the number of occurrences if each integer and
    // compute the frequency. Note that the expected frequency is. Compute the
    // chi-squared statistic. k (0; k)N j (0 <=j <=k) N=k
    std::cout << "Observed frequencies: ";
    for (int count : observed) {
        std::cout << count << " ";
    }
    std::cout << "\nExpected frequencies: ";
    for (double freq : expected) {
        std::cout << freq << " ";
    }

    std::cout << "\nChi-squared statistic: " << chiSquared << std::endl;

    // c) Now choose an integer and create uniform integers in the range .
    // Generate draws and count the number of occurrences if each integer and
    // compute the frequency. Note that the expected frequency is. Compute the
    // chi-squared statistic. k (0; k)N j (0 <=j <=k) N=k
    std::random_device rd2;
    std::mt19937 gen2(rd());
    std::uniform_int_distribution<> dis2(0, 5);

    const int numDraws = 1000;
    const int numBins = 6;
    std::vector<int> observed2(numBins, 0);
    std::vector<double> expected2(numBins,
        numDraws / static_cast<double>(numBins));

    for (int i = 0; i < numDraws; ++i) {
        int value = dis2(gen2);
        observed2[value]++;
    }

    chiSquared = computeChiSquared(observed2, expected2);

    std::cout << "Observed counts: ";
    for (int count : observed2) {
        std::cout << count << " ";
    }
    std::cout << "\nExpected counts: ";
    for (double freq : expected2) {
        std::cout << freq << " ";
    }

    std::cout << "\nChi-squared statistic: " << chiSquared << std::endl;

    return 0;
}