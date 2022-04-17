#include <iostream>
#include <fstream>
#include <regex>

/*
		ЗАДАНИЕ:
	В текстовом файле могут содержаться (как отдельные слова)
	IP-адреса компьютеров в формате  d.d.d.d, где d - целое число из диапазона от 0 до 255.
	Создать новый файл, удаляя IP-адреса, в которых последнее число d начинается с заданной цифры
	(данная цифра вводится с клавиатуры).

			TASK:
	The text file can contain (as separate words)
	IP addresses of computers in the format d.d.d.d, where d is an integer from the range 0 to 255.
	Create a new file by deleting IP addresses where the last number d begins with the given digit
	(this digit is entered from the keyboard).

*/

using namespace std;

int main() {

	cmatch result;
	
	//regex re("([0-9]{1,3}[\.]){3}[0-9]{1,3}");
	//string pattern = "(\\d{1,3}(\\.\\d{1,3}){3})"; // "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})"
	string ipv4 = "((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";
	regex re(ipv4);
	
	string text, temp;

	const char* input_filename = "input.txt";
	ifstream fin;
	fin.open(input_filename, ios_base::in);

	if (!fin) 
		cerr << "Error open file " << input_filename << endl;

	while (!fin.eof()) {
		getline(fin, temp);
		text += temp;
	}

	fin.close();
	
	cout << "\n\t\tTEXT\n" << text << endl;

	temp = text;
	cout << "\nMatches:" << endl;
	while (regex_search(temp.c_str(), result, re)) {
		auto x = result.str();
		cout << x << " " << std::endl;
		temp = result.suffix().str();
	}

	string number;
	cout << "\nEnter a number -> ", cin >> number;
	string new_pattern = "((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(" + number + ")\\d{0,2}";
	regex new_re(new_pattern);
	string new_text = regex_replace(text.c_str(), new_re, "");

	cout << "\n\t\tNEW TEXT\n" << new_text << endl;

	ofstream fout;
	fout.open("output.txt", ios_base::out);
	fout << new_text;
	fout.close();


	return 0;
}