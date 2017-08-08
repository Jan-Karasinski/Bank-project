#pragma once
#include <string>
#include "AccountFwd.h"

class Login{
	client_number_t cn;
	password_t pass;

public:
	bool attempt();
};