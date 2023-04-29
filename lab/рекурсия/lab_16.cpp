#include <iostream>
#include <ctime>
using namespace std;

void fill_array(int* const arr, const int N)
{
	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() % 50;
	}
}

void show_array(const int* const arr, const int N)
{
	cout << "Исходный массив:\n";
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void calculate_sum_procedure(const int* const arr, const int N, int& sum)
{
	if (N > 1)
	{
		calculate_sum_procedure(arr, N - 1, sum);
	}
	sum += arr[N - 1];
}

int calculate_sum_function(const int* const arr, const int N)
{
	if (N == 1)
	{
		return arr[0];
	}
	return arr[N - 1] + calculate_sum_function(arr, N - 1);
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));
	int N, sum = 0;
	cout << "Введите размер одномерного массива:\t";
	cin >> N;
	while (N <= 0)
	{
		cout << "Количество элементов в массиве не может быть отрицательным или равным 0!\n";
		cout << "Введите корректный размер одномерного массива:\t";
		cin >> N;
	}
	int* arr = new int[N];
	fill_array(arr, N);
	show_array(arr, N);
	cout << "Сработала ФУНКЦИЯ:\n";
	cout << "Сумма элементов массива = " << calculate_sum_function(arr, N) << endl;
	calculate_sum_procedure(arr, N, sum);
	cout << "Сработала ПРОЦЕДУРА:\n";
	cout << "Сумма элементов массива = " << sum << endl;
	delete[] arr;
	return 0;
}