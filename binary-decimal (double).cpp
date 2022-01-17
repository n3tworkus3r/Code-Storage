/*
	Преобразовать строку в с двоичным числом в вещественное
*/

#include <iostream>

using namespace std;

void binary_to_decimal(string bin) {

	auto dot_index=bin.find_first_of('.', 0); // Находим индекс точки в строке
	auto int_sum = 0;
	auto i = 0;

	while (bin.at(i) != '.') {
		if (bin.at(i) =='1')
			int_sum += pow(2, dot_index - i - 1); // Если находим единицу, умножаем её на 2 в степени её разряда
		
		i++;
	}

	i = dot_index;  // Переходим к индексу точки
	i++;  // Переходим к элементу следующему за точкой
	double frac_sum = 0.0;

	while (i < bin.length()) {
		if (bin.at(i) == '1') {
			int degrees = 0 -(i - dot_index);  // Получаем отрицательную степень
			frac_sum += pow(2,degrees); // Умножаем на 2 в степени разряда после запятой
		}
		i++;
	}

	double decimal = int_sum + frac_sum; 
	cout << decimal;
}

int main() {
	setlocale(LC_ALL, "");	
	string binary;
	cout << "Введите двоичное число:\t", cin >> binary;
	binary_to_decimal(binary);
	return 0;
}