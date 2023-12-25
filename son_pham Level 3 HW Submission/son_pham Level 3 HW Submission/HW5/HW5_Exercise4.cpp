/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 4: Synchronizing Queue
*/

#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>

namespace {
    template <typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
    class SynchronizingQueue {
    public:
        SynchronizingQueue() = default;

        // Part a) Functions for equeneing and dequeing.
        void enqueue(const T& item) {
            // Locking mechanism so that only either enqueue or deque is done at once.
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(item);
            lock.unlock();
            // Thread notification mechanism
            condition_.notify_one();
        }

        T dequeue() {
            std::unique_lock<std::mutex> lock(mutex_);
            while (queue_.empty()) {
                condition_.wait(lock);
            }
            T item = queue_.top();
            queue_.pop();
            return item;
        }

        bool empty() const {
            std::unique_lock<std::mutex> lock(mutex_);
            return queue_.empty();
        }

        std::size_t size() const {
            std::unique_lock<std::mutex> lock(mutex_);
            return queue_.size();
        }

    private:
        std::priority_queue<T, Container, Compare> queue_;
        mutable std::mutex mutex_;
        std::condition_variable condition_;
    };
}

int main54() {
    SynchronizingQueue<int> queue;

    // Enqueue elements using multiple threads
    std::thread producer1([&queue]() {
        for (int i = 0; i < 5; ++i) {
            queue.enqueue(i);
        }
        });

    std::thread producer2([&queue]() {
        for (int i = 5; i < 10; ++i) {
            queue.enqueue(i);
        }
        });

    producer1.join();
    producer2.join();

    // Dequeue elements using multiple threads
    std::thread consumer([&queue]() {
        while (!queue.empty()) {
            int item = queue.dequeue();
            std::cout << "Consumer dequeued: " << item << std::endl;
        }
        });

    consumer.join();

    return 0;
}