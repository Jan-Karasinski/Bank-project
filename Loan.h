#pragma once
#include "AccountFwd.h"

class Loan {
	currency_t m_amount, m_repayment;
	float m_interest;
	bool payed = false;

public:
	Loan(currency_t t_amount, float t_inerest = 0.1);

	void repay(currency_t);

	void report();

	currency_t get_amount();

	currency_t get_repayment();

	float get_interest();

	bool is_payed();
};