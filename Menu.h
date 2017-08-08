#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "Utilities.h"
#include "InputHandler.h"

class MenuItems {
protected:
	typedef void(*option)(void);
	typedef std::string caption;
	std::vector< std::pair<caption, option> > menu_items;

public:
	virtual void addMenuItem(caption, option) = 0;
	virtual void resetMenuItems(void) = 0;
};

class Menu : public MenuItems, public InputHandler {
protected:
	std::string m_title = "";

public:
	void setTitle(std::string);

	void display();

	void addMenuItem(caption, option);

	void resetMenuItems();

	void getInput();

};
