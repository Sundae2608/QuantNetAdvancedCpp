/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 1, Exercise 2: Controlling Thread Execution: Synchronizing Access to Shared Resources
*/

#include <iostream>
#include <mutex>
#include <chrono>
#include <boost/thread/thread.hpp>

namespace {
    std::mutex mtx; // Mutex for synchronization
    int failed_attempts = 0; // Counter for failed attempts

    void Iprint(const std::string& s, int count) {
        for (int i = 0; i < count; ++i) {
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
        }
    }

    void IprintMutex(const std::string& s, int count) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        for (int i = 0; i < count; ++i) {
            // Critical section: Access the shared resource (console)
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;

            // Unlock the mutex implicitly when lock_guard goes out of scope
        }
    }

    void IprintTrylock(const std::string& s, int count) {
        if (mtx.try_lock()) {
            for (int i = 0; i < count; ++i) {
                // Critical section: Access the shared resource (console)
                std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
            }
            mtx.unlock();
        }
        else {
            ++failed_attempts;
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

}

int main12() {
    // a) Use the std::mutex synchronization to control access to the shared resource. Use lock() and unlock(). Measure processing time.
    // I will call this new IPrint function IprintMutex to show the fact that they use mutex for resource logging. I will also
    // run the version without the mutex to see if there is a difference in performance.
    std::cout << "Mutex version" << std::endl;
    std::chrono::time_point
        <std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    std::thread t1(IprintMutex, "Thread 1", 3);
    std::thread t2(IprintMutex, "Thread 2", 3);
    std::thread t3(IprintMutex, "Thread 3", 3);

    t1.join();
    t2.join();
    t3.join();

    end = std::chrono::system_clock::now();
    PrintTotalElapsedTime(start, end);

    // The version that uses the previous IPrint
    std::cout << "Non-mutex version" << std::endl;
    start = std::chrono::system_clock::now();

    std::thread t4(Iprint, "Thread 1", 3);
    std::thread t5(Iprint, "Thread 2", 3);
    std::thread t6(Iprint, "Thread 3", 3);

    t4.join();
    t5.join();
    t6.join();

    end = std::chrono::system_clock::now();
    PrintTotalElapsedTime(start, end);

    // Example run output
    // Mutex version
    // Thread ID : 38368 - Thread 1
    // Thread ID : 38368 - Thread 1
    // Thread ID : 38368 - Thread 1
    // Thread ID : 27276 - Thread 2
    // Thread ID : 27276 - Thread 2
    // Thread ID : 27276 - Thread 2
    // Thread ID : 14640 - Thread 3
    // Thread ID : 14640 - Thread 3
    // Thread ID : 14640 - Thread 3
    // Finished computation at elapsed time : 0.0024888s
    // Non - mutex version
    // Thread ID : Thread ID : Thread ID : 43544 - Thread 2
    // Thread ID : 43544 - Thread 2
    // Thread ID : 43544 - Thread 2
    // 73552 - Thread 3
    // Thread ID : 73552 - Thread 3
    // Thread ID : 73552 - Thread 3
    // 38104 - Thread 1
    // Thread ID : 38104 - Thread 1
    // Thread ID : 38104 - Thread 1
    // Finished computation at elapsed time : 0.0019329s
    // Notice that the mutex version is slightly slower. However, each thread seems to execute concretely
    // On the other hand, for the non-mutex version, sometimes the order of operations get really wobbly.

    // b) Now use try_lock() and measure the number of times each thread has failed to acquire the lock. 
    // Again, measure processing time.
    std::cout << "Trylock version" << std::endl;
    start = std::chrono::system_clock::now();

    std::thread t7(IprintTrylock, "Thread 1", 3);
    std::thread t8(IprintTrylock, "Thread 2", 3);
    std::thread t9(IprintTrylock, "Thread 3", 3);

    t7.join();
    t8.join();
    t9.join();

    end = std::chrono::system_clock::now();
    PrintTotalElapsedTime(start, end);
    std::cout << "Number of failed attempts to acquire the lock: " << failed_attempts << std::endl;
    // It fails 6 times, and only one thread managed to fully execute, as we can see in the output
    // Thread ID: 25032 - Thread 1
    // Thread ID : 25032 - Thread 1
    // Thread ID : 25032 - Thread 1
    // Finished computation at elapsed time : 0.0007821s
    // Number of failed attempts to acquire the lock : 6
    
    // c) Simulate deadlock (for example, a thread that never unlocks a mutex) by commenting out unlock() in your code. What happens?
    std::cout << "Deadlock version" << std::endl;
    start = std::chrono::system_clock::now();
    std::mutex mtx1; // First mutex
    std::mutex mtx2; // Second mutex

    auto thread1_func = [&mtx1, &mtx2](){
        std::lock_guard<std::mutex> lock1(mtx1); // Lock the first mutex
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Introduce delay to create synchronization order

        std::lock_guard<std::mutex> lock2(mtx2); // Attempt to lock the second mutex (deadlock)
        std::cout << "Thread 1 executed" << std::endl;
    };

    auto thread2_func = [&mtx1, &mtx2]() {
        std::lock_guard<std::mutex> lock2(mtx2); // Lock the second mutex
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Introduce delay to create synchronization order

        std::lock_guard<std::mutex> lock1(mtx1); // Attempt to lock the first mutex (deadlock)
        std::cout << "Thread 2 executed" << std::endl;
    };

    std::thread t10(thread1_func);
    std::thread t11(thread2_func);

    t10.join();
    t11.join();
    end = std::chrono::system_clock::now();
    PrintTotalElapsedTime(start, end);
    // Program gets frozen. The print function is not even rea
    return 0;
}