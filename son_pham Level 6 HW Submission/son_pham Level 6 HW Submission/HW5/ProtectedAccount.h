/*
* Advanced C++ and Modern Design
* Level 6, Homework 5
* Author: Son Pham
* Protected Account class header
*/

#ifndef PROTECTED_ACCOUNT_H
#define PROTECTED_ACCOUNT_H

#include "Account.h"
#include "NoAccessException.h"
#include "RealAccount.h"
#include <string>

class ProtectedAccount : public Account {
private:
	std::string password;
	Account* realAccount;

public:
	ProtectedAccount(double initialBalance, const std::string& password);

	void Withdraw(double amount) override;
	double GetBalance() override;

	~ProtectedAccount();
};

#endif // PROTECTED_ACCOUNT_H