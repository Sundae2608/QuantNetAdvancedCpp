/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 4, Exercise 4: Packaged Tasks
*/

#include <iostream>
#include <future>
#include <random>
#include <cmath>
#include <thread>
#include <queue>
#include <functional>

// Thread function
double compute(double x, double y) {
    // Wait for a random amount of time (simulating some computation)
    std::default_random_engine dre(42);
    std::uniform_int_distribution<int> delay(0, 1000);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay(dre)));

    return std::cos(x) * std::exp(y);
}

int main44() {
    // a) This part is basically just running the code given in the exercise.
    double x = 0.0;
    double y = 2.71;
    std::future<double> fut = std::async(compute, x, y);
    double result = fut.get();
    std::cout << "Result: " << result << '\n';

    // b) Rewrite / port the code in order to use a packaged task and delayed
    // execution.
    std::packaged_task<double(double, double)> task(compute);
    std::future<double> fut2 = task.get_future();

    // Start the task in a separate thread
    std::thread threadObj(std::move(task), x, y);

    // Wait for the thread to finish
    threadObj.join();

    // Get the shared data
    double result2 = fut2.get();
    std::cout << "Result: " << result2 << '\n';

    // c) Create a queue of packaged tasks, dequeue each task and execute it.
    std::vector<double> x_values{ 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
    std::vector<double> y_values{ 3.14, 6.28, 9.42, 12.56, 15.7, 18.84, 21.98};
    std::queue<std::packaged_task<double()>> taskQueue;

    for (int i = 0; i < x_values.size(); i++) {
        taskQueue.emplace(std::bind(compute, x_values[i], y_values[i]));
    }

    // Start executing tasks in separate threads
    std::vector<std::future<double>> futures;

    while (!taskQueue.empty()) {
        std::packaged_task<double()> task;
        task = std::move(taskQueue.front());
        taskQueue.pop();

        std::future<double> fut = task.get_future();

        // Start the task in a separate thread
        std::thread(std::move(task)).detach();
        futures.push_back(std::move(fut));
    }

    // Wait for all threads to finish
    for (auto& fut : futures) {
        double result = fut.get();
        std::cout << "Result: " << result << '\n';
    }

    return 0;
}