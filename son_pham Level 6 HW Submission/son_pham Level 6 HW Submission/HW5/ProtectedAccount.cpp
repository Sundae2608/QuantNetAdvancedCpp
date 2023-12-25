/*
* Advanced C++ and Modern Design
* Level 6, Homework 5
* Author: Son Pham
* Protected Account class
*/

#include "ProtectedAccount.h"
#include "NoAccessException.h"

ProtectedAccount::ProtectedAccount(double initialBalance,
    const std::string& password)
    : password(password), realAccount(new RealAccount(initialBalance)) {}

void ProtectedAccount::Withdraw(double amount) {
    realAccount->Withdraw(amount);
}

double ProtectedAccount::GetBalance() {
    if (password != "validpassword") {
        throw NoAccessException();
    }
    return realAccount->GetBalance();
}

ProtectedAccount::~ProtectedAccount() { delete realAccount; }