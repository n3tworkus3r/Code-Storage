#include <iostream>
#include <iomanip>			 // Библиотека для работы с манипуляторами ввода-вывода (setw, left)
#include <vector>
#include <string>			 // Библиотека для работы со строками
#include <ctime>			 // Библиотека для постоянной генерации случайных чисел
#include <conio.h>			 // Бибилиотека для работы со считыванием клавиш
#include <sstream>
#include <windows.h>
using namespace std;

// Функция для перевода из любого типа в тип string
template <typename T> // Создаём шаблонный тип, который принимает любой базовый тип данных
string to_string(T val) {
	string str; // Временная строка, в которую помещается конвертируемое значение 
	ostringstream oss;
	oss << val;
	return oss.str();
}

void print(int n, int m, vector <vector <string>> string_vector) {
	 
	for (int i = 0; i < n; i++) { // Вложенными циклами перебираем каждый элемент двумерного вектора
		for (int j = 0; j < m; j++) {
			cout << left << setw(5) << string_vector[i][j]; // Устанавливаем для элемента ширину поля 5 и выводим его
		}
		cout << endl;
	}
}

//void convert(int n, int m, vector <vector <int>>  int_vector, vector < vector <string> >  string_vector) { print(string_vector); }

void move(int n, int m, vector <vector <string>> string_vector, vector <vector <int>> int_vector) {
	// Устанавливаем значения координат текущего элемента на (0,0) - первый элемент
	int i = 0;
	int j = 0;
	string temp = string_vector[i][j]; 
	string temp2;
	string my_template = "[]"; // Шаблонная строка, для помещения в неё элементов вектора string_vector

	my_template.insert(1, temp); // Вставляем сконвертированный элемент в шаблонный элемент
	string_vector[0][0] = my_template; // Делаем 1-ый элемент массива шаблонным (заключённым в скобки)
	print(n, m, string_vector); // Выводим двумерный вектор

	while (true) {

		if (_kbhit()) { // Считывает нажатия на клаву

			switch (_getch()) { // Ждёт нажатия на клаву
			
			case 72: // Нажатие "вверх"
				while (i-1 >= 0) {									// Цикл сработает если позиция, на которую мы перемещаем элемент не превысит размер двумерного вектора
					
					my_template = "[]";								// Создаём шаблонную строку
					temp = to_string(int_vector[i][j]);				// Значение текущего элемента из вектора int переводим в строковое и записываем в переменную temp
					temp2 = string_vector[i-1][j];					// В переменую temp2 помещаем элемент, находящийся выше текущего (т.к. этот цикл case при нажатии клавиши "вверх")
					my_template.insert(1, temp2);					// Помещаем значение temp2 в шаблоннную строку  (x -> [x])
					string_vector[i-1][j] = my_template;			// В двумерном векторе string заменяем элемент, стоящий выше текущего на шаблонный
					string_vector[i][j] = temp;						// Текущий элемент переводим из шаблонного в обычный ( [z] -> z)
					system("cls");									// Очищаем консоль
					print(n, m, string_vector);						// Выводим измененённый вектор string
					cout << "Up" << endl;							// Выводим последнее перемещение
					cout << "\nEnter - заменить элемент" << endl;	// Выводим строку 
					i--;											// Изменяем индекс текущего элемента
					break;
				}
				break;
			case 80: // Нажатие "вниз"
				while (i+1 < n) {
					my_template = "[]"; // Создаём шаблонную строку
					temp = to_string(int_vector[i][j]);
					temp2 = string_vector[i + 1][j];
					my_template.insert(1, temp2);
					string_vector[i + 1][j] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Down" << endl;
					cout << "\nEnter - заменить элемент" << endl;
					i++;
					break;
				}
				break;
			case 75: // Нажатие "влево"
				
				while (j - 1 >= 0 ) {
					my_template = "[]"; // Создаём шаблонную строку
					temp = to_string(int_vector[i][j]);
					temp2 = string_vector[i][j - 1];
					my_template.insert(1, temp2);
					string_vector[i][j - 1] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Left" << endl;
					cout << "\nEnter - заменить элемент" << endl;
					j--;
					break;
				}
				break;
			case 77: // Нажатие "вправо"
				while (j+1 < m) {
					my_template = "[]";									// Создаём шаблонную строку
					temp = to_string(int_vector[i][j]);
					temp2 = string_vector[i][j+1];
					my_template.insert(1, temp2);
					string_vector[i][j+1] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Right" << endl;
					cout << "\nEnter - заменить элемент" << endl;
					j++;
					break;
				}
				break;
			case 13: // Нажатие "Enter"
				int x = 0;
				cout << "Введите новое значение: ", cin >> x;			// После нажатия Enter вводим новое значение
				while (j + 1 < m) {
					my_template = "[]";									// Создаём шаблонную строку
					int_vector[i][j] = x;								// Значение из вектора int заменяем на введённое 
					temp = to_string(int_vector[i][j]);					// Далее по аналогии...
					temp2 = string_vector[i][j + 1];
					my_template.insert(1, temp2);
					string_vector[i][j + 1] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Right" << endl;
					cout << "\nEnter - заменить элемент" << endl;
					j++;
					break;
				}
				break;
			}
		}
	}
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int m, n;
	int num = 0;
	cout << "Введите размер массива (n, m): ", cin >> n >> m;
	vector < vector <int> >  int_vector(n, vector <int>(m)); // Объявление вектора на n строк по m элементов 
	vector < vector <string> >  string_vector(n, vector <string>(m)); // Создаём ещё один вектор состоящий из векторов строк

	srand(time(NULL)); // Генератор случайных чесил для функции rand()

	// Заполнение двумерного вектора
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			num = rand()%100;
			int_vector[i][j] = num;
		}
	}

	cout << endl;

	string convert_str;		// Создаём пустую строку, которая будет принимать значение int из двумерного вектора int_vector 

	for (int i = 0; i < n; i++) { // Вложенными циклами перебираем каждый элемент двумерного вектора
		for (int j = 0; j < m; j++) {
			convert_str = to_string(int_vector[i][j]);  // Конвертируем каждый элемент вектора int_vector из типа int в тип string
			string_vector[i][j] = convert_str; // Добавляем конвертированный элемент в вектор строк - string_vector
		}
	}

	move(n, m, string_vector, int_vector); // Вызываем функцию пермещения

	return 0;
}