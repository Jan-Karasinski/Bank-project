#pragma once
#include <string>
#include "Menu.h"
#include "Storage.h"
#include "Utilities.h"
#include "Transaction_types.h"

namespace options {
	void resetFlag(bool&);
	extern bool running;
	extern bool logged;
	extern bool editing;

	bool isRunning();
	bool isLogged();
	bool isEditing();

	extern std::shared_ptr<Account> current;

	namespace menu_main {
		void signIn();

		void signUp();

		void about();

		void exit();
	}

	namespace menu_account {
		void edit();

		void withdraw();

		void deposit();

		void loans();

		void trHistory();

		void logout();
	}

	namespace menu_edit {
		void changeFirst();

		void changeLast();

		void changePass();

		void back();
	}

	namespace menu_loans {
		void takeLoan();

		void repay();
	}

};