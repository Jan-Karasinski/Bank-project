#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>


struct InputHandler {
	std::string m_input;

	void getInput() {
		std::cin >> m_input;
	}

	std::string operator()() {
		getInput();
		return m_input;
	}
};