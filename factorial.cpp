/*
    Create a function to calculate the factorial of a number
	# Создать функцию для вычисления факториала числа
*/

#include <iostream>

using namespace std;

int factorial(int n) {
	int f;
	(n == 0) ? f = 1 :	f = n * factorial(n - 1);
	return f;
}

int main() {
	setlocale(LC_ALL, "");
	int a;
	cout << "Enter a number: ", cin >> a;
	cout << factorial(a) << endl;
	return 0;
}

