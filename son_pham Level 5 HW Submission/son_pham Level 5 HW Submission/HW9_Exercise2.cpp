/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 9, Exercise 2
*/

#include <iostream>
#include <boost/signals2.hpp>

int main92() {
    // a) Modify the code in exercise 1 by placing each slot in its own group.
    boost::signals2::signal<void()> signalA;
    boost::signals2::signal<void()> signalB;
    boost::signals2::signal<void()> signalC;
    boost::signals2::signal<void()> signalD;

    auto slotB = []() { std::cout << "Slot B called by B\n"; };
    auto slotC = []() { std::cout << "Slot C called by C\n"; };
    auto slotD1 = []() { std::cout << "Slot D1 called by D\n"; };
    auto slotD2 = []() { std::cout << "Slot D2 called by D\n"; };

    // Connect Slot B to Signal B
    signalB.connect(0, slotB);

    // Connect Slot C to Signal C
    signalC.connect(1, slotC);

    // Connect Slot D1 to Signal D
    signalD.connect(3, slotD1);

    // Connect Slot D2 to Signal D
    signalD.connect(2, slotD2);

    // Connect Signal B to Signal A
    signalA.connect(signalB);

    // Connect Signal C to Signal B
    boost::signals2::connection connectionCtoB = signalB.connect(signalC);

    // Connect Signal D to Signal C
    signalC.connect(signalD);

    // Emit Signal A
    std::cout << "Emitting signal A:" << std::endl;
    signalA();

    // Disconnect C to B
    connectionCtoB.disconnect();

    // Emit Signal A again
    std::cout << "Emitting signal A after disconnecting signal C from signal B:" << std::endl;
    signalA();

    // b) Run the program and examine the output.
    // Hierarchy is still respected, but flipping the ordering of D1 and D2 allows D2 to be connected first.
    // Emitting signal A :
    // Slot B called by B
    // Slot C called by C
    // Slot D2 called by D
    // Slot D1 called by D
    return 0;
}