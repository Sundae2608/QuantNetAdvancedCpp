/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 1, Exercise 3: Safe Locking
*/

#include <boost/thread/thread.hpp>
#include <chrono>
#include <iostream>
#include <mutex>
#include <system_error>
#include <utility>

namespace {
    std::mutex mtx; // Mutex for synchronization
    std::timed_mutex timed_mtx; // Mutex for synchronization
    static std::mutex global_mtx; // Mutex for synchronization
    int counter = 0; // Shared counter variable

    void IncrementCounter() {
        // Critical section: Increment the counter
        counter++;
    }

    // The function from previous exercise was already implemented with lock_guard here.
    // I simply added an Increment counter here
    void IprintMutex(const std::string& s, int count) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        for (int i = 0; i < count; ++i) {
            // Critical section: Access the shared resource (console)
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
            IncrementCounter();

            // Unlock the mutex implicitly when lock_guard goes out of scope
        }
    }

    // This function will use try_lock to accquire the lock
    void IprintTrylock(const std::string& s, int count) {
        // Defer lock means we only associate the mutex with the lock, but we defer the locking
        std::unique_lock<std::mutex> lock(mtx, std::defer_lock);

        // Attempting to lock
        std::cout << "Attempting to lock the mutex..." << std::endl;
        if (lock.try_lock()) {
            try {
                for (int i = 0; i < count; ++i) {
                    // Critical section: Access the shared resource (console)
                    std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
                    IncrementCounter();
                }
            }
            catch (const std::system_error& ex) {
                const std::error_code& ec = ex.code();

                if (ec == std::errc::resource_deadlock_would_occur) {
                    std::cout << "Resource deadlock would occur. Mutex already locked by another thread." << std::endl;
                }
                else if (ec == std::errc::operation_not_permitted) {
                    std::cout << "Operation not permitted. No associated mutex." << std::endl;
                }
                else {
                    std::cout << "Failed to acquire the lock. Error code: " << ec.value() << " - " << ec.message() << std::endl;
                }
            }
            lock.unlock();
        }
        else {
            std::cout << "Failed to acquire the lock" << std::endl;
        }
        // Unlock the mutex implicitly when lock_guard goes out of scope
    }

    // This function will use try_lock_for to accquire the lock
    void IprintTrylockFor(const std::string& s, int count, int seconds_locked, int seconds_waited) {
        // Defer lock means we only associate the mutex with the lock, but we defer the locking
        std::unique_lock<std::timed_mutex> lock(timed_mtx, std::defer_lock);

        // Attempting to lock
        std::cout << "Attempting to lock the mutex..." << std::endl;
        if (lock.try_lock_for(std::chrono::seconds(seconds_locked))) {
            try {
                std::this_thread::sleep_for(std::chrono::seconds(seconds_waited));
                for (int i = 0; i < count; ++i) {
                    // Critical section: Access the shared resource (console)
                    std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
                    IncrementCounter();
                }
            }
            catch (const std::system_error& ex) {
                const std::error_code& ec = ex.code();

                if (ec == std::errc::resource_deadlock_would_occur) {
                    std::cout << "Resource deadlock would occur. Mutex already locked by another thread." << std::endl;
                }
                else if (ec == std::errc::operation_not_permitted) {
                    std::cout << "Operation not permitted. No associated mutex." << std::endl;
                }
                else {
                    std::cout << "Failed to acquire the lock. Error code: " << ec.value() << " - " << ec.message() << std::endl;
                }
            }
            lock.unlock();
        }
        else {
            std::cout << "Failed to acquire the lock" << std::endl;
        }
        // Unlock the mutex implicitly when lock_guard goes out of scope
    }

    // This function will use try_lock_for to accquire the lock
    void IprintTrylockUntil(const std::string& s, int count, int seconds_locked, int seconds_waited) {
        // Defer lock means we only associate the mutex with the lock, but we defer the locking
        std::unique_lock<std::timed_mutex> lock(timed_mtx, std::defer_lock);

        // Attempting to lock
        std::cout << "Attempting to lock the mutex..." << std::endl;
        std::chrono::time_point timeout = std::chrono::steady_clock::now() + std::chrono::seconds(seconds_locked);
        if (lock.try_lock_until(timeout)) {
            try {
                for (int i = 0; i < count; ++i) {
                    // Critical section: Access the shared resource (console)
                    std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
                    IncrementCounter();
                }
            }
            catch (const std::system_error& ex) {
                const std::error_code& ec = ex.code();

                if (ec == std::errc::resource_deadlock_would_occur) {
                    std::cout << "Resource deadlock would occur. Mutex already locked by another thread." << std::endl;
                }
                else if (ec == std::errc::operation_not_permitted) {
                    std::cout << "Operation not permitted. No associated mutex." << std::endl;
                }
                else {
                    std::cout << "Failed to acquire the lock. Error code: " << ec.value() << " - " << ec.message() << std::endl;
                }
            }
            lock.unlock();
        }
        else {
            std::cout << "Failed to acquire the lock" << std::endl;
        }
        // Unlock the mutex implicitly when lock_guard goes out of scope
    }

    // This function will lock the mutex but by using adopt_lock and aut
    void IprintNoUnlock(const std::string& s, int count) {
        std::cout << "Releasing the associated mutex without unlocking it..." << std::endl;
        std::lock_guard<std::mutex> lock(global_mtx, std::adopt_lock);

        // Attempting to lock
        try {
            for (int i = 0; i < count; ++i) {
                // Critical section: Access the shared resource (console)
                std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
                IncrementCounter();
            }
        }
        catch (const std::system_error& ex) {
            const std::error_code& ec = ex.code();

            if (ec == std::errc::resource_deadlock_would_occur) {
                std::cout << "Resource deadlock would occur. Mutex already locked by another thread." << std::endl;
            }
            else if (ec == std::errc::operation_not_permitted) {
                std::cout << "Operation not permitted. No associated mutex." << std::endl;
            }
            else {
                std::cout << "Failed to acquire the lock. Error code: " << ec.value() << " - " << ec.message() << std::endl;
            }
        }
        // By the time the code goes out of code. releasedLock will disappear, and the lock no longer has anyone owning it, effectively "unlock" it.
    }

    // Simple Iprint function
    void SimpleIPrint(const std::string& s, int count) {
        for (int i = 0; i < count; ++i) {
            // Critical section: Access the shared resource (console)
            std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << s << std::endl;
            IncrementCounter();

            // Unlock the mutex implicitly when lock_guard goes out of scope
        }
    }
}

