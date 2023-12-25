/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 2, Exercise 3: Active objects 101
*/

#include <iostream>
#include <thread>
#include <functional>

namespace {
    void threadFunction() {
        for (int i = 0; i < 30; ++i) {
            std::cout << "Thread function executing: " << i << std::endl;
        }
    }

    // Default thread function that does nothing
    void kDefaultThreadFunction() {}

    // Thread function object
    struct ThreadFunctionObject {
        void operator()() {
            for (int i = 0; i < 30; ++i) {
                std::cout << "Thread function object executing: " << i << std::endl;
            }
        }
    };

    // b) Create an active object based on a thread with no associated thread function.
    // I am not quite sure what the exercise means by this to be honest. If there is no
    // associated thread function, this means that the input has no function. But then
    // later in part c), the exercise wants me to initialize the Active Object with 
    // function object or lambda function.
    //
    // I am just gonna do both of them.
    class ActiveObject {
    private:
        std::thread m_thread;

    public:
        // Constructor accepting a thread function. If there is no input thread, just default to nothing.
        // We will achieve this by having two explicit constructors with different arguments.
        explicit ActiveObject() : m_thread(kDefaultThreadFunction) {
            std::cout << "ActiveObject: Thread started." << std::endl;
        }

        explicit ActiveObject(std::thread input_thread) : m_thread(std::move(input_thread)) {
            std::cout << "ActiveObject: Thread started." << std::endl;
        }

        // Destructor
        ~ActiveObject() {
            if (m_thread.joinable()) {
                m_thread.join();
                std::cout << "ActiveObject: Thread joined and destroyed." << std::endl;
            }
        }
    };
}

int main23() {
    // a) Create a thread and a function that will be its thread function.
    std::thread myThread(threadFunction);

    // c) Implement thread functions using function objects and lambda functions.
    // d) Test the code.
    
    // Test 1: Using default thread function.
    ActiveObject activeObj1;

    // Test 2: Using created thread function
    ActiveObject activeObj2(std::move(myThread));


    // Test 3: Using function object
    // Interesting. I am not quite sure what I did wrong here, 
    // as it doesn't seem to work for thread function object if I don't have std::move().
    // But if I include std::move in, then it doesn't seem to work.
    ActiveObject activeObj3(std::move(std::thread(ThreadFunctionObject())));

    // Test 4: Using lambda functions
    ActiveObject activeObj4(std::thread([]() {
        for (int i = 0; i < 30; ++i) {
            std::cout << "Lambda thread function executing: " << i << std::endl;
        }
        }));
    return 0;
}