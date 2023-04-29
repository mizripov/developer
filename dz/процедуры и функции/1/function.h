#pragma once
#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <iostream>
#include <ctime>
using namespace std;

// заполн€ет матрицу случайными числами
void fill_array(int* const* arr, const int rows, const int cols);

// выводит матрицу на экран
void show_array(const int* const* arr, const int rows, const int cols);

// возвращает количество строк, у которых элемент, расположенный на главной диагонали „≈“Ќџ…
int number_of_rows_even(const int* const* arr, const int rows);

// возвращает количество строк, у которых элемент, расположенный на главной диагонали Ќ≈„≈“Ќџ…
int number_of_rows_uneven(const int* const* arr, const int rows);

// заполн€ет массив индексами строк, у которых элемент, расположенный на главной диагонали „≈“Ќџ…
void fill_index_even(const int* const* arr, const int rows, int* const index_even, const int index_rows_even);

// заполн€ет массив индексами строк, у которых элемент, расположенный на главной диагонали Ќ≈„≈“Ќџ…
void fill_index_uneven(const int* const* arr, const int rows, int* const index_uneven, const int index_rows_uneven);

// выводит всю информацию об удал€емых строках
void show_info_uneven(const int* const* arr, const int rows, const int cols, int* const index_uneven, const int index_rows_uneven);

// выводит всю информацию об Ќ≈удал€емых строках
void show_info_even(const int* const* arr, const int rows, const int cols, int* const index_even, const int index_rows_even);

// удал€ет строки, у которых элемент, расположенный на главной диагонали Ќ≈„≈“Ќџ…
void delete_rows(int**& arr, int& rows, const int cols, int* const index_even, const int index_rows_even);
#endif

