/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 3, Exercise 1: Random Number Generators and Distributions
*/

#include <iostream>
#include <random>

template <typename Engine, typename Distribution>
void generateRandomNumbers(Engine&& engine, Distribution&& distribution,
    int nTrials) {
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << distribution(engine) << ", ";
    }
    std::cout << "end\n\n";
}

int main31() {
    // a) Copy and adapt this code by using the engine
    // std::linear_congruential_engine and the engine adapter with predefined
    // parameters std::mt19937 and std::mt19937_64.
    int nTrials = 30;

    // std::linear_congruential_engine with predefined parameters
    std::linear_congruential_engine<unsigned long long, 16807, 0, 2147483647>
        lce_eng;

    // Produce uniform variates using std::linear_congruential_engine
    std::uniform_real_distribution<double> lce_dist(0.0, 1.0);
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << lce_dist(lce_eng) << ", ";
    }
    std::cout << "end\n\n";

    // std::mt19937 engine
    std::mt19937 mt_eng;

    // Produce uniform variates using std::mt19937 engine
    std::uniform_real_distribution<double> mt_dist(0.0, 1.0);
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << mt_dist(mt_eng) << ", ";
    }
    std::cout << "end\n\n";

    // std::mt19937_64 engine
    std::mt19937_64 mt64_eng;

    // Produce uniform variates using std::mt19937_64 engine
    std::uniform_real_distribution<double> mt64_dist(0.0, 1.0);
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << mt64_dist(mt64_eng) << ", ";
    }
    std::cout << "end\n\n";

    // b) Adapt the code in a) so that it works with the following distributions:
    // Normal, chi-squared, Bernoulli and Cauchy. Normal distribution with mean 0
    // and standard deviation 1
    std::normal_distribution<double> normal_dist(0.0, 1.0);
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << normal_dist(mt_eng) << ", ";
    }
    std::cout << "end\n\n";

    // Chi-squared distribution with 5 degrees of freedom
    std::chi_squared_distribution<double> chi_squared_dist(5);
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << chi_squared_dist(mt_eng) << ", ";
    }
    std::cout << "end\n\n";

    // Bernoulli distribution with probability of success 0.3
    std::bernoulli_distribution bernoulli_dist(0.3);
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << bernoulli_dist(mt_eng) << ", ";
    }
    std::cout << "end\n\n";

    // Cauchy distribution with location 0 and scale 1
    std::cauchy_distribution<double> cauchy_dist(0.0, 1.0);
    for (int i = 1; i <= nTrials; ++i) {
        std::cout << cauchy_dist(mt_eng) << ", ";
    }
    std::cout << "end\n\n";

    // c) Write a generic function to generate a list of random numbers for a
    // generic engine and a generic distribution. Test the examples from parts a)
    // and b) on this new function.
    generateRandomNumbers(mt_eng, lce_dist, nTrials);
    generateRandomNumbers(mt_eng, mt_dist, nTrials);
    generateRandomNumbers(mt_eng, mt64_dist, nTrials);
    generateRandomNumbers(mt_eng, normal_dist, nTrials);
    generateRandomNumbers(mt_eng, chi_squared_dist, nTrials);
    generateRandomNumbers(mt_eng, bernoulli_dist, nTrials);
    generateRandomNumbers(mt_eng, cauchy_dist, nTrials);

    generateRandomNumbers(mt64_eng, lce_dist, nTrials);
    generateRandomNumbers(mt64_eng, mt_dist, nTrials);
    generateRandomNumbers(mt64_eng, mt64_dist, nTrials);
    generateRandomNumbers(mt64_eng, normal_dist, nTrials);
    generateRandomNumbers(mt64_eng, chi_squared_dist, nTrials);
    generateRandomNumbers(mt64_eng, bernoulli_dist, nTrials);
    generateRandomNumbers(mt64_eng, cauchy_dist, nTrials);
    return 0;
}