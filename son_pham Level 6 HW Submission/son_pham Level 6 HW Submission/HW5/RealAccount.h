/*
* Advanced C++ and Modern Design
* Level 6, Homework 5
* Author: Son Pham
* Real Account class header
*/

#ifndef REAL_ACCOUNT_H
#define REAL_ACCOUNT_H

#include "Account.h"

class RealAccount : public Account {
private:
	double balance;

public:
	RealAccount(double initialBalance);

	void Withdraw(double amount) override;
	double GetBalance() override;
};

#endif // REAL_ACCOUNT_H