/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 3, Exercise 2: Categories of Distributions
*/

#include <iostream>
#include <map>
#include <random>
#include <string>

namespace {

    // a) Design and implement the above code to generate what is essentially a
    // histogram of values of a distribution.
    template <typename Dist, typename Eng>
    std::vector<double> GenerateRandomNumbers(Dist d, Eng eng, int nTrials) {
        std::vector<double> values;

        for (int i = 0; i < nTrials; ++i) {
            double value = d(eng);
            values.push_back(value);
        }

        return values;
    }

    void CreateHistogram(const std::vector<double>& values, const std::string& s) {
        std::map<long long, int> counter;

        // Bucketize the values and populate the counter
        for (double value : values) {
            long long bucket = static_cast<long long>(value); // Bucketizing the values
            counter[bucket]++;
        }

        std::cout << "Histogram for " << s << " distribution:" << std::endl;
        for (const auto& pair : counter) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
        std::cout << std::endl;
    }

} // namespace

int main32() {
    // b) Test the code by choosing the distributions: geometric, uniform and
    // poisson.
    int nTrials = 10000;

    // Random number engine
    std::mt19937 mt_eng;

    // Geometric distribution with success probability 0.2
    std::geometric_distribution<int> geometric_dist(0.2);
    std::vector<double> geometric_values =
        GenerateRandomNumbers(geometric_dist, mt_eng, nTrials);
    CreateHistogram(geometric_values, "Geometric");

    // Uniform distribution
    std::uniform_real_distribution<double> uniform_dist(1.0, 6.0);
    std::vector<double> uniform_values =
        GenerateRandomNumbers(uniform_dist, mt_eng, nTrials);
    CreateHistogram(uniform_values, "Uniform");

    // Poisson distribution with mean 5
    std::poisson_distribution<int> poisson_dist(5);
    std::vector<double> poisson_values =
        GenerateRandomNumbers(poisson_dist, mt_eng, nTrials);
    CreateHistogram(poisson_values, "Poisson");

    // c) The input for each distribuion is the following
    //   Histogram for Geometric distribution:
    // 0: 2071
    // 1: 1555
    // 2: 1231
    // 3: 1050
    // 4: 871
    // 5: 664
    // 6: 488
    // 7: 409
    // 8: 340
    // 9: 254
    // 10: 209
    // 11: 166
    // 12: 121
    // 13: 117
    // 14: 92
    // 15: 68
    // 16: 63
    // 17: 46
    // 18: 25
    // 19: 44
    // 20: 20
    // 21: 22
    // 22: 20
    // 23: 14
    // 24: 8
    // 25: 8
    // 26: 5
    // 27: 2
    // 28: 3
    // 29: 2
    // 30: 4
    // 31: 2
    // 32: 1
    // 33: 1
    // 34: 1
    // 35: 1
    // 39: 1
    // 43: 1

    // Histogram for Uniform distribution:
    // 1: 2071
    // 2: 1955
    // 3: 1991
    // 4: 2013
    // 5: 1970

    //   Histogram for Poisson distribution:
    // 0: 74
    // 1: 348
    // 2: 823
    // 3: 1434
    // 4: 1764
    // 5: 1733
    // 6: 1488
    // 7: 1007
    // 8: 674
    // 9: 346
    // 10: 176
    // 11: 76
    // 12: 31
    // 13: 13
    // 14: 8
    // 15: 3
    // 16: 1
    // 17: 1

    // They all look accurate
    return 0;
}