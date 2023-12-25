/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 2, Exercise 5: Barbershop Problem
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>

namespace {
    class Producer {
    public:
        Producer(std::queue<int>& waitingRoom, std::condition_variable& cv)
            : waitingRoom(waitingRoom), cv(cv) {}

        void run() {
            while (true) {
                // To make it easier to test, I will 
                std::this_thread::sleep_for(std::chrono::seconds(3)); // New customer arrives every 3 seconds
                produce();
            }
        }

        void produce() {
            if (waitingRoom.size() < nChairs) {
                waitingRoom.push(1); // New customer occupies a free chair
                std::cout << "A customer arrived. Total customers waiting: " << waitingRoom.size() << std::endl;
                cv.notify_one(); // Notify the barber that there's a customer waiting
            }
            else {
                std::cout << "The waiting room is full. Customer left without service." << std::endl;
            }
        }

    private:
        std::queue<int>& waitingRoom;
        std::condition_variable& cv;
        const int nChairs = 5; // Total number of chairs in the waiting room
    };

    class Consumer {
    public:
        Consumer(std::queue<int>& waitingRoom, std::mutex& mtx, std::condition_variable& cv)
            : waitingRoom(waitingRoom), mtx(mtx), cv(cv) {}

        void run() {
            while (true) {
                consume();
            }
        }

        void consume() {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !waitingRoom.empty(); }); // Wait until there's a customer in the waiting room

            int customerId = waitingRoom.front();
            waitingRoom.pop(); // Customer leaves the waiting room as they are getting service
            std::cout << "Barber is serving customer " << customerId << ". Total customers waiting: " << waitingRoom.size() << std::endl;

            // Simulate the time it takes to serve the customer
            int serviceTime = getRandomServiceTime();
            std::this_thread::sleep_for(std::chrono::seconds(serviceTime));

            std::cout << "Barber finished serving customer " << customerId << ". Total customers waiting: " << waitingRoom.size() << std::endl;
        }

    private:
        std::queue<int>& waitingRoom;
        std::mutex& mtx;
        std::condition_variable& cv;

        // Helper function to generate a random service time (between 4 and 8 seconds)
        int getRandomServiceTime() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<int> distribution(4, 8);
            return distribution(gen);
        }
    };
}

int main25() {
    std::queue<int> waitingRoom; // Shared waiting room queue
    std::mutex mtx;              // Mutex to synchronize access to the waiting room
    std::condition_variable cv;  // Condition variable for synchronization

    Producer producer(waitingRoom, cv);
    Consumer consumer(waitingRoom, mtx, cv);

    // Start the producer and consumer threads
    std::thread producerThread(&Producer::run, &producer);
    std::thread consumerThread(&Consumer::run, &consumer);

    // Wait for the producer and consumer threads to finish (this will not happen in this example)
    producerThread.join();
    consumerThread.join();
    return 0;

}