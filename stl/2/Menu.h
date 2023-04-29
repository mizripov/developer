#ifndef _MENU_H_
#define _MENU_H_

#include "Records.h"

class Menu
{
public:
	void run();
private:
	void print_menu();
	bool isContinue = true;
};

#endif // !_MENU_H_
