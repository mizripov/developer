#include "function.h"
#define TAB "======================================================================================\n"

int main()
{
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));
	int rows, cols;
	cout << "Введите размер квадратной матрицы N*N в диапазоне [1;10]: ";
	cin >> rows;
	while ((rows <= 0) || (rows > 10))
	{
		cout << "Вы нарушили размеры диапазона!\nВведите корректный размер: ";
		cin >> rows;
	}
	cols = rows;
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	cout << TAB;
	fill_array(arr, rows, cols);
	cout << "Исходная матрица " << rows << "*" << cols << ":\n";
	show_array(arr, rows, cols);
	cout << TAB;
	int index_rows_even = number_of_rows_even(arr, rows);
	int* index_even = new int[index_rows_even];
	fill_index_even(arr, rows, index_even, index_rows_even);
	int index_rows_uneven = number_of_rows_uneven(arr, rows);
	int* index_uneven = new int[index_rows_uneven];
	fill_index_uneven(arr, rows, index_uneven, index_rows_uneven);
	show_info_uneven(arr, rows, cols, index_uneven, index_rows_uneven);
	cout << TAB;
	show_info_even(arr, rows, cols, index_even, index_rows_even);
	delete_rows(arr, rows, cols, index_even, index_rows_even);
	cout << TAB;
	cout << "Полученная матрица " << rows << "*" << cols << ":\n";
	show_array(arr, rows, cols);
	delete[] index_uneven;
	delete[] index_even;
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}