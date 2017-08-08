#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include "Account.h"

namespace Storage
{
	extern std::vector<std::shared_ptr<Account>> accounts;

	// Finds account in vector of unique_ptrs by client number
	std::shared_ptr<Account> FindAccount(const client_number_t&);

	// Finds position of an account (for checking if exist and deleting acc)
	std::vector<std::shared_ptr<Account>>::iterator FindAccountPosition(const client_number_t&);

	bool exist(const client_number_t&);
}