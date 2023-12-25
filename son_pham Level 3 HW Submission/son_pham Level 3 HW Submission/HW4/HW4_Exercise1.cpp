/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 4, Exercise 1: Tasks 101 - Running Functions Asynchronously
*/

#include <iostream>
#include <chrono>
#include <thread>
#include <future>

namespace {

    // a) Create two functions having the following signatures:
    // You may place any code into the body of these functions for the purpose of this exercise.
    // For function 1, I will just print the beginning and the end of the function with some
    // wait time in between.
    // For function 2, I will 
    void func1()
    {
        std::cout << "func1 is running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "func1 has completed." << std::endl;
    }

    double func2(double a, double b)
    {
        std::cout << "func2 is running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));  // Intentionally let func2 waits longer
        double result = a + b;
        std::cout << "func2 has completed and returned " << result << std::endl;
        return result;
    }
}

int main41() {
    auto start = std::chrono::system_clock::now();

    // b) Use std::async (default settings) to launch func1 and func2. Get the results of the computations and print them when applicable.
    // Check the validity of the associated future before and after getting the result.
    
    // Launch func1 asynchronously
    // std::future<void> fut1 = std::async(func1);
    std::future<void> fut1 = std::async(std::launch::async, func1);

    // Launch func2 asynchronously
    // std::future<double> fut2 = std::async(func2, 3.5, 2.7);
    // std::future<double> fut2 = std::async(std::launch::async, func2, 3.5, 2.7);
    std::future<double> fut2 = std::async(std::launch::deferred, func2, 3.5, 2.7);  // Deferred the 2nd execution for part 3

    // Check if the future is valid before getting the result
    if (fut1.valid())
    {
        std::cout << "fut1 is valid before getting the result." << std::endl;
    }

    if (fut2.valid())
    {
        std::cout << "fut2 is valid before getting the result." << std::endl;
    }

    // Get the results of the computations and print them
    fut1.get();
    double result = fut2.get();
    std::cout << "Result of func2: " << result << std::endl;

    // Check if the future is valid after getting the result
    if (!fut1.valid())
    {
        std::cout << "fut1 is invalid after getting the result." << std::endl;
    }

    if (!fut2.valid())
    {
        std::cout << "fut2 is invalid after getting the result." << std::endl;
    }

    // c) What happens if you try to get the result of a std::future more than once?
    // Trying to get the result of a std::future more than once will result in an exception.
    // Once the std::future object's get() function has been called and the result obtained,
    // any subsequent call to get() will throw an std::future_error with error code
    // std::future_errc::future_already_retrieved.
    //
    // Let's try to do this.
    try
    {
        double result = fut2.get();
        std::cout << "Result of func2: " << result << std::endl;
    }
    catch (const std::future_error& ex)
    {
        std::cout << "Exception caught while getting fut2: " << ex.what() << std::endl;  // This will print out instead
    }

    // d) Now test the same code using the launch parameter std::launch::async. Do you notice any differences?
    // I added the code of std::launch::async in. To be honest, I don't really notice any difference between
    // the two runs. Perhaps the two functions aren't complicated enough to show any difference. It seems to me
    // that in both cases, both functions complete their execution after about 5 seconds, which is the longer
    // wait time defined in func2.
    //
    // According to the documentation in https://en.cppreference.com/w/cpp/thread/async. The addition of
    // std::launch::async explicitly makes the execution asynchornous. While leaving it unknown means we don't know if they
    // would be asynced or deferred.
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Total execution time: " << duration.count() << " milliseconds." << std::endl;

    // e) We now wish to asynchronously call a function at some time later in the client code (deferred/lazy evaluation).
    // Get the result of the function and check that it is the same as before.
    // 
    // There is a comment block that will change the function execution to std::launch::deferred. Here, we can see
    // the execution of func 2 waits for func1 to complete. We sitll have the same results of 6.2 as before, but
    // now, the total time takes 7 seconds instead of 5 seconds.
    return 0;
}