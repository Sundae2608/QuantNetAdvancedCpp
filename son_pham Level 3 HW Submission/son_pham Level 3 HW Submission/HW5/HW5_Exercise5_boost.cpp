/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 5: Producer-Consumer Pattern (Boost)
*/

#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <queue>
#include <functional>

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

    using FunctionType = std::function<double(double)>;

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
            boost::this_thread::sleep(boost::posix_time::millisec(500));
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
    void consumeCommands(SynchronizingQueue<Command>& commandQueue) {
        while (true) {

            Command cmd = commandQueue.dequeue();
            if (dynamic_cast<EndCommand*>(&cmd) != nullptr) {
                // End of input signal received, stop processing
                break;
            }

            cmd.Execute(5.0); // Replace 5.0 with any desired input for the command function
        }
    }
}

int main55_boost() {

    // Create a queue to hold the commands
    SynchronizingQueue<Command> commandQueue;

    // Create Boost thread group for producers
    boost::thread_group producers;

    // Add commands to the thread group for producers
    producers.create_thread([&commandQueue]() {
        commandQueue.enqueue(Command([](double x) { return x * x; }, 3));
        commandQueue.enqueue(Command([](double x) { return x * x * x; }, 1));
        commandQueue.enqueue(Command([](double x) { return x + x; }, 2));

        commandQueue.enqueue(Command([](double x) { return x * x; }, 3));
        commandQueue.enqueue(Command([](double x) { return x * x * x; }, 1));
        commandQueue.enqueue(Command([](double x) { return x + x; }, 2));

        commandQueue.enqueue(Command([](double x) { return x * x; }, 3));
        commandQueue.enqueue(Command([](double x) { return x * x * x; }, 1));
        commandQueue.enqueue(Command([](double x) { return x + x; }, 2));
        // Add the EndCommand to signal the end of input
        commandQueue.enqueue(EndCommand());
        });

    // Create Boost thread group for consumers
    boost::thread_group consumers;

    // Add commands to the thread group for consumers
    for (int i = 0; i < 2; ++i) {
        consumers.create_thread(boost::bind(&consumeCommands, boost::ref(commandQueue)));
    }

    // Start the application
    producers.join_all();
    consumers.join_all();

    // TODO: For some reason, this version of the code aborts. I am not sure what is the reason for this.

    return 0;
}