/*
	Определить объединение с битовыми полями для представления заданной информации.
	Описать функцию вывод полей на экран.
	Сгенерировать случайный массив таких структур.
	Отсортировать элементы массива стандартной фенкцией std::sort.
	Найти повторяющиеся элементы и вывести их на экран.

	Объединяющий тип unsigned short для хранения положения стрелок часов.
	Битовые поля: час (0-11), минута(0-59), секунда(0-59).
*/

#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

struct Time {
	unsigned short hours : 4;
	unsigned short minutes : 8;
	unsigned short seconds : 8;
};

void print(Time* array,int n) {
	for (int i = 0; i < n; i++) 
		cout << array[i].hours << "." << array[i].minutes << "." << array[i].seconds << endl;
}

bool hours_comparator(Time a, Time b) {
	return a.hours > b.hours;
}

void repeat(Time* array, int n) {
	cout << "repeat: \n";
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++)
			if (array[i].hours == array[j].hours && array[i].minutes == array[j].minutes && array[i].seconds == array[j].seconds)
				count++;
		
		if (count > 1)
			cout << array[i].hours << "." << array[i].minutes << "." << array[i].seconds << endl;
	}
}

int main() {
	srand(time(NULL));
	int n=rand()%30 + 20;
	Time* array=new struct Time[n];
	for (int i = 0; i < n; i++) {
		array[i].hours = rand() % 5;
		array[i].minutes = rand() % 10;
		array[i].seconds = rand() % 10;
	}

	print(array, n);
	cout << endl;

	cout << "sort:\n";
	sort(array,array+n, hours_comparator);
	print(array, n);
	cout << endl;

	repeat(array, n);
	cout << endl;

	return 0;
}