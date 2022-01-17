#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <windows.h>

using namespace std;

struct Student {
	char name[30];
	char contract_number[30];
	int group_number;
	int mark;
};

// ������ � ����� �� �����
void display(const char*);

// ����� ��������� �� �������
void print(const Student&);

// ���������� �������� � ���������
void add_element(const char*);

// ����� ���������� � �������� �� �������� �������
void output_by_last_name(const char*);

// ����� ��������� � ��������� � ������� ������ ������ 5
void output_less_than_five(const char*);

// �������� �������� �� ��������� ������ ��������
void del_by_contract_number(const char*, const char*);

// ��������� ���������� � ������ ������ ��� ���� ��������� ������� �������������������� �������
void change_group(const char* iname, const char* oname);

// ����� ������� ��������� � ������������ �������� �� ���������� �����
void output_by_mark(const char* input_file_name);

//
void change_by_last_name(const char* iname, const char* oname);

// �������� ��������� �� ���������� ����������
Student create_struct();

