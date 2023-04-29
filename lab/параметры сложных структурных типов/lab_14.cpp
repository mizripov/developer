#include "function.h"

int main()
{
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));
	int N, M;
	cout << "Введите количество строк матрицы в диапазоне [1;10]:\t";
	cin >> N;
	while ((N <= 0) || (N > 10))
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
	for (int j = 0; j < M; j++)
	{
		cout << "В " << j + 1 << " столбце среднее арифметическое элементов равно: " << fixed << setprecision(5) << calculate_average_in_column(arr, N, j) << endl;
	}
	for (int i = 0; i < N; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
	return 0;
}