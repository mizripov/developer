#include <iostream>
using namespace std;

class Cash_Register
{
public:
	Cash_Register(const int number_10, const int number_5, const int number_2, const int number_1);
	void return_the_change(int payment);
private:
	class Coin
	{
	public:
		int value;
		int number;
		int count;
		Coin(const int value, const int number = 0)
		{
			this->value = value;
			this->number = number;
			count = 0;
		}
	};
	Coin ten{ 10 };
	Coin five{ 5 };
	Coin two{ 2 };
	Coin one{ 1 };
	int SUM;
	int calls = 0;
	void give_change(int payment)
	{
		calls++;
		if (payment == 0)
		{
			return;
		}
		if ((ten.number != 0) && (payment / ten.value > 0))
		{
			ten.number--;
			give_change(payment - ten.value);
			ten.count++;
			return;
		}
		if ((five.number != 0) && (payment / five.value > 0))
		{
			five.number--;
			give_change(payment - five.value);
			five.count++;
			return;
		}
		if ((two.number != 0) && (payment / two.value > 0))
		{
			two.number--;
			give_change(payment - two.value);
			two.count++;
			return;
		}
		if ((one.number != 0) && (payment / one.value > 0))
		{
			one.number--;
			give_change(payment - one.value);
			one.count++;
			return;
		}
	}
	void print_info()
	{
		system("cls");
		cout << "Общее количество монет составило - " << ten.count + five.count + two.count + one.count << endl;
		cout << "Количество монет каждого достоинства:\n";
		cout << "10 - " << ten.count << " - [" << ten.number << "]" << endl;
		cout << "5 - " << five.count << " - [" << five.number << "]" << endl;
		cout << "2 - " << two.count << " - [" << two.number << "]" << endl;
		cout << "1 - " << one.count << " - [" << one.number << "]" << endl;
		cout << "\nЧисло ВЫЗОВОВ рекурсивной программы - " << calls << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	int ten, five, two, one, payment;
	cout << "Введите количество монет достоинства 10, имеющихся на кассе - ";
	cin >> ten;
	cout << "Введите количество монет достоинства 5, имеющихся на кассе - ";
	cin >> five;
	cout << "Введите количество монет достоинства 2, имеющихся на кассе - ";
	cin >> two;
	cout << "Введите количество монет достоинства 1, имеющихся на кассе - ";
	cin >> one;
	Cash_Register cash(ten, five, two, one);
	cout << "Введите сумму сдачи - ";
	cin >> payment;
	cash.return_the_change(payment);
	return 0;
}

Cash_Register::Cash_Register(const int number_10, const int number_5, const int number_2, const int number_1)
{
	ten.number = number_10;
	five.number = number_5;
	two.number = number_2;
	one.number = number_1;
	SUM = ten.number * ten.value + five.number * five.value + two.number * two.value + one.number * one.value;
}

void Cash_Register::return_the_change(int payment)
{
	if (payment > SUM)
	{
		system("cls");
		cout << "В кассе недостаточно средств...\n";
	}
	else
	{
		give_change(payment);
		print_info();
	}
}
