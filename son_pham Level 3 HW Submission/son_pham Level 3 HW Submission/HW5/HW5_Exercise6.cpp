/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 6: std::chrono
*/

#include <chrono>
#include <iostream>

namespace {

    // a) Implement an adapter class with the following interface.
    class StopWatch
    {
    public:
        StopWatch() : running(false) {}

        void StartStopWatch() {
            if (!running) {
                startTime = std::chrono::high_resolution_clock::now();
                running = true;
            }
        }

        void StopStopWatch() {
            if (running) {
                endTime = std::chrono::high_resolution_clock::now();
                running = false;
            }
        }

        void Reset() {
            running = false;
        }

        double GetTime() const {
            if (running) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                return std::chrono::duration<double>(currentTime - startTime).count();
            }
            else {
                return std::chrono::duration<double>(endTime - startTime).count();
            }
        }

    private:
        bool running;
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
    };
}

int main56() {
    StopWatch watch;

    // Start the stopwatch and do some operation (simulate work)
    watch.StartStopWatch();
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulating some work that takes 2 seconds
    watch.StopStopWatch();

    // Get the elapsed time
    double elapsedSeconds = watch.GetTime();
    std::cout << "Elapsed time: " << elapsedSeconds << " seconds" << std::endl;

    // Reset and measure again
    watch.Reset();
    watch.StartStopWatch();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating some work that takes 1 second
    watch.StopStopWatch();

    // Get the elapsed time again
    elapsedSeconds = watch.GetTime();
    std::cout << "Elapsed time: " << elapsedSeconds << " seconds" << std::endl;

    return 0;
}