/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 1, Exercise 4: Synchronizing Queue
*/

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace {
    // a) SynchronizedQueue is the class that have a template parameter and functions for queing and dequeing
    template<typename T>
    class SynchronizedQueue {
    public:
        void Enqueue(const T& item) {
            // b) During enqueue, there is a simple lock to ensure safety
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(item);
            lock.unlock();
            condition_.notify_one();
        }

        T Dequeue() {
            // b) During enqueue, there is a simple lock to ensure safety
            std::unique_lock<std::mutex> lock(mutex_);
            condition_.wait(lock, [this] { return !queue_.empty(); });  // Condition to ensure dequeue gets executed only when it is not empty.
            T item = queue_.front();
            queue_.pop();
            return item;
        }

    private:
        std::queue<T> queue_;
        std::mutex mutex_;
        std::condition_variable condition_;
    };
}

int main14() {
    SynchronizedQueue<int> queue;

    // Producer thread
    std::thread producer([&queue]() {
        for (int i = 1; i <= 10; ++i) {
            std::cout << "Enqueue item: " << i << std::endl;
            queue.Enqueue(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        });

    // Consumer thread
    std::thread consumer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            int item = queue.Dequeue();
            std::cout << "Dequeued item: " << item << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        });

    producer.join();
    consumer.join();

    return 0;
}