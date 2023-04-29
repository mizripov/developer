#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#define CLEAR system("cls")
#define PAUSE system("pause")
using namespace std;

enum direct
{
	IMPORT,
	EXPORT
};

struct Product
{
	int ID;
	int year = 0;
	int price = 0;
	char name[50] = "";
	char country[50] = "";
	bool direction = 0;
	static int counter;
	Product()
	{
	}
	Product(const int i)
	{
		CLEAR;
		cout << "ДАННЫЕ ТОВАРА №" << i + 1 << ":\n";
		cout << "Введите наименование товара: ";
		gets_s(name);
		cout << "Введите объем сделки: ";
		cin >> price;
		cout << "Введите год заключения сделки: ";
		cin >> year;
		cout << "Введите страну: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		gets_s(country);
		cout << "Введите направление товара (0 - import, 1 - export): ";
		cin >> direction;
		counter++;
		ID = counter;
	}
	static void print_heading()
	{
		CLEAR;
		cout << "-------------------------------------------------------------------------------------------------------\n";
		cout << setw(5) << "|#ID|" << setw(20) << "НАИМЕНОВАНИЕ ТОВАРА|" << setw(19) << right << "ОБЪЕМ СДЕЛКИ|" << setw(28) << right << "ГОД ЗАКЛЮЧЕНИЯ СДЕЛКИ|" << setw(13) << right << "СТРАНА|" << setw(18) << right << "НАПРАВЛЕНИЕ|" << endl;
		cout << "-------------------------------------------------------------------------------------------------------\n";
	}
	void print_info()
	{
		cout << "  " << setw(3) << left << ID << setw(19) << right << name << setw(19) << right << price << setw(28) << right << year << setw(13) << right << country << setw(18) << right << direction << "\n";
		cout << "-------------------------------------------------------------------------------------------------------\n";
	}
};

int Product::counter = 0;

void menu_text()
{
	CLEAR;
	cout << "__________МЕНЮ__________\n";
	cout << "1.НОВАЯ ЗАПИСЬ\n";
	cout << "2.ДОБАВЛЕНИЕ ЗАПИСИ\n";
	cout << "3.ВЫВОД ДАННЫХ\n";
	cout << "4.УДАЛЕНИЕ ДАННЫХ\n";
	cout << "5.ВЫХОД\n";
	cout << ">";
}

void request_choice()
{
	CLEAR;
	cout << "1.Вывести ВСЮ актуальную информацию из файла\n";
	cout << "2.Вывести УЗКУЮ информацию по запросам\n";
	cout << "3.Возврат на главный экран\n";
	cout << ">";
}

void requests()
{
	CLEAR;
	cout << "1.Определить все товары, импортируемые из данной страны и суммарный объем сделок\n";
	cout << "2.Определить страну, экспорт в которую имеет наибольший объем\n";
	cout << "3.Определить все страны, из которых импортируется данный товар, и объем сделок в каждом случае\n";
	cout << ">";
}

void first_request(fstream& file, const string path)
{
	CLEAR;
	int sum = 0;
	char country[50] = "";
	cout << "Импорт из какой страны Вас интересует: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	gets_s(country);
	file.open(path, fstream::binary | fstream::in);
	if (!file.is_open())
	{
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		Product object;
		Product::print_heading();
		while (file.read((char*)&object, sizeof(Product)))
		{
			if ((object.direction == direct::EXPORT) && (!strcmp(object.country, country)))
			{
				object.print_info();
				sum += object.price;
			}
		}
	}
	file.close();
	cout << "Суммарный объем сделок составил:\t" << sum << endl;
}

void second_request(fstream& file, const string path)
{
	char str[50] = "";
	char country[50] = "";
	int sum = 0;
	int MAX = 0;
	file.open(path, fstream::binary | fstream::in);
	if (!file.is_open())
	{
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		Product object;
		while (file.read((char*)&object, sizeof(Product)))
		{
			sum = 0;
			if (object.direction == direct::IMPORT)
			{
				strcpy_s(str, object.country);
				Product temp;
				fstream newfile(path, fstream::binary | fstream::in);
				while (newfile.read((char*)&temp, sizeof(Product)))
				{
					if ((temp.direction == direct::IMPORT) && (!strcmp(temp.country, str)))
					{
						sum += temp.price;
					}
				}
				newfile.close();
			}
			if (sum >= MAX)
			{
				MAX = sum;
				strcpy_s(country, str);
			}
		}
		CLEAR;
		cout << "Страна, экспорт в которую имеет наибольший объем: " << country << endl;
		cout << "Суммарный объем сделок составил: " << MAX << endl;
	}
	file.close();
}