int main13() {
    // a) Modify the code in exercise 2 to let it work with std::lock_guard. 
    // My understanding of the exercise is that I have to
    // 1) Modify the Iprint function to use lockguard.
    // 2) Add the Increment Counter function nside the thread.
    std::cout << "Part a)" << std::endl;
    std::thread t1(IprintMutex, "Thread 1", 3);
    std::thread t2(IprintMutex, "Thread 2", 3);
    std::thread t3(IprintMutex, "Thread 3", 3);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Counter value: " << counter << std::endl;  // 3, as expected.

    // b) We now test the functionality of std::unique_lock. In particular, 
    // you should investigate its interface (for example, www.cpppreference.com)
    // in order to answer the questions in the rest of this exercise.
    // Not sure what the exercise is asking for here, but I read a bit about
    // unique_lock. It seems that std::unique_lock is a more flexible mutex 
    // ownership wrapper compared to std::lock_guard. It provides various features
    // and interfaces that offer additional control over mutex locking and unlocking. 

    // c) Lock an associated mutex without locking using std::unique_lock::try_lock
    // Take care of exceptions such as i) no associated mutex and ii) mutex is already
    // locked. You need to use std::system::error_code and std::errc as discussed in
    // section 2.7 of the course.
    std::cout << "Part c)" << std::endl;
    std::thread t4(IprintTrylock, "Thread 4", 3);
    std::thread t5(IprintTrylock, "Thread 5", 3);
    std::thread t6(IprintTrylock, "Thread 6", 3);
    t4.join();
    t5.join();
    t6.join();

    // d) Apply std::unique_lock::try_lock_for that tries to lock a mutex that blocks
    // until a specific timeout duration has elapsed or the lock has been acquired.
    // As in part c) you need to catch system errors.
    std::cout << "Part d.1) When each thread takes less than the time it locks" << std::endl;
    std::thread t7(IprintTrylockFor, "Thread 7", 3, /*seconds_locked=*/3, /*seconds_waited=*/2);
    std::thread t8(IprintTrylockFor, "Thread 8", 3, /*seconds_locked=*/3, /*seconds_waited=*/2);
    std::thread t9(IprintTrylockFor, "Thread 9", 3, /*seconds_locked=*/3, /*seconds_waited=*/2);
    t7.join();
    t8.join();
    t9.join();

    std::cout << "Part d.2) When each thread takes mroe than the time it locks " << std::endl;
    std::thread t10(IprintTrylockFor, "Thread 10", 3, /*seconds_locked=*/3, /*seconds_waited=*/4);
    std::thread t11(IprintTrylockFor, "Thread 11", 3, /*seconds_locked=*/3, /*seconds_waited=*/4);
    std::thread t12(IprintTrylockFor, "Thread 12", 3, /*seconds_locked=*/3, /*seconds_waited=*/4);
    t10.join();
    t11.join();
    t12.join();


    // e) Apply std::unique_lock::unlock that unlocks the associated mutex and releases ownership. 
    // As in parts c) and d) you need to catch system errors.
    // I already perform unlocking in part c) and part d). I unlocked the mutex after
    // locking the mutex for the period of the operation.

    // f) Apply std::unique_lock::try_lock_until that tries to lock a mutex that blocks until a 
    // specific time has been reached or the lock has been acquired.As in parts c), d) and e) 
    // you need to catch system errors.
    std::cout << "Part f.1) When each thread takes less than the time it locks" << std::endl;
    std::thread t13(IprintTrylockUntil, "Thread 13", 3, /*seconds_locked=*/3, /*seconds_waited=*/2);
    std::thread t14(IprintTrylockUntil, "Thread 14", 3, /*seconds_locked=*/3, /*seconds_waited=*/2);
    std::thread t15(IprintTrylockUntil, "Thread 15", 3, /*seconds_locked=*/3, /*seconds_waited=*/2);
    t13.join();
    t14.join();
    t15.join();

    std::cout << "Part f.2) When each thread takes mroe than the time it locks " << std::endl;
    std::thread t16(IprintTrylockUntil, "Thread 16", 3, /*seconds_locked=*/3, /*seconds_waited=*/4);
    std::thread t17(IprintTrylockUntil, "Thread 17", 3, /*seconds_locked=*/3, /*seconds_waited=*/4);
    std::thread t18(IprintTrylockUntil, "Thread 18", 3, /*seconds_locked=*/3, /*seconds_waited=*/4);
    t16.join();
    t17.join();
    t18.join();

    // g) Show how to release an associated mutex without unlocking it.
    // In part a), I already implement IprintMutex in such a way that the unlock function is not called.
    // TODO: Dig a bit further into this exercise, it might not be that simple
    return 0;
}