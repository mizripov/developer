#ifndef _MENU_
#define _MENU_

#include "Header.h"
#include "createData.h"
#include "loadData.h"
#include "modify.h"
#include "outputResult.h"

template<typename Container_Type>
class Menu
{
private:
	Container_Type Container;

	void createDataRun()
	{
		bool key_1 = true;
		while (key_1)
		{
			int choice_1;
			CLEAR;
			cout << "1 - ofstream\n";
			cout << "2 - generate/copy\n";
			cout << "3 - back\n";
			cout << ">";
			cin >> choice_1;
			switch (choice_1)
			{
			case 1:
			{
				CLEAR;
				string path;
				cout << "Enter the file name: ";
				cin >> path;
				createData(path);
			}
			break;
			case 2:
			{
				CLEAR;
				string path;
				cout << "Enter the file name: ";
				cin >> path;
				createData<Container_Type>(path, 100);
			}
			break;
			case 3:
			{
				key_1 = false;
			}
			break;
			default:
			{
				cout << "Incorrect operation, try again\n";
			}
			break;
			}
			if (key_1 == true)
			{
				PAUSE;
			}
		}
	}

	void loadDataRun()
	{
		bool key_2 = true;
		while (key_2)
		{
			int choice_2;
			CLEAR;
			cout << "1 - ifstream\n";
			cout << "2 - copy/istream_iterator\n";
			cout << "3 - back\n";
			cout << ">";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> choice_2;
			switch (choice_2)
			{
			case 1:
			{
				CLEAR;
				string path;
				cout << "Enter the file name: ";
				cin >> path;
				Container = loadData<Container_Type>(path);
			}
			break;
			case 2:
			{
				CLEAR;
				Container = loadData<Container_Type>();
			}
			break;
			case 3:
			{
				key_2 = false;
			}
			break;
			default:
			{
				cout << "Incorrect operation, try again\n";
			}
			break;
			}
			if (key_2 == true)
			{
				PAUSE;
			}
		}
	}

	void modifyRun()
	{
		bool key_3 = true;
		while (key_3)
		{
			int choice_3;
			CLEAR;
			cout << "1 - sum/average\n";
			cout << "2 - iterators\n";
			cout << "3 - for_each\n";
			cout << "4 - transform/stream_iterators\n";
			cout << "5 - back\n";
			cout << ">";
			cin >> choice_3;
			switch (choice_3)
			{
			case 1:
			{
				CLEAR;
				try
				{
					modify<Container_Type>(Container);
				}
				catch (MyException& ex)
				{
					ex.what_mean();
				}
			}
			break;
			case 2:
			{
				CLEAR;
				try
				{
					modify<Container_Type>(Container.rbegin(), Container.rend());
				}
				catch (MyException& ex)
				{
					ex.what_mean();
				}
			}
			break;
			case 3:
			{
				CLEAR;
				try
				{
					modify<Container_Type>(Container, 1);
				}
				catch (MyException& ex)
				{
					ex.what_mean();
				}
			}
			break;
			case 4:
			{
				CLEAR;
				string path1;
				cout << "Enter the file_1 name: ";
				cin >> path1;
				string path2;
				cout << "Enter the file_2 name: ";
				cin >> path2;
				try
				{
					modify<Container_Type>(path1, path2);
				}
				catch (MyException& ex)
				{
					ex.what_mean();
				}
			}
			break;
			case 5:
			{
				key_3 = false;
			}
			break;
			default:
			{
				cout << "Incorrect operation, try again\n";
			}
			break;
			}
			if (key_3 == true)
			{
				PAUSE;
			}
		}
	}

	void outputResultRun()
	{
		bool key_4 = true;
		while (key_4)
		{
			int choice_4;
			CLEAR;
			cout << "1 - ofstream\n";
			cout << "2 - ofstream, ostream_iterator\n";
			cout << "3 - console\n";
			cout << "4 - back\n";
			cout << ">";
			cin >> choice_4;
			switch (choice_4)
			{
			case 1:
			{
				CLEAR;
				string path;
				cout << "Enter the file name: ";
				cin >> path;
				outputResult<Container_Type>(Container, path);
			}
			break;
			case 2:
			{
				CLEAR;
				string path;
				cout << "Enter the file name: ";
				cin >> path;
				outputResult<Container_Type>(Container, path, 1);
			}
			break;
			case 3:
			{
				CLEAR;
				cout << "Data:\n";
				outputResult<Container_Type>(Container);
			}
			break;
			case 4:
			{
				key_4 = false;
			}
			break;
			default:
			{
				cout << "Incorrect operation, try again\n";
			}
			break;
			}
			if (key_4 == true)
			{
				PAUSE;
			}
		}
	}

public:
	void run()
	{
		bool key = true;
		while (key)
		{
			int choice;
			CLEAR;
			cout << "____________________MENU____________________\n";
			cout << "1 - createData\n";
			cout << "2 - loadData\n";
			cout << "3 - modify\n";
			cout << "4 - outputResult\n";
			cout << "5 - exit\n";
			cout << ">";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				createDataRun();
			}
			break;
			case 2:
			{
				loadDataRun();
			}
			break;
			case 3:
			{
				modifyRun();
			}
			break;
			case 4:
			{
				outputResultRun();
			}
			break;
			case 5:
			{
				key = false;
			}
			break;
			default:
			{
				cout << "Incorrect operation, try again\n";
			}
			break;
			}
			if (key)
			{
				PAUSE;
			}
		}
	}
};

#endif // !_MENU_