void third_request(fstream& file, const string path)
{
	CLEAR;
	int counter = 0;
	char name[50] = "";
	cout << "Какой товар Вас интересует: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	gets_s(name);
	file.open(path, fstream::binary | fstream::in);
	if (!file.is_open())
	{
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		Product object;
		Product::print_heading();
		while (file.read((char*)&object, sizeof(Product)))
		{
			if ((object.direction == direct::EXPORT) && (!strcmp(object.name, name)))
			{
				object.print_info();
				counter++;
			}
		}
		if (!counter)
		{
			CLEAR;
			cout << "Такого товара в базе данных нет...\n";
		}
	}
	file.close();
}

void new_record(fstream& file, const string path, const int& number)
{
	file.open(path, fstream::binary | fstream::out | fstream::trunc);
	if (!file.is_open())
	{
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		for (int i = 0; i < number; i++)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Product object(i);
			file.write((char*)&object, sizeof(Product));
		}
	}
	file.close();
}

void add_record(fstream& file, const string path, const int& number)
{
	file.open(path, fstream::binary | fstream::app);
	if (!file.is_open())
	{
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		for (int i = 0; i < number; i++)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			Product object(i);
			file.write((char*)&object, sizeof(Product));
		}
	}
	file.close();
}

void show_data(fstream& file, const string path)
{
	file.open(path, fstream::binary | fstream::in);
	if (!file.is_open())
	{
		cout << "Файл " << path << " не найден...\n";
	}
	else
	{
		Product::print_heading();
		Product object;
		while (file.read((char*)&object, sizeof(Product)))
		{
			object.print_info();
		}
	}
	file.close();
}

void main_to_reserve(fstream& file, fstream& temp, const string path, const int id, int& counter)
{
	file.open(path, fstream::binary | fstream::in);
	if (file.is_open())
	{
		Product object;
		temp.open("reserve.bin", fstream::binary | fstream::out | fstream::trunc);
		if (temp.is_open())
		{
			while (file.read((char*)&object, sizeof(Product)))
			{
				if (object.ID == id)
				{
					counter++;
				}
				if (object.ID != id)
				{
					temp.write((char*)&object, sizeof(Product));
				}
			}
		}
		temp.close();
	}
	file.close();
}

void reserve_to_main(fstream& file, fstream& temp, const string path)
{
	temp.open("reserve.bin", fstream::binary | fstream::in);
	if (temp.is_open())
	{
		Product object;
		file.open(path, fstream::binary | fstream::out | fstream::trunc);
		if (file.is_open())
		{
			while (temp.read((char*)&object, sizeof(Product)))
			{
				file.write((char*)&object, sizeof(Product));
			}
		}
		file.close();
	}
	temp.close();
}

void delete_data(fstream& file, const string path, const int id)
{
	fstream temp;
	int counter = 0;
	main_to_reserve(file, temp, path, id, counter);
	reserve_to_main(file, temp, path);
	if (!counter)
	{
		cout << "Товар с ID #" << id << " не найден в базе...\n";
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int menu, number, counter = 0;
	fstream file;
	string path = "main.bin";
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
					cout << "Сначала необходимо сделать первую запись в файл!\n";
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
			CLEAR;
			cout << "Сколько товаров Вы желаете внести в базу данных: ";
			cin >> number;
			new_record(file, path, number);
		}
		break;
		case 2:
		{
			CLEAR;
			cout << "Сколько товаров Вы желаете внести в базу данных: ";
			cin >> number;
			add_record(file, path, number);
		}
		break;
		case 3:
		{
			int submenu;
			do
			{
				request_choice();
				cin >> submenu;
				switch (submenu)
				{
				case 1:
				{
					show_data(file, path);
					PAUSE;
				}
				break;
				case 2:
				{
					requests();
					int request_menu;
					cin >> request_menu;
					switch (request_menu)
					{
					case 1:
					{
						first_request(file, path);
						PAUSE;
					}
					break;
					case 2:
					{
						second_request(file, path);
						PAUSE;
					}
					break;
					case 3:
					{
						third_request(file, path);
						PAUSE;
					}
					break;
					default:
					{
						cout << "Такого пункта не существует...\n";
						PAUSE;
					}
					break;
					}
				}
				break;
				}
			} while (submenu != 3);
		}
		break;
		case 4:
		{
			CLEAR;
			int id;
			cout << "Введите ID товара, который хотите удалить из базы: ";
			cin >> id;
			delete_data(file, path, id);
		}
		break;
		case 5:
		{
			CLEAR;
			cout << "Программа завершена.\n";
			return 0;
		}
		break;
		}
		if (menu != 5)
		{
			system("pause");
		}
		counter++;
	} while (menu != 5);
}