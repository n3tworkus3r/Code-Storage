#include <iostream>
#include <ctime>

using namespace std;

// Вывод  2-d матрицы
void print(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		cout << endl;
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
	}
}

// Вывод  1-d матрицы
void print(int* array, int n) {
	for (int i = 0; i < n; i++)
		cout << array[i] << " ";
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////
// Для двумерной матрицы и вектора
void row_multiply_2d(int** matrix, int* vector, int n) {

	cout << "\nMatrix(2d):";
	print(matrix, n);
	cout << endl;

	int** square = new int* [n];
	for (int i = 0; i < n; i++)
		square[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			square[i][j] = 0;

    // Матрица в квадрате:
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			for (int k = 0; k < n; k++) 
				square[i][j] += matrix[i][k] * matrix[k][j];
			
	cout << "\nMatrix(2d) in power 2:";

	print(square, n);

	cout << endl;
	// Вектор c - произведение a*a*b
	int* c = new int[n];
	for (int j = 0; j < n; j++)
		c[j] = 0;

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			c[j] += vector[i] * square[i][j];
		
	cout << endl;
	cout << "Row multiply result(2d):" << endl;

	for (int i = 0; i < n; i++) {
		cout << c[i] << " ";
	}
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////

void col_multiply_2d(int** matrix, int* vector, int n) {

	int* result=new int[n];
	for (int i = 0; i < n; i++) {
		result[i] = 0;
	}

	int** square = new int* [n];
	for (int i = 0; i < n; i++)
		square[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			square[i][j] = 0;


	// Матрица в квадрате:
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				square[i][j] += matrix[i][k] * matrix[k][j];
			}
		}
	}

	// Алгоритм умножения
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result[i] += square[i][j] * vector[j]; //Суммируем по строке
		}
	}
	cout << "\n\nColumn multiply result(2d)\n";
	print(result, n);
}

///////////////////////////////////////////////////////////////////////////////////

void row_multiply_1d(int* array, int* vector, int n) {

	cout << "\nMatrix(1d):\n";
	print(array, n * n);

	int* result = new int[n];
	for (int i = 0; i < n; i++)
		result[i] = 0;

	int* square = new int [n*n];
	for (int i = 0; i < n * n; i++)
		square[i] = 0;
	
	cout << "\nMatrix(1d) in power 2:\n";
	
	for (int i = 0; i < n ; i++) {
		for (int j = 0; j < n; j++) {
			int temp = 0;
			for (int k = 0; k < n; k++) {
				temp += array[i * n + k] * array[k* n + j];

				square[i * n + j] = temp;
			}
		}
	}

	print(square, n * n);

	//Алгоритм умножения
	for (int i = 0; i < n ; i++) {//Итерирует элементы array
		int temp = 0;//обнуление элементов блока
		for (int j = 0; j < n; j++) {//итерирует элементы вектора
			temp += square[i + n * j] * vector[j];//n*j-изменение блока,i-изменение элементов в блоке
		}
		result[i] = temp;
	}
	cout << "\nresult(1d)" << endl;
	print(result, n);
}

///////////////////////////////////////////////////////////////////////////////////


int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	int n = 3;
	int k = 0;

	int** matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			k++;
			matrix[i][j] = k;//rand() % 10 + 2;
		}
	}

	int* array = new int[n * n];
	for (int i = 0; i < n * n; i++)
		array[i] = i + 1;//rand() % 10 + 2;


	int* vector = new int[n];
	for (int i = 0; i < n; i++)
		vector[i] = rand() % 10 + 2;

	
	cout << endl << "\nVector b:\n";
	print(vector, n);

	row_multiply_2d(matrix, vector, n);
	col_multiply_2d(matrix, vector, n);
	row_multiply_1d(array, vector, n);
	//col_multiply_1d(array, n,vector);
	return 0;
}
