#pragma once

class Transaction {
	const transaction::Type m_type;
	const currency_t m_amount;
	currency_t m_LoanAmount, m_repayment;
	float m_interest;

public:
	Transaction(transaction::Type, currency_t, std::shared_ptr<Loan>);

	void report();
};