#include <iostream>
#include "number_theory.cpp"

using namespace std;

char alphabet[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я' };

int findInAlph(char c) {
	for (int i = 0; i < strlen(alphabet); i++) {
		

		if (c == alphabet[i]) {
			return i;
		}
	}
	return -1;
}


string to_number(string msg) {
	string number;
	
	for (int i = 0; i < msg.size(); i++) {
		int char_number = findInAlph(msg.at(i));
		
		if (char_number == -1) {
			return "Error";
		}
		char_number++;
		if (char_number < 10) {
			number.push_back('0');
		}
		number.append(to_string(char_number));
	}
	return number;
}

int simple(int n) {
	int stop = n + 100;
	while (n<stop) {
		vector<int> fact = vector<int>();
		Factorization(n, fact);
		if (n == fact.at(0)) {
			return n;
		}
		n++;
	}
	return -1;
}

int findE(int start,int phi) {
	int e = start;
	while (NODEuclidean(e, phi) != 1) {
		e++;
	}
	return e;
}


int main() {
	setlocale(LC_ALL, "");
	
	string msg;
	
	string number = to_number("слот");
	
	cout << " -->" <<  number << endl;
	int p, q;
	p = simple(number.size() * 10);
	q = simple(p + 1);
	int n = p * q;
	
	while (n < atoi(number.c_str()) || NODEuclidean(n, atoi(number.c_str())) != 1)
	{
		p = simple(q + 1);
		q = simple(p + 1);
		n = p * q;
	}

	printf("Простые числа p = %d   q = %d \n", p, q);
	printf("n = %d\n", n);
	int phi = (p - 1) * (q - 1);
	int e = findE(p / 2, phi);
	printf("Число e = %d \n", e);
	int c = DegreeRemainder2(atoi(number.c_str()), e, n);
	printf("Передаваемое сообщение: (%d,%d,%d)\n", c, e, n);

	return 0;
}