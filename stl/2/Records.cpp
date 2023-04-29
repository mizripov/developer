#include "Records.h"

Records::Records(const string filename)
{
	this->filename = filename;
	getContainer();
}

void Records::addRecord(Journal& jr)
{
	ofstream fout(filename, ofstream::binary | ofstream::app);
	if (!fout.is_open())
	{
		cout << "File opening error\n";
		return;
	}
	jr.ID = key;
	Container[key] = jr;
	key++;
	fout.write(reinterpret_cast<char*>(&jr), sizeof(Journal));
	fout.close();
}

void Records::delRecord(const size_t id)
{
	if (Container.find(id) == Container.cend())
	{
		cout << "There is no record with " << id << " in the log\n";
		return;
	}
	Records(filename + "_deleted").addRecord(Container[id]);
	Records(filename + "_deleted").toText();
	Container.erase(id);
	ofstream fout(filename, ofstream::binary);
	if (fout.is_open())
	{
		for (const auto& elem : Container)
		{
			fout.write(reinterpret_cast<const char*>(&elem.second), sizeof(Journal));
		}
	}
	fout.close();
	Records(filename).toText();
}

void Records::replaceRecord(const size_t id, Journal& jr)
{
	if (Container.find(id) == Container.cend())
	{
		cout << "There is no record with " << id << " in the log\n";
		return;
	}
	jr.ID = id;
	Container[id] = jr;
	ofstream fout(filename, ofstream::binary);
	if (fout.is_open())
	{
		for (const auto& elem : Container)
		{
			fout.write(reinterpret_cast<const char*>(&elem.second), sizeof(Journal));
		}
	}
	fout.close();
	Records(filename).toText();
}

void Records::toText()
{
	ofstream fout(filename + ".txt");
	if (!fout.is_open())
	{
		cout << "File opening error\n";
		return;
	}
	fout << "|" << setw(2) << "ID"
		 << "|" << setw(4) << "Курс"
		 << "|" << setw(12) << "Группа"
		 << "|" << setw(14) << "Фамилия"
		 << "|" << setw(6) << "№ЗК"
		 << "|" << setw(18) << "Дисциплина"
		 << "|" << setw(6) << "Оценка"
		 << "|" << endl;
	for (const auto& elem : Container)
	{
		fout << "|" << setw(2) << elem.second.ID
			 << "|" << setw(4) << elem.second.Course
			 << "|" << setw(12) << elem.second.Group_Code
			 << "|" << setw(14) << elem.second.Surname
			 << "|" << setw(6) << elem.second.Student_ID_number
			 << "|" << setw(18) << elem.second.Subject
			 << "|" << setw(6) << elem.second.Estimation
			 << "|" << endl;
	}
	fout.close();
}

void Records::searchByCourse(const size_t course)
{
	bool isExist = false;
	ofstream fout(to_string(course) + "_course", ofstream::binary);
	for_each(Container.begin(), Container.end(), [course, &fout, &isExist](const pair<size_t, Journal>& elem)
		{
			if (elem.second.Course == course)
			{
				isExist = true;
				fout.write(reinterpret_cast<const char*>(&elem.second), sizeof(Journal));
			}
		});
	if (!isExist)
	{
		throw MyException("The course is not in the database");
	}
	fout.close();
	Records(to_string(course) + "_course").toText();
}

void Records::searchByGroup(const string& group_code)
{
	bool isExist = false;
	ofstream fout(group_code + "_group_code", ofstream::binary);
	for_each(Container.begin(), Container.end(), [group_code, &fout, &isExist](const pair<size_t, Journal>& elem)
		{
			if (elem.second.Group_Code == group_code)
			{
				isExist = true;
				fout.write(reinterpret_cast<const char*>(&elem.second), sizeof(Journal));
			}
		});
	if (!isExist)
	{
		throw MyException("The group is not in the database");
	}
	fout.close();
	Records(group_code + "_group_code").toText();
}

