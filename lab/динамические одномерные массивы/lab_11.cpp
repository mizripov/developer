#include <iostream>
#include <iomanip>
#include <ctime>
#define TEST
using namespace std;

void fill_array(int* const arr, const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 50 - 25;
	}
}

void show_array(const int* const arr, const int n)
{
	cout << "Исходный массив:\n";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void show_address_of_negative(const int* const arr, const int n)
{
#ifdef TEST
	cout << "Адрес первого элемента массива для проверки:\t" << arr << endl;
#endif
	int counter = 0;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < 0)
		{
			cout << arr[i] << " (" << (i + 1) << " элемент) имеет адрес:\t" << (arr + i) << endl;
			counter++;
		}
	}
	if (counter == 0)
	{
		cout << "Отрицательных элементов в массиве нет\n";
		cout << "Частное от деления количества положительных элементов на количество отрицательных искаться не будет.\n";
	}
}

void count_numbers(const int* const arr, const int n, int& negative_number, int& positive_number)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < 0)
		{
			negative_number++;
		}
		else if (arr[i] > 0)
		{
			positive_number++;
		}
	}
}

void quotient(int& negative_number, int& positive_number)
{
	if (negative_number > 0)
	{
		cout << "Частное от деления количества положительных элементов на количество отрицательных равно: " << fixed << setprecision(6) << positive_number / (double)negative_number << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));
	int n;
	int negative_number = 0, positive_number = 0;
	cout << "Введите размер одномерного массива:\t";
	cin >> n;
	while (n <= 0)
	{
		cout << "Количество элементов в массиве не может быть отрицательным или равным 0!\n";
		cout << "Введите корректный размер одномерного массива:\t";
		cin >> n;
	}
	int* arr = new int[n];
	fill_array(arr, n);
	show_array(arr, n);
	count_numbers(arr, n, negative_number, positive_number);
	cout << "Количество положительных элементов в массиве:\t" << positive_number << endl;
	cout << "Количество отрицательных элементов в массиве:\t" << negative_number << endl;
	show_address_of_negative(arr, n);
	quotient(negative_number, positive_number);
	delete[] arr;
	return 0;
}