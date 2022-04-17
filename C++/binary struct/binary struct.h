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

// Чтение и вывод на экран
void display(const char*);

// Вывод структуры на консоль
void print(const Student&);

// Добавление элемента в структуру
void add_element(const char*);

// Вывод информации о студента по заданной фамилии
void output_by_last_name(const char*);

// Вывод информаци о студентах у которых оценка меньше 5
void output_less_than_five(const char*);

// Удаление элемента по заданному номеру договора
void del_by_contract_number(const char*, const char*);

// Изменение информации о номере группы для всех студентов имеющих неудовлетворительную отметку
void change_group(const char* iname, const char* oname);

// Вывод фамилий студентов с максимальной отметкой из выбранного файла
void output_by_mark(const char* input_file_name);

//
void change_by_last_name(const char* iname, const char* oname);

// создание структуры по задаваемым параметрам
Student create_struct();

