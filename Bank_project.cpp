#pragma once
#include "stdafx.h"
#include "Menu.h"
#include "Options.h"

int main()
{
	Menu menuMain;
	{
		using namespace options::menu_main;
		menuMain.setTitle("Main menu");
		menuMain.addMenuItem("Sign in",		signIn);
		menuMain.addMenuItem("Sign up",		signUp);
		menuMain.addMenuItem("About us",	about);
		menuMain.addMenuItem("Exit",		exit);
	}
	while (options::isRunning())
	{
		menuMain.display();
		menuMain.getInput();
	}

	return 0;
}