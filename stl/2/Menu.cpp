#include "Menu.h"

void Menu::run()
{
	string filename = "Journal";
	Records rec(filename);
	Journal log;
	int choice;
	size_t temp_int;
	string temp_str;
	while (isContinue)
	{
		print_menu();
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			CLEAR;
			cout << "Input log to add\n";
			cin >> log;
			rec.addRecord(log);
		}
		break;
		case 2:
		{
			CLEAR;
			cout << "Input index of log to delete: ";
			cin >> temp_int;
			rec.delRecord(temp_int);
		}
		break;
		case 3:
		{
			CLEAR;
			cout << "Input index of log to replace: ";
			cin >> temp_int;
			cout << "Input log to insert\n";
			cin >> log;
			rec.replaceRecord(temp_int, log);
		}
		break;
		case 4:
		{
			CLEAR;
			cout << "Input number of course to search: ";
			cin >> temp_int;
			try
			{
				rec.searchByCourse(temp_int);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 5:
		{
			CLEAR;
			cout << "Input code of group to search: ";
			cin >> temp_str;
			try
			{
				rec.searchByGroup(temp_str);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 6:
		{
			CLEAR;
			cout << "Input student id number to search: ";
			cin >> temp_str;
			try
			{
				rec.searchByStudentIdNumber(temp_str);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 7:
		{
			CLEAR;
			cout << "Input surname to search: ";
			cin >> temp_str;
			try
			{
				rec.searchBySurname(temp_str);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 8:
		{
			CLEAR;
			cout << "Input estimation to search: ";
			cin >> temp_int;
			try
			{
				rec.searchByEstimation(temp_int);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 9:
		{
			CLEAR;
			rec.toText();
			cout << "Uploaded successfully\n";
		}
		break;
		case 10:
		{
			CLEAR;
			cout << "Input subject to calculate: ";
			cin >> temp_str;
			try
			{
				rec.calcAverageScoreSubject(temp_str);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 11:
		{
			CLEAR;
			cout << "Input code of group to calculate: ";
			cin >> temp_str;
			try
			{
				rec.calcAverageScoreGroup(temp_str);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 12:
		{
			CLEAR;
			cout << "Input number of course to calculate: ";
			cin >> temp_int;
			try
			{
				rec.calcAverageScoreCourse(temp_int);
			}
			catch (MyException& ex)
			{
				ex.what();
			}
		}
		break;
		case 13:
		{
			isContinue = false;
		}
		break;
		default:
		{
			CLEAR;
			cout << "Incorrect operation, try again\n";
		}
		break;
		}
		if (isContinue)
		{
			PAUSE;
		}
	}
}

void Menu::print_menu()
{
	CLEAR;
	cout << "____________________MENU____________________\n";
	cout << "1 - add log\n";
	cout << "2 - delete log\n";
	cout << "3 - replace log\n";
	cout << "4 - search by course\n";
	cout << "5 - search by group\n";
	cout << "6 - search by student id number\n";
	cout << "7 - search by surname\n";
	cout << "8 - search by estimation\n";
	cout << "9 - load to .txt file\n";
	cout << "10 - calculate the average score for the subject\n";
	cout << "11 - calculate the average score for the group\n";
	cout << "12 - calculate the average score for the course\n";
	cout << "13 - exit\n";
	cout << ">";
}
