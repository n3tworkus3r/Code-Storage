/*
	Создать функцию для вычисления факториала числа
*/

#include <iostream>

using namespace std;

int factorial(int n) {
	int f; // Переменная для факториала
	if (n == 0) // Факториал 0 равен 1
		f = 1;
	else
		f = n * factorial(n - 1); // В противном случае, высчитываем по формуле произведение в обратном порядке
	return f;
}

int main() {
	setlocale(LC_ALL, "");
	int a;
	cout << "Введите число: ", cin >> a;

	cout << factorial(a) << endl;

	return 0;
}

