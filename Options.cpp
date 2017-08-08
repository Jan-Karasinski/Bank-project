#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Options.h"
#include "Login.h"
#include "Transaction_types.h"
#include "Validation.h"

namespace options {
	void resetFlag(bool& flag) {
		flag = true;
	}
	extern bool running = true;
	extern bool logged = true;
	extern bool editing = true;

	bool isRunning() {
		return running;
	}
	bool isLogged() {
		return logged;
	}
	bool isEditing() {
			return editing;
		}

	extern std::shared_ptr<Account> current = nullptr;

	namespace menu_main{
		void signIn() {
			if (!Storage::accounts.size()) {
				printf("\nNo accounts in database\n");
				Utilities::pause();
				Utilities::cls();
			}
			else {
				Login login;
				if (login.attempt()) {
					printf("\nSuccesfully signed in\n");
					Utilities::pause();
					Utilities::cls();

					Menu menuAccount;
					{
						using namespace options::menu_account;
						menuAccount.addMenuItem("Change personal data",		edit);
						menuAccount.addMenuItem("Withdraw",					withdraw);
						menuAccount.addMenuItem("Deposit",					deposit);
						menuAccount.addMenuItem("Loans",					loans);
						menuAccount.addMenuItem("Transaction history",		trHistory);
						menuAccount.addMenuItem("Logout",					logout);
					}

					resetFlag(logged);
					while (isLogged())
					{
						current->report();
						menuAccount.display();
						menuAccount.getInput();
					}

				}
				else {
					Utilities::pause();
					Utilities::cls();
				}
			}
		}

		void signUp() {
			try {
				name_t fname, lname;
				password_t pass;
				client_number_t login;
				std::string input;
				
				InputHandler getinput;
				{
					printf("Enter your login: "); input = getinput();

					Validation<ClientNumber> validate(input);
					login = stoll(input);
					if (Storage::exist(login))	throw std::runtime_error("\nLogin is occupied\n");
				}
				{
					printf("Enter your password: "); input = getinput();

					Validation<Password> validate(input);
					pass = input;
				}
				{
					printf("Enter your first name: "); input = getinput();
					Validation<Name> validate(input);
					fname = input;
				}
				{
					printf("Enter your last name: ");  input = getinput();
					Validation<Name> validate(input);
					lname = input;
				}
				Storage::accounts.push_back(std::make_shared<Account>(Account(login, pass, fname, lname)));
				printf("\nAccount succesfully created.\n");
			}
			catch (const PassException& e) {
				std::cerr << e;
			}
			catch(const std::exception& e){
				std::cerr << e.what();
			}
			Utilities::pause();
			Utilities::cls();
		}

		void about() {
			printf("\nabout\n");
			Utilities::pause();
			Utilities::cls();
		}

		void exit() {
			running = false;
		}
	}

	namespace menu_account {
		void edit() {
			Menu menuEdit;
			{
				using namespace options::menu_edit;
				menuEdit.addMenuItem("Change first name",	changeFirst);
				menuEdit.addMenuItem("Change last name",	changeLast);
				menuEdit.addMenuItem("Change password",		changePass);
				menuEdit.addMenuItem("Back",				back);
			
			}

			resetFlag(editing);
			while (isEditing())
			{
				current->report();
				menuEdit.display();
				menuEdit.getInput();
			}
		}

