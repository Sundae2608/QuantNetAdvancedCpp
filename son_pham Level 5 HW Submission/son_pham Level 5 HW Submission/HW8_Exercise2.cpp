/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 8, Exercise 1
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

namespace {
    template <typename T, typename Container, typename Compare>
    void printPriorityQueue(const std::string& description,
        const std::priority_queue<T, Container, Compare>& pq) {
        std::cout << description << ": ";
        std::priority_queue<T, Container, Compare> pqCopy = pq;
        while (!pqCopy.empty()) {
            std::cout << pqCopy.top() << " ";
            pqCopy.pop();
        }
        std::cout << std::endl;
    }
} // namespace

int main() {
    // a) Create a default priority queue of integers with elements
    // {10,5,20,30,25,7,40}. Print the queue.
    std::priority_queue<int> pq1;
    pq1.push(10);
    pq1.push(5);
    pq1.push(20);
    pq1.push(30);
    pq1.push(25);
    pq1.push(7);
    pq1.push(40);
    printPriorityQueue("a - Default priority queue", pq1);

    // b) Modify the queue in part a) using std::greater<int> as comparator
    // function. Print the queue.
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq2;
    pq2.push(10);
    pq2.push(5);
    pq2.push(20);
    pq2.push(30);
    pq2.push(25);
    pq2.push(7);
    pq2.push(40);
    printPriorityQueue("b - Priority queue with std::greater<int>", pq2);

    // c) Create a priority queue using an underlying data container and the
    // following lambda function as comparator:
    auto cmp = [](int left, int right) -> bool { return left > right; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq3(cmp);
    pq3.push(10);
    pq3.push(5);
    pq3.push(20);
    pq3.push(30);
    pq3.push(25);
    pq3.push(7);
    pq3.push(40);
    printPriorityQueue("c - Priority queue with custom comparator", pq3);
}