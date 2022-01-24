#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <tuple>
#include <iomanip>
#include <conio.h>


using namespace std;

void output_field(int n, vector < vector <string> > my, string mode) {
	for (int i = 0; i < n + 2; i++) {
		cout << endl;
		for (int j = 0; j < n + 2; j++) {
			cout << left << setw(3) << my.at(i).at(j);
		}

		if (mode == "create_ships_mode") {
			switch (i) {
			case 1:
				cout << "\tUP, DOWN, LEFT, RIGHT - MOVE";
				break;
			case 2:
				cout << "\tSPACE - INSTALL SHIP";
				break;
			case 3:
				cout << "\tENTER - ACCEPT SHIP";
				break;

			case 4:
				cout << "\tBACKSPACE - REMOVE SHIP";
				break;
			case 5:
				cout << "\tESC - FINISH SHIP INSTALLATION";
				break;
			}
		}

		if (mode == "the_game_mode") {
			switch (i) {
			case 1:
				cout << "\tUP, DOWN, LEFT, RIGHT - MOVE";
				break;
			case 2:
				cout << "\tENTER - ATTACK CELL";
				break;
			}
		}	
	}
}

void filling_fields(vector < vector <string> >& my, vector < vector <string> >& enemy, int n) {

	///////////////  ЗАПОЛЕННИЕ ПОЛЕЙ  ////////////////

	for (int i = 0; i < n + 2; i++)
		for (int j = 0; j < n + 2; j++)
			enemy[i][j] = ".";

	for (int i = 0; i < n + 2; i++)
		for (int j = 0; j < n + 2; j++)
			my[i][j] = ".";

}

void borders(vector < vector <string> >& my, vector < vector <string> >& enemy, int n) {

	
	////////////  Установка границ  (####)
	int temp = 1;
	for (int i = 1; i < n + 2;i++) {
		enemy[i][0] = to_string(temp);
		my[i][0] = to_string(temp);
		temp++;

		enemy[i][n + 1] = " ";
		my[i][n + 1] = " ";
	}

	temp = 65; // 65 - код буквы 'A' из ASCII
	for (int j = 1; j < n + 2;j++) {
		enemy[0][j] = char(temp);
		my[0][j] = char(temp);
		temp++;

		enemy[n + 1][j] = " ";
		my[n + 1][j] = " ";
	}

	/////////////

	enemy[0][0] = " ";
	my[0][0] = " ";
	enemy[0][n + 1] = " ";
	my[0][n + 1] = " ";
	enemy[n + 1][0] = " ";
	my[n + 1][0] = " ";
}

//void output_legend() {
//	cout << "\n\n\n\n"
//		<< "\tUP,DOWN,RIGHT,LEFT - MOVE\n"
//		<< "\tSPACE - INSTALL SHIP\n"
//		<< "\tENTER - ACCEPT SHIP\n"
//		<< "\tBACKSPACE - REMOVE SHIP\n"
//		<< "\tESC - FINISH SHIP INSTALLATION\n";
//}
//
//void output_second_legend() {
//	cout << "\n\n\n\n"
//		<< "\tUP,DOWN,RIGHT,LEFT - MOVE\n"
//		<< "\tENTER - ATTACK CELL\n";
//		
//}

