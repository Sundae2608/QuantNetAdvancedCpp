/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 9, Exercise 6
*/

#include <iostream>
#include <boost/signals2.hpp>

namespace {
    // Layer: Hardware
    void SlotHardware(double& d) {
        if (d < 2.0 || d > 4.0) {
            d = 3.0; // Set to the value 3 if not in range [2, 4]
        }
    }

    // Layer: Data
    void SlotData(double& d) {
        d = d * 2; // Modify data by an algorithm (multiply by 2)
    }

    // Layer: Communication
    void SlotCommunication(double& d) {
        std::cout << "Formatted and printed data: " << d << std::endl;
    }
}

int main96() {
    boost::signals2::signal<void(double&)> signalExterior;
    boost::signals2::signal<void(double&)> signalHardware;
    boost::signals2::signal<void(double&)> signalData;
    boost::signals2::signal<void(double&)> signalCommunication;

    // Connect the signals to slots
    signalExterior.connect(&SlotHardware);
    signalHardware.connect(&SlotData);
    signalData.connect(&SlotCommunication);

    signalExterior.connect(signalHardware);
    signalHardware.connect(signalData);
    signalData.connect(signalCommunication);

    // Initialize data and trigger the chain
    double value = -3.7; // in range [2.0, 5.0]
    signalExterior(value);
    std::cout << std::endl;

    // Formatted and printed data: 6
    // Make sense. -3.7 is out of bound of 2.0 and 4.0, so it returns 3
    // and then we double it which makes it 6.
    return 0;
}
