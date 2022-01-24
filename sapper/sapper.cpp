#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <string>
using namespace std;


///////////////  ВЫВОД ПОЛЯ  ////////////////
void field_print(int n, int m , vector < vector <string> > field) {

	for (int i = 1; i < n+1; i++) {
		cout << endl;
		for (int j = 1; j < m+1; j++) {
			cout << setw(3) << field.at(i).at(j);
			//cout << endl;
		}
	}
}

void output_field(int n, int m, vector < vector <string> > mask) {
	for (int i = 0; i < n + 2; i++) {
		cout << endl;
		for (int j = 0; j < m + 2; j++) {
			cout << left << setw(3) << mask.at(i).at(j);
		}
	}
}

void calculating(int n, int m, vector < vector <string> > &field) {
	for (int i = 1; i < n-1; i++) {
		for (int j = 1; j < m-1; j++) {
			if (field[i][j] != "*" ) {
					int count = 0;
					for (int s = i - 1; s <= i + 1; s++)
						for (int k = j - 1;k <= j + 1;k++)
							if (field[s][k] == "*")
								count++;

					// ПРЕОБРАЗОВАНИЕ ТИПОВ
					field[i][j] = to_string(count);

					/*
					if (mask[i-1][j-1] == "*")
						count++;

					if (mask[i-1][j] == "*")
						count++;

					if (mask[i-1][j+1] == "*")
						count++
					*/

					/*
					if (mask[i][j - 1] == "*")
						count++;

					if (mask[i][j + 1] == "*")
						count++;
					*/


					/*
					if (mask[i + 1][j - 1] == "*")
						count++;

					if (mask[i + 1][j] == "*")
						count++;

					if (mask[i + 1][j + 1] == "*")
						count++;
					*/



					//for (int k = j - 1;k <= j + 1;k++)
					//	if (mask[i - 1][k] == "*")
					//		count++;

					//for (int k = j - 1; k <= j + 1;k++)
					//	if (mask[i][k] == "*")
					//		count++;

					//for (int k = j - 1; k <= j + 1; k++)
					//	if (mask[i + 1][k] == "*")
					//		count++;
			}
			
			
			//for (int i = 0; i < n; i++) {
			//	int count = 0;
			//	int second_count = 0;
			//	int k = 0;
			//	if (k > 0 && k < m-1) {
			//		for (int k = i - 1;k <= i + 1;k++)
			//			if (mask[i][1] == "*")
			//				count++;
			//		if (mask[i][m - 2] == "*")
			//			second_count++;
			//	}

			//	if (k > 0 && k < m - 1) {
			//		for (int k = i - 1;k <= i + 1;k++)
			//			if (mask[i][1] == "*")
			//				count++;
			//		if (mask[i][m - 2] == "*")
			//			second_count++;
			//	}
			//	
			//	//if (mask[i][1] == "*")
			//	//	count++;
			//	//if (mask[i][m-2] == "*")
			//	//	second_count++;

			//	mask[i][0] = to_string(count);
			//	mask[i][m-1] = to_string(count);
			//}


		}
	}
}

void filling_fields(vector < vector <string> > &field, vector < vector <string> > &mask, int n, int m) {
	
	///////////////  ЗАПОЛЕННИЕ ПОЛЕЙ  ////////////////

	for (int i = 0; i < n + 2; i++)
		for (int j = 0; j < m + 2; j++)
			mask[i][j] = " ";

	for (int i = 0; i < n + 2; i++)
		for (int j = 0; j < m + 2; j++)
			field[i][j] = "0";

}

void add_mines(vector < vector <string> >& field, int n, int m) {
	///////////////  Заполнение минами  ////////////////
	int mines = 0;
	//mines = rand() % 10 +5; // Рандомное заполнение минами
	cout << "Введите количество мин: ", cin >> mines;

	for (int i = 0; i <= mines; i++) {
		field[rand() % n][rand() % m] = '*';
	}
}

void borders(vector < vector <string> >& field, vector < vector <string> >& mask, int n, int m) {
	////////////  Установка границ  (####)
	for (int i = 0; i < n + 2;i++) {
		mask[i][0] = "#";
		mask[i][m + 1] = "#";

		field[i][0] = "#";
		field[i][m + 1] = "#";
	}

	for (int j = 0; j < m + 2;j++) {
		mask[0][j] = "#";
		mask[n + 1][j] = "#";

		field[0][j] = "#";
		field[n + 1][j] = "#";
	}
	////////////
}

