/*
	Вывести в консоль 4 типа флага для указанных с клавиатуры размерностей двумерного массива
*/ 

#include <iostream>

using namespace std;

void output(int n, int m, int** array) {
	// Выводим элементы массива
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

void cross_flag(int n, int m, int** array) {
	cout << endl << "Флаг 'Крест'" << endl;
	// Заполняем матрицу
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // Заполняем матрицу нулями
			if (i == j) 
				array[i][j] = 1; // Условие принадлежности к главной диагонали
			
			if (j == (n - 1) - i)
				array[i][j] = 1; // Условие принадлежности к побочной диагонали	
		}
	}
}

void plus_flag(int n, int m, int** array) {
	cout << endl << "Флаг 'Плюс'" << endl;
	// Заполняем матрицу
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // Заполняем матрицу нулями
			if (i == 2) {
				array[i][j] = 1; // Условие принадлежности к 3 строке
			}

			if (j == 2) {
				array[i][j] = 1; // Условие принадлежности к 3-му столбцу
			}
		}
	}
}

void frame_flag(int n, int m, int** array) {
	cout << endl << "Флаг 'Рамка'" << endl;
	// Заполняем матрицу
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // Заполняем матрицу нулями

			if (i == 0) { // Условие принадлежности к первой строке
				array[i][j] = 1;
			}
			if (j == 0) { // Условие принадлежности к первому столбцу
				array[i][j] = 1; 
			}
			if (i == n - 1) { // Условие принадлежности к последней строке
				array[i][j] = 1;
			}
			if (j == m - 1) { // Условие принадлежности к последнему столбцу
				array[i][j] = 1;
			}
		}
	}
}

void chessboard_flag(int n, int m, int** array) {
	cout << endl << "Флаг 'Шахматное поле'" << endl;
	// Заполняем матрицу
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // Заполняем матрицу нулями
			if (i % 2 != 0 && j % 2 == 0) { // Если i нечётное и j чётное
				array[i][j] = 1;
			}

			if (i % 2 == 0 && j % 2 != 0) { // Если i чётное и j нечётное
				array[i][j] = 1;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	int n, m, choice = 5;
	cout << "Введите количество строк массива ", cin >> n;
	cout << "Введите количество столбцов массива ", cin >> m;

	int** array = new int* [n];

	for (int i = 0; i < n; i++)
		array[i] = new int[m];
	
	/*
	  Индексы строк и столбцов элементов матрицы:

		11 12 13 14 15
		21 22 23 24 25
		31 32 33 34 35
		41 42 43 44 45
		51 52 53 54 55
	*/
	
	do {
		cout << "\n Выберите тип флага:";
		cout << "\n 1) Крест";
		cout << "\n 2) Плюс";
		cout << "\n 3) Рамка";
		cout << "\n 4) Шахматное поле";
		cout << "\n 5) Выход\n";
		cin >> choice;

		switch (choice) {

		case 1:
			cross_flag(n, m, array);
			output(n, m, array);
			break;
		case 2:
			plus_flag(n, m, array);
			output(n, m, array);
			break;
		case 3:
			frame_flag(n, m, array);
			output(n, m, array);
			break;
		case 4:
			chessboard_flag(n, m, array);
			output(n, m, array);
			break;
		}
	} while (choice != 5);
	return 0;
}