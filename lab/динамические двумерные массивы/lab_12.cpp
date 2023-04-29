#include <iostream>
#include <ctime>
//#define TEST
using namespace std;

void fill_array(int* const* arr, const int N, const int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			arr[i][j] = rand() % 10;
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

void show_address_of_last(const int* const* arr, const int N, const int M)
{
	for (int i = 0; i < N; i++)
	{
#ifdef TEST
		cout << "Адрес первого элемента в " << i+1 << " строке для проверки: \t" << (*(arr + i) + 0) << endl;
#endif
		cout << arr[i][M-1] << " (" << (i + 1) << " строка) имеет адрес:\t" << (*(arr + i)+(M-1)) << endl;
	}
}

int calculate_average(const int* const arr, const int M)
{
	int sum = 0;
	for (int j = 0; j < M; j++)
	{
		sum += arr[j];
	}
	return sum / M;
}

void swap_average_on_last(int* const* arr, const int N, const int M)
{
	for (int i = 0; i < N; i++)
	{
		arr[i][M - 1] = calculate_average(arr[i], M);
	}
}

void show_average(const int* const* arr, const int N, const int M)
{
	for (int i = 0; i < N; i++)
	{
		cout << "В " << i+1 << " строке среднее арифметическое равно:\t" << calculate_average(arr[i], M) << endl;
	}
}

void formatted_output(const int* const* arr, const int N, const int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1 - i; j++)
		{
			cout << "\t";
		}
		for (int k = 0; k < M; k++)
		{
			cout << arr[i][k] << "\t";
		}
		cout << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));
	int N, M;
	cout << "Введите количество строк матрицы в диапазоне [1;10]:\t";
	cin >> N;
	while ((N <= 0)||(N > 10))
	{
		cout << "Соблюдайте диапазон значений [1;10]\n";
		cout << "Введите корректное число строк:\t";
		cin >> N;
	}
	cout << "Введите количество столбцов матрицы в диапазоне [1;10]:\t";
	cin >> M;
	while ((M <= 0) || (M > 10))
	{
		cout << "Соблюдайте диапазон значений [1;10]\n";
		cout << "Введите корректное число столбцов:\t";
		cin >> M;
	}
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		arr[i] = new int[M];
	}
	fill_array(arr, N, M);
	cout << "Исходная матрица " << N << "*" << M << ":\n";
	show_array(arr, N, M);
	show_address_of_last(arr, N, M);
	show_average(arr, N, M);
	swap_average_on_last(arr, N, M);
	cout << "Полученная матрица " << N << "*" << M << ":\n";
	show_array(arr, N, M);
	cout << "Форматированный вывод полученной матрицы:\n";
	formatted_output(arr, N, M);
	for (int i = 0; i < N; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}