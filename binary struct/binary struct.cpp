#include "binary struct.h"

void display(const char* iname) { // Чтение  структуры из файла и вывод в консоль
	fstream fin; // fin - поток ввода (для чтения структуры)
	// Открытие файла для чтения в бинарном режиме
	fin.open(iname, ios_base::in | ios_base::binary); // Функция fin.open открывает файл, имя которого указано в параметре fname и связывает его с потоком, который может быть идентифицирован для выполнения различных операций с файлом
	if (!fin) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl; // iname - динамический массив
		exit(EXIT_FAILURE);
	}

	/*
	fin.open( const char * fname, const char * modeopen );
	fname - Си-строка, содержащая имя файла, который необходимо открыть.
	modeopen - Строка, содержащая режим доступа к файлу

	Класс ios_base описывает параметры потока
	*/

	while (true) {
		Student temp;  // Создаём временную переменную 
		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // reinterpret_cast — операция приведения типов данных: reinterpret_cast<dataType>( value )
		if (fin.eof()) break;  // Проверяет конец файла (EOF).        
		print(temp); // Вывод структыру на консоль
		// eof - выдаёт истину, если файл пуст, а если файл не пуст, то выдаётся ложь.
	}
	fin.close(); // Закрываем поток
}


void print(const Student& s) {
	cout << left  // left - выравнивание по левому краю
		<< setw(18) << s.name // setw - задать ширину поля
		<< setw(21) << s.contract_number
		<< setw(27) << s.group_number
		<< setw(27) << s.mark;
	cout << endl;
}


void add_element(const char* iname) {

	fstream f; // Поток ввода, для считывания входного файла
	f.open(iname, ios_base::app | ios_base::out | ios_base::binary); // Параметр app класса ios_base устанавливает, что данные всегда записываются в конец файла,
	if (!f) { // Если поток не запущен, выводим сообщение об ошибке
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	fstream fout; // Поток вывода, для записи элемента в структуру
	fout.open(iname, ios_base::app | ios_base::binary);
	if (!fout) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	Student temp; // Временная переменная temp, для записи туда введённых данных элемента структуры

	f.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // Читаем входной файл для записи в него нового элемента

	temp = create_struct(); // В переменную помещаем вызов функции create_struct

	fout.write(reinterpret_cast<char*>(&temp), sizeof(Student)); // Записываем новый элемент во входной файл в конец исходной структуры

	// Закрываем потоки
	f.close(); 
	fout.close();
}


Student create_struct() {

	cin.ignore();
	Student temp = { "", 0, 0, 0 };
	cout << endl;
	cout << "\tФамилия -> ";
	cin.getline(temp.name, 30);
	cout << "\tНомер договора -> ";
	cin.getline(temp.contract_number, 30);
	cout << "\tНомер группы -> ";
	cin >> temp.group_number;
	cout << "\tОценка -> ";
	cin >> temp.mark;
	cout << endl;
	return temp;
}


void output_by_last_name(const char* iname) {

	char last_name[30];

	cout << "Введите фамилию: ", cin >> last_name;
	
	fstream fin; // fin - поток ввода (для чтения структуры)
	// Открытие файла для чтения в бинарном режиме
	fin.open(iname, ios_base::in | ios_base::binary); // Функция fin.open открывает файл, имя которого указано в параметре fname и связывает его с потоком, который может быть идентифицирован для выполнения различных операций с файлом
	if (!fin) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl; // iname - динамический массив
		exit(EXIT_FAILURE);
	}

	Student temp; // Временная переменная temp, для чтения структуры
	
	while (true) {

		if (fin.eof()) break;  // Проверяет конец файла (EOF). 

		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // Читаем входной файл для записи в него нового элемента

		if (strcmp(temp.name, last_name) == 0) {
			cout << endl << temp.name << "\t" << temp.contract_number << "\t" << temp.group_number << "\t" << temp.mark << endl << endl;
			break;
		}
	}
	
}


void output_less_than_five(const char* iname) {

	cout << endl;
	cout << "Студенты с отметкой ниже 5:" << endl;

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	while (true) 
	{
		Student temp;

		f.read(reinterpret_cast<char*>(&temp), sizeof(Student));
		
		if (!f.eof()) {
			if (temp.mark < 5) {
				cout << temp.name << "\t\t" << temp.contract_number << "\t\t" << temp.group_number << "\t\t" << temp.mark << endl;
			}
		}
		else break;
	}
	f.close();
}