void Records::searchByStudentIdNumber(const string& student_id_number)
{
	bool isExist = false;
	ofstream fout(student_id_number + "_student_id_number", ofstream::binary);
	for_each(Container.begin(), Container.end(), [student_id_number, &fout, &isExist](const pair<size_t, Journal>& elem)
		{
			if (elem.second.Student_ID_number == student_id_number)
			{
				isExist = true;
				fout.write(reinterpret_cast<const char*>(&elem.second), sizeof(Journal));
			}
		});
	if (!isExist)
	{
		throw MyException("The student id number is not in the database");
	}
	fout.close();
	Records(student_id_number + "_student_id_number").toText();
}

void Records::searchBySurname(const string& surname)
{
	bool isExist = false;
	ofstream fout(surname + "_surname", ofstream::binary);
	for_each(Container.begin(), Container.end(), [surname, &fout, &isExist](const pair<size_t, Journal>& elem)
		{
			if (elem.second.Surname == surname)
			{
				isExist = true;
				fout.write(reinterpret_cast<const char*>(&elem.second), sizeof(Journal));
			}
		});
	if (!isExist)
	{
		throw MyException("The surname is not in the database");
	}
	fout.close();
	Records(surname + "_surname").toText();
}

void Records::searchByEstimation(const size_t estimation)
{
	bool isExist = false;
	ofstream fout(to_string(estimation) + "_estimation", ofstream::binary);
	for_each(Container.begin(), Container.end(), [estimation, &fout, &isExist](const pair<size_t, Journal>& elem)
		{
			if (elem.second.Estimation == estimation)
			{
				isExist = true;
				fout.write(reinterpret_cast<const char*>(&elem.second), sizeof(Journal));
			}
		});
	if (!isExist)
	{
		throw MyException("The estimation is not in the database");
	}
	fout.close();
	Records(to_string(estimation) + "_estimation").toText();
}

void Records::calcAverageScoreSubject(const string& subject)
{
	int counter = 0;
	int total_sum = accumulate(Container.begin(), Container.end(), 0, [subject, &counter](const int prev_sum, const pair<size_t, Journal>& elem)
		{
			if (elem.second.Subject == subject)
			{
				counter++;
				return prev_sum + elem.second.Estimation;
			}
		});
	if (!counter)
	{
		throw MyException("The subject is not in the database");
	}
	CLEAR;
	cout << "Average score in " << subject << " is " << fixed << setprecision(5) << total_sum / (double)counter << endl;
}

void Records::calcAverageScoreGroup(const string& group_code)
{
	int counter = 0;
	int total_sum = accumulate(Container.begin(), Container.end(), 0, [group_code, &counter](const int prev_sum, const pair<size_t, Journal>& elem)
		{
			if (elem.second.Group_Code == group_code)
			{
				counter++;
				return prev_sum + elem.second.Estimation;
			}
		});
	if (!counter)
	{
		throw MyException("The group is not in the database");
	}
	CLEAR;
	cout << "Average score in the " << group_code << " is " << fixed << setprecision(5) << total_sum / (double)counter << endl;
}

void Records::calcAverageScoreCourse(const size_t course)
{
	int counter = 0;
	int total_sum = accumulate(Container.begin(), Container.end(), 0, [course, &counter](const int prev_sum, const pair<size_t, Journal>& elem)
		{
			if (elem.second.Course == course)
			{
				counter++;
				return prev_sum + elem.second.Estimation;
			}
		});
	if (!counter)
	{
		throw MyException("The course is not in the database");
	}
	CLEAR;
	cout << "Average score on the " << course << " course is " << fixed << setprecision(5) << total_sum / (double)counter << endl;
}

void Records::getContainer()
{
	ifstream fin(filename, ifstream::binary);
	Journal log;
	while (fin.read(reinterpret_cast<char*>(&log), sizeof(Journal)))
	{
		Container[log.ID] = log;
		key = log.ID;
	}
	key++;
	fin.close();
}
