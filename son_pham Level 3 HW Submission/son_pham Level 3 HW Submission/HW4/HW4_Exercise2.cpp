/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 4, Exercise 2: Shared Futures 101
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <future>

namespace {
    void func()
    {
        std::cout << "func1 is running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "func1 has completed." << std::endl;
    }

    void infiniteLoop()
    {
        while (true)
        {
            // Infinite loop, does not finish
        }
    }
}

int main42()
{
    // Create the following shared future by calling the appropriate constructor
    // Default instance of shared_future
    std::shared_future<void> sharedFutureDefault;

    // Create a future
    std::future<void> fut = std::async(func);

    // As a shared future that shares the same state as another shared state
    std::shared_future<void> sharedFutureFromAnotherSharedState(fut.share());

    // Transfer shared state from a 'normal' future to a shared future
    std::shared_future<void> sharedFutureFromNormalFuture = fut.share();

    // Transfer shared state from a shared future to another shared future
    std::shared_future<void> sharedFutureTransferFromAnotherSharedFuture(sharedFutureFromNormalFuture);

    // b) Check the member functions from std::future that they are also applicable to std::shared_future.
    //
    // To decide on this, I read the CPP Reference documentation for
    // - std::future: https://en.cppreference.com/w/cpp/thread/future
    // - std::shared_future: https://en.cppreference.com/w/cpp/thread/shared_future
    //
    // Both std::future and std::shared_future contains get, valid, wait, wait_for, wait_util. We can conlude
    // that they have the same interface.

    // c) Test what happens when you call get() twice on a shared future.
    // When you call get() twice on a std::shared_future, the first get() call will succeed and return the result,
    // but the second get() call will throw an std::future_error with error code std::future_errc::future_already_retrieved.
    std::shared_future<void> sharedFut = fut.share();
    try
    {
        sharedFut.get();
        sharedFut.get(); // Second get() call will throw an exception.
    }
    catch (const std::future_error& ex)
    {
        std::cout << "Exception caught: " << ex.what() << std::endl;
    }
    
    // d) Create a shared future that waits for an infinite loop to finish (which it never does). 
    // To this end, use wait_for and wait_until to trigger a time out.
    // Launch the infiniteLoop asynchronously
    std::future<void> infiniteLoopFut = std::async(infiniteLoop);

    // Create a shared_future from the future
    std::shared_future<void> sharedInfiniteLoopFut = infiniteLoopFut.share();

    // Wait for a timeout (e.g., 5 seconds)
    auto timeout = std::chrono::seconds(5);
    auto status = sharedInfiniteLoopFut.wait_for(timeout);

    if (status == std::future_status::timeout)
    {
        std::cout << "Timeout occurred. Infinite loop is still running." << std::endl;
    }
    else if (status == std::future_status::ready)
    {
        std::cout << "Infinite loop has finished." << std::endl;
    }
    return 0;
}