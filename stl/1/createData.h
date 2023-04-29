#ifndef _CREATEDATA_
#define _CREATEDATA_

#include "Header.h"

void createData(const string& path)
{
	srand((unsigned)time(nullptr));
	ofstream file(path);
	if (!file.is_open())
	{
		CLEAR;
		cout << "File opening error\n";
	}
	else
	{
		CLEAR;
		for (int i = 0; i < 100; i++)
		{
			file << rand() % 100 - 50 << " ";
		}
		cout << "The file " << path << " is created\n";
	}
}

template<typename Container_Type>
void createData(const string& path, const int size)
{
	typedef typename Container_Type::value_type value_type;
	Container_Type Container(size);
	generate(begin(Container), end(Container), []()
		{
			return rand() % 100 - 50;
		});
	ofstream file;
	file.open(path);
	if (!file.is_open())
	{
		CLEAR;
		cout << "File opening error\n";
	}
	else
	{
		CLEAR;
		copy(begin(Container), end(Container), ostream_iterator<value_type>(file, " "));
		cout << "The file " << path << " is created\n";
	}
}

#endif // !_CREATEDATA_
