/*
* Advanced C++ and Modern Design
* Level 6, Homework 5
* Author: Son Pham
* Real Account class
*/

#include "RealAccount.h"
#include "NoFundsException.h"

RealAccount::RealAccount(double initialBalance) : balance(initialBalance) {}

void RealAccount::Withdraw(double amount) {
    if (amount > balance) {
        throw NoFundsException();
    }
    balance -= amount;
}

double RealAccount::GetBalance() { return balance; }