/*
* Advanced C++ and Modern Design
* Level 3
* Author: Son Pham
* Homework 5, Exercise 3: Forward List 101
*/

#include <iostream>
#include <forward_list>
#include <iterator>

namespace {
    template<typename T>
    std::size_t forwardListSize(const std::forward_list<T>& flist) {
        return std::distance(flist.begin(), flist.end());
    }

    template<typename T>
    void eraseAfter(std::forward_list<T>& flist, typename std::forward_list<T>::iterator pos) {
        if (pos != flist.end()) {
            flist.erase_after(pos);
        }
    }

    template<typename T>
    void eraseRange(std::forward_list<T>& flist, typename std::forward_list<T>::iterator first,
        typename std::forward_list<T>::iterator last) {
        if (first != flist.end() && last != flist.end()) {
            flist.erase_after(first, last);
        }
    }

    template<typename T>
    void printForwardList(const std::forward_list<T>& flist) {
        for (const T& element : flist) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main53() {
    // a) Create default list, a list with n elements and a given value,
    // and a list that is built from an initialiser list (two forms).
    
    // Create default list
    std::forward_list<int> defaultList;

    // Create a list with n elements and a given value
    int n = 5; // Number of elements
    int value = 42; // Value for all elements
    std::forward_list<int> nElementsList(n, value);

    // Create a list that is built from an initializer list (two forms)
    std::forward_list<int> initializerList1 = { 1, 2, 3, 4, 5 };
    std::forward_list<int> initializerList2{ 10, 20, 30, 40, 50 };

    // b) Forward lists have no member functions to give their size. 
    // Write you own function in terms of std::distance().
    std::cout << "Forward list size: " << forwardListSize(initializerList1) << std::endl;

    // c) Create code to insert values after a given position based on value,
    // value and a count, two iterators and initialiser list. The code makes
    // direct calls to std::forward_list::insert_after.
    std::forward_list<int> myForwardList = { 1, 2, 3, 4, 5 };

    // Insert value 10 after the first element
    myForwardList.insert_after(myForwardList.before_begin(), 10);

    // Insert three occurrences of value 20 after the second element
    myForwardList.insert_after(std::next(myForwardList.begin(), 1), 3, 20);

    // Create another forward list and insert its elements after the third element
    std::forward_list<int> otherList = { 100, 200, 300 };
    myForwardList.insert_after(std::next(myForwardList.begin(), 2), otherList.begin(), otherList.end());

    // Insert elements from an initializer list after the fourth element
    myForwardList.insert_after(std::next(myForwardList.begin(), 3), { 1000, 2000, 3000 });

    // d) Create functions to erase values after a given position as well as in a range of iterators.
    // Erase element after the first element
    eraseAfter(myForwardList, myForwardList.before_begin());

    // Erase elements between the second and fourth elements
    eraseRange(myForwardList, std::next(myForwardList.begin(), 1), std::next(myForwardList.begin(), 4));

    // e) Create examples to show how splice and merge functionality work.
    std::forward_list<int> list1 = { 1, 2, 3 };
    std::forward_list<int> list2 = { 10, 20, 30 };

    // Splice list2 after the second element of list1
    list1.splice_after(std::next(list1.begin(), 1), list2);

    std::cout << "List1 after splice: ";
    printForwardList(list1);
 
    // Merge both lists in ascending order (lists need to be sorted)
    list1.sort();
    list2.sort();
    list1.merge(list2);

    std::cout << "List1 after merge: ";
    printForwardList(list1);

    return 0;
}