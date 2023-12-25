/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 1, Exercise 5: Atomics and Atomic Operations
*/

#include <atomic>
#include <iostream>

int main15() {
	// a) Create atomic objects of type long long, bool and int.
	std::atomic<long long> atomic_long_long;
	std::atomic<bool> atomic_bool;
	std::atomic<int> atomic_int;

	// b) Determine which atomic types are lock-free.
	// To determine whether an atomic type is lock-free, 
	// you can use the std::atomic<T>::is_lock_free() member function. 
	// It returns true if atomic operations on the specified type T are lock-free, and false otherwise.
	std::cout << "Part b)" << std::endl;
	std::cout << std::boolalpha;
	std::cout << "Atomic int is lock-free: " << atomic_long_long.is_lock_free() << std::endl;
	std::cout << "Atomic long long is lock-free: " << atomic_bool.is_lock_free() << std::endl;
	std::cout << "Atomic long long is lock-free: " << atomic_int.is_lock_free() << std::endl;

	// c) Atomically replace the value of one atomic object by another atomic object.
	std::cout << "Part c)" << std::endl;
	std::atomic<int> atomic_int_1(10);
	std::atomic<int> atomic_int_2(20);
	int previous_value = atomic_int_1.exchange(atomic_int_2.load());
	std::cout << "Previous value of atomic_int: " << previous_value << std::endl;
	std::cout << "New atomic_int_1: " << atomic_int_1 << std::endl;

	// d) Atomically load an atomic object and return its current value.
	std::cout << "Part d)" << std::endl;
	int currentValue = atomic_int_1.load();
	std::cout << "Current value of atomicInt: " << currentValue << std::endl;  // 20, since atomic_int_1 is 20 by this point
	return 0;
}