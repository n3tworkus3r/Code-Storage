#include "Binary Struct.h"

void display(const char* iname) { // ������  ��������� �� ����� � ����� � �������
	fstream fin; // fin - ����� ����� (��� ������ ���������)
	// �������� ����� ��� ������ � �������� ������
	fin.open(iname, ios_base::in | ios_base::binary); // ������� fin.open ��������� ����, ��� �������� ������� � ��������� fname � ��������� ��� � �������, ������� ����� ���� ��������������� ��� ���������� ��������� �������� � ������
	if (!fin) {
		cerr << "������ �������� ����� " << iname << "!" << endl; // iname - ������������ ������
		exit(EXIT_FAILURE);
	}

	/*
	fin.open( const char * fname, const char * modeopen );
	fname - ��-������, ���������� ��� �����, ������� ���������� �������.
	modeopen - ������, ���������� ����� ������� � �����

	����� ios_base ��������� ��������� ������
	*/

	while (true) {
		Student temp;  // ������ ��������� ���������� 
		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // reinterpret_cast � �������� ���������� ����� ������: reinterpret_cast<dataType>( value )
		if (fin.eof()) break;  // ��������� ����� ����� (EOF).        
		print(temp); // ����� ��������� �� �������
		// eof - ����� ������, ���� ���� ����, � ���� ���� �� ����, �� ������� ����.
	}
	fin.close(); // ��������� �����
}


void print(const Student& s) {
	cout << left  // left - ������������ �� ������ ����
		<< setw(18) << s.name // setw - ������ ������ ����
		<< setw(21) << s.contract_number
		<< setw(27) << s.group_number
		<< setw(27) << s.mark;
	cout << endl;
}


