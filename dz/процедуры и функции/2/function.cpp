#include "function.h"

void menu_text()
{
	system("cls");
	cout << "____________________����____________________\n";
	cout << "1 - ���� ����������� �����\n";
	cout << "2 - ������� � ������ ������� ���������\n";
	cout << "3 - ����� ���������� ����������� �� �����\n";
	cout << "4 - ����� �� ���������\n";
	cout << ">";
}

void menu_number_system()
{
	system("cls");
	cout << "____�����_�������_���������____\n";
	cout << "1 - � ��������\n";
	cout << "2 - � ������������\n";
	cout << "3 - � �����������������\n";
	cout << ">";
}

int size_of_bin(int dec_number)
{
	int size = 1;
	while (dec_number > 1)
	{
		size++;
		dec_number /= 2;
	}
	return size;
}

int size_of_oct(int dec_number)
{
	int size = 1;
	while (dec_number > 7)
	{
		size++;
		dec_number /= 8;
	}
	return size;
}

int size_of_hex(int dec_number)
{
	int size = 1;
	while (dec_number > 15)
	{
		size++;
		dec_number /= 16;
	}
	return size;
}

void dec_to_bin(int dec_number, int* arr, const int size)
{
	if (dec_number > 1)
	{
		dec_to_bin(dec_number / 2, arr - 1, size);
	}
	arr[size - 1] = dec_number % 2;
}

void dec_to_oct(int dec_number, int* arr, const int size)
{
	if (dec_number > 7)
	{
		dec_to_oct(dec_number / 8, arr - 1, size);
	}
	arr[size - 1] = dec_number % 8;
}

void dec_to_hex(int dec_number, int* arr, const int size)
{
	if (dec_number > 15)
	{
		dec_to_hex(dec_number / 16, arr - 1, size);
	}
	arr[size - 1] = dec_number % 16;
}