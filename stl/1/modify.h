#ifndef _MODIFY_
#define _MODIFY_

#include "Header.h"
#include "MyException.h"

template<typename Container_Type>
void modify(Container_Type& Container)
{
	typedef typename Container_Type::value_type value_type;
	value_type abs_sum = accumulate(begin(Container), end(Container), 0, [](value_type a, value_type b)
		{
			return a + abs(b);
		});
	Container.push_back(accumulate(begin(Container), end(Container), 0));
	Container.push_back(abs_sum/(Container.size() - 1));
}

template<typename Container_Type>
void modify(typename Container_Type::reverse_iterator it_1, typename Container_Type::reverse_iterator it_2)
{
	typedef typename Container_Type::value_type value_type;
	typedef typename Container_Type::reverse_iterator riter;
	riter pos = find_if(it_1, it_2, [](value_type a) {return a < 0; });
	if (pos == it_2)
	{
		throw MyException("There are no negative numbers");
	}
	else
	{
		auto value = *pos / 2;
		for (auto i = it_1; i != it_2; ++i)
		{
			*i += value;
		}
	}
}

template<typename Container_Type>
void modify(Container_Type& Container, int flag)
{
	typedef typename Container_Type::value_type value_type;
	typedef typename Container_Type::reverse_iterator riter;
	riter pos = find_if(Container.rbegin(), Container.rend(), [](value_type a) {return a < 0; });
	if (pos == Container.rend())
	{
		throw MyException("There are no negative numbers");
	}
	else
	{
		value_type value = *pos / 2;
		for_each(begin(Container), end(Container), [value](value_type& element)
			{
				element += value;
			});
	}
}

template<typename Container_Type>
void modify(const string& path1, const string& path2)
{
	typedef typename Container_Type::value_type value_type;
	ifstream fin;
	ofstream fout;
	fin.open(path1);
	fout.open(path2);
	if (!fin.is_open() || !fout.is_open())
	{
		CLEAR;
		cout << "File opening error\n";
	}
	else
	{
		Container_Type Container;
		ifstream fin_2(path1);
		copy(istream_iterator<value_type>(fin_2), istream_iterator<value_type>(), back_inserter(Container));
		fin_2.close();
		reverse(Container.begin(), Container.end());
		typedef typename Container_Type::iterator iter;
		iter pos = find_if(Container.begin(), Container.end(), [](value_type a) {return a < 0; });
		if (pos == Container.end())
		{
			throw MyException("There are no negative numbers");
		}
		else
		{
			value_type value = *pos / 2;
			transform(istream_iterator<value_type>(fin), istream_iterator<value_type>(), ostream_iterator<value_type>(fout, " "), [value](value_type v)
				{
					return v + value;
				});
		}
	}
}

#endif // !_MODIFY_