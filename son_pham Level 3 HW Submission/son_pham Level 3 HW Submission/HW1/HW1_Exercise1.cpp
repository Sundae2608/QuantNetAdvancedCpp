/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 1, Exercise 1: Thread Class in C++11
*/

#include <iostream>
#include <chrono>
#include <ctime>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace {

    void Iprint(const std::string& s, int count) {
        for (int i = 0; i < count; ++i) {
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
        }
    }

    void PrintTotalElapsedTime(
        std::chrono::time_point<std::chrono::system_clock> start,
        std::chrono::time_point<std::chrono::system_clock> end) {

        std::chrono::duration<double>
            elapsed_seconds = end - start;
        std::time_t end_time =
            std::chrono::system_clock::to_time_t(end);

        std::cout << "Finished computation at "
            << "elapsed time: "
            << elapsed_seconds.count() << "s" << std::endl;
    }


    // Free function
    void freeFunction(int count) {
        Iprint("Free function", count);
    }

    // Stored lambda function
    class LambdaClass {
    public:
        void operator()(int count) {
            Iprint("Stored lambda function", count);
        }
    };

    // Function object
    class FunctionObject {
    public:
        FunctionObject(std::string str) : str_(str) {};
        void operator()(int count) {
            Iprint(str_, count);
        }
    private:
        std::string str_;
    };

    // Member function
    class MemberFunctionClass {
    public:
        void memberFunction(int count) {
            Iprint("Member function", count);
        }
    };

    // Static member function
    class StaticClass {
    public:
        static void staticFunction(int count) {
            Iprint("Static member function", count);
        }
    };
}
int main11() {
    // Create a start point and the end point. This will be used as time management tools.
    std::chrono::time_point
        <std::chrono::system_clock> start, end;

    // a) Create as many callable objects as you can that all call the interface Iprint above.
    // * free functions
    // * lambda function
    // * stored lambda function
    // * function object
    // * binded member function
    // * static member function
    // 
    // For ease of differentiation, the calls will always call with the count of 3

    // Lambda function
    std::cout << "Part a)" << std::endl;

    // Exemplar code for system performance
    start = std::chrono::system_clock::now();

    // Initialize all the functions
    auto lambdaFunction = [](int count) {
        Iprint("Lambda function", count);
    };

    // Binded member function
    auto bindedMemberFunction = std::bind(Iprint, "Binded Iprint", std::placeholders::_1);

    // Calling each of those functions just to test the functionality of it
    freeFunction(3);        // Free function
    lambdaFunction(3);      // Lambda function
    LambdaClass lambdaObj;  // Lambda class
    lambdaObj(3);
    FunctionObject funcObj("Function object"); // Function object
    funcObj(3);
    MemberFunctionClass obj; // Member function class 
    obj.memberFunction(3);
    StaticClass::staticFunction(3);  // Static class function
    end = std::chrono::system_clock::now();
    PrintTotalElapsedTime(start, end);

    // b) Create a thread for each of the callable objects in part a). 
    // One of the threads should be a detached thread. Each thread’s function has its own unique ID.
    std::cout << "Part b onwards)" << std::endl;
    end = std::chrono::system_clock::now();
    std::thread t1([](int count) {
        Iprint("Lambda function", count);
        }, 3);

    std::thread t2([](int count) {
        Iprint("Stored lambda function", count);
        }, 3);

    std::thread t3(FunctionObject("Function object"), 3);

    MemberFunctionClass obj2;
    std::thread t4(&MemberFunctionClass::memberFunction, &obj2, 3);

    std::thread t5(&StaticClass::staticFunction, 3);

    auto bindedIprint = std::bind(Iprint, "Binded Iprint", std::placeholders::_1);
    std::thread t6(bindedIprint, 3);

    t6.detach();  // We will pick t6 as the detached thread.

    // c) Introduce code to check if threads have completed and then join each one if this is the case.
    // d) We need to introduce exception handling in the case that a thread may not be joined.In these cases we need to introduce join() inside the catch blocks.
    // I merged the two parts into the same part here, since part c) code gets changed anyway by the exception catch introduction.
    std::thread threads[] = { std::move(t1), std::move(t2), std::move(t3),
                             std::move(t4), std::move(t5) };

    for (auto& thread : threads) {
        if (thread.joinable()) {
            try {
                thread.join();
            }
            catch (...) {
                std::cout << "Exception caught, calling join()." << std::endl;
                thread.join();
            }
        }
    }

    // e) Print the thread ID of each thread in each implementation of Iprint.
    // I already changed the implementation of IPrint to include the printing of Thread ID

    // f) Compute the running time of the program based on the example code in the summary based on std::chrono.
    // Here, I already included the running time of both part a (calling each function sequentially) and part b (using threads)
    // for comparison.
    end = std::chrono::system_clock::now();
    PrintTotalElapsedTime(start, end);

    // Examine the output; what do you see? What is happening?
    // While not having consistent output across the board, what I consistently noticed in several different runs of these two parts
    // are:
    // * The thread versions are consistently slower than the sequentially called function in total time.
    //   The thread baed version usually takes a total of 0.013s to 0.023s to complete their operation.
    //   On the other hand, the sequential version takes 0.004s to complete, and the total time is usually much more consistent.
    // * I wouldn't count this against the thread based version however. In a more intensive task, there should be genuine savings
    //   However, the execution time should be expected to be inconsistent, as there will be more variability in task execution
    //   such as context switching, overhead, order of operations etc.
    // * Speaking of operations ordering. One of the run (shown in full output text below), shows that the ordering of operations
    //   for the none-thread version is very consistent, while the ordering for the threaded version is very inconsistent.
    // * Notice that the priting function is not always in the same order. And sometimes, the ordering can be disrupted in the
    //   middle of the IPrint function.
    return 0;
}