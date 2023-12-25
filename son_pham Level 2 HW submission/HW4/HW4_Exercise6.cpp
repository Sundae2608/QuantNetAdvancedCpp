/*
* Advanced C++ and Modern Design
* Level 2
* Author: Son Pham
* Homework 4, Exercise 6: Weak Pointers
*/

#include <iostream>
#include <memory>

int main46() {
    // a) Create a shared pointer, print the use count and then create a weak pointer that observes it.
    // Print the use count again. What are the values?
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(42);
    std::cout << "Shared pointer use count: " << sharedPtr.use_count() << std::endl;  // 1
    std::weak_ptr<int> weakPtr = sharedPtr;
    std::cout << "Shared pointer use count after creating weak pointer: " << sharedPtr.use_count() << std::endl;  
    // Still 1, because weakPtr doesn't share the ownership

    // b) Assign a weak pointer to a shared pointer and check that the weak pointer is not empty.
    std::shared_ptr<int> assignedSharedPtr = weakPtr.lock();
    if (assignedSharedPtr) {
        std::cout << "Weak pointer successfully assigned to shared pointer." << std::endl;
    }
    if (!weakPtr.expired()) {
        std::cout << "Weak pointer not empty" << std::endl;
    }
    else {
        std::cout << "Weak pointer empty" << std::endl;
    }
    // "Weak pointer not empty" was printed, so the weak pointer was not empty
    std::cout << "Shared pointer use count after assigning weak ptr to shared ptr: " << sharedPtr.use_count() << std::endl;  // 2
    // Notice that the count is 2, because weakPtr previously refers to the SharedPtr. The assignment actually adds an
    // extra ownership.

    // c) Assign a weak pointer to another weak pointer; assign a weak pointer to shared pointer.
    // What is the use count in both cases?
    // We already assign a weak pointer to a shared pointer and observe the count increase.
    // Now, let's test assigning a weak pointer to a weak pointer.
    std::weak_ptr<int> weakPtr2 = weakPtr;
    std::cout << "Shared pointer use count after assigning weak ptr to weak ptr: " << sharedPtr.use_count() << std::endl;  // 2
    // Looks like assigning weakptr around does nothing to the ownership count.
    return 0;
}