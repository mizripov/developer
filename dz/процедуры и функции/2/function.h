#pragma once
#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <iostream>
using namespace std;

void menu_text();
void menu_number_system();
int size_of_bin(int dec_number);
int size_of_oct(int dec_number);
int size_of_hex(int dec_number);
void dec_to_bin(int dec_number, int* arr, const int size);
void dec_to_oct(int dec_number, int* arr, const int size);
void dec_to_hex(int dec_number, int* arr, const int size);
#endif

