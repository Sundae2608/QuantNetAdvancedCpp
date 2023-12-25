/*
Name: Son Pham
QuantNet / Baruch College Advanced C++
Level 5, Exercise 3: Application II, Tuples as Return Types of Functions
Compiled in C++ 20
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <unordered_map>
#include <vector>

// Return the following statistics in the vector:
// Mean
// Mean deviation
// Range,
// Standard deviation
// Variance
template <typename T>
std::tuple<T, T, T, T, T> CalculateStatistics(const std::vector<T>& vector) {
    T sum = std::accumulate(vector.begin(), vector.end(), T{});  // T{} is the default value of T.
    T mean = sum / vector.size();
    T mean_deviation = T{};
    std::for_each(vector.begin(), vector.end(), [mean, &mean_deviation](const T& t) {
        mean_deviation += std::abs(t - mean);
    });
    mean_deviation /= vector.size();
    T min_so_far = vector.at(0);
    T max_so_far = vector.at(0);
    std::for_each(vector.begin(), vector.end(), [&min_so_far, &max_so_far](const T& t) {
        if (t < min_so_far) {
            min_so_far = t;
        }
        if (t > max_so_far) {
            max_so_far = t;
        }
    });
    T range = max_so_far - min_so_far;
    T std_deviation = T{};
    std::for_each(vector.begin(), vector.end(), [mean, &std_deviation](const T& t) {
        std_deviation += (t - mean) * (t - mean);
        });
    std_deviation = std::sqrt(std_deviation / (vector.size() - 1));
    
    T variance = T{};
    std::for_each(vector.begin(), vector.end(), [mean, &variance](const T& t) {
        variance += (t - mean) * (t - mean);
        });
    variance /= vector.size();
    return {mean, mean_deviation, range, std_deviation, variance};
}

// Return a median and mode of the sorted vector
template <typename T>
std::tuple<T, T> CalculateMedianAndMode(const std::vector<T>& sorted_vector) {
    // Calculate median
    T median;
    if (sorted_vector.size() % 2 == 1) {
        median = sorted_vector.at(sorted_vector.size() / 2);
    }
    else {
        median = (sorted_vector.at(sorted_vector.size() / 2 - 1) + sorted_vector.at(sorted_vector.size() / 2)) / 2;
    }

    // Calculate mode
    T mode;
    int max_count = 0;
    std::unordered_map<T, int> count_dict;
    std::for_each(sorted_vector.begin(), sorted_vector.end(), [&](const T& t) {
        if (auto it = count_dict.find(t); it != count_dict.end()) {
            it->second++;
        }
        else {
            count_dict[t] = 1;
        }
        
        // Check the max
        auto it = count_dict.find(t);
        if (it->second > max_count) {
            max_count = it->second;
            mode = it->first;
        }
    });
    return { median, mode };
}

// Print vector
template <typename T>
void PrintVector(const std::vector<T>& vector) {
    std::for_each(vector.begin(), vector.end(), [](const T& t) {
        std::cout << t << ", ";
    });
    std::cout << std::endl;
}

int main53() {

    // 3ab. Create a function that calculate statistical properties: mean, mean deviation,
    // range, standard deviation and variance, and then test the function from part a.
    std::vector<double> vector{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    std::cout << "3ab. Vector content: "; 
    PrintVector(vector);

    auto [mean, mean_deviation, range, std_deviation, variance] = CalculateStatistics(vector);
    std::cout << "Mean:               " << mean << std::endl;
    std::cout << "Mean deviation:     " << mean_deviation << std::endl;
    std::cout << "Range:              " << range << std::endl;
    std::cout << "Standard deviation: " << std_deviation << std::endl;
    std::cout << "Variance:           " << variance << std::endl;

    // 3c. Median and mode
    std::vector<double> vector2{ 1.0, 2.0, 3.0, 4.0, 4.0, 4.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    std::cout << std::endl << "3c. Vector content: ";
    PrintVector(vector2);
    auto [median, mode] = CalculateMedianAndMode(vector2);
    std::cout << "Median:             " << median << std::endl;
    std::cout << "Mode:               " << mode << std::endl;
    return 0;
}