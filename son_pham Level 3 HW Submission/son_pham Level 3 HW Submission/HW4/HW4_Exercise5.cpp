/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 4, Exercise 5: Loop-Level Parallelism with Tasks
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <future>

namespace {

    // This is the function that performs parallel accumulation. The rule is that
    // we basically split the array size until the size of array is less than 1000.
    // This function is recursive.
    int parallel_accumulate(const std::vector<int>& array, int start, int end) {
        int size = end - start;
        if (size <= 1000) {
            return std::accumulate(array.begin() + start, array.begin() + end, 0);
        }
        else {
            int mid = start + size / 2;
            auto fut = std::async(std::launch::async, parallel_accumulate, std::ref(array), start, mid);
            int sum = parallel_accumulate(array, mid, end);
            return fut.get() + sum;
        }
    }

    template <typename T>
    T openmp_accumulate(const std::vector<T>& array) {
        T sum = T(0);
        #pragma omp parallel for reduction(+:sum)
        for (long i = 0; i < array.size(); ++i) {
            sum += array[i];
        }
        return sum;
    }

    void thread_accumulate(const std::vector<int>& array, int start, int end, int& sum) {
        int size = end - start;
        if (size <= 1000) {
            sum = std::accumulate(array.begin() + start, array.begin() + end, 0);
        }
        else {
            int mid = start + size / 2;
            int leftSum, rightSum;
            std::thread leftThread(thread_accumulate, std::ref(array), start, mid, std::ref(leftSum));
            thread_accumulate(array, mid, end, rightSum);
            leftThread.join();
            sum = leftSum + rightSum;
        }
    }

}

int main45() {
    // a) Create a huge numeric array and sum its elements using std::accumulate().
    // Measure processing time.
    // 
    // Create a huge numeric array
    const int N = 200000;
    std::vector<int> array(N, 2); // Initialize all elements to 2

    // Measure processing time
    auto start = std::chrono::high_resolution_clock::now();

    // Sum the elements using std::accumulate
    int sum = std::accumulate(array.begin(), array.end(), 0);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << std::endl;
    std::cout << "a) Normal accumulate" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Time taken: " << duration << " milliseconds" << std::endl;

    // b) We create an algorithm to parallelize the code in part a). To this end,
    // we split the index space into two halves; the right half is run in an
    // asynchronous task while the left part constitutes a recursive call to the
    // algorithm for the appropriate index range. If the size of the array is less
    // than 1000 we then side-track parallel processing by calling std::accumulate()
    // directly.
    // Measure processing time
    start = std::chrono::high_resolution_clock::now();

    // Sum the elements using parallel_accumulate
    int sum2 = parallel_accumulate(array, 0, array.size());

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::endl;
    std::cout << "b) Parallel accumulate" << std::endl;
    std::cout << "Sum: " << sum2 << std::endl;
    std::cout << "Time taken: " << duration << " milliseconds" << std::endl;

    // There is no speed up. The 2nd version is actually *slower* than the first version.
    // I did not manage to get the parallel version work with the input length of more than 10M
    // Not really sure why here.
    // At N = 1 000 000, the result is the following:
    // a) Normal accumulate
    // Sum: 1000000
    // Time taken : 6 milliseconds
    // 
    // b) Parallel accumulate
    // Sum : 1000000
    // Time taken : 25 milliseconds

    // d)  Compare the speedup with that achieved by using OpenMP. OpenMP is delivered with Visual Studio.
    // I followed the code shown but I have no idea what is the purpose of #pragma omp parallel for reduction(+:sum)
    // The timing is roughly the same (7 milliseconds), regardless of whether the #pragma is there or not.
    start = std::chrono::high_resolution_clock::now();

    // Sum the elements using parallel_accumulate
    int sum3 = openmp_accumulate(array);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::endl;
    std::cout << "d) OpenMP accumulate" << std::endl;
    std::cout << "Sum: " << sum3 << std::endl;
    std::cout << "Time taken: " << duration << " milliseconds" << std::endl;

    // e) Now use threads instead of tasks in order to perform accumulation. Compare speedup.
    start = std::chrono::high_resolution_clock::now();

    // Sum the elements using thread accumulate
    int sum4 = 0;
    thread_accumulate(array, 0, array.size(), sum4);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << std::endl;
    std::cout << "e) Thread accumulate" << std::endl;
    std::cout << "Sum: " << sum4 << std::endl;
    std::cout << "Time taken: " << duration << " milliseconds" << std::endl;
    // Thread accumulate is even slower at 47 milliseconds to complete the task.

    // f) Write parallel code that use std::accumulate() with a binary function as last parameter. Test the algorithm
    // by computing the product of the elements of an array.
    start = std::chrono::high_resolution_clock::now();

    // Compute the product of the elements using std::accumulate with a binary function
    int product = std::accumulate(array.begin(), array.end(), 1, std::multiplies<int>());

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << std::endl;
    std::cout << "f) Product accumulate" << std::endl;
    std::cout << "Product: " << product << std::endl;
    std::cout << "Time taken: " << duration << " milliseconds" << std::endl;

    // g) Compare performance improvements by using the new parallel features in C++. We focus on three STL algorithms 
    // (or algorithms of your choice) as applied to std::vector, namely: std::transform, std::sort, std::find.
    //
    // I am not sure of the requirement by the exercise here. I already used std::accumulate for the above exercise
    // std::vector, std::transform, std::sort and std::find are unrelated to the accumlation calculation.
    //
    // I will complete the final part which requires me to compare the operation with different N
    //                     | 1,000,000 | 800,000 | 600,000 | 400,000 | 200,000
    // std::accumuate      | 6         | 5       | 4       | 3       | 1
    // parallel accumulate | 25        | 25      | 28      | 15      | 6
    // Open MP accumulate  | 7         | 5       | 4       | 3       | 1
    // Thread accumulate   | 47        | 46      | 45      | 26      | 12
    // Product accumulate  | 6         | 5       | 4       | 2       | 1
    //
    // I am unable to run the software for any N larger than 1,000,000, at that N value, parallel accumulate just freezes.
    // This potentially points to some overhead that was unresolved by async mechanism.
    return 0;
}