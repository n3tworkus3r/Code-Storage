#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
/*
АиСД. Лабораторная работа №4
Беляев Максим Сергеевич

Задание. Реализовать 5 алгоритмов сортировок:
1.	сортировка выбором
2.	сортировка вставками
3.	сортировка обменом


Провести экспериментальное сравнение производительности работы алгоритмов:
	  - оценить число операций сравнения и число операций обмена (перемещений) элементов;
	  - время работы (в милисекундах).
Сравнение методов сортировки провести для n = 10, 100, 1 000, 10 000 и следующем порядке входных элементов:
	  - элементы уже упорядочены;
	  - элементы упорядочены в обратном порядке;
	  - расстановка элементов случайна.
*/

using namespace std;

void print_header(string sort_name) {
	cout << "\n" << setw(50) << sort_name << setw(30) << "" << endl;
	cout << "|    n    |" << " Параметр |" << " По возрастанию |" << " По убыванию |" << " Случайный порядок |" << " Среднее значение |" << endl;
	cout << "|------------------------------------------------------------------------------------------|" << endl;
}

void print_table(int a_compares, int d_compares, int r_compares, int a_swaps, int d_swaps, int r_swaps, double a_seconds,double d_seconds, double r_seconds, int n) {	
	cout << "|" << setw(10) << "|" << " Compare  |" << setw(15) << a_compares << setw(13) << d_compares << setw(20) << r_compares << setw(20) << (a_compares+ d_compares+ r_compares) / 3 << " |" << endl;
	cout << "|" << setw(5) << n << setw(5) <<  "|" << " Swap     |" << setw(15) << a_swaps << setw(13) << d_swaps << setw(20) << r_swaps << setw(20) << (a_swaps + d_swaps + r_swaps) / 3 << " |" << endl;
	cout << "|" << setw(10) << "|" << " Time     |" << setw(15) << a_seconds << setw(13) << d_seconds << setw(20) << r_seconds << setw(20) << (a_seconds + d_seconds + r_seconds) / 3 << " |" << endl;
	cout << "|------------------------------------------------------------------------------------------|" << endl;

}

void selection_sort(int n) {
	int a_swaps = 0, a_compares = 0; double a_seconds;
	int d_swaps = 0, d_compares = 0; double d_seconds;
	int r_swaps = 0, r_compares = 0; double r_seconds;

	// Массив по возрастанию
	int* asc_arr = new int[n];
	for (int i = 0; i < n; i++) {
		asc_arr[i] = i + 1;
	}

	// Массив по убыванию
	int* des_arr = new int[n];
	for (int i = 0; i < n; i++) {
		des_arr[i] = n - i;
	}

	// Массив случайных чисел
	int* rand_arr = new int[n];
	for (int i = 0; i < n; i++) {
		rand_arr[i] = rand() % n;
	}

	//////////////////////////////////////////////////////////////////
	//					 Ascending array							//
	clock_t start = clock();
	for (int startIndex = 0; startIndex < n - 1; ++startIndex) {
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
		// Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		int smallestIndex = startIndex;

		// Затем ищем элемент поменьше в остальной части массива
		for (int currentIndex = startIndex + 1; currentIndex < n; ++currentIndex) {
			// Если мы нашли элемент, который меньше нашего наименьшего элемента,
			if (asc_arr[currentIndex] < asc_arr[smallestIndex]) {
				// то запоминаем его
				smallestIndex = currentIndex;
				a_compares++;
			}
		}
		// smallestIndex теперь наименьший элемент. 
		// Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
		swap(asc_arr[startIndex], asc_arr[smallestIndex]);
		a_swaps++;
	}
	clock_t finish = clock();
	a_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	//					Descending array							//
	start = clock();
	for (int startIndex = 0; startIndex < n - 1; ++startIndex) {
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
		// Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		int smallestIndex = startIndex;

		// Затем ищем элемент поменьше в остальной части массива
		for (int currentIndex = startIndex + 1; currentIndex < n; ++currentIndex) {
			// Если мы нашли элемент, который меньше нашего наименьшего элемента,
			if (des_arr[currentIndex] < des_arr[smallestIndex]) {
				// то запоминаем его
				smallestIndex = currentIndex;
				d_compares++;
			}
		}
		// smallestIndex теперь наименьший элемент. 
		// Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
		swap(des_arr[startIndex], des_arr[smallestIndex]);
		d_swaps++;
	}
	finish = clock();
	d_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	//					    Random array				  		    //
	start = clock();
	for (int startIndex = 0; startIndex < n - 1; ++startIndex) {
		// В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
		// Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
		int smallestIndex = startIndex;

		// Затем ищем элемент поменьше в остальной части массива
		for (int currentIndex = startIndex + 1; currentIndex < n; ++currentIndex) {
			// Если мы нашли элемент, который меньше нашего наименьшего элемента,
			if (rand_arr[currentIndex] < rand_arr[smallestIndex]) {
				// то запоминаем его
				smallestIndex = currentIndex;
				r_compares++;
			}
		}
		// smallestIndex теперь наименьший элемент. 
		// Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
		swap(rand_arr[startIndex], rand_arr[smallestIndex]);
		r_swaps++;
	}
	finish = clock();
	r_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	print_table(a_compares, d_compares, r_compares, a_swaps, d_swaps, r_swaps, a_seconds, d_seconds, r_seconds, n);
}

