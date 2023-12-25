/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 1: Priority Queue 101.
*/

#include <iostream>
#include <queue>

int main51() {
    // a) Create a priority queue whose elements are long long using the above default template parameters.In particular, perform the following :
    std::priority_queue<long long> pq;
   
    // Uncomment this for part b)
    // std::priority_queue<long long, std::deque<long long>, std::greater<long long>> pq;  

    // Uncomment the following code for part c
    // auto comparator = [](long long a, long long b) { return a > b; };
    // std::priority_queue<long long, std::deque<long long>, decltype(comparator)> pq(comparator);

    // Push values 66, 22, 44
    pq.push(66);
    pq.push(22);
    pq.push(44);

    // Print top element and then pop it
    std::cout << "Top element: " << pq.top() << std::endl;
    pq.pop();

    // Push values 11, 22, 33
    pq.push(11);
    pq.push(22);
    pq.push(33);

    // Pop an element
    pq.pop();

    // Iterate in the priority queue until it is empty
    while (!pq.empty()) {
        std::cout << "Top element: " << pq.top() << std::endl;
        pq.pop();
    }

    // The code returns the following prints
    // Top element: 66
    // Top element: 33
    // Top element: 22
    // Top element: 22
    // Top element: 11
    // This makes sense. After we popped the first element and print out 66, the next
    // biggest element was 44, which was popped out without reprinting.
    
    // b) Create a priority queue whose elements are long long whose container is
    // std::deque and whose comparator is std::greater<long long>. Test this case
    // with the data in part a) of the exercise. Inspect the output.
    //
    // I added the code right below the pq initialization of part a. Simply uncomment
    // it to run the code.
    // I got the following prints
    // Top element : 22
    // Top element : 22
    // Top element : 33
    // Top element : 44
    // Top element : 66
    // Basically the queue reverses the ordering. This makes sense.  The first element
    // to be popped and printed is 22. The element was popped and not printed is 11.
    
    // c) Modify the code in part b) to use a lambda function instead of 
    // std::greater<long long>. Inspect the output. I added the code for part c) right below
    // part b). Simply uncomment to run the code.
    // I got the following prints
    // Top element : 22
    // Top element : 22
    // Top element : 33
    // Top element : 44
    // Top element : 66
    return 0;
}