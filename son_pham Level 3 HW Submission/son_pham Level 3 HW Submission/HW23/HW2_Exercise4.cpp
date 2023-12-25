/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 2, Exercise 4: My first Master-Worker Pattern in C++ 11.
* TODO: Check this code. Not sure if it is correct
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>


namespace {
    // b) Create the thread function: it updates the resource by acquiring the lock, waiting on the worker ready flag to be set,
    // updating the resource and then finally notifying the master.
    void workerFunction(std::string& data, std::mutex& m, std::condition_variable& cv, std::atomic<bool>& workerReady)
    {
        // Wait until the master indicates that a task is ready
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&workerReady] { return workerReady.load(); });

        // Perform the task and update the shared resource
        data += " processed";

        // Notify the master that the task is completed
        workerReady = false;
        cv.notify_one();
    }

    // c) Create the code that implements the master’s duties. Test the code.
    void masterFunction(std::string& data, std::mutex& m, std::condition_variable& cv, std::atomic<bool>& workerReady, std::atomic<bool>& masterReady)
    {
        // Master sets up the problem and creates a worker
        std::cout << "Master initiates the computation and sets up the problem." << std::endl;
        std::thread workerThread(workerFunction, std::ref(data), std::ref(m), std::ref(cv), std::ref(workerReady));

        // Indicate that the worker is ready to work
        workerReady = true;

        // Master waits until the job is done
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&workerReady] { return !workerReady.load(); });

        // Master consumes the results
        std::cout << "Master received the result: " << data << std::endl;

        // Master shuts down
        workerThread.join();
        masterReady = true;
    }

    // d) Worker and master function, but using atomic flags
    // Worker function
    void workerFunctionAtomicFlag(std::string& data, std::mutex& m, std::condition_variable& cv, std::atomic_flag& workerReady)
    {
        // Wait until the master indicates that a task is ready
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&workerReady] { return workerReady.test_and_set(); });

        // Perform the task and update the shared resource
        data += " processed";

        // Notify the master that the task is completed
        workerReady.clear();
        cv.notify_one();
    }

    // Master function
    void masterFunctionAtomicFlag(std::string& data, std::mutex& m, std::condition_variable& cv, std::atomic_flag& workerReadyAtomicFlag, std::atomic_flag& masterReadyAtomicFlag)
    {
        // Master sets up the problem and creates a worker
        std::cout << "Master initiates the computation and sets up the problem." << std::endl;
        std::thread workerThread(workerFunctionAtomicFlag, std::ref(data), std::ref(m), std::ref(cv), std::ref(workerReadyAtomicFlag));

        // Indicate that the worker is ready to work
        workerReadyAtomicFlag.test_and_set();

        // Master waits until the job is done
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&workerReadyAtomicFlag] { return !workerReadyAtomicFlag.test_and_set(); });

        // Master consumes the results
        std::cout << "Master received the result: " << data << std::endl;

        // Master shuts down
        workerThread.join();
        masterReadyAtomicFlag.test_and_set();
    }
}

int main24() {
    // a) We start with the following global data that is needed in order to implement this pattern:
    // Types and data needed
    std::string data; // Shared data between master and worker
    std::mutex m;     // Ensures no race condition

    // Synchronization between master and worker
    std::condition_variable cv;

    // Initial state of worker and master
    std::atomic<bool> workerReady = false;
    std::atomic<bool> masterReady = false;

    // c) Test the code of the master function.
    masterFunction(data, m, cv, workerReady, masterReady);

    // d) We now replace atomic Booleans by class std::atomic_flag which is a bare-bones lock-free data type.
    // It does not provide load nor store operations. It has functions to set and clear. Modify the code
    // accordingly and test again.
    std::atomic_flag workerReadyAtomicFlag;
    std::atomic_flag masterReadyAtomicFlag;
    masterFunctionAtomicFlag(data, m, cv, workerReadyAtomicFlag, masterReadyAtomicFlag);
    return 0;
}