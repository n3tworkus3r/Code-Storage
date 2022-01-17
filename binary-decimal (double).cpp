/*
	������������� ������ � � �������� ������ � ������������
*/

#include <iostream>

using namespace std;

void binary_to_decimal(string bin) {

	auto dot_index=bin.find_first_of('.', 0); // ������� ������ ����� � ������
	auto int_sum = 0;
	auto i = 0;

	while (bin.at(i) != '.') {
		if (bin.at(i) =='1')
			int_sum += pow(2, dot_index - i - 1); // ���� ������� �������, �������� � �� 2 � ������� � �������
		
		i++;
	}

	i = dot_index;  // ��������� � ������� �����
	i++;  // ��������� � �������� ���������� �� ������
	double frac_sum = 0.0;

	while (i < bin.length()) {
		if (bin.at(i) == '1') {
			int degrees = 0 -(i - dot_index);  // �������� ������������� �������
			frac_sum += pow(2,degrees); // �������� �� 2 � ������� ������� ����� �������
		}
		i++;
	}

	double decimal = int_sum + frac_sum; 
	cout << decimal;
}

int main() {
	setlocale(LC_ALL, "");	
	string binary;
	cout << "������� �������� �����:\t", cin >> binary;
	binary_to_decimal(binary);
	return 0;
}