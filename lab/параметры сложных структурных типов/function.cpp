#include "function.h"

void fill_array(int* const* arr, const int N, const int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			arr[i][j] = rand() % 50;
		}
	}
}

void show_array(const int* const* arr, const int N, const int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
}

double calculate_average_in_column(const int* const* arr, const int N, const int number)
{
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += arr[i][number];
	}
	return sum / (double)N;
}
