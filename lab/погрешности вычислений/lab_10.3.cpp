#include <iostream>
#include <math.h>
using namespace std;

void asd(const float* const array, const int m)
{
	for (int i = 0; i < m; i++)
	{
		cout << "Для значения аргумента " << array[i] << ":\n";
		printf("Значение выражения равно: %20.16f\t\t", pow(sin(array[i]), 2) + pow(cos(array[i]), 2));
		printf("\nЗначение абсолютной погрешности равно: %20.16f\n", abs(1 - (pow(cos(array[i]), 2) + pow(sin(array[i]), 2))));
		printf("Значение относительной погрешности равно: %20.16f\n\n", (abs(1 - (pow(cos(array[i]), 2) + pow(sin(array[i]), 2)))) / 1.0);
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int n;
	cout << "Введите количество элементов:\t";
	cin >> n;
	cout << "Введите значения аргумента:\n";
	float* arr = new float[n];
	for (int i = 0; i < n; i++)
	{
		cin >> *(arr + i);
	}
	cout << endl;
	asd(arr, n);
	delete[]  arr;
	return 0;
}

