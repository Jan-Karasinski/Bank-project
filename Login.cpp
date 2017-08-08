#pragma once
#include "stdafx.h"
#include "Login.h"
#include "Options.h"
#include "Storage.h"
#include "Validation.h"

bool Login::attempt() {
	try {
		{
			InputHandler getinput;
			printf("Account number: "); std::string input = getinput(); 
									cn = validation::isdigit(input) ? stoll(input) : 0;
			printf("Password: ");	pass = getinput();
		}
		options::current = Storage::FindAccount(cn);
		if (options::current == nullptr)		throw std::runtime_error("\nIncorrect account number or password.\n");
		if (!options::current->chkPass(pass))	throw std::runtime_error("\nIncorrect account number or password.\n");
		
		return true;
	}
	catch (const PassException& e) {
		std::cerr << e;
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
	return false;
}