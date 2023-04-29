#include "function.h"

void fill_array(int* const* arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 20;
		}
	}
}

void show_array(const int* const* arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

int number_of_rows_even(const int* const* arr, const int rows)
{
	int counter = 0;
	for (int i = 0; i < rows; i++)
	{
		if (arr[i][i] % 2 == 0)
		{
			counter++;
		}
	}
	return counter;
}

int number_of_rows_uneven(const int* const* arr, const int rows)
{
	int counter = 0;
	for (int i = 0; i < rows; i++)
	{
		if (arr[i][i] % 2 != 0)
		{
			counter++;
		}
	}
	return counter;
}

void fill_index_even(const int* const* arr, const int rows, int* const index_even, const int index_rows_even)
{
	for (int i = 0; i < index_rows_even;)
	{
		for (int j = 0; j < rows; j++)
		{
			if (arr[j][j] % 2 == 0)
			{
				index_even[i] = j;
				i++;
			}
		}
	}
}

void fill_index_uneven(const int* const* arr, const int rows, int* const index_uneven, const int index_rows_uneven)
{
	for (int i = 0; i < index_rows_uneven;)
	{
		for (int j = 0; j < rows; j++)
		{
			if (arr[j][j] % 2 != 0)
			{
				index_uneven[i] = j;
				i++;
			}
		}
	}
}

void show_info_uneven(const int* const* arr, const int rows, const int cols, int* const index_uneven, const int index_rows_uneven)
{
	cout << "\nКоличество удаляемых строк:\t" << index_rows_uneven << endl << endl;
	for (int i = 0; i < index_rows_uneven; i++)
	{
		cout << "Номер строки:\t" << index_uneven[i] + 1 << endl;
		cout << "Элемент главной диагонали:\t" << arr[index_uneven[i]][index_uneven[i]] << endl;
		cout << "Строка:\t";
		for (int j = 0; j < cols; j++)
		{
			cout << arr[index_uneven[i]][j] << "\t";
		}
		cout << endl << endl;
	}
}

void show_info_even(const int* const* arr, const int rows, const int cols, int* const index_even, const int index_rows_even)
{
	cout << "\nКоличество остающихся строк:\t" << index_rows_even << endl << endl;
	for (int i = 0; i < index_rows_even; i++)
	{
		cout << "Номер строки:\t" << index_even[i] + 1 << endl;
		cout << "Элемент главной диагонали:\t" << arr[index_even[i]][index_even[i]] << endl;
		cout << "Строка:\t";
		for (int j = 0; j < cols; j++)
		{
			cout << arr[index_even[i]][j] << "\t";
		}
		cout << endl << endl;
	}
}

void delete_rows(int**& arr, int& rows, const int cols, int* const index_even, const int index_rows_even)
{
	int** new_arr = new int* [index_rows_even];
	for (int i = 0; i < index_rows_even; i++)
	{
		new_arr[i] = new int[cols];
	}
	for (int i = 0; i < index_rows_even; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new_arr[i][j] = arr[index_even[i]][j];
		}
	}
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	rows = index_rows_even;
	arr = new_arr;
}