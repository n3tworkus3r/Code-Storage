/*
	Output to the console 4 types of flags for the specified from the keyboard dimensions of a two-dimensional array
	# Вывести в консоль 4 типа флага для указанных с клавиатуры размерностей двумерного массива
*/ 

#include <iostream>

using namespace std;

void output(int n, int m, int** array) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}

void cross_flag(int n, int m, int** array) {
	cout << endl << "'Cross' Flag" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;
			if (i == j) 
				array[i][j] = 1; // Condition of belonging to the main diagonal	
			if (j == (n - 1) - i)
				array[i][j] = 1; // Condition of belonging to a side diagonal	
		}
	}
}

void plus_flag(int n, int m, int** array) {
	cout << endl << "'Plus' Flag" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;
			if (i == 2) 
				array[i][j] = 1;
			if (j == 2) 
				array[i][j] = 1;
			
		}
	}
}

void frame_flag(int n, int m, int** array) {
	cout << endl << "'Frame' Flag" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;
			if (i == 0) 
				array[i][j] = 1;
			if (j == 0) 
				array[i][j] = 1; 
			if (i == n - 1)
				array[i][j] = 1;
			if (j == m - 1) 
				array[i][j] = 1;
			
		}
	}
}

void chessboard_flag(int n, int m, int** array) {
	cout << endl << "'Chessboard' Flag" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			array[i][j] = 0;
			if (i % 2 != 0 && j % 2 == 0)  // If i is odd and j is even
				array[i][j] = 1;

			if (i % 2 == 0 && j % 2 != 0)  //  If i is even and j is odd
				array[i][j] = 1;
			
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	int n, m, choice = 5;
	cout << "Enter the number of rows of the array ", cin >> n;
	cout << "Enter the number of columns of the array ", cin >> m;

	int** array = new int* [n];

	for (int i = 0; i < n; i++)
		array[i] = new int[m];
	
	/*
	  Rows and columns indices of matrix elements:

		11 12 13 14 15
		21 22 23 24 25
		31 32 33 34 35
		41 42 43 44 45
		51 52 53 54 55
	*/
	
	do {
		cout << "\n Select the type of flag::";
		cout << "\n 1) Cross";
		cout << "\n 2) Plus";
		cout << "\n 3) Frame";
		cout << "\n 4) Chessboard";
		cout << "\n 5) exit\n";
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