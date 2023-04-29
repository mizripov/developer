#pragma once
#ifndef _FUNCTION_H
#define _FUNCTION_H
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
void fill_array(int* const* arr, const int N, const int M);
void show_array(const int* const* arr, const int N, const int M);
double calculate_average_in_column(const int* const* arr, const int N, const int number);
#endif
