/*
	Создать функцию, которая считает максимальное количество нулевых элементов в одномерном массиве.
*/

#include <iostream>
#include <ctime>

using namespace std;

void counting_zeros(int* array, int n) { // *array - указатель на первый элемент в массиве
	int count = 0; // Счётчик количества нулей в массиве
	for (int i = 0; i < n; i++) 
		if (array[i] == 0)
			count++;
	cout << "\nКоличество нулевых элементов в массиве равно " << count;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));

	int n;
	cout << "Введите размерность массива: ", cin >> n;

	int* array = new int [n];
	for (int i = 0; i < n; i++) {		
		array[i] = rand() % 3; // Присваиваем элементу массива случайное значение в диапазоне от 0 до 2-х
		cout << array[i] << " "; // Выводим элемент массива
	}
	
	counting_zeros(array, n);
	return 0;
}