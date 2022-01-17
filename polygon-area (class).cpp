/*
	1) Создать класс многоугольник, подсичтать его площадь.
	2) Создать класс матрица, который будет сортировать строки по наименьшему элементу в строке.
*/
#include <iostream>
#include <iomanip>

using namespace std;

class Polygon {
	int n;
	double** coordinates;

public:
	Polygon() { // коструктор по умолчанию
		this->n = 0;
		this->coordinates = new double* [n];
	}

	Polygon(int new_n) { // конструктор с параметром
		this->n = new_n;
		this->coordinates = new double* [n];
		for (int i = 0; i < n; i++) {
			coordinates[i] = new double[2];
		}
	}

	void fill() {
		for (int i = 0; i < n; i++) {
			//cout << "Вершина " << i+1 <<":\n";
			cout << "x,y: ", cin >> coordinates[i][0] >> coordinates[i][1];
			/*
			if(j == 0)
				cout <<"x: ", cin >> coordinates[i][j];
			else
				cout <<"y: ", cin >> coordinates[i][j];*/
		}
	}

	void area() {

		double sum_x = 0;

		////////////////////////

		for (int i = 0; i < n - 1; i++) {
			double temp = coordinates[i][0] * coordinates[i + 1][1];
			sum_x += temp;
			// temp = 0;
		}
		sum_x += coordinates[n - 1][0] * coordinates[0][1];

		////////////////////////

		double sum_y = 0;
		for (int i = 0; i < n - 1; i++) {
			double temp = coordinates[i][1] * coordinates[i + 1][0];
			sum_y += temp;
			// temp = 0;
		}
		sum_y += coordinates[n - 1][1] * coordinates[0][0];

		////////////////////////

		double area = abs(sum_x - sum_y);
		cout << "Площать " << n << "-угольника равна " << area/2 << endl;
	}
};


class Matrix {
	int n;
	double** matrix;

public:
	Matrix(int new_n) {
		n = new_n;
		matrix = new double* [n];

		for (int i = 0; i < n; i++) 
			matrix[i] = new double[n];
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				double number = 0;
				matrix[i][j] = ++number;
			}
		}
	}

	void fill() {
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
				cout << "matrix[" << i + 1 << "][" << j + 1 << "] = ", cin >> matrix[i][j];
	}

	void print() {
		for (int i = 0; i  < n; i++) {
			for (int j = 0; j < n; j++) 
				cout << setw(7) << matrix[i][j];
			cout << endl;
		}
		cout << endl;
	}

	void sort() {
		cout << "Рассортировано i – му наименьшему элементу строки, где i – номер строки: \n\n";
		int row = 0;
		int min = matrix[0][0];
		int min_row_index = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] > min) {
					min = matrix[i][j];
					min_row_index = j;
				}
			}
			swap(matrix[row], matrix[min_row_index]);
			row++;
		}
	}
};




int main() {
	setlocale(LC_ALL, "");

	//cout << "Задание 1\n";
	//Polygon A;
	//Polygon B(5);
	//B.fill();
	//B.area();

	int n;
	cout << "Задание 2\n";
	cout << "Введите размерность матрицы: ", cin >> n;
	Matrix A(n);
	A.fill();
	A.print();
	A.sort();
	A.print();
	system("pause");
	return 0;
}