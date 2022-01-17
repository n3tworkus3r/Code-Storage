/*
	������� � ������� 4 ���� ����� ��� ��������� � ���������� ������������ ���������� �������
*/ 

#include <iostream>

using namespace std;

void output(int n, int m, int** array) {
	// ������� �������� �������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

void cross_flag(int n, int m, int** array) {
	cout << endl << "���� '�����'" << endl;
	// ��������� �������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // ��������� ������� ������
			if (i == j) 
				array[i][j] = 1; // ������� �������������� � ������� ���������
			
			if (j == (n - 1) - i)
				array[i][j] = 1; // ������� �������������� � �������� ���������	
		}
	}
}

void plus_flag(int n, int m, int** array) {
	cout << endl << "���� '����'" << endl;
	// ��������� �������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // ��������� ������� ������
			if (i == 2) {
				array[i][j] = 1; // ������� �������������� � 3 ������
			}

			if (j == 2) {
				array[i][j] = 1; // ������� �������������� � 3-�� �������
			}
		}
	}
}

void frame_flag(int n, int m, int** array) {
	cout << endl << "���� '�����'" << endl;
	// ��������� �������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // ��������� ������� ������

			if (i == 0) { // ������� �������������� � ������ ������
				array[i][j] = 1;
			}
			if (j == 0) { // ������� �������������� � ������� �������
				array[i][j] = 1; 
			}
			if (i == n - 1) { // ������� �������������� � ��������� ������
				array[i][j] = 1;
			}
			if (j == m - 1) { // ������� �������������� � ���������� �������
				array[i][j] = 1;
			}
		}
	}
}

void chessboard_flag(int n, int m, int** array) {
	cout << endl << "���� '��������� ����'" << endl;
	// ��������� �������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;     // ��������� ������� ������
			if (i % 2 != 0 && j % 2 == 0) { // ���� i �������� � j ������
				array[i][j] = 1;
			}

			if (i % 2 == 0 && j % 2 != 0) { // ���� i ������ � j ��������
				array[i][j] = 1;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	int n, m, choice = 5;
	cout << "������� ���������� ����� ������� ", cin >> n;
	cout << "������� ���������� �������� ������� ", cin >> m;

	int** array = new int* [n];

	for (int i = 0; i < n; i++)
		array[i] = new int[m];
	
	/*
	  ������� ����� � �������� ��������� �������:

		11 12 13 14 15
		21 22 23 24 25
		31 32 33 34 35
		41 42 43 44 45
		51 52 53 54 55
	*/
	
	do {
		cout << "\n �������� ��� �����:";
		cout << "\n 1) �����";
		cout << "\n 2) ����";
		cout << "\n 3) �����";
		cout << "\n 4) ��������� ����";
		cout << "\n 5) �����\n";
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