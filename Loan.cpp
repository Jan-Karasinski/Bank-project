#pragma once
#include "stdafx.h"
#include <iostream>
#include "Loan.h"

Loan::Loan(currency_t t_amount, float t_inerest)
	: m_amount(t_amount), m_interest(t_inerest), m_repayment(t_amount + (t_amount * t_inerest))
{}

void Loan::repay(currency_t t_amount) {
	m_repayment -= t_amount;
	if (0 == static_cast<long long>(m_repayment * 100)) {
		payed = true;
	}
}

void Loan::report() {
	std::cout << "Amount: " << m_amount << " Repayment: " << m_repayment << " Interest: " << m_interest;
}

currency_t Loan::get_amount() {
	return m_amount;
}

currency_t Loan::get_repayment() {
	return m_repayment;
}

float Loan::get_interest() {
	return m_interest;
}

bool Loan::is_payed()
{
	return payed;
}
