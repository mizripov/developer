#include <iostream>
#include <fstream>
#include <string>
#define CLEAR system("cls")
#define PAUSE system("pause")
using namespace std;

void menu_text()
{
	system("cls");
	cout << "_____________МЕНЮ_____________\n";
	cout << "1 - Новая запись в файл\n";
	cout << "2 - Добавление записи в файл\n";
	cout << "3 - Вывод данных из файла\n";
	cout << "4 - Удаление строки\n";
	cout << "5 - Выход из программы\n";
	cout << "Выберете пункт МЕНЮ - ";
}

void new_record(fstream& file, const string path)
{
	file.open(path, fstream::out | fstream::trunc);
	if (!file.is_open())
	{
		CLEAR;
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		CLEAR;
		string data;
		cout << "Введите данные для записи в файл: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, data);
		file << data << endl;
	}
	file.close();
}

void add_record(fstream& file, const string path)
{
	file.open(path, fstream::app);
	if (!file.is_open())
	{
		CLEAR;
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		CLEAR;
		string data;
		cout << "Введите данные для записи в файл: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, data);
		file << data << endl;
	}
	file.close();
}

void show_data(fstream& file, const string path)
{
	file.open(path, fstream::in);
	if (!file.is_open())
	{
		CLEAR;
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		char data;
		while (file.get(data))
		{
			cout << data;
		}
	}
	file.close();
}

string deleted_line(fstream& file, const string path, int& MAX, int& row_number)
{
	int counter = 1;
	string deletedstr;
	file.open(path, fstream::in);
	if (file.is_open())
	{
		string temp;
		while (!file.eof())
		{
			temp = "";
			getline(file, temp);
			if (temp != "")
			{
				int i = 1;
				int words = 0;
				while (temp[i] != '\0')
				{
					if ((temp[i] == ' ') && (temp[i - 1] != ' '))
					{
						words++;
					}
					i++;
				}
				if ((temp[i] == '\0') && (temp[i - 1] != ' '))
				{
					words++;
				}
				if (words >= MAX)
				{
					MAX = words;
					row_number = counter;
					deletedstr = temp;
				}
			}
			counter++;
		}
	}
	file.close();
	return deletedstr;
}

void delete_line(fstream& file, const string path)
{
	CLEAR;
	cout << "ФАЙЛ ДО УДАЛЕНИЯ:\n";
	show_data(file, path);
	int MAX, row_number;
	string data = "", compare = deleted_line(file, path, MAX, row_number);
	file.open(path, fstream::in);
	if (!file.is_open())
	{
		CLEAR;
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		string temp;
		while (!file.eof())
		{
			temp = "";
			getline(file, temp);
			if ((temp != compare) && (temp != ""))
			{
				data += temp + "\n";
			}
		}
	}
	cout << "Номер удаляемой строки: " << row_number << endl;
	cout << "Количество слов этой строки: " << MAX << endl;
	cout << "Удаляемая строка: " << compare << endl;
	file.close();
	file.open(path, fstream::out | fstream::trunc);
	if (file.is_open())
	{
		file << data;
	}
	file.close();
}

int main()
{
	setlocale(LC_ALL, "ru");
	int menu, counter = 0;
	string path = "lab_15.txt";
	fstream file;
	do
	{
		menu_text();
		cin >> menu;
		if (!counter)
		{
			while ((menu < 1) || (menu == 2) || (menu == 3) || (menu == 4) || (menu > 5))
			{
				switch (menu)
				{
				case 2:
				{
					cout << "Сначала необходимо сделать первую запись в файл!\n";
					cout << "Повторите попытку: ";
					cin >> menu;
				}
				break;
				case 3:
				{
					cout << "Сначала необходимо сделать первую запись в файл!\n";
					cout << "Повторите попытку: ";
					cin >> menu;
				}
				break;
				case 4:
				{
					cout << "На данный момент нет данных в файле для удаления!\n";
					cout << "Повторите попытку: ";
					cin >> menu;
				}
				break;
				default:
				{
					cout << "Такой команды в МЕНЮ не существует!\n";
					cout << "Повторите попытку: ";
					cin >> menu;
				}
				break;
				}
			}
		}
		while ((menu < 1) || (menu > 5))
		{
			switch (menu)
			{
			default:
			{
				cout << "Такой команды в МЕНЮ не существует!\n";
				cout << "Повторите попытку: ";
				cin >> menu;
			}
			break;
			}
		}
		switch (menu)
		{
		case 1:
		{
			new_record(file, path);
		}
		break;
		case 2:
		{
			add_record(file, path);
		}
		break;
		case 3:
		{
			CLEAR;
			cout << "Актуальные данные из файла " << path << ":\n";
			show_data(file, path);
		}
		break;
		case 4:
		{
			delete_line(file, path);
		}
		break;
		case 5:
		{
			CLEAR;
			cout << "Программа завершена...\n";
			return 0;
		}
		break;
		}
		if (menu != 5)
		{
			PAUSE;
		}
		counter++;
	} while (menu != 5);
}