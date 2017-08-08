#include "stdafx.h"
#include "Account.h"
#include "Storage.h"

namespace Storage
{
	std::vector<std::shared_ptr<Account>> accounts;

	std::shared_ptr<Account> FindAccount(const client_number_t& id) {
		auto it = FindAccountPosition(id);
		return it != accounts.end() ? *it : nullptr;
	}

	// Finds position of an account (for checking if exist and deleting acc)
	std::vector<std::shared_ptr<Account>>::iterator FindAccountPosition(const client_number_t& id) {
		return find_if(accounts.begin(), accounts.end(),
			[&](std::shared_ptr<Account> const& acc) { return acc->getNo() == id; });
	}

	bool exist(const client_number_t& id) {
		return FindAccountPosition(id) != accounts.end();
	}
}