		void withdraw() {
			try
			{
				Utilities::cls();
				current->report();
				printf("How much would you like to withdraw? ");
				
				InputHandler getinput;
				std::string input = getinput();

				Validation<currency_t> validate(input);

				currency_t t_amount = stold(input);

				if (t_amount >= current->getBalance()) throw std::runtime_error("\nAmount bigger than balance!\n");
				current->transaction(transaction::Type::Withdraw, t_amount);
				std::cout << "\nYour balance: " << current->getBalance();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			Utilities::pause();
			Utilities::cls();
		}

		void deposit() {
			try
			{
				Utilities::cls();
				current->report();
				printf("How much would you like to deposit? ");

				InputHandler getinput;
				std::string input = getinput();

				Validation<currency_t> validate(input);

				currency_t t_amount = stold(input);
				current->transaction(transaction::Type::Deposit, t_amount);
				std::cout << "\nYour balance: " << current->getBalance();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			Utilities::pause();
			Utilities::cls();
		}

		void loans() {
			Menu menuLoans;
			{
				using namespace options::menu_loans;
				menuLoans.addMenuItem("Take new loan",	takeLoan);
				menuLoans.addMenuItem("Repay",			repay);
			}

			current->report();
			menuLoans.display();
			menuLoans.getInput();
		}

		void trHistory() {
			if (current->transactions.size()) {
				bool viewing = true;

				const int cmprt = 5; // max transactions per page
				int end = current->transactions.size(), set_begin = 0, set_treshold = end >= 5 ? cmprt : end;

				int pages = static_cast<int>(ceil(current->transactions.size() / static_cast<float>(cmprt)));
				auto page = [&set_begin, &cmprt]() { return static_cast<int>(set_begin / cmprt) + 1; };

				InputHandler getinput;
				std::string input;

				while (viewing) {
					Utilities::cls();
					for (int j = set_begin; j < set_treshold; j++) {
						current->transactions[j]->report();
					}
					std::cout << "(" << page() << "/" << pages << ")" << "\n\n1) Next\n2) Previous\n3) Back\nYour choice: ";
					
					input = getinput();
					switch (validation::isdigit(input) ? stoull(input) : 0) {
						case 1: {
						if (set_treshold < end) {
							set_begin += cmprt;
							set_treshold += cmprt;
							if (set_treshold > end) {
								set_treshold = end;
							}
						}
						break;
					}
						case 2: {
						if (set_begin) {
							set_begin -= cmprt;
							set_treshold -= cmprt;
							if (set_treshold % cmprt != 0) {
								set_treshold += cmprt - (set_treshold % cmprt);
							}
						}
						break;
					}
						case 3: {
						viewing = false;
					}
					}
				}
			}
			else {
				std::cout << "Lack of transactions!";
				Utilities::pause();
				Utilities::cls();
			}
		}

		void logout() {
			logged = false;
			current = nullptr;
		}
	}

	namespace menu_edit {
		void changeFirst() {
			try
			{
				current->report();

				printf("Your new first name: ");
				InputHandler getinput;
				name_t name = getinput();

				Validation<Name> validate(name);

				current->changeFName(name);
				printf("\nName has been changed!\n");
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			Utilities::pause();
			Utilities::cls();
		}

		void changeLast() {
			try
			{
				current->report();

				printf("Your new last name: ");
				InputHandler getinput;
				name_t name = getinput();

				Validation<Name> validate(name);

				current->changeLName(name);
				printf("\nName has been changed!\n");
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			Utilities::pause();
			Utilities::cls();
		}

		void changePass() {
			try
			{
				current->report();

				InputHandler getinput;
				printf("Your current password: ");		password_t cPass = getinput();
				
				if (!current->chkPass(cPass)) throw std::runtime_error("\nIncorrect password!\n");
				
				printf("\nYour new password: ");		password_t nPass = getinput();
				{
					Validation<Password> validate(nPass);
				}
				printf("\nRepeat your new password: "); password_t repeat = getinput();
				{
					Validation<Password> validate(repeat);
				}
				if (nPass != repeat) throw std::runtime_error("\nPasswords are not equal!\n");
				
				current->setPass(repeat);
				printf("\nPassword has been changed!\n");
			}
			catch (const PassException& e) {
				std::cerr << e;
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			Utilities::pause();
			Utilities::cls();
		}

		void back() {
			editing = false;
		}
	}

	namespace menu_loans {
		void takeLoan() {
			try
			{
				current->report();
				
				printf("How much would you like to borrow: ");

				InputHandler getinput;
				std::string input = getinput();

				Validation<currency_t> validate(input);

				current->transaction(transaction::Type::Take_loan, stold(input));

				printf("\nLoan has been taken!\n");
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
			Utilities::pause();
			Utilities::cls();
		}

		void repay() {
			current->report();
			if (!current->loans.empty()) {
				try
				{
					for (size_t i = 0; i < current->loans.size(); i++) {
						printf("%i) ", i + 1); current->loans[i]->report(); printf("\n");
					}

					size_t choice;
					{
						InputHandler getinput;

						printf("\nYour choice: ");
						std::string input = getinput();
						
						Validation<size_t> validate(input);
						choice = stoull(input);
					}

					if (choice <= 0 || choice > current->loans.size())	throw std::runtime_error("\nIncorrect number!\n");
					
					printf("\nHow much would you like to repay: ");

					currency_t t_amount;
					{
						InputHandler getinput;
						std::string input = getinput();

						Validation<currency_t> validate(input);

						t_amount = stold(input);
						if (t_amount > current->getBalance()) throw std::runtime_error("\nAmount bigger than balance!\n");
					}

					auto loan = current->loans[choice - 1];
					{
						if (t_amount > loan->get_repayment())
							t_amount = loan->get_repayment();

						current->transaction(transaction::Type::Repay, t_amount, loan);
					}

					if (!loan->is_payed()) {
						std::cout << "\nYou still have to repay " << loan->get_repayment() << '\n';
					}
					else {
						printf("\nLoan has been paid off!\n");
						current->loans.erase(current->loans.begin() + choice - 1);
					}
				}
				catch (const std::exception& e)
				{
					std::cerr << e.what();
				}
			}
			else {
				printf("You have no unpayed loans!\n");
			}
			Utilities::pause();
			Utilities::cls();
		}
	}
}