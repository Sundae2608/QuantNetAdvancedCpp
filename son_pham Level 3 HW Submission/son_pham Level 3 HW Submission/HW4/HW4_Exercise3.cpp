/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 4, Exercise 3: C++11 Promises 101
*/

#include <iostream>
#include <future>

namespace {
    // Thread function that uses the value of the shared data
    void threadFunction(std::future<double>& futureResult) {
        // Retrieve the value from the future
        double result = futureResult.get();
        std::cout << "Value received in the thread: " << result << std::endl;
    }
}

int main43() {
    // a) Create a default promise, a promise with an empty shared state and
    // a promise based on the move constructor.

    // Create a default promise
    std::promise<double> defaultPromise;
    std::future<double> defaultFuture = defaultPromise.get_future();

    // Create a promise with an empty shared state
    // I am not sure what it means by an empty shared state. Doesn't the promise
    // have empty state by default? Or do I have to pass {} in?
    std::promise<double> emptyStatePromise({});
    std::future<double> emptyStateFuture = emptyStatePromise.get_future();


    // Create a promise using the move constructor
    std::promise<std::string> sourcePromise;
    std::promise<std::string> movePromise(std::move(sourcePromise));

    // b) Create a promise with double as stored value. Then create a future 
    // that is associated with the promise.
    std::promise<double> doublePromise;

    // Create a future associated with the promise
    std::future<double> futureResult = doublePromise.get_future();

    // c) Start a thread with the new future from part b). Create a thread
    // function that uses the value of the shared data.
    // d) Use the promise to set the value of the shared data.
    // Start a thread with the future
    std::thread threadObj(threadFunction, std::ref(futureResult));
    // std::thread threadObj(threadFunction, std::ref(emptyStateFuture));
    // std::thread threadObj(threadFunction, std::ref(defaultFuture));

    // Set the value of the promise
    doublePromise.set_value(6.28);

    // Wait for the thread to finish
    threadObj.join();

    // As a learning exercise, I also have some commented code in which I passed the
    // futures that don't have the promise value being set. The thread basically stops
    // working.
    // This demonstrates the power of this tool. The thread doesn't not execute its function
    // unless its promised value is filled.
    return 0;
}