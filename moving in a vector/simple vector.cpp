
#include <iostream> 
#include <windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
using namespace std;
int N, M;
int **mainArray;
int row = 0, column = 0;
void print() {
	system("cls");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == row&& j == column)
				cout << "[";
			cout << mainArray[i][j];
			if (i == row&& j == column)
				cout << "]";
			cout << setw(5) << " ";
		}

		cout << endl;		
	}
	cout << "Для закрытия программы нажмите Esc." << endl;
}
int main()
{
	setlocale(0,"");
	
	cout << "Введите размер матрицы [NxM]: ";
	cin >> N >> M;
	if (N < 1 || M < 1) {
		cout << "Неверные данные." << endl;
		return 1;
	}
	
	mainArray = new int*[N];
	for (int i = 0; i < N; i++)
		mainArray[i] = new int[M];
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			mainArray[i][j] =rand()%(N*M);
	
	print();
	while (true)
	{
		if (_kbhit()) // слушатель нажатия на клаву
		{
			switch (_getch()) // ждёт нажатия на клаву без Enter после этого
			{
			case 27: //esc
				for (int i = 0; i < N; i++)
					delete[]mainArray[i];
				delete mainArray;
				return 0;
			case 13: //enter
				cout << "Введите новое значение: ";
				cin >> mainArray[row][column];
				break;
			case 72: //вверх
				if(row>0)
					row--;
				break;
			case 80: //вниз
				if(row<N-1)
				row++;
				break;
			case 75: //влево 
				if(column>0)
				column--;
				break;
			case 77: //вправо
				if(column<M-1)
				column++;
				break;
			}
			print();
		}
	}
	
	
}