#pragma once
#include "stdafx.h"
#include "Menu.h"
#include "Validation.h"

void Menu::setTitle(std::string t_title) {
	m_title = std::move(t_title);
}

void Menu::display() {
	if (m_title.size() > 1)
		std::cout << m_title + "\n\n";
	for (size_t i = 0; i < menu_items.size(); i++) {
		std::cout << i + 1 << ") " << std::get<0>(menu_items[i]) << '\n';
	}
}

void Menu::addMenuItem(caption cap, option opt) {
	menu_items.push_back(make_pair(std::move(cap), opt));
}

void Menu::resetMenuItems() {
	menu_items.clear();
}

void Menu::getInput() {
	printf("\nYour choice: ");
	std::cin >> m_input;
	if (m_input.size() < MAX_CHOICE) {
		if (validation::isdigit(m_input)) {
			size_t choice = stoull(m_input) - 1;
			if (choice >= 0 && choice < menu_items.size()) {
				Utilities::cls();
				std::get<1>(menu_items[choice])();
			}
		}
	}
	Utilities::cls();
}