#include <iostream>
#include "number_theory.cpp"

using namespace std;

/*
	Вариант 1
	Расшифровать c помощью CRT:
	p = 2038074743
	q = 2038074751
	e = 1299709
	ciphertext = 2428010006080722311

	В задании 2 полученный открытый текст разбить на двузначные числа (если длина
	открытого текста — нечетное число, то приписать вначале один нуль) и сопоставить
	каждому числу символ алфавита (а — 01, б — 02 и т.д.).
*/

char alphanet[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я',
					'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я' };

string ConvertToText(long long int ciphertext) {
	string msg;
	long long int index; long long int i = 0;
	while (ciphertext >= 1) {
		index = ciphertext % 100;
		msg.push_back(alphanet[index - 1]);
		ciphertext /= 100;
		i++;
	}
	string ret = string();
	for (long long int i = msg.size() - 1; i >= 0; i--) {
		ret.push_back(msg.at(i));
	}
	return ret;
}

 int main() {
	setlocale(0, "");
	cout << "\n\t\t CRT Presentation\n\n ";
	long long int n, e, ciphertext, p, q, h;
	//p = 2038074743; q = 2038074751; e = 1299709; ciphertext = 2428010006080722311;
	p = 4373; q = 4391; e = 2187; ciphertext = 10166970;

	long long int eiler_function = (p - 1) * (q - 1);
	long long int d = InverseBezu(e, eiler_function);
	cout << "\tD(secret key): " << d << endl << endl;
	long long int ah = ciphertext % p;
	long long int bh = ciphertext % q;
	cout << "\tCRT(ciphertext) --> (" << ah << "," << bh << ")" << endl << endl;
	long long int a = DegreeRemainder1(ah, d, p);
	long long int b = DegreeRemainder1(bh, d, q);
	long long int num = InverseBezu(q, p);
	long long int c = ((((a - b) + p) % p) * num) % p * q + b;
	cout << "\tMessage: " << c << endl << endl;
	cout << "\tText Message: " << ConvertToText(c) << endl << endl;
	return 0;
}