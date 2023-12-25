/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 9, Exercise 5
*/

#include <iostream>
#include <boost/signals2.hpp>

namespace {
    // a) Reprogramed Subject class
    class Subject {
    private:
        boost::signals2::signal<void(double)> attentionList;

    public:
        void AddObserver(const boost::signals2::slot<void(double)>& slot) {
            attentionList.connect(slot);
        }

        void ChangeEvent(double x) {
            attentionList(x);
        }
    };

    void CPrint(double x) {
        std::cout << "C function: " << x << std::endl;
    }

    struct Print {
        void operator()(double x) {
            std::cout << "I am a printer " << x << std::endl;
        }
    };

    // MathsWhiz and database
    struct MathsWhiz {
        double factor;

        MathsWhiz(double f) : factor(f) {}

        void operator()(double x) {
            double result = x * factor;
            std::cout << "Maths result: " << result << std::endl;
        }
    };

    struct Database {
        void operator()(double x) {
            // Simulate storing data in a database
            std::cout << "Storing data: " << x << " in the database" << std::endl;
        }
    };
}

int main95() {
    Subject mySubject;

    Print myPrint;
    MathsWhiz myMaths(2.0);
    Database myDatabase;

    mySubject.AddObserver(myPrint);
    mySubject.AddObserver(myMaths);
    mySubject.AddObserver(myDatabase);
    mySubject.AddObserver(&CPrint);

    double val;
    std::cout << "Give the value: ";
    std::cin >> val;
    mySubject.ChangeEvent(val);

    // When I give the value 5, it shows the following:
    // Give the value : 10
    // I am a printer 10
    // Maths result : 20
    // Storing data : 10 in the database
    // C function : 10
    return 0;
}