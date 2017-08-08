#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "Utilities.h"

namespace Utilities
{
	void cls() {
		#ifdef _WIN32
			system("CLS");
		#else
			int x = 50;
			while (x-- > 0) {
				printf("\n");
			}
		#endif
	}

	void pause() {
		printf("\nPress enter to continue...");
		std::cin.get();
		std::cin.ignore();
		std::cin.clear();
	}

}