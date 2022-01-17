/*
	������� �������, ������� ����������� �� 5% �������� �������, ������� ��� LIMIT.
	�������� LIMIT �������� �������������.
*/

#include <iostream>
#include <ctime>

using namespace std;

void grow(double* array, int n, int LIMIT) {
	double five = 0; // ���������� ��� �������� 5% �� �������� �������
	for (int i = 0; i < n; i++) {
		if (LIMIT < array[i]) {
			five = array[i] * 0.05;  // ����������� 5% ��� ������� �������� �������, ������ limit
			array[i]+=five; // ���������� � �������� 5%
		}
	}
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	int LIMIT, n, num = 0;
	cout << "������� ����������� �������: ", cin >> n;
	cout << " ������� limit: ", cin >> LIMIT;

	double* array = new double[n];

	for (int i = 0; i < n; i++) {
		//cout << "������� ������� �������: ", cin >> array[i];
		num = rand() % 10;
		array[i] = num;
		cout << array[i] << "\t";
	}

	cout << endl;
	grow(array, n, LIMIT);

	for (int i = 0; i < n; i++) 
		cout << array[i] << "\t";
	return 0;
}