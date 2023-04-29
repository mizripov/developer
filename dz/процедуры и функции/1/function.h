#pragma once
#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <iostream>
#include <ctime>
using namespace std;

// ��������� ������� ���������� �������
void fill_array(int* const* arr, const int rows, const int cols);

// ������� ������� �� �����
void show_array(const int* const* arr, const int rows, const int cols);

// ���������� ���������� �����, � ������� �������, ������������� �� ������� ��������� ������
int number_of_rows_even(const int* const* arr, const int rows);

// ���������� ���������� �����, � ������� �������, ������������� �� ������� ��������� ��������
int number_of_rows_uneven(const int* const* arr, const int rows);

// ��������� ������ ��������� �����, � ������� �������, ������������� �� ������� ��������� ������
void fill_index_even(const int* const* arr, const int rows, int* const index_even, const int index_rows_even);

// ��������� ������ ��������� �����, � ������� �������, ������������� �� ������� ��������� ��������
void fill_index_uneven(const int* const* arr, const int rows, int* const index_uneven, const int index_rows_uneven);

// ������� ��� ���������� �� ��������� �������
void show_info_uneven(const int* const* arr, const int rows, const int cols, int* const index_uneven, const int index_rows_uneven);

// ������� ��� ���������� �� ����������� �������
void show_info_even(const int* const* arr, const int rows, const int cols, int* const index_even, const int index_rows_even);

// ������� ������, � ������� �������, ������������� �� ������� ��������� ��������
void delete_rows(int**& arr, int& rows, const int cols, int* const index_even, const int index_rows_even);
#endif