void insert_sort(int n) {
	int a_swaps = 0, a_compares = 0; double a_seconds;
	int d_swaps = 0, d_compares = 0; double d_seconds;
	int r_swaps = 0, r_compares = 0; double r_seconds;

	// Массив по возрастанию
	int* asc_arr = new int[n];
	for (int i = 0; i < n; i++) {
		asc_arr[i] = i + 1;
	}

	// Массив по убыванию
	int* des_arr = new int[n];
	for (int i = 0; i < n; i++) {
		des_arr[i] = n - i;
	}

	// Массив случайных чисел
	int* rand_arr = new int[n];
	for (int i = 0; i < n; i++) {
		rand_arr[i] = rand() % n;
	}

	//////////////////////////////////////////////////////////////////
	//					 Ascending array							//
	clock_t start = clock();

	int key = 0;
	int temp = 0;
	for (int i = 0; i < n - 1; i++) { // Итерация всех элементов исходного массива
		key = i + 1; // Позиция выбираемого элемента
		temp = asc_arr[key]; // Выбираемый элемент
		for (int j = i + 1; j > 0; j--) { // Итерация по убыванию по проверенным эл-там
			if (temp < asc_arr[j - 1]) { // Если найден элемент меньший, чем выбираемый
				a_compares++;
				asc_arr[j] = asc_arr[j - 1]; // Смещаем все элементы на одну позицию вправо
				key = j - 1;
			}
		}
		asc_arr[key] = temp; // Меняем местами эл-ты
		a_swaps++;
	}

	clock_t finish = clock();
	a_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	//					Descending array							//
	start = clock();

	key = 0;
	temp = 0;
	for (int i = 0; i < n - 1; i++) {
		key = i + 1;
		temp = des_arr[key];
		for (int j = i + 1; j > 0; j--) {
			if (temp < asc_arr[j - 1]) {
				d_compares++;
				des_arr[j] = des_arr[j - 1];
				key = j - 1;
			}
		}
		des_arr[key] = temp;
		d_swaps++;
	}

	finish = clock();
	d_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	//					    Random array				  		    //
	start = clock();

	key = 0;
	temp = 0;
	for (int i = 0; i < n - 1; i++) {
		key = i + 1;
		temp = rand_arr[key];
		for (int j = i + 1; j > 0; j--) {
			if (temp < rand_arr[j - 1]) {
				r_compares++;
				rand_arr[j] = rand_arr[j - 1];
				key = j - 1;
			}
		}
		rand_arr[key] = temp;
		r_swaps++;
	}

	finish = clock();
	r_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	print_table(a_compares, d_compares, r_compares, a_swaps, d_swaps, r_swaps, a_seconds, d_seconds, r_seconds, n);
}

void bubble_sort(int n) {
	int a_swaps = 0, a_compares = 0; double a_seconds;
	int d_swaps = 0, d_compares = 0; double d_seconds;
	int r_swaps = 0, r_compares = 0; double r_seconds;

	// Массив по возрастанию
	int* asc_arr = new int[n];
	for (int i = 0; i < n; i++) {
		asc_arr[i] = i + 1;
	}

	// Массив по убыванию
	int* des_arr = new int[n];
	for (int i = 0; i < n; i++) {
		des_arr[i] = n - i;
	}

	// Массив случайных чисел
	int* rand_arr = new int[n];
	for (int i = 0; i < n; i++) {
		rand_arr[i] = rand() % n;
	}

	//////////////////////////////////////////////////////////////////
	//					 Ascending array							//
	clock_t start = clock();

	// Для всех элементов
	for (int i = 0; i < n - 1; i++) {
		for (int j = (n - 1); j > i; j--) { // Для всех элементов после i-ого
			if (asc_arr[j - 1] > asc_arr[j]) { // Если текущий элемент меньше предыдущего
				a_compares++;
				int temp = asc_arr[j - 1]; // Меняем их местами
				a_swaps++;
				asc_arr[j - 1] = asc_arr[j];
				asc_arr[j] = temp;
			}
		}
	}
	clock_t finish = clock();
	a_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	//					Descending array							//
	start = clock();

	// Для всех элементов
	for (int i = 0; i < n - 1; i++) {
		for (int j = (n - 1); j > i; j--) { // для всех элементов после i-ого
			if (des_arr[j - 1] > des_arr[j]) { // если текущий элемент меньше предыдущего
				d_compares++;
				int temp = des_arr[j - 1]; // меняем их местами
				d_swaps++;
				des_arr[j - 1] = des_arr[j];
				des_arr[j] = temp;
			}
		}
	}
	finish = clock();
	d_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////
	//					    Random array				  		    //
	start = clock();

	// Для всех элементов
	for (int i = 0; i < n - 1; i++) {
		for (int j = (n - 1); j > i; j--) { // для всех элементов после i-ого
			if (rand_arr[j - 1] > rand_arr[j]) { // если текущий элемент меньше предыдущего
				r_compares++;
				int temp = rand_arr[j - 1]; // меняем их местами
				r_swaps++;
				rand_arr[j - 1] = rand_arr[j];
				rand_arr[j] = temp;
			}
		}
	}
	finish = clock();
	r_seconds = (double)(finish - start) / CLOCKS_PER_SEC;
	//////////////////////////////////////////////////////////////////

	print_table(a_compares, d_compares, r_compares, a_swaps, d_swaps, r_swaps, a_seconds, d_seconds, r_seconds, n);
}


int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));

	print_header("\nСортировка выбором:\n");
	selection_sort(10);
	selection_sort(100);
	selection_sort(1000);

	print_header("\nСортировка вставками:\n");
	insert_sort(10);
	insert_sort(100);
	insert_sort(1000);

	print_header("\nСортировка обменом:\n");
	bubble_sort(10);
	bubble_sort(100);
	bubble_sort(1000);

	return 0;
}