void del_by_contract_number(const char* iname, const char* oname) {
	cout << endl << "Введите номер договора: " << endl << "-> ";

	char c_number[30];
	cin.ignore();
	cin.getline(c_number, 30);

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	fstream f2;
	f2.open(oname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "Ошибка открытия файла " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	short count = 0; // Счётчик кол-ва элементов 

	while (true) {
		Student tmp;

		if (!f.eof()) {

			f.read(reinterpret_cast<char*>(&tmp), sizeof(Student));  // Считываем из входного файла в буферную переменную temp

			count++; // Считаем исходное количество элементов в структуре

			if (!strstr(tmp.contract_number, c_number)) { // Если номер договора структуры в temp не равен введённому номеру договора

				f2.write(reinterpret_cast<char*>(&tmp), sizeof(Student));  // Из temp записываем в выходной файл
			}
		}
		else break;
	}
	f.close();
	f2.close();

	std::remove("input.bin"); // Удаление входного файла

	f.open(oname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "Ошибка открытия файла " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	f2.open(iname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < count-2; i++) {
		Student tmp;

		if (!f.eof()) {
			f.read(reinterpret_cast<char*>(&tmp), sizeof(Student));
			f2.write(reinterpret_cast<char*>(&tmp), sizeof(Student));
		}
		else break;
	}
}


void change_group(const char* iname, const char* oname) {
	cout << endl;
	cout << "Студенты чью группу следует изменить:" << endl;

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	fstream f2;
	f2.open(oname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "Ошибка открытия файла " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	short count = 0;
	short delta = -1;
	int new_group = 0;;
	while (true) {
		Student temp;

		if (!f.eof()) {

			f.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // Считываем из входного файла

			count++;

			if (!f.eof()) {
				if (temp.mark > 3) {  // Если оценка больше 3-х
					f2.write(reinterpret_cast<char*>(&temp), sizeof(Student));  // Из temp записываем в выходной файл

				}
				else {

					cout << temp.name << "\t" << temp.contract_number << "\t" << temp.group_number << "\t" << temp.mark << endl;
					cout << "Введите номер новой группы студента: ", cin >> new_group;
					temp.group_number = new_group;

					delta++;
					f2.write(reinterpret_cast<char*>(&temp), sizeof(Student));  // Из temp записываем в выходной файл
					continue;

				}
			}
			else break;
		}
		else break;
	}

	f.close();
	f2.close();

	remove("input.bin"); // Удаление входного файла

	f.open(oname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "Ошибка открытия файла " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	f2.open(iname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < count - 1; i++) {
		Student tmp;

		f.read(reinterpret_cast<char*>(&tmp), sizeof(Student));
		f2.write(reinterpret_cast<char*>(&tmp), sizeof(Student));
	}	

	f.close();
	f2.close();
}


void output_by_mark(const char* iname) {

	int max_mark = 0; 

	fstream fin; // fin - поток ввода (для чтения структуры)
	// Открытие файла для чтения в бинарном режиме
	fin.open(iname, ios_base::in | ios_base::binary); // Функция fin.open открывает файл, имя которого указано в параметре fname и связывает его с потоком, который может быть идентифицирован для выполнения различных операций с файлом
	if (!fin) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl; // iname - динамический массив
		exit(EXIT_FAILURE);
	}

	Student temp; // Временная переменная temp, для чтения структуры

	while (true) {

		if (fin.eof()) break;  // Проверяет конец файла (EOF). 

		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // Читаем входной файл для записи в него нового элемента

		if (temp.mark > max_mark)  max_mark = temp.mark;
		
	}
	fin.close();

	fin.open(iname, ios_base::in | ios_base::binary); // Функция fin.open открывает файл, имя которого указано в параметре fname и связывает его с потоком, который может быть идентифицирован для выполнения различных операций с файлом
	if (!fin) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl; // iname - динамический массив
		exit(EXIT_FAILURE);
	}

	while (!fin.eof()) {
		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // Читаем входной файл для записи в него нового элемента
		if (!fin.eof()) {
			if (temp.mark == max_mark) cout << temp.name << endl;
		}
		else break;
	}
	fin.close();


}


void change_by_last_name(const char* iname, const char* oname) {

	char last_name[30];
	int new_mark;
	int count = 0;

	cout << "Введите фамилию: ", cin >> last_name;
	cout << "Введите оценку: ", cin >> new_mark;

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	fstream f2;
	f2.open(oname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "Ошибка открытия файла " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	while (true) {

		Student temp; // Временная переменная temp, для чтения структуры

		if (f.eof()) break;  // Проверяет конец файла (EOF). 

		count++; // Считаем количество считынных элементов из фходного файла

		f.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // Читаем входной файл и помещаем в temp

		if (strcmp(temp.name, last_name) == 0) { // Сравниваем фамилии
			temp.mark = new_mark; // Заменяем оценку на новую
		}

		f2.write(reinterpret_cast<char*>(&temp), sizeof(Student)); // Записываем в выходной файл
	}

	f.close();
	f2.close();

	remove("input.bin"); // Удаление входного файла

	f.open(oname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "Ошибка открытия файла " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	f2.open(iname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "Ошибка открытия файла " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < count - 1; i++) {
		Student tmp;
		f.read(reinterpret_cast<char*>(&tmp), sizeof(Student));
		f2.write(reinterpret_cast<char*>(&tmp), sizeof(Student));
	}
	f.close();
	f2.close();

	
}