void create_ships(vector < vector <string> >& my, vector < vector <string> >& enemy, int n) {
	bool finish = false;
	int cells = 20;
	///// Установка первой позиции
	int i = 1;
	int j = 1;

	string current = "[]";
	current.insert(1, my[i][j]);
	string temp = my[i][j];
	my[i][j] = current;

	////////////////////////////////////////////////////////////
	while (!finish) { // для бесконечного перемещения в поле
		if (_kbhit()) { // ПРоверка на нажатие на клаву
			switch (_getch()) {
				///// 13 -enter
					// 27 - Esc
					// 8 - Backspace
					// 32 - Space

			case 72: // UP
				while (i - 1 >= 1) {

					string current = "[]";
					current.insert(1, my[i - 1][j]);


					my[i][j].erase(0, 1);
					my[i][j].erase(my[i][j].size() - 1, my[i][j].size() - 1);

					my[i - 1][j] = current;

					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");
					

					i--;

					cout << "\tLAST ACTION -  UP";
					break; // Для только одного перемещения на поле за одно нажатие
				}
				break;
			case 80: // DOWN
				while (i + 1 < n + 1) {

					string current = "[]";
					current.insert(1, my[i + 1][j]);

					my[i][j].erase(0, 1);
					my[i][j].erase(my[i][j].size() - 1, my[i][j].size());


					my[i + 1][j] = current;


					i++;
					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");
					cout << "\tLAST ACTION -  DOWN";
					 

					break;
				}
				break;
			case 75: // LEFT
				while (j - 1 >= 1) {

					string current = "[]";
					current.insert(1, my[i][j - 1]);
					string temp = my[i][j];

					my[i][j].erase(0, 1);
					my[i][j].erase(my[i][j].size() - 1, my[i][j].size());


					my[i][j - 1] = current;



					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");
					j--;
					cout << "\tLAST ACTION -  LEFT";
					 
					break;
				}
				break;
			case 77: // RIGHT
				while (j + 1 < n + 1) {

					string current = "[]";
					current.insert(1, my[i][j + 1]);

					my[i][j].erase(0, 1);
					my[i][j].erase(my[i][j].size() - 1, my[i][j].size());


					my[i][j + 1] = current;


					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");
					j++;
					cout << "\tLAST ACTION -  RIGHT";
					 
					break;
				}
				break;
			case 32:// space
				if (my[i][j] == "[.]"){

					if (cells > 0) {

						string current = "[]";
						current.insert(1, "X");
						my[i][j] = current;
						cells--;

						system("cls");
						output_field(n, enemy, "the_game_mode");
						output_field(n, my, "create_ships_mode");
						cout << "\tLAST ACTION -  SPACE";
						 
					}
					else
						cout << "\t ALL SHIPS FINISHED!";
				}
				else
					continue;

				break;
			case 13: // ENTER

				for (int i = 1; i < n + 1; i++) {
					for (int j = 1; j < n + 1; j++) {
						if (my[i][j] == "X" || my[i][j] == "[X]") {
							for (int s = i - 1; s <= i + 1; s++)
								for (int k = j - 1;k <= j + 1;k++)
									if (my[s][k] == "." || my[s][k] == "[.]")
										my[s][k] = " ";
						}	
					}
				}
				system("cls");
				output_field(n, enemy, "the_game_mode");
				output_field(n, my, "create_ships_mode");
				cout << "\tLAST ACTION -  ENTER";
				 
				break;
			case 8: // backspace
					if (my[i][j] == "[X]") {

						string current = "[]";
						current.insert(1, ".");
						my[i][j] = current;
						cells++;


						for (int s = i - 1; s <= i + 1; s++)
							for (int k = j - 1;k <= j + 1;k++)
								if (my[s][k] == " ")
									my[s][k] = ".";


						system("cls");
						output_field(n, enemy, "the_game_mode");
						output_field(n, my, "create_ships_mode");
						cout << "\n\t BACKSPACE";
						 

						

					}
					

				break;
				
			case 27:// ESC


				for (int i = 1; i < n + 1; i++) {
					for (int j = 1; j < n + 1; j++) {

						if (my[i][j] == "." || my[i][j] == "[.]" || my[i][j] == "[ ]")
							my[i][j] = " ";

						if (my[i][j] == "[X]")
							my[i][j] = "X";
					}
				}
				system("cls");
				output_field(n, enemy, "the_game_mode");
				output_field(n, my, "create_ships_mode");
				cout << "\tLAST ACTION -  ESC";
				 

				finish = true;

				


				break;
			}

		}
	}
}


void random(vector < vector < pair<int, int>>>& ships) {
	//for (int i = 0; i < ships.size(); i++) { // Перебирая каждый корабль
	//	for (int j = 0; j < ships.at(i).size(); j++) {// Перебирая каждую ячейку в корабле
	//		ships[i][j].first = rand() % 10 + 1; // Для каждой ячейки первую координату присваиваем рандомно
	//		ships[i][j].second = rand() % 10 + 1;// ... вторую координату присваиваем рандомно
	//	}
	//}
 
			ships[0][0].first = 1; 
			ships[0][0].second = 1;

			ships[0][1].first = 2;
			ships[0][1].second = 1;

			ships[0][2].first = 3;
			ships[0][2].second = 1;

			ships[0][3].first = 4;
			ships[0][3].second = 1;



			


			ships[1][0].first = 5;
			ships[1][0].second = 6;

			ships[1][1].first = 5;
			ships[1][1].second = 7;

			ships[1][2].first = 5;
			ships[1][2].second = 8;
 
}




	

