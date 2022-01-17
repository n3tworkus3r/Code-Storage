/*
	Read the text from a file.
	Replace the word in the text with the one entered from the keyboard.
	If the word you are looking for is not present, display it in the console. 
	
	# Считать тескт из файла.
	# Заменить в тексте слово на введённое из клавиатуры.
	# Если искомого слова нет, отобразить это в консоль. 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "");

	const char* input_file_name = "text.txt";
	vector <string> my_vector;
	string temp, s1, s2;
	fstream f;
	bool find = false;
	cout << "Type the word you are looking for: ", cin >> s1;
	cout << "Enter the word you want to replace with: ", cin >> s2;

	f.open(input_file_name, ios_base::in);

	while (!f.eof()) {
		getline(f, temp);
		int index = temp.find(s1);
		if (index != -1) {
			temp.replace(index, s1.length(),s2);
			find = true;
			cout << "Word " << s1 << "  changed to  " << s2 << endl;
		}
		my_vector.push_back(temp);
	}
	if (!find) cout << "Not a single word was found " << s1 << "  in the text" << endl;
	
	f.close();

	f.open(input_file_name, ios_base::out);
	for(int i = 0; i < my_vector.size();i++)
		f << my_vector.at(i) << endl;
	f.close();
	return 0;
}