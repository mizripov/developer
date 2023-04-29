#include "function.h"

int main()
{
	setlocale(LC_ALL, "ru");
	int var_menu, counter = 0, dec_number = 0;
	int* address_of_arr = nullptr;
	char* address_of_arr_hex = nullptr;
	do
	{
		menu_text();
		cin >> var_menu;
		if (!counter)
		{
			while ((var_menu < 1) || (var_menu == 2) || (var_menu == 3) || (var_menu > 4))
			{
				switch (var_menu)
				{
				case 2:
				{
					cout << "Сначала необходимо ввести десятичное число!\n";
					cout << "Повторите попытку: ";
					cin >> var_menu;
				}
				break;
				case 3:
				{
					cout << "На данный момент нет данных для вывода на экран!\n";
					cout << "Повторите попытку: ";
					cin >> var_menu;
				}
				break;
				default:
				{
					cout << "Такой команды в МЕНЮ не существует!\n";
					cout << "Повторите попытку: ";
					cin >> var_menu;
				}
				break;
				}
			}
		}
		while ((var_menu < 1) || (var_menu > 4))
		{
			switch (var_menu)
			{
			default:
			{
				cout << "Такой команды в МЕНЮ не существует!\n";
				cout << "Повторите попытку: ";
				cin >> var_menu;
			}
			break;
			}
		}
		switch (var_menu)
			{
			int past_path;
			int number_system_path;
			case 1: // Ввод десятичного числа
			{
				system("cls");
				past_path = var_menu;
				cout << "Введите десятичное число: ";
				cin >> dec_number;
			}
			break;
			case 2: // Перевод в другую систему счисления
			{
				past_path = var_menu;
				int var_number_system;
				menu_number_system();
				cin >> var_number_system;
				number_system_path = var_number_system;
				switch (var_number_system)
				{
				case 1: // в двоичную
				{
					int size_bin = size_of_bin(dec_number);
					int* arr = new int[size_bin];
					address_of_arr = arr;
					dec_to_bin(dec_number, arr, size_bin);
				}
				break;
				case 2: // в восьмеричную
				{
					int size_oct = size_of_oct(dec_number);
					int* arr = new int[size_oct];
					address_of_arr = arr;
					dec_to_oct(dec_number, arr, size_oct);
				}
				break;
				case 3: // в шестнадцатеричную
				{
					char STR[] = "0123456789ABCDEF";
					int ARRAY[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
					int size_hex = size_of_hex(dec_number);
					int* arr = new int[size_hex];
					char* answer = new char[size_hex + 1];
					address_of_arr_hex = answer;
					dec_to_hex(dec_number, arr, size_hex);
					for (int i = 0; i < size_hex; i++)
					{
						for (int j = 0; j < 16; j++)
						{
							if (arr[i] == ARRAY[j])
							{
								answer[i] = STR[j];
							}
						}
					}
					answer[size_hex] = '\0';
					delete[] arr;
				}
				break;
				}
			}
			break;
			case 3: // Вывод полученных результатов на экран
			{
				switch (past_path)
				{
				case 1: // Вывод десятичного числа
				{
					system("cls");
					cout << "На данный момент Вы не выполняли операций над числом " << dec_number << ", кроме его ввода\n";
				}
				break;
				case 2: // Вывод представления десятичного числа в другой системе счисления
				{
					switch (number_system_path)
					{
					case 1:
					{
						system("cls");
						cout << "Актуальное десятичное число: " << dec_number << endl;
						cout << "Двоичное представление числа " << dec_number << ": ";
						for (int i = 0; i < size_of_bin(dec_number); i++)
						{
							cout << *(address_of_arr + i);
						}
						cout << endl;
						delete[] address_of_arr;
					}
					break;
					case 2:
					{
						system("cls");
						cout << "Актуальное десятичное число: " << dec_number << endl;
						cout << "Восьмеричное представление числа " << dec_number << ": ";
						for (int i = 0; i < size_of_oct(dec_number); i++)
						{
							cout << *(address_of_arr + i);
						}
						cout << endl;
						delete[] address_of_arr;
					}
					break;
					case 3:
					{
						system("cls");
						cout << "Актуальное десятичное число: " << dec_number << endl;
						cout << "Шестнадцатеричное представление числа " << dec_number << ": ";
						for (int i = 0; i < size_of_hex(dec_number); i++)
						{
							cout << *(address_of_arr_hex + i);
						}
						cout << endl;
						delete[] address_of_arr_hex;
					}
					break;
					}
				}
				break;
				}
			}
			break;
			case 4: // Выход из программы
			{
				system("cls");
				cout << "Программа завершена...";
				return 0;
			}
			break;
			}
		if (var_menu != 4)
		{
			system("pause");
		}
		counter++;
	} while (var_menu != 4);
}