void create_enemy_ships(vector < vector <string> >& enemy_ships, vector < vector < pair<int, int>>>& ships,int n) {

	for (int i = 0; i < n+2; i++)
		for (int j = 0; j < n + 2; j++)
			enemy_ships[i][j] = " ";


	//for (int k = 0; k < 20; k++)
	for (int i = 0; i < ships.size(); i++) { // Перебирая каждый корабль
		for (int j = 0; j < ships.at(i).size(); j++) {// Перебирая каждую ячейку в корабле
			enemy_ships[ships[i][j].first][ships[i][j].second] = "*";
		}
	}

	for(int i = 0; i < ships[1].size(); i++)
		enemy_ships[ships[1][i].first][ships[1][i].second] = "0";

	for (int i = 0; i < ships[0].size(); i++)
		enemy_ships[ships[0][i].first][ships[0][i].second] = "U";

	//enemy_ships[i + 1][j - 1] = rand() % 5 + 2;
	
	//enemy_ships[1][1] = "*";
	//enemy_ships[2][1] = "*";
	//enemy_ships[3][1] = "*";
	//enemy_ships[4][1] = "*";
	// 
	//enemy_ships[6][1] = "*";
	//enemy_ships[7][3] = "*";
	//enemy_ships[9][1] = "*";
	// 
	//enemy_ships[1][10] = "*";
	//enemy_ships[1][4] = "*";
	//enemy_ships[7][4] = "*";
	//enemy_ships[1][5] = "*";
	//enemy_ships[1][6] = "*";
	//enemy_ships[4][5] = "*";
	//enemy_ships[5][5] = "*";
	//enemy_ships[9][6] = "*";
	//enemy_ships[7][8] = "*";
	//enemy_ships[10][9] = "*";
	//enemy_ships[3][10] = "*";
	//enemy_ships[4][10] = "*";
	//enemy_ships[5][10] = "*";
}

void check_death(vector < vector <string> >& my, vector < vector <string> >& enemy, vector < vector <string> >& enemy_ships, int n, string mode) {
	bool death = false;
	string symbol = "";
	string sec_symbol = "";
	sec_symbol.push_back(char(135));
	symbol.push_back(char(134));


	if (mode == "enemy_attack") {
		for (int i = 1; i < n + 1; i++) {
			for (int j = 1; j < n + 1; j++) {

				if (my[i][j] == symbol) {
					my[i][j] = sec_symbol;
					death = true;
					for (int s = i - 1; s <= i + 1; s++)
						for (int k = j - 1;k <= j + 1;k++)
							if (my[s][k] == "X") {
								death = false;
								break;
							}

				}
			}
		}

		if (death) {
			for (int i = 1; i < n + 1; i++)
				for (int j = 1; j < n + 1; j++)
					if (my[i][j] == sec_symbol)
						for (int s = i - 1; s <= i + 1; s++)
							for (int k = j - 1;k <= j + 1;k++)
								if (my[s][k] == " ")
									my[s][k] = "o";
		}
	}

	if(mode =="my_attack") {
		for (int i = 1; i < n + 1; i++) {
			for (int j = 1; j < n + 1; j++) {

				if (enemy[i][j] == "*" || enemy[i][j] == "[*]") {
					enemy[i][j] = "[X]";
					enemy_ships[i][j] = "X";
					death = true;
					for (int s = i - 1; s <= i + 1; s++)
						for (int k = j - 1;k <= j + 1;k++)
							if (enemy[s][k] == "*") {
								death = false;
								break;
							}


				}
			}			
		}

		if (death) {
			for (int i = 1; i < n + 1; i++)
				for (int j = 1; j < n + 1; j++)
					if (enemy_ships[i][j] == "[X]" || enemy_ships[i][j] == "X")
						for (int s = i - 1; s <= i + 1; s++)
							for (int k = j - 1;k <= j + 1;k++)
								if (enemy[s][k] == ".")
									enemy[s][k] = " ";
		}
	}
}

void enemy_attack(vector < vector <string> >& my, int n) {
	
	// 134
	//
	string symbol = "";
	symbol.push_back(char(134));

	string sec_symbol = "";
	sec_symbol.push_back(char(135));

	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++)
			if (my[i][j] == "O")
				my[i][j] = "o";

	////// АЛГОРИТМ СТРЕЛЬБЫ
	int i = 0;
	int j = 0;

	do {
		i = rand() % n + 1;
		j = rand() % n + 1;
	} while (my[i][j] == "o" || my[i][j] == "O" || my[i][j] == symbol || my[i][j] == sec_symbol);

	
	if (my[i][j] == "X")
		my[i][j] = symbol;
	else 
		my[i][j] = "O";


	
	
	
}