void add_element(const char* iname) {

	fstream f; // ����� �����, ��� ���������� �������� �����
	f.open(iname, ios_base::app | ios_base::out | ios_base::binary); // �������� app ������ ios_base �������������, ��� ������ ������ ������������ � ����� �����,
	if (!f) { // ���� ����� �� �������, ������� ��������� �� ������
		cerr << "������ �������� ����� " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	fstream fout; // ����� ������, ��� ������ �������� � ���������
	fout.open(iname, ios_base::app | ios_base::binary);
	if (!fout) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	Student temp; // ��������� ���������� temp, ��� ������ ���� �������� ������ �������� ���������

	f.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // ������ ������� ���� ��� ������ � ���� ������ ��������

	temp = create_struct(); // � ���������� �������� ����� ������� create_struct

	fout.write(reinterpret_cast<char*>(&temp), sizeof(Student)); // ���������� ����� ������� �� ������� ���� � ����� �������� ���������

	// ��������� ������
	f.close(); 
	fout.close();
}


Student create_struct() {

	cin.ignore();
	Student temp = { "", 0, 0, 0 };
	cout << endl;
	cout << "\t������� -> ";
	cin.getline(temp.name, 30);
	cout << "\t����� �������� -> ";
	cin.getline(temp.contract_number, 30);
	cout << "\t����� ������ -> ";
	cin >> temp.group_number;
	cout << "\t������ -> ";
	cin >> temp.mark;
	cout << endl;
	return temp;
}


void output_by_last_name(const char* iname) {

	char last_name[30];

	cout << "������� �������: ", cin >> last_name;
	
	fstream fin; // fin - ����� ����� (��� ������ ���������)
	// �������� ����� ��� ������ � �������� ������
	fin.open(iname, ios_base::in | ios_base::binary); // ������� fin.open ��������� ����, ��� �������� ������� � ��������� fname � ��������� ��� � �������, ������� ����� ���� ��������������� ��� ���������� ��������� �������� � ������
	if (!fin) {
		cerr << "������ �������� ����� " << iname << "!" << endl; // iname - ������������ ������
		exit(EXIT_FAILURE);
	}

	Student temp; // ��������� ���������� temp, ��� ������ ���������
	
	while (true) {

		if (fin.eof()) break;  // ��������� ����� ����� (EOF). 

		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // ������ ������� ���� ��� ������ � ���� ������ ��������

		if (strcmp(temp.name, last_name) == 0) {
			cout << endl << temp.name << "\t" << temp.contract_number << "\t" << temp.group_number << "\t" << temp.mark << endl << endl;
			break;
		}
	}
	
}


void output_less_than_five(const char* iname) {

	cout << endl;
	cout << "�������� � �������� ���� 5:" << endl;

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
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
	cout << endl << "������� ����� ��������: " << endl << "-> ";

	char c_number[30];
	cin.ignore();
	cin.getline(c_number, 30);

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	fstream f2;
	f2.open(oname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "������ �������� ����� " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	short count = 0; // ������� ���-�� ��������� 

	while (true) {
		Student tmp;

		if (!f.eof()) {

			f.read(reinterpret_cast<char*>(&tmp), sizeof(Student));  // ��������� �� �������� ����� � �������� ���������� temp

			count++; // ������� �������� ���������� ��������� � ���������

			if (!strstr(tmp.contract_number, c_number)) { // ���� ����� �������� ��������� � temp �� ����� ��������� ������ ��������

				f2.write(reinterpret_cast<char*>(&tmp), sizeof(Student));  // �� temp ���������� � �������� ����
			}
		}
		else break;
	}
	f.close();
	f2.close();

	std::remove("input.bin"); // �������� �������� �����

	f.open(oname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "������ �������� ����� " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	f2.open(iname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
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
	cout << "�������� ��� ������ ������� ��������:" << endl;

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	fstream f2;
	f2.open(oname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "������ �������� ����� " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	short count = 0;
	short delta = -1;
	int new_group = 0;;
	while (true) {
		Student temp;

		if (!f.eof()) {

			f.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // ��������� �� �������� �����

			count++;

			if (!f.eof()) {
				if (temp.mark > 3) {  // ���� ������ ������ 3-�
					f2.write(reinterpret_cast<char*>(&temp), sizeof(Student));  // �� temp ���������� � �������� ����

				}
				else {

					cout << temp.name << "\t" << temp.contract_number << "\t" << temp.group_number << "\t" << temp.mark << endl;
					cout << "������� ����� ����� ������ ��������: ", cin >> new_group;
					temp.group_number = new_group;

					delta++;
					f2.write(reinterpret_cast<char*>(&temp), sizeof(Student));  // �� temp ���������� � �������� ����
					continue;

				}
			}
			else break;
		}
		else break;
	}

	f.close();
	f2.close();

	remove("input.bin"); // �������� �������� �����

	f.open(oname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "������ �������� ����� " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}
	f2.open(iname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
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

	fstream fin; // fin - ����� ����� (��� ������ ���������)
	// �������� ����� ��� ������ � �������� ������
	fin.open(iname, ios_base::in | ios_base::binary); // ������� fin.open ��������� ����, ��� �������� ������� � ��������� fname � ��������� ��� � �������, ������� ����� ���� ��������������� ��� ���������� ��������� �������� � ������
	if (!fin) {
		cerr << "������ �������� ����� " << iname << "!" << endl; // iname - ������������ ������
		exit(EXIT_FAILURE);
	}

	Student temp; // ��������� ���������� temp, ��� ������ ���������

	while (true) {

		if (fin.eof()) break;  // ��������� ����� ����� (EOF). 

		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // ������ ������� ���� ��� ������ � ���� ������ ��������

		if (temp.mark > max_mark)  max_mark = temp.mark;
		
	}
	fin.close();

	fin.open(iname, ios_base::in | ios_base::binary); // ������� fin.open ��������� ����, ��� �������� ������� � ��������� fname � ��������� ��� � �������, ������� ����� ���� ��������������� ��� ���������� ��������� �������� � ������
	if (!fin) {
		cerr << "������ �������� ����� " << iname << "!" << endl; // iname - ������������ ������
		exit(EXIT_FAILURE);
	}

	while (!fin.eof()) {
		fin.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // ������ ������� ���� ��� ������ � ���� ������ ��������
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

	cout << "������� �������: ", cin >> last_name;
	cout << "������� ������: ", cin >> new_mark;

	fstream f;
	f.open(iname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	fstream f2;
	f2.open(oname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "������ �������� ����� " << oname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	while (true) {

		Student temp; // ��������� ���������� temp, ��� ������ ���������

		if (f.eof()) break;  // ��������� ����� ����� (EOF). 

		count++; // ������� ���������� ��������� ��������� �� �������� �����

		f.read(reinterpret_cast<char*>(&temp), sizeof(Student)); // ������ ������� ���� � �������� � temp

		if (strcmp(temp.name, last_name) == 0) { // ���������� �������
			temp.mark = new_mark; // �������� ������ �� �����
		}

		f2.write(reinterpret_cast<char*>(&temp), sizeof(Student)); // ���������� � �������� ����
	}

	f.close();
	f2.close();

	remove("input.bin"); // �������� �������� �����

	f.open(oname, ios_base::in | ios_base::binary);
	if (!f) {
		cerr << "������ �������� ����� " << iname << "!" << endl;
		exit(EXIT_FAILURE);
	}

	f2.open(iname, ios_base::out | ios_base::binary);
	if (!f2) {
		cerr << "������ �������� ����� " << oname << "!" << endl;
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