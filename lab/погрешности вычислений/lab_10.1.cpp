#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	long double y = 1.0, ap, op;
	printf("До преобразований y =%20.16f\n", y);
	y = y / 3;
	printf("Представление числа 1/3 в памяти y =%20.16f\n", y);
	printf("Точное представление числа 1/3 =%20.16f\n", 1.0 / 3.0);
	ap = abs(1.0 / 3.0 - y);
	op = ap / (abs(1.0 / 3.0));
	printf("Абсолютная погрешность представления 1/3 равна ap =%20.16f\n", ap);
	printf("Относительная погрешность представления 1/3 равна op =%20.16f\n", op);
	y = y / 6000;
	y = exp(y);
	y = sqrt(y);
	y = y / 14;
	y = 14 * y;
	y = pow(y, 2);
	y = log(y);
	y = 6000 * y;
	y = y * 3;
	printf("После преобразований y =%20.16f\n", y);
	ap = abs(1 - y);
	op = ap / 1.0;
	printf("Абсолютная погрешность равна ap =%20.16f\n", ap);
	printf("Относительная погрешность равна op =%20.16f\n", op);
	return 0;
}
