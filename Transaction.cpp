#pragma once
#include "stdafx.h"
#include <iostream>
#include <memory>
#include "Transaction_types.h"
#include "Loan.h"
#include "Transaction.h"

Transaction::Transaction(transaction::Type t_type, currency_t t_amount, std::shared_ptr<Loan> t_loan = nullptr)
	: m_type(t_type), m_amount(t_amount)
{
	if (t_loan != nullptr) {
		m_LoanAmount = t_loan->get_amount();
		m_repayment = t_loan->get_repayment();
		m_interest = t_loan->get_interest();
	}
}

void Transaction::report() {
	switch (m_type) {
		using transaction::Type;
		using transaction::types;

		case Type::Deposit:
		case Type::Withdraw: {
			std::cout << types[static_cast<int>(m_type)] << " Amount: " << m_amount << std::endl;
			break;
		}
		case Type::Take_loan:
		case Type::Repay: {
			std::cout << types[static_cast<int>(m_type)] << " Amount: " << m_amount << " Repayment: " << m_repayment << " Interest: " << m_interest << std::endl;
			break;
		}
		default: {
			std::cerr << "transaction::Type of transaction was not handled\n";
		}
	}
}