/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 4, Exercise 6: Loop-Level Parallelism with Tasks
* TODO: The exercise does ask me to experiment with different types. Do that before submission
*/

#include <iostream>
#include <chrono>
#include <future>

namespace {
    // Simulate some computation by sleeping for the given milliseconds
    void simulateWorkload(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    // Functions corresponding to the nodes in the dependency graph
    int F1(int a) {
        simulateWorkload(500);
        return a * 2;
    }

    int F2(int a) {
        simulateWorkload(600);
        return a + 5;
    }

    int F3(int input) {
        simulateWorkload(700);
        return input * 3;
    }

    int F4(int input1, int input2) {
        simulateWorkload(800);
        return input1 + input2;
    }

    // Functions corresponding to the nodes in the dependency graph
    void F1Promise(int a, std::promise<int>& result) {
        simulateWorkload(500);
        int output = a * 2;
        result.set_value(output);
    }

    void F2Promise(int a, std::promise<int>& result) {
        simulateWorkload(600);
        int output = a + 5;
        result.set_value(output);
    }

    void F3Promise(std::future<int>& input, std::promise<int>& result) {
        simulateWorkload(700);
        int output = input.get() * 3;
        result.set_value(output);
    }

    void F4Promise(std::future<int>& input1, std::future<int>& input2, std::promise<int>& result) {
        simulateWorkload(800);
        int output = input1.get() + input2.get();
        result.set_value(output);
    }

    // a) Write single-threaded code for this dependency graph. This 
    // will be the baseline code. Measure the processing time.
    // Start measuring time
    int partA(int a) {
        int b = F1(a);
        int c = F2(a);
        int d = F3(c);
        int f = F4(b, d);
        return f;
    }

    // b) Implement the graph using std::async and std::future.
    int partB(int a) {
        // Using std::async to run each function in a separate thread
        auto futureF1 = std::async(std::launch::async, F1, a);
        auto futureF2 = std::async(std::launch::async, F2, a);
        int b = futureF1.get();
        int c = futureF2.get();
        auto futureF3 = std::async(std::launch::async, F3, c);
        int d = futureF3.get();
        auto futureF4 = std::async(std::launch::async, F4, b, d);
        int f = futureF4.get();
        return f;
    }

    // c) Implement the graph using promises.
    int partC(int a) {
        // Create promises and futures for the functions
        std::promise<int> promiseF1, promiseF2, promiseF3, promiseF4;
        std::future<int> futureF1 = promiseF1.get_future();
        std::future<int> futureF2 = promiseF2.get_future();
        std::future<int> futureF3 = promiseF3.get_future();
        std::future<int> futureF4 = promiseF4.get_future();

        // Start each function in a separate thread with the necessary input
        std::thread t1(F1Promise, a, std::ref(promiseF1));
        std::thread t2(F2Promise, a, std::ref(promiseF2));
        std::thread t3(F3Promise, std::ref(futureF2), std::ref(promiseF3));
        std::thread t4(F4Promise, std::ref(futureF1), std::ref(futureF3), std::ref(promiseF4));

        // Wait for all threads to finish
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        // Get the final result from the last function
        int f = futureF4.get();
        return f;
    }

    // d) Implement the graph using packaged tasks
    int partD(int a) {
        // Create packaged tasks and associated futures for the functions
        std::packaged_task<int(int)> taskF1(F1);
        std::packaged_task<int(int)> taskF2(F2);
        std::packaged_task<int(int)> taskF3(F3);
        std::packaged_task<int(int, int)> taskF4(F4);

        std::future<int> futureF1 = taskF1.get_future();
        std::future<int> futureF2 = taskF2.get_future();
        std::future<int> futureF3 = taskF3.get_future();
        std::future<int> futureF4 = taskF4.get_future();

        // Start each function in a separate thread with the necessary input
        std::thread t1(std::move(taskF1), a);
        std::thread t2(std::move(taskF2), a);
        std::thread t3(std::move(taskF3), futureF2.get());
        std::thread t4(std::move(taskF4), futureF1.get(), futureF3.get());

        // Wait for all threads to finish
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        // Get the final result from the last function
        int f = futureF4.get();
        return f;
    }
}


int main46() {
    int a = 0;

    // Part a)
    auto start = std::chrono::high_resolution_clock::now();
    int f = partA(a);
    auto end = std::chrono::high_resolution_clock::now();
    auto baselineTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time baseline: " << baselineTime << " ms" << std::endl;
    std::cout << "Result " << f << std::endl;

    // Part b)
    start = std::chrono::high_resolution_clock::now();
    f = partB(a);
    end = std::chrono::high_resolution_clock::now();
    baselineTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time using std::async and std::future: " << baselineTime << " ms" << std::endl;
    std::cout << "Result " << f << std::endl;

    // Part c)
    start = std::chrono::high_resolution_clock::now();
    f = partC(a);
    end = std::chrono::high_resolution_clock::now();
    baselineTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time using promises: " << baselineTime << " ms" << std::endl;
    std::cout << "Result " << f << std::endl;

    // Part d)
    start = std::chrono::high_resolution_clock::now();
    f = partD(a);
    end = std::chrono::high_resolution_clock::now();
    baselineTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time using packaged tasks: " << baselineTime << " ms" << std::endl;
    std::cout << "Result " << f << std::endl;
    return 0;
}