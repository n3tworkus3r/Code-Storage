/*
	Convert a string with a binary number to a real number
	# Преобразовать строку в с двоичным числом в вещественное
*/

#include <iostream>

using namespace std;

void binary_to_decimal(string bin) {

	auto dot_index=bin.find_first_of('.', 0); // Find the index of the point in the line ## Находим индекс точки в строке
	auto int_sum = 0;
	auto i = 0;

	while (bin.at(i) != '.') {
		if (bin.at(i) =='1')
			int_sum += pow(2, dot_index - i - 1); // If we find one, multiply it by 2 to the power of its digit  ## Если находим единицу, умножаем её на 2 в степени её разряда
		i++;
	}

	i = dot_index;  // Go to the point index  ## Переходим к индексу точки
	i++;  // Go to the element following the point ## Переходим к элементу следующему за точкой
	double frac_sum = 0.0;

	while (i < bin.length()) {
		if (bin.at(i) == '1') {
			int degrees = 0 -(i - dot_index);  // We get the negative degree ## Получаем отрицательную степень
			frac_sum += pow(2,degrees); // Multiplied by 2 decimal places ## Умножаем на 2 в степени разряда после запятой
		}
		i++;
	}

	double decimal = int_sum + frac_sum; 
	cout << decimal;
}

int main() {
	setlocale(LC_ALL, "");	
	string binary;
	cout << "������� �������� �����:\t", cin >> binary;
	binary_to_decimal(binary);
	return 0;
}