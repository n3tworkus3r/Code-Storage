#include <iostream>
#include <iomanip>			 // ���������� ��� ������ � �������������� �����-������ (setw, left)
#include <vector>
#include <string>			 // ���������� ��� ������ �� ��������
#include <ctime>			 // ���������� ��� ���������� ��������� ��������� �����
#include <conio.h>			 // ����������� ��� ������ �� ����������� ������
#include <sstream>
#include <windows.h>
using namespace std;

// ������� ��� �������� �� ������ ���� � ��� string
template <typename T> // ������ ��������� ���, ������� ��������� ����� ������� ��� ������
string to_string(T val) {
	string str; // ��������� ������, � ������� ���������� �������������� �������� 
	ostringstream oss;
	oss << val;
	return oss.str();
}

void print(int n, int m, vector <vector <string>> string_vector) {
	 
	for (int i = 0; i < n; i++) { // ���������� ������� ���������� ������ ������� ���������� �������
		for (int j = 0; j < m; j++) {
			cout << left << setw(5) << string_vector[i][j]; // ������������� ��� �������� ������ ���� 5 � ������� ���
		}
		cout << endl;
	}
}

//void convert(int n, int m, vector <vector <int>>  int_vector, vector < vector <string> >  string_vector) { print(string_vector); }

void move(int n, int m, vector <vector <string>> string_vector, vector <vector <int>> int_vector) {
	// ������������� �������� ��������� �������� �������� �� (0,0) - ������ �������
	int i = 0;
	int j = 0;
	string temp = string_vector[i][j]; 
	string temp2;
	string my_template = "[]"; // ��������� ������, ��� ��������� � �� ��������� ������� string_vector

	my_template.insert(1, temp); // ��������� ����������������� ������� � ��������� �������
	string_vector[0][0] = my_template; // ������ 1-�� ������� ������� ��������� (����������� � ������)
	print(n, m, string_vector); // ������� ��������� ������

	while (true) {

		if (_kbhit()) { // ��������� ������� �� �����

			switch (_getch()) { // ��� ������� �� �����
			
			case 72: // ������� "�����"
				while (i-1 >= 0) {									// ���� ��������� ���� �������, �� ������� �� ���������� ������� �� �������� ������ ���������� �������
					
					my_template = "[]";								// ������ ��������� ������
					temp = to_string(int_vector[i][j]);				// �������� �������� �������� �� ������� int ��������� � ��������� � ���������� � ���������� temp
					temp2 = string_vector[i-1][j];					// � ��������� temp2 �������� �������, ����������� ���� �������� (�.�. ���� ���� case ��� ������� ������� "�����")
					my_template.insert(1, temp2);					// �������� �������� temp2 � ���������� ������  (x -> [x])
					string_vector[i-1][j] = my_template;			// � ��������� ������� string �������� �������, ������� ���� �������� �� ���������
					string_vector[i][j] = temp;						// ������� ������� ��������� �� ���������� � ������� ( [z] -> z)
					system("cls");									// ������� �������
					print(n, m, string_vector);						// ������� ����������� ������ string
					cout << "Up" << endl;							// ������� ��������� �����������
					cout << "\nEnter - �������� �������" << endl;	// ������� ������ 
					i--;											// �������� ������ �������� ��������
					break;
				}
				break;
			case 80: // ������� "����"
				while (i+1 < n) {
					my_template = "[]"; // ������ ��������� ������
					temp = to_string(int_vector[i][j]);
					temp2 = string_vector[i + 1][j];
					my_template.insert(1, temp2);
					string_vector[i + 1][j] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Down" << endl;
					cout << "\nEnter - �������� �������" << endl;
					i++;
					break;
				}
				break;
			case 75: // ������� "�����"
				
				while (j - 1 >= 0 ) {
					my_template = "[]"; // ������ ��������� ������
					temp = to_string(int_vector[i][j]);
					temp2 = string_vector[i][j - 1];
					my_template.insert(1, temp2);
					string_vector[i][j - 1] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Left" << endl;
					cout << "\nEnter - �������� �������" << endl;
					j--;
					break;
				}
				break;
			case 77: // ������� "������"
				while (j+1 < m) {
					my_template = "[]";									// ������ ��������� ������
					temp = to_string(int_vector[i][j]);
					temp2 = string_vector[i][j+1];
					my_template.insert(1, temp2);
					string_vector[i][j+1] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Right" << endl;
					cout << "\nEnter - �������� �������" << endl;
					j++;
					break;
				}
				break;
			case 13: // ������� "Enter"
				int x = 0;
				cout << "������� ����� ��������: ", cin >> x;			// ����� ������� Enter ������ ����� ��������
				while (j + 1 < m) {
					my_template = "[]";									// ������ ��������� ������
					int_vector[i][j] = x;								// �������� �� ������� int �������� �� �������� 
					temp = to_string(int_vector[i][j]);					// ����� �� ��������...
					temp2 = string_vector[i][j + 1];
					my_template.insert(1, temp2);
					string_vector[i][j + 1] = my_template;
					string_vector[i][j] = temp;
					system("cls");
					print(n, m, string_vector);
					cout << "Right" << endl;
					cout << "\nEnter - �������� �������" << endl;
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
	cout << "������� ������ ������� (n, m): ", cin >> n >> m;
	vector < vector <int> >  int_vector(n, vector <int>(m)); // ���������� ������� �� n ����� �� m ��������� 
	vector < vector <string> >  string_vector(n, vector <string>(m)); // ������ ��� ���� ������ ��������� �� �������� �����

	srand(time(NULL)); // ��������� ��������� ����� ��� ������� rand()

	// ���������� ���������� �������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			num = rand()%100;
			int_vector[i][j] = num;
		}
	}

	cout << endl;

	string convert_str;		// ������ ������ ������, ������� ����� ��������� �������� int �� ���������� ������� int_vector 

	for (int i = 0; i < n; i++) { // ���������� ������� ���������� ������ ������� ���������� �������
		for (int j = 0; j < m; j++) {
			convert_str = to_string(int_vector[i][j]);  // ������������ ������ ������� ������� int_vector �� ���� int � ��� string
			string_vector[i][j] = convert_str; // ��������� ���������������� ������� � ������ ����� - string_vector
		}
	}

	move(n, m, string_vector, int_vector); // �������� ������� ����������

	return 0;
}