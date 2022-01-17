/*
	������� ������� ��� ���������� ���������� �����
*/

#include <iostream>

using namespace std;

int factorial(int n) {
	int f; // ���������� ��� ����������
	if (n == 0) // ��������� 0 ����� 1
		f = 1;
	else
		f = n * factorial(n - 1); // � ��������� ������, ����������� �� ������� ������������ � �������� �������
	return f;
}

int main() {
	setlocale(LC_ALL, "");
	int a;
	cout << "������� �����: ", cin >> a;

	cout << factorial(a) << endl;

	return 0;
}