void start_game(vector < vector <string> >& enemy, vector < vector <string> >& my, vector < vector <string>> &enemy_ships , int n ) {


	bool finish = false;
	int cells = 20;
	///// Установка первой позиции
	int i = 1;
	int j = 1;

	string current = "[]";
	current.insert(1, enemy[i][j]);
	string temp = enemy[i][j];
	enemy[i][j] = current;

	////////////////////////////////////////////////////////////
	while (!finish) { // для бесконечного перемещения в поле
		if (_kbhit()) { // ПРоверка на нажатие на клаву
			switch (_getch()) {
				///// 13 -enter
					// 27 - Esc
					// 8 - Backspace
					// 32 - Space

			case 72: // UP
				while (i - 1 >= 1) {

					string current = "[]";
					current.insert(1, enemy[i - 1][j]);


					enemy[i][j].erase(0, 1);
					enemy[i][j].erase(enemy[i][j].size() - 1, enemy[i][j].size() - 1);

					enemy[i - 1][j] = current;


					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");

					i--;

					cout << "\tLAST ACTION -  UP";
					break; // Для только одного перемещения на поле за одно нажатие
				}
				break;
			case 80: // DOWN
				while (i + 1 < n + 1) {

					string current = "[]";
					current.insert(1, enemy[i + 1][j]);

					enemy[i][j].erase(0, 1);
					enemy[i][j].erase(enemy[i][j].size() - 1, enemy[i][j].size());

					enemy[i + 1][j] = current;

					i++;
					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");
					cout << "\tLAST ACTION - DOWN";
					

					break;
				}
				break;
			case 75: // LEFT
				while (j - 1 >= 1) {

					string current = "[]";
					current.insert(1, enemy[i][j - 1]);
					string temp = enemy[i][j];

					enemy[i][j].erase(0, 1);
					enemy[i][j].erase(enemy[i][j].size() - 1, enemy[i][j].size());


					enemy[i][j - 1] = current;

					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");
					j--;
					cout << "\tLAST ACTION - LEFT";
					
					break;
				}
				break;
			case 77: // RIGHT
				while (j + 1 < n + 1) {

					string current = "[]";
					current.insert(1, enemy[i][j + 1]);

					enemy[i][j].erase(0, 1);
					enemy[i][j].erase(enemy[i][j].size() - 1, enemy[i][j].size());

					enemy[i][j + 1] = current;


					system("cls");
					output_field(n, enemy, "the_game_mode");
					output_field(n, my, "create_ships_mode");
					j++;
					cout << "\tLAST ACTION - RIGHT";
					
					break;
				}
				break;

			case 13: // ENTER

				enemy[i][j] = enemy_ships[i][j];

				string current = "[]";
				current.insert(1, enemy[i][j]);

				enemy[i][j] = current;

				enemy_attack(my,n);
				check_death(my, enemy, enemy_ships, n, "enemy_attack");
				check_death(my,enemy, enemy_ships, n, "my_attack");
				system("cls");
				output_field(n, enemy, "the_game_mode");
				output_field(n, my, "create_ships_mode");

				cout << "\tLAST ACTION -  ENTER";
				
				break;



			}
		}
	}
}





int main()
{

	SetConsoleOutputCP(1251);
	srand(time(NULL));

	int n = 10;
	
	/*tuple < pair<int, int>, pair<int, int>, pair<int, int>, pair<int, int>> sh4_1;
	tuple < pair<int, int>, pair<int, int>, pair<int, int>> sh3_1;
	tuple < pair<int, int>, pair<int, int>, pair<int, int>> sh3_2;
	tuple < pair<int, int>, pair<int, int>> sh2_1;
	tuple < pair<int, int>, pair<int, int>> sh2_2;
	tuple < pair<int, int>, pair<int, int>> sh2_3;
	tuple < pair<int, int>> sh1_1;
	tuple < pair<int, int>> sh1_2;
	tuple < pair<int, int>> sh1_3;
	tuple < pair<int, int>> sh1_4;*/


	vector <pair<int, int>> sh4_1(4);
	vector <pair<int, int>> sh3_1(3);
	vector <pair<int, int>> sh3_2(3);
	vector <pair<int, int>> sh2_1(2);
	vector <pair<int, int>> sh2_2(2);
	vector <pair<int, int>> sh2_3(2);
	vector <pair<int, int>> sh1_1(1);
	vector <pair<int, int>> sh1_2(1);
	vector <pair<int, int>> sh1_3(1);
	vector <pair<int, int>> sh1_4(1);
	

	vector < vector < pair<int, int>>> ships = {
		sh4_1,sh3_1,sh3_2,sh2_1,sh2_2,sh2_3,sh1_1,sh1_2,sh1_3,sh1_4
	};
	
	vector < vector <string> > enemy(n + 2, vector <string>(n + 2));
	vector < vector <string> > my(n + 2, vector <string>(n + 2));
	vector < vector <string> > enemy_ships(n + 2, vector <string>(n + 2));
	

	ships[0][0].first = 1;
	ships[0][0].second = 1;
	random(ships);
	filling_fields(my, enemy, n);
	borders(my, enemy, n);
	//cout << "\n\n\n\t\tPRESS ENTER TO PLAY";
	create_enemy_ships(enemy_ships, ships, n);
	output_field(n, enemy_ships, "");


	create_ships(my , enemy, n);
	start_game(enemy, my, enemy_ships, n);
	


}
