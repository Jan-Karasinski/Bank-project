#pragma once
#include <string>

namespace transaction {
	enum class Type : int {
		Withdraw = 0,
		Deposit = 1,
		Take_loan = 2,
		Repay = 3
	};

	std::string types[];

}