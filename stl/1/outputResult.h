#ifndef _OUTPUTRESULT_
#define _OUTPUTRESULT_

#include "Header.h"

template<typename Container_Type>
void outputResult(const Container_Type& Container, const string& path)
{
	ofstream file(path);
	if (!file.is_open())
	{
		CLEAR;
		cout << "File opening error\n";
	}
	else
	{
		CLEAR;
		for (auto elem : Container)
		{
			file << elem << " ";
		}
		cout << "The file " << path << " is created\n";
	}
}

template<typename Container_Type>
void outputResult(const Container_Type& Container, const string& path, int flag)
{
	typedef typename Container_Type::value_type value_type;
	ofstream file(path);
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

template<typename Container_Type>
void outputResult(const Container_Type& Container)
{
	int counter = 0;
	for (auto i = Container.begin(); i != Container.end(); ++i)
	{
		cout << *i << " ";
		counter++;
		if (counter == 20)
		{
			cout << endl;
			counter = 0;
		}
	}
	cout << endl;
}

#endif // !_OUTPUTRESULT_
