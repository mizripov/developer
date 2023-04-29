#include <iostream>
#define CORRECT
#define CLEAR system("cls")
#define PAUSE system("pause")
using namespace std;

int get_size_string(char* str)
{
	int size = strlen(str) + 1;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '*')
		{
			size++;
		}
	}
	return size;
}

void get_address_symbol(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '*')
		{
			cout << "Адрес * (" << i + 1 << " элемент) равен: " << (void*)(str + i) << endl;
		}
	}
}

void build_new_row(char* str1, char* str2)
{
	int counter = 0;
	for (int i = 0; i < strlen(str2); i++)
	{
		if (str1[i - counter] == '*')
		{
			str2[i] = str1[i - counter];
			str2[i + 1] = '*';
			i++;
			counter++;
			continue;
		}
		str2[i] = str1[i - counter];
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int select;
	do
	{
		char str1[255];
		CLEAR;
		cout << "Введите текст: ";
#ifdef CORRECT
		cin.getline(str1, 255, '\n');
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			CLEAR;
			cout << "Вы превысили допустимое количество символов!\nВведите новый текст: ";
			cin.getline(str1, 255, '\n');
			PAUSE;
		}
#endif
#ifndef CORRECT
		cin.getline(str1, 255, '\n');
		PAUSE;
#endif
		char* str2 = new char[get_size_string(str1)];
		build_new_row(str1, str2);
		get_address_symbol(str1);
		PAUSE;
		CLEAR;
		cout << "Изначальная строка: " << str1 << endl;
		cout << "Новая строка: " << str2 << endl;
		delete[] str2;
		PAUSE;
		CLEAR;
		cout << "Желаете ли Вы ввести новую строку?\n1.Да\n2.Нет\n>";
		cin >> select;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (select == 1);
	return 0;
}