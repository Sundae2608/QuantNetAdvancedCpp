/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 4, Exercise 4: Variadic Hash
*/

#include <iostream>
#include <unordered_set>

template <typename Key, typename Hash, typename EqPred>
void BucketInformation(const std::unordered_set<Key, Hash, EqPred>& c) {
    std::cout << "Number of buckets: " << c.bucket_count() << std::endl;
    std::cout << "Maximum possible buckets: " << c.max_bucket_count() << std::endl;

    std::cout << "Current load factor: " << c.load_factor() << std::endl;
    std::cout << "Current maximum load factor: " << c.max_load_factor() << std::endl;

    std::cout << "Size of each bucket:" << std::endl;
    for (std::size_t i = 0; i < c.bucket_count(); ++i) {
        std::cout << "Bucket " << i << ": " << c.bucket_size(i) << std::endl;
    }
}

int main45() {
    std::unordered_set<int> mySet = { 1, 2, 3, 4, 5 };
    BucketInformation(mySet);

    // Rehash the container
    mySet.rehash(10);
    std::cout << "Bucket information after rehash:" << std::endl;
    BucketInformation(mySet);

    // Printing information
    // Number of buckets : 8
    // Maximum possible buckets : 1152921504606846975
    // Current load factor : 0.625
    // Current maximum load factor : 1
    // Size of each bucket :
    // Bucket 0 : 1
    // Bucket 1 : 1
    // Bucket 2 : 0
    // Bucket 3 : 0
    // Bucket 4 : 1
    // Bucket 5 : 0
    // Bucket 6 : 1
    // Bucket 7 : 1
    // Bucket information after rehash :
    // Number of buckets : 16
    // Maximum possible buckets : 1152921504606846975
    // Current load factor : 0.3125
    // Current maximum load factor : 1
    // Size of each bucket :
    // Bucket 0 : 1
    // Bucket 1 : 1
    // Bucket 2 : 0
    // Bucket 3 : 0
    // Bucket 4 : 1
    // Bucket 5 : 0
    // Bucket 6 : 1
    // Bucket 7 : 1
    // Bucket 8 : 0
    // Bucket 9 : 0
    // Bucket 10 : 0
    // Bucket 11 : 0
    // Bucket 12 : 0
    // Bucket 13 : 0
    // Bucket 14 : 0
    // Bucket 15 : 0

    return 0;
}