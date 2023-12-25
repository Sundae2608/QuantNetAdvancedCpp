/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 9, Exercise 1
*/

#include <iostream>
#include <boost/signals2.hpp>

namespace {
    struct MyStruct {
        double val;

        MyStruct(double v) : val(v) {}

        void modify(double newValue) {
            val = newValue;
            std::cout << "A third slot " << val << std::endl;
        }
    };

    void FreeFunctionSlot() {
        std::cout << "Free function slot called\n";
    }

    struct FunctionObjectSlot {
        void operator()() const {
            std::cout << "Function object slot called\n";
        }
    };
}

int main91() {
    // a) Create a signal and create slots using lambda functions, free functions and function objects. 
    // Connect the slots to the signal and emit the signal. Examine the output.
    boost::signals2::signal<void()> signal;

    // Connect slots
    auto connection1 = signal.connect([]() { std::cout << "Lambda function slot called\n"; });
    auto connection2 = signal.connect(&FreeFunctionSlot);
    auto connection3 = signal.connect(FunctionObjectSlot());

    // Emit the signal
    signal();

    // Output is the following:
    // Lambda function slot called
    // Free function slot called
    // Function object slot called
    // Quite straight forward the all the functions were called.

    // Create an instance of this class and create a slot based on modify() whose argument is equal to some value. 
    // Add this slot to the signal and then emit the signal.
    MyStruct myInstance(42.0);

    // Connect slot based on modify()
    auto connection4 = signal.connect(boost::bind(&MyStruct::modify, &myInstance, 24.0));

    // Emit the signal
    signal();

    // Output is the following:
    // Lambda function slot called
    // Free function slot called
    // Function object slot called
    // A third slot 24

    // c) Experiment with disconnecting slots in your code.
    // Disconnect slot 2 and slot 3
    connection2.disconnect();
    connection3.disconnect();

    // Emit the signal
    signal();

    // Output is the following:
    // Lambda function slot called
    // A third slot 24
    // Basically, the middle 2 slots were disconnected

    // d) Signals hierarchy
    boost::signals2::signal<void()> signalA;
    boost::signals2::signal<void()> signalB;
    boost::signals2::signal<void()> signalC;
    boost::signals2::signal<void()> signalD;

    auto slotB = []() { std::cout << "Slot B called by B\n"; };
    auto slotC = []() { std::cout << "Slot C called by C\n"; };
    auto slotD1 = []() { std::cout << "Slot D1 called by D\n"; };
    auto slotD2 = []() { std::cout << "Slot D2 called by D\n"; };

    // Connect Slot B to Signal B
    signalB.connect(slotB);

    // Connect Slot C to Signal C
    signalC.connect(slotC);

    // Connect Slot D1 to Signal D
    signalD.connect(slotD1);

    // Connect Slot D2 to Signal D
    signalD.connect(slotD2);

    // Connect Signal B to Signal A
    signalA.connect(signalB);

    // Connect Signal C to Signal B
    boost::signals2::connection connectionCtoB = signalB.connect(signalC);

    // Connect Signal D to Signal C
    signalC.connect(signalD);

    // Emit Signal A
    std::cout << "Emitting signal A:" << std::endl;
    signalA();

    // Emitting signal A:
    // Slot B called by B
    // Slot C called by C
    // Slot D1 called by D
    // Slot D2 called by D

    // Examine what happens when you try to disconnect signal C from signal B.
    // Is it possible or do you have to first disconnect the terminal slot?
    // Disconnect Signal C from Signal B
    connectionCtoB.disconnect();

    // Emit Signal A again
    std::cout << "Emitting signal A after disconnecting signal C from signal B:" << std::endl;
    signalA();

    // Slot B called by B
    // Yes, no need to disconnect the termimal slot. The trees are basically cut, and only
    // the SignalB calling SlotB is left.
    return 0;
}