/*
* Advanced C++ and Modern Design
* Level 6, Homework 5
* Author: Son Pham
* Account class header
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "NoFundsException.h"

class Account {
public:
	virtual void Withdraw(double amount) = 0;
	virtual double GetBalance() = 0;
};

#endif // ACCOUNT_H