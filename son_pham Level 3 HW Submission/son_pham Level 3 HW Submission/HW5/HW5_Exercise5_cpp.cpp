/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 5: Producer-Consumer Pattern (C++ version)
*/

#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>

namespace {
    using FunctionType = std::function<double(double)>;

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

    class Command
    {
    private:
        long ID; // priority of command
        FunctionType algo;

    public:
        Command(const FunctionType& algorithm, long priority)
            : algo(algorithm), ID(priority) {}

        virtual ~Command() {}

        void Execute(double x) {
            // Introduce delay to simulate a heavy algorithm
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << algo(x) << '\n';
        }

        int priority() const {
            return ID;
        }

        // Overload the less-than operator to compare based on priority
        bool operator<(const Command& other) const {
            return ID > other.ID;
        }
    };

    // Special command object to signal the end of input
    class EndCommand : public Command
    {
    public:
        EndCommand() : Command(nullptr, -1) {} // Priority set to -1 to ensure it's processed last
    };

    // Function to be executed by consumers
    void consumeCommands(SynchronizingQueue<Command>& commandQueue, std::condition_variable& cv, std::mutex& mtx) {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&]() { return !commandQueue.empty(); });

            if (commandQueue.empty()) {
                // End of input signal received, stop processing
                break;
            }

            Command cmd = commandQueue.dequeue();
            lock.unlock();

            if (dynamic_cast<EndCommand*>(&cmd) != nullptr) {
                // End of input signal received, stop processing
                break;
            }

            cmd.Execute(5.0); // Replace 5.0 with any desired input for the command function
        }
    }
}


int main55_cpp() {
    // Create a queue to hold the commands
    SynchronizingQueue<Command> commandQueue;

    // Create threads for producers
    std::thread producerThread([&commandQueue]() {
        commandQueue.enqueue(Command([](double x) { return x * x; }, 3));
        commandQueue.enqueue(Command([](double x) { return x * x * x; }, 1));
        commandQueue.enqueue(Command([](double x) { return x + x; }, 2));
        // Add the EndCommand to signal the end of input
        commandQueue.enqueue(EndCommand());
        });

    // Create threads for consumers
    std::vector<std::thread> consumerThreads;
    std::mutex mtx;
    std::condition_variable cv;
    for (int i = 0; i < 2; ++i) {
        consumerThreads.emplace_back(consumeCommands, std::ref(commandQueue), std::ref(cv), std::ref(mtx));
    }

    // Start the application
    producerThread.join();
    cv.notify_all();
    for (auto& thread : consumerThreads) {
        thread.join();
    }

    // TODO: For some reason, there is some aborting action here.
    // It is best to refer to the previous Producer - Consumer pattern that I have successfully coded before, but let's do that later.
    return 0;
}