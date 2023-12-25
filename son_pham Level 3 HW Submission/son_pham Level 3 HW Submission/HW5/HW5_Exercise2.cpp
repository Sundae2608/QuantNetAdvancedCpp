/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 2: Simple Single-Threaded Command Processor Pattern
*/

#include <iostream>
#include <queue>
#include <boost/thread/thread.hpp>
#include <functional>
#include <cmath>

namespace {
    using FunctionType = std::function<double(double)>;

    // Command class copied from the assignment
    class Command
    {
    private:
        long ID; // priority of command
        FunctionType algo;

    public:
        Command(const FunctionType& algorithm, long priority)
            : algo(algorithm), ID(priority) {}

        void Execute(double x) {
            // Introduce delay to simulate a heavy algorithm
            boost::this_thread::sleep(boost::posix_time::millisec(5000));
            std::cout << algo(x) << '\n';
        }

        int priority() const {
            return ID;
        }
    };

    // a) Create a comparator for Command to compare two of its instances.
    struct CommandComparator {
        bool operator()(const Command& lhs, const Command& rhs) const {
            return lhs.priority() > rhs.priority(); // Compare by priority in descending order
        }
    };
}

int main52() {
    // b) Create several instances of Command.
    // Define the functions for the commands
    FunctionType square = [](double x) { return x * x; };
    FunctionType cube = [](double x) { return x * x * x; };
    FunctionType squareRoot = [](double x) { return sqrt(x); };

    // Create instances of Command with different priorities
    Command command1(square, 3);
    Command command2(cube, 2);
    Command command3(squareRoot, 1);

    // c) Create a priority queue and insert the commands
    std::priority_queue<Command, std::vector<Command>, CommandComparator> pq;
    pq.push(command1);
    pq.push(command2);
    pq.push(command3);

    // d) Execute each command in the priority queue until it is empty
    while (!pq.empty()) {
        Command currentCommand = pq.top();
        currentCommand.Execute(5.0); // Example input value: 5.0
        pq.pop();
    }
    return 0;
}