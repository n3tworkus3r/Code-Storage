/*
	Создать функцию, которая увеличивает на 5% элементы массива, большие чем LIMIT.
	Значение LIMIT вводится пользователем.
*/

#include <iostream>
#include <ctime>

using namespace std;

void grow(double* array, int n, int LIMIT) {
	double five = 0; // Переменная для хранения 5% от элемента массива
	for (int i = 0; i < n; i++) {
		if (LIMIT < array[i]) {
			five = array[i] * 0.05;  // Высчитываем 5% для каждого элемента массива, больше limit
			array[i]+=five; // Прибавляем к элементу 5%
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	int LIMIT, n, num = 0;
	cout << "Введите размерность массива: ", cin >> n;
	cout << " Введите limit: ", cin >> LIMIT;

	double* array = new double[n];

	for (int i = 0; i < n; i++) {
		//cout << "Введите элемент массива: ", cin >> array[i];
		num = rand() % 10;
		array[i] = num;
		cout << array[i] << "\t";
	}

	cout << endl;
	grow(array, n, LIMIT);

	for (int i = 0; i < n; i++) 
		cout << array[i] << "\t";
	return 0;
}