/*
* Advanced C++ and Modern Design
* Level 5
* Author: Son Pham
* Homework 2 - 3, Exercise 1: Regex 101, regex_match()
*/
#include <iostream>
#include <regex>
#include <string>

namespace {
    void part_a() {
        std::cout << "Part a)" << std::endl;
        std::regex myReg("[a-z]*");
        std::regex myReg2("[a-z]+");

        std::string s1("aza");
        std::string s2("1");
        std::string s3("b");
        std::string s4("ZZ TOP");

        std::cout << std::boolalpha;
        std::cout << "s1 matches myReg: " << std::regex_match(s1, myReg)
            << std::endl; // true
        std::cout << "s2 matches myReg: " << std::regex_match(s2, myReg)
            << std::endl; // false
        std::cout << "s3 matches myReg: " << std::regex_match(s3, myReg)
            << std::endl; // true
        std::cout << "s4 matches myReg: " << std::regex_match(s4, myReg)
            << std::endl; // false

        std::cout << "s1 matches myReg2: " << std::regex_match(s1, myReg2)
            << std::endl; // true
        std::cout << "s2 matches myReg2: " << std::regex_match(s2, myReg2)
            << std::endl; // false
        std::cout << "s3 matches myReg2: " << std::regex_match(s3, myReg2)
            << std::endl; // true
        std::cout << "s4 matches myReg2: " << std::regex_match(s4, myReg2)
            << std::endl; // false
    }

    void part_b() {
        std::cout << "Part b)" << std::endl;
        std::regex myNumericReg("\\d{2}");

        std::string f("34");
        std::string s("345");

        std::cout << std::boolalpha;
        std::cout << "f matches myNumericReg: " << std::regex_match(f, myNumericReg)
            << std::endl; // true
        std::cout << "s matches myNumericReg: " << std::regex_match(s, myNumericReg)
            << std::endl; // false
    }

    void part_c() {
        std::cout << "Part c)" << std::endl;
        std::regex myAltReg("(new)|(delete)");

        std::string s4A("new");
        std::string s5("delete");
        std::string s6("malloc");

        std::cout << std::boolalpha;
        std::cout << "s4A matches myAltReg: " << std::regex_match(s4A, myAltReg)
            << std::endl; // true
        std::cout << "s5 matches myAltReg: " << std::regex_match(s5, myAltReg)
            << std::endl; // true
        std::cout << "s6 matches myAltReg: " << std::regex_match(s6, myAltReg)
            << std::endl; // false
    }

    void part_d() {
        std::cout << "Part d)" << std::endl;
        std::regex myReg3("A*");
        std::regex myReg4("A+");
        std::regex myReg5("(\\d{2})");
        std::regex myReg7("\\d{1,}");

        std::string testA("1");

        std::cout << std::boolalpha;
        std::cout << "testA matches myReg3: " << std::regex_match(testA, myReg3)
            << std::endl; // false
        std::cout << "testA matches myReg4: " << std::regex_match(testA, myReg4)
            << std::endl; // false
        std::cout << "testA matches myReg5: " << std::regex_match(testA, myReg5)
            << std::endl; // false
        std::cout << "testA matches myReg7: " << std::regex_match(testA, myReg7)
            << std::endl; // true
    }

    void part_e() {
        std::cout << "Part e)" << std::endl;
        std::regex rC("(\\w)*");
        std::regex rC1("(\\W)*");
        std::regex rC2("[A-Za-z0-9_]*");

        std::string sC1("abc");
        std::string sC2("A12678Z909za");

        std::cout << std::boolalpha;
        std::cout << "sC1 matches rC: " << std::regex_match(sC1, rC)
            << std::endl; // true
        std::cout << "sC1 matches rC1: " << std::regex_match(sC1, rC1)
            << std::endl; // false
        std::cout << "sC1 matches rC2: " << std::regex_match(sC1, rC2)
            << std::endl; // true

        std::cout << "sC2 matches rC: " << std::regex_match(sC2, rC)
            << std::endl; // true
        std::cout << "sC2 matches rC1: " << std::regex_match(sC2, rC1)
            << std::endl; // false
        std::cout << "sC2 matches rC2: " << std::regex_match(sC2, rC2)
            << std::endl; // true
    }
} // namespace

int main21() {
    part_a();
    part_b();
    part_c();
    part_d();
    part_e();
}