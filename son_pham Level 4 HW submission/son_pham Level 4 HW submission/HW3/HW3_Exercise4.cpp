/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 3, Exercise 4: Computing pi = 3.14159265358979323846
*/

#include <iostream>
#include <random>

namespace {
    void approximatePi(int nTrials) {
        int insideCircle = 0; // Counter for points inside the quarter circle

        std::random_device rd;     // Random seed
        std::mt19937 mt_eng(rd()); // Mersenne Twister random engine
        std::uniform_real_distribution<double> dist(
            0.0, 1.0); // Uniform distribution in [0, 1)

        for (int i = 0; i < nTrials; ++i) {
            double x = dist(mt_eng);
            double y = dist(mt_eng);

            // Check if point (x, y) is inside the quarter circle
            if (x * x + y * y <= 1) {
                insideCircle++;
            }
        }

        double piApproximation = static_cast<double>(insideCircle) / nTrials * 4.0;
        std::cout << "nTrials: " << nTrials
            << ", Approximated pi: " << piApproximation << std::endl;
    }
} // namespace

int main34() {
    // Pi appromination using Monte-carlo
    std::vector<int> nTrialsVector = { 10,    100,     1000,     1000,
                                      10000, 1000000, 10000000, 100000000 };
    for (int n : nTrialsVector) {
        approximatePi(n);
    }

    // The results are the following
    return 0;
}