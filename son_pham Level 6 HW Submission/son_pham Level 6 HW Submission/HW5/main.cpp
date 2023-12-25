/*
* Advanced C++ and Modern Design
* Level 6, Homework 5
* Author: Son Pham
* Main file testing implementations
*/

#include "ProtectedAccount.h"
#include <iostream>

int main() {
    // Test with valid password
    Account* protectedAccount = new ProtectedAccount(1000, "validpassword");
    std::cout << "Initial Balance: " << protectedAccount->GetBalance()
        << std::endl;

    protectedAccount->Withdraw(200); // Withdraw from ProtectedAccount
    std::cout << "Balance after withdrawal: " << protectedAccount->GetBalance()
        << std::endl;

    // Test with invalid password
    Account* invalidAccount = new ProtectedAccount(1000, "invalidpassword");
    try {
        invalidAccount->GetBalance(); // This should throw NoAccessException
    }
    catch (NoAccessException& naex) {
        std::cout << "No access to balance!" << std::endl;
    }

    // Test withdrawing from ProtectedAccount (valid password but not enough
    // funds)
    try {
        protectedAccount->Withdraw(801); // Withdraw more than balance
        std::cout << "Balance after withdrawal: " << protectedAccount->GetBalance()
            << std::endl;
    }
    catch (NoFundsException& nfex) {
        std::cout << "Not enough funds for withdrawal!" << std::endl;
    }
    return 0;
}