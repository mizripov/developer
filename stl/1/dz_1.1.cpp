#include "Menu.h"

int main()
{
	setlocale(LC_ALL, "ru");
	Menu<list<int>> app;
	app.run();
	return 0;
}