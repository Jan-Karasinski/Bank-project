#pragma once
#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "Account.h"
#include "Utilities.h"

Account::Account(client_number_t cn, password_t pass, name_t fn, name_t ln)
	: mClientNumber(cn), mPassword(std::move(pass)), customer(std::move(fn), std::move(ln))
{}

// Getting client number
client_number_t Account::getNo() {
	return mClientNumber;
}

currency_t Account::getBalance() {
	return mBalance;
}

// Password validation
bool Account::chkPass(password_t pass) {
	return mPassword == pass ? true : false;
}

void Account::setPass(password_t pass) {
	mPassword = std::move(pass);
}

// Display info about account
inline void Account::report() {
	std::cout <<"Client Number: "<< mClientNumber <<
				"\nFirst name: " << customer.name.mFirstName <<
				"\nLast name: "	 << customer.name.mLastName << std::fixed << std::setprecision(2) <<
				"\nBalance: "	 << mBalance <<"\n\n";
}

void Account::changeFName(name_t nName) {
	customer.name.mFirstName = std::move(nName);
}
void Account::changeLName(name_t nName) {
	customer.name.mLastName = std::move(nName);
}

void Account::transaction(transaction::Type t_type, currency_t t_amount, std::shared_ptr<Loan> t_loan) {
	if (transaction::Type::Withdraw == t_type) {
		withdraw(t_amount);
	}
	else if (transaction::Type::Deposit == t_type) {
		deposit(t_amount);
	}
	else if (transaction::Type::Take_loan == t_type) {
		t_loan = std::make_shared<Loan>(Loan(t_amount));
		newLoan(t_loan);
		deposit(t_amount);
	}
	else if (transaction::Type::Repay == t_type) {
		t_loan->repay(t_amount);
		withdraw(t_amount);
	}
	transactions.push_back(std::make_shared<Transaction>(Transaction(t_type, t_amount, t_loan)));
}

void Account::withdraw(currency_t t_amount) {
	mBalance -= t_amount;
}

void Account::deposit(currency_t t_amount) {
	mBalance += t_amount;
}

// Adding new loan
void Account::newLoan(std::shared_ptr<Loan> l) {
	loans.push_back(l);
}