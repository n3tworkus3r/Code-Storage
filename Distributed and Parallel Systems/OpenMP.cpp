#include <iostream>
#include <iomanip>
#include "omp.h"

/*
	Вариант 1
	Для введенной матрицы A размера n×n подсчитайте минимум среди всех сумм по столбцам значений в строках с четными номерами.
*/

using namespace std;

int main() {

	srand(time(NULL));

	int n, k, sum = 0;
	cout << "Array amount: ", cin >> n;
	cout << "Threads number: ", cin >> k;

	//////////// ARRAYS CREATING /////////////

	int** array = new int*[n];

	////////// FILLING AND OUTPUT ///////////

	//int value = 1;
	for (int i = 1; i <= n; i++) {
		array[i] = new int[n];
		for (int j = 1; j <= n; j++) {
			//array[i][j] = value;
			array[i][j] = rand() % 10 + 1;
			//value++;
			cout << setw(5) << array[i][j] << " ";
		}
		cout << endl;
	}

	/////////////////////////////////////////

	omp_set_num_threads(k);

	////////////// ALGORITHM ////////////////

	#pragma omp parallel reduction(+:sum)
	{
		int* columns = new int[n];

		#pragma omp for

		for (int i = 1; i <= n; i++) {
			sum = 0;
			cout << "\nelements:\n";

			for (int j = 2; j <= n; j+=2) {
				sum += array[j][i];
				cout << array[j][i] << " ";
			}

			columns[i] = sum;
			cout << endl << "sum[" << i << "] = " << sum << endl;
		}

		//////////// FIND MIN VALUE /////////////

		int min = columns[1];
		for (int i = 1; i <= n; i++)
			if (columns[i] < min)
				min = columns[i];

		cout << "\n\tRESULT:\nmin sum = " << min;

		/////////////////////////////////////////

	}


	return 0;
}