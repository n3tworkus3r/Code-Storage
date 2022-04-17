/*
	Use the map to navigate through the links
	# При помощи map реализовать навигацию по ссылкам
*/

#include <iostream>
#include <map>
#include <string>
#include <windows.h>

using namespace std;

void print(map <string, string> route) {
	map <string, string> ::iterator it;
	for (it = route.begin(); it != route.end(); it++) 
		cout << it->first << " - " << it->second << endl;
}

void start(map<string, string> route) {
	string bookmark;
	cout << "What kind of bookmark?\n";
	cin.ignore();
	getline(cin, bookmark);
	map <string, string> ::iterator it;
	for (it = route.begin(); it != route.end(); it++) {
		if (it->first == bookmark) {
			string browser;
			cout << "Which browser?\n", getline(cin, browser);
			string adress;
			adress = "start " + browser + ".exe " + it->second;

			const char* c_adress = adress.c_str();
			//cout << c_adress;
			system(c_adress);
			cout << "\nDone!\n";
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto choice = 0;
	map <string, string> route;
	route.insert(pair<string, string>("some bookmark 1", "https://www.youtube.com/watch?v=kFMFpDfDoVg"));
	route.insert(pair<string, string>("some bookmark 2", " https://www.youtube.com/watch?v=ygpDDwh0Xf0"));
	do {
		cout << "\n[1] Show bookmark list";
		cout << "\n[2] Go to...";
		cout << "\n[0] Complete\n";
		cin >> choice;

		switch (choice) {
		case 1:
			print(route);
			break;
		case 2:
			start(route);
			break;
		}
	} while (choice != 0);
	return 0;
}