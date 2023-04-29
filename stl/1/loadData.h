#ifndef _LOADDATA_
#define _LOADDATA_

#include "Header.h"

template<typename Container_Type>
Container_Type loadData(const string& path)
{
	typedef typename Container_Type::value_type value_type;
	Container_Type Container;
	ifstream file;
	file.open(path);
	if (!file.is_open())
	{
		CLEAR;
		cout << "File opening error\n";
	}
	else
	{
		CLEAR;
		value_type value;
		while (!file.eof())
		{
			if (file >> value)
			{
				Container.push_back(value);
			}
		}
		cout << "The container is formed\n";
	}
	return Container;
}

template<typename Container_Type>
Container_Type loadData()
{
	typedef typename Container_Type::value_type value_type;
	CLEAR;
	Container_Type Container;
	cout << "Input data: ";
	copy(istream_iterator<value_type>(cin), istream_iterator<value_type>(), back_inserter(Container));
	CLEAR;
	cout << "The container is formed\n";
	return Container;
}

#endif // !_LOADDATA_
