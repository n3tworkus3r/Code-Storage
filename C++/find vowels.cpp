/*
	Создайте вектор из произвольных слов, а затем отфильтруйте из него только те слова, 
	в которых содержится гласных больше, чем задаваемое пользователем значение.
*/

#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, counter, vowels;
	vector <string> my_vector;
	char characters[] = { 'а','у','о','ы','и','э','я','ю','е','ё',
						  'А','У','О','Ы','И','Э','Я','Ю','Е','Ё',
						  'a','e','i','o','u','y',
						  'A','E','I','O','U','Y' };

	string name;
	cout << "Введите количество слов:", cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Введите слово:", cin >> name;
		my_vector.push_back(name);
	}

	cout << "Введите кол-во гласных: ", cin >> vowels;

	for (int i = 0; i < my_vector.size(); i++) { // Цикл для слов: my_vector.at(i) - это слово
		counter = 0;
		for (int j = 0; j < my_vector.at(i).length(); j++) { // Цикл для букв в слове my_vector.at(i).at(j) - буква на позиции j в слове i
			for (int k = 0; k < 32; k++) 
				if (my_vector.at(i).at(j)==characters[k])  // Цикл для элементов character (гласных)
					counter++; // Если буква гласная, прибавляем к счётчику 1
				
			
			if (counter > vowels) {
				my_vector.erase(my_vector.begin() + i); // Удаление из вектора слова на позиции i
				if(i > 0) i--; // Смещаем итератор слов назад, т.к. было удалено одно слово
			}
		}	
	}

	cout << "Оставшиеся слова: " << endl;
	for (int i = 0; i < my_vector.size(); i++)
		cout << my_vector.at(i) << " ";
	
	return 0;
}