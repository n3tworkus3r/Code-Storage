/*
	������� �������, ������� ������� ������������ ���������� ������� ��������� � ���������� �������.
*/

#include <iostream>
#include <ctime>

using namespace std;

void counting_zeros(int* array, int n) { // *array - ��������� �� ������ ������� � �������
	int count = 0; // ������� ���������� ����� � �������
	for (int i = 0; i < n; i++) 
		if (array[i] == 0)
			count++;
	cout << "\n���������� ������� ��������� � ������� ����� " << count;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));

	int n;
	cout << "������� ����������� �������: ", cin >> n;

	int* array = new int [n];
	for (int i = 0; i < n; i++) {		
		array[i] = rand() % 3; // ����������� �������� ������� ��������� �������� � ��������� �� 0 �� 2-�
		cout << array[i] << " "; // ������� ������� �������
	}
	
	counting_zeros(array, n);
	return 0;
}