/*
* Advanced C++ and Modern Design
* Level 4
* Author: Son Pham
* Homework 1, Exercise 1: Adapter Classes for Bitsets
*/

#include <iostream>
#include <bitset>

namespace {
    int booleanValuePermutations[][3] = {
        {false, false, false},
        {false, false, true},
        {false, true, false},
        {false, true, true},
        {true, false, false},
        {true, false, true},
        {true, true, false},
        {true, true, true}
    };

    class Proposition
    {
    private:
        std::bitset<1> data;

    public:
        // a) Create the following constructors: default, bool as argument and a std::bitset<1> as argument.
        // These are the constructors required by the assignments.
        Proposition() : data(0) {}
        Proposition(bool value) : data(value) {}
        Proposition(std::bitset<1> value) : data(value) {}

        // Boolean operators as member functions
        Proposition operator==(const Proposition& other) const { return Proposition(data == other.data); }
        Proposition operator!=(const Proposition& other) const { return Proposition(data != other.data); }
        Proposition operator&(const Proposition& other) const { return Proposition(data & other.data); }
        Proposition operator|(const Proposition& other) const { return Proposition(data | other.data); }
        Proposition operator^(const Proposition& other) const { return Proposition(data ^ other.data); }
        Proposition operator!() const { return Proposition(~data); }

        // Friend functions for conditional and biconditional
        friend Proposition operator%(const Proposition& lhs, const Proposition& rhs); // Conditional
        friend Proposition operator<(const Proposition& lhs, const Proposition& rhs); // Biconditional

        // Conversion to bool
        operator bool() const { return data.test(0); }
    };

    // Conditional (->) as non-member friend function
    Proposition operator%(const Proposition& lhs, const Proposition& rhs)
    {
        return Proposition(!lhs.data.test(0) || rhs.data.test(0));
    }

    // Biconditional (<->) as non-member friend function
    Proposition operator<(const Proposition& lhs, const Proposition& rhs)
    {
        return Proposition((lhs % rhs).data.test(0) && (rhs % lhs).data.test(0));
    }

    // Test the operators
    void testOperators()
    {
        Proposition A(true);
        Proposition B(true);
        Proposition C(false);

        std::cout << "A == B: " << (A == B) << std::endl;
        std::cout << "A != B: " << (A != B) << std::endl;
        std::cout << "A & B: " << (A & B) << std::endl;
        std::cout << "A | B: " << (A | B) << std::endl;
        std::cout << "A ^ B: " << (A ^ B) << std::endl;
        std::cout << "!A: " << !A << std::endl;

        std::cout << "(A -> B): " << (A % B) << std::endl;
        std::cout << "(B -> C): " << (B % C) << std::endl;
        std::cout << "(A <-> B): " << (A < B) << std::endl;
    }

    // c) Check that your code satisfies De Morgan’s Laws:
    // NOT(A OR B) == NOT(A) AND NOT(B)
    // NOT(A AND B) == NOT(A) OR NOT(B).
    void checkDeMorgansLaws()
    {
        bool deMorganLaw1 = true;
        for (int i = 0; i < 8; ++i) {
            bool A_val = booleanValuePermutations[i][0];
            bool B_val = booleanValuePermutations[i][1];
            bool C_val = booleanValuePermutations[i][2];

            Proposition A(A_val);
            Proposition B(B_val);
            Proposition C(C_val);

            // NOT (A OR B) == NOT(A) AND NOT(B)
            Proposition leftSide = !(A | B);
            Proposition rightSide = (!A & !B);
            deMorganLaw1 &= (leftSide == rightSide);
        }
        std::cout << "De Morgan's Law 1: " << deMorganLaw1 << std::endl;

        bool deMorganLaw2 = true;
        for (int i = 0; i < 8; ++i) {
            bool A_val = booleanValuePermutations[i][0];
            bool B_val = booleanValuePermutations[i][1];
            bool C_val = booleanValuePermutations[i][2];

            Proposition A(A_val);
            Proposition B(B_val);
            Proposition C(C_val);

            // NOT (A AND B) == NOT(A) OR NOT(B)
            Proposition leftSide = !(A & B);
            Proposition rightSide = (!A | !B);
            deMorganLaw2 &= (leftSide == rightSide);
        }
        std::cout << "De Morgan's Law 2: " << deMorganLaw2 << std::endl;
    }

    // d) Check that your code satisfies the Distributive Laws:
    // A AND(B OR C) == (A AND B) OR(A OR C)
    // A OR(B AND C) == (A OR B) AND(A OR C).
    void checkDistributiveLaws()
    {
        bool distributiveLaw1 = true;
        for (int i = 0; i < 8; ++i) {
            bool A_val = booleanValuePermutations[i][0];
            bool B_val = booleanValuePermutations[i][1];
            bool C_val = booleanValuePermutations[i][2];

            Proposition A(A_val);
            Proposition B(B_val);
            Proposition C(C_val);

            // A AND(B OR C) == (A AND B) OR (A OR C)
            Proposition leftSide = A & (B | C);
            Proposition rightSide = (A & B) | (A & C);
            distributiveLaw1 &= (leftSide == rightSide);
        }
        std::cout << "Distributive Law 1: " << distributiveLaw1 << std::endl;

        bool distributiveLaw2 = true;
        for (int i = 0; i < 8; ++i) {
            bool A_val = booleanValuePermutations[i][0];
            bool B_val = booleanValuePermutations[i][1];
            bool C_val = booleanValuePermutations[i][2];

            Proposition A(A_val);
            Proposition B(B_val);
            Proposition C(C_val);

            // A OR(B AND C) == (A OR B) AND (A OR C)
            Proposition leftSide = A | (B & C);
            Proposition rightSide = (A | B) & (A | C);
            distributiveLaw2 &= (leftSide == rightSide);
        }
        std::cout << "Distributive Law 2: " << distributiveLaw2 << std::endl;
    }

    // e) Let A, B and C be propositions. Check that the statement form:
    // [A -> (B->C)] < ->[(A & B)->C]
    // Is a tautology
    void checkTautology()
    {
        bool tautologyTest = true;
        for (int i = 0; i < 8; ++i) {
            bool A_val = booleanValuePermutations[i][0];
            bool B_val = booleanValuePermutations[i][1];
            bool C_val = booleanValuePermutations[i][2];

            Proposition A(A_val);
            Proposition B(B_val);
            Proposition C(C_val);

            bool tautology = ((A % (B % C)) < ((A & B) % C));
            tautologyTest &= tautology;
        }
        std::cout << "Is the statement a tautology? " << tautologyTest << std::endl;
    }
}

int main11()
{
    std::cout << std::boolalpha;
    testOperators();
    checkDeMorgansLaws();
    checkDistributiveLaws();
    checkTautology();

    return 0;
}