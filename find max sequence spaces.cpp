/*
	������� �������, ������� � ������������ ������ ������� ���������� ���������� ������ ������ ��������
*/

#include <iostream>

using namespace std;

void find(string str) {
	int count = 0; // ������� �������� ���������� ��������
	int max_count = 0; // ������������ ���������� ��������
	
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') {
			count = 0; // ����� ������ ������������������ �������� �������� �������
			while (str.at(i) == ' ') {
				count++; // ����������� ������� �� 1
				i++; // ��������� � ���������� �������� ������
			}
			if (max_count < count) max_count = count;
		}
	}
	cout << "���������� ���������� ������ ������ �������� � ������ ����� " << max_count;
}

void main(){
	setlocale(LC_ALL, "");
	string str = "*   *     * * ***";
	find(str);
}