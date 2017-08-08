#pragma once
#include <vector>
#include <memory>
#include "Utilities.h"
#include "Transaction_types.h"
#include "AccountFwd.h"
#include "Loan.h"
#include "Transaction.h"
#include "Person.h"

class iAccount {
	virtual client_number_t getNo() = 0;

	virtual currency_t getBalance() = 0;

	// Showing info about account
	virtual void report() = 0;

	virtual bool chkPass(password_t) = 0;
	virtual void setPass(password_t) = 0;

	virtual void changeFName(name_t) = 0;
	virtual void changeLName(name_t) = 0;

	virtual void transaction(transaction::Type, currency_t, std::shared_ptr<Loan> l = nullptr) = 0;

	virtual void withdraw(currency_t) = 0;
	virtual void deposit(currency_t) = 0;

	virtual void newLoan(std::shared_ptr<Loan>) = 0;
};

class Account : public iAccount
{
protected:
	Person customer;
	password_t mPassword;
	client_number_t mClientNumber;
	long double mBalance = 0;

public:
	std::vector<std::shared_ptr<Loan>> loans;
	std::vector<std::shared_ptr<Transaction>> transactions;

	Account(client_number_t, password_t, name_t, name_t);

	client_number_t getNo();
	currency_t  getBalance();

	bool chkPass(password_t);	// Password validation
	void setPass(password_t);

	inline void report();	// Showing info about account
	
	void changeFName(name_t);
	void changeLName(name_t);

	void transaction(transaction::Type, currency_t, std::shared_ptr<Loan> l = nullptr);

	void withdraw(currency_t);

	void deposit(currency_t);

	void newLoan(std::shared_ptr<Loan>);

};