#include <iostream>
#include<tuple>
using namespace std;

tuple<int, double, string, string, string> check(double number) {
	string choice, choice_2, choice_3;

	choice = (number > 0) ? "Да" : "Нет";
	choice_2 = (int(number) % 2 == 0) ? "Да" : "Нет";
	// функция int() преобразует число, принимаемое в параметры, в целочисленный тип (int)
	double dec = number - int(number); // Число (number) минус его целая часть ( int(number) ) ## пример: 3.34 - 3 = 0.34
	if (number != 1 && number != -1)
	{
		bool prime = true;
		// в цикле перебираем числа от 2 до n - 1
		for (int i = 2; i < number; i++) {
			if (int(number) % i == 0) {// если n делится без остатка на i - возвращаем false (число не простое)
				choice_3 = "Составное";
				prime = false;
				break;
			}
		}

		// если программа дошла до данного оператора, то возвращаем true (число простое) - проверка пройдена
		if (prime == true) choice_3 = "Простое";
	}
	else {
		choice_3 = "Ни простое, ни составное";
	}

	tuple<int, double, string, string, string>t; // Создаём шаблон кортежа, схожий с типом значения, возвращаемым функцией
	t = make_tuple(int(number), dec, choice, choice_2, choice_3); // Создаём сам кортеж из указанных объектов
	return t;
}
int main() {
	setlocale(LC_ALL, "ru");
	int integer;
	double number, fractional;
	string greater_than_zero, even, prime;

	cout << "Введите число: ", cin >> number;
	tie(integer, fractional, greater_than_zero, even, prime) = check(number);

	cout << "Целая часть числа: " << integer << endl;
	cout << "Дробная часть числа: " << fractional << endl;
	cout << "Больше нуля? " << greater_than_zero << endl;
	cout << "Чётное? " << even << endl;
	cout << "Простое? " << prime << endl;
	return 0;
}