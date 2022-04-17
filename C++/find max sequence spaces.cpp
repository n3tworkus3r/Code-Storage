/*
	Создать функцию, которая в передаваемой строке находит наибольшее количество идущих подряд пробелов
*/

#include <iostream>

using namespace std;

void find(string str) {
	int count = 0; // Счётчик текущего количества пробелов
	int max_count = 0; // Максимальное количество пробелов
	
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') {
			count = 0; // После каждой последовательности пробелов обнуляем счётчик
			while (str.at(i) == ' ') {
				count++; // Увеличиваем счётчик на 1
				i++; // Переходим к следующему элементу строки
			}
			if (max_count < count) max_count = count;
		}
	}
	cout << "Наибольшее количество идущих подряд пробелов в строке равно " << max_count;
}

void main(){
	setlocale(LC_ALL, "");
	string str = "*   *     * * ***";
	find(str);
}