bool loser(string current) {
	if (current == "[*]") {

		cout << "\n\n\n\t\tYOU LOSE!!!!\n\n\n\n\n\n\n";
		system("pause");
		return true;
	}
	return false;
}

bool winner(vector < vector <string> >& field, vector < vector <string> >& mask, int n, int m) {
	int counter = 0;
	int mines = 0;

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (field[i][j] == "*")
				mines++;
		}
	}

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (mask[i][j] == " ")
				counter++;
		}
	}

	if (counter == mines) {
		cout << "\n\n\n\t\tYOU WIN!!!!\n\n\n\n\n\n\n";
		system("pause");
		return true;
	}
	return false;

}
void game(vector < vector <string> >& field, vector < vector <string> >& mask, int n, int m) {

	///// Установка первой позиции
	int i = 0;
	int j = 0;

	string current = "[]";
	current.insert(1, mask[i][j]);
	string temp = mask[i][j];
	mask[i][j] = current;

	////////////////////////////////////////////////////////////
	while (true) { // для бесконечного перемещения в поле
		if (_kbhit()) { // ПРоверка на нажатие на клаву
			switch (_getch()) {
			///// 13 -enter
				// 27 - Esc
				// 8 - Backspace
				// 32 - Space
				
			case 72: // UP
				while (i - 1 >= 1) {

					string current = "[]";
					current.insert(1, mask[i - 1][j]);


					mask[i][j].erase(0, 1);
					mask[i][j].erase(mask[i][j].size() - 1, mask[i][j].size() - 1);

					mask[i - 1][j] = current;

					system("cls");
					output_field(n, m, mask);

					i--;

					cout << "\n\t\t UP";
					break; // Для только одного перемещения на поле за одно нажатие
				}
				break;
			case 80: // DOWN
				while (i + 1 < n + 1) {

					string current = "[]";
					current.insert(1, mask[i + 1][j]);

					mask[i][j].erase(0, 1);
					mask[i][j].erase(mask[i][j].size() - 1, mask[i][j].size());


					mask[i + 1][j] = current;


					i++;
					system("cls");
					output_field(n, m, mask);
					cout << "\n\t DOWN";
					break;
				}
				break;
			case 75: // LEFT
				while (j - 1 >= 1) {

					string current = "[]";
					current.insert(1, mask[i][j - 1]);
					string temp = mask[i][j];

					mask[i][j].erase(0, 1);
					mask[i][j].erase(mask[i][j].size() - 1, mask[i][j].size());


					mask[i][j - 1] = current;



					system("cls");
					output_field(n, m, mask);
					j--;
					cout << "\n\t LEFT";
					break;
				}
				break;
			case 77: // RIGHT
				while (j + 1 < m + 1) {

					string current = "[]";
					current.insert(1, mask[i][j + 1]);

					mask[i][j].erase(0, 1);
					mask[i][j].erase(mask[i][j].size() - 1, mask[i][j].size());


					mask[i][j + 1] = current;


					system("cls");
					output_field(n, m, mask);
					j++;
					cout << "\n\t RIGHT";
					break;
				}
				break;
			case 32: // SPACE
				if (mask[i][j] == "[ ]") {
					string current = "[]";
					current.insert(1,"$");
					mask[i][j] = current;

					system("cls");
					output_field(n, m, mask);
					cout << "\n\t SPACE";
				}
				else
					continue;
				break;
			case 13: // ENTER
				
				mask[i][j] = field[i][j];

				string current = "[]";
				current.insert(1, mask[i][j]);

				mask[i][j] = current;

				/////// КОНЕЦ ИГРЫ
				system("cls");
				output_field(n, m, mask);

				if (winner(field, mask, n, m))
					break;
				if (loser(current))
					break;
				break;
			
			}

		}
	}
}


int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	int x;
	cout << "Введите размерность поля: ",cin >> x;
	int n = x, m = x;
	
	vector < vector <string> > mask(n + 2, vector <string>(m + 2));
	vector < vector <string> > field(n + 2, vector <string>(m + 2));


	filling_fields(field, mask, n, m);

	add_mines(field, n, m);

	borders(field, mask , n, m );

	calculating(n + 2, m + 2, field);

	game(field, mask, n, m);

	return 0;

}
