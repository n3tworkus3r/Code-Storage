#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;

int Factorization(int n, vector<int>& mas) {
	int k = 2; int i = 0;
	while (n > 1) {
		if (n % k == 0) {
			n /= k;
			mas.push_back(k);
		}
		else {
			k++;
		}
	}
	return k;
}

char alphabet[] = { 'а','б','в','г','д','е','ё','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я',
					'А','Б','В','Г','Д','Е','Ё','Ж','З','И','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ъ','Ы','Ь','Э','Ю','Я' };

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

int UniversalEulerFunc(int m) {
	vector<int> factorization = vector<int>();
	Factorization(m, factorization);
	double phi = m;
	int repeat = -1;
	for (int i = 0; i < factorization.size(); i++) {
		if (repeat != factorization.at(i)) {    
			phi *= 1.0 - (1.0 / factorization.at(i));
			repeat = factorization.at(i);
		}
	}
	return (int)phi;
}

long long int NodEuclidean(long long int a, long long int b) {
	if (a % b == 0) {
		return b;
	}
	if (b % a == 0) {
		return a;
	}
	long long int rn = 1;
	long long int r = a % b;

	while (b % r != 0) {
		rn = b % r;
		b = r;
		r = rn;
	}
	return r;
}
long long int DegreeRemainder2(long long int a, long long int s, long long int n)
{
	if (s == 0) {
		return 1;
	}
	if (s == 1) {
		return a % n;
	}
	if (s > 0 && s % 2 == 0) {
		return (DegreeRemainder2(a, s >> 1, n) % n * DegreeRemainder2(a, s >> 1, n) % n) % n;

	}
	if (s > 0 && s % 2 != 0) {
		return (DegreeRemainder2(a, s >> 1, n) % n * DegreeRemainder2(a, s >> 1, n) % n * DegreeRemainder2(a, (long long int)1, n)) % n;
	}
}

int Nok(int a, int b) {

	return (a * b) / NodEuclidean(a, b);

}



int simple(int n) {
	int stop = n + 100;
	while (n < stop) {
		vector<int> fact = vector<int>();
		Factorization(n, fact);
		if (n == fact.at(0)) {
			return n;
		}
		n++;
	}
	return -1;
}

int findE(int start, int phi) {
	int e = start;
	while (NodEuclidean(e, phi) != 1) {
		e++;
	}
	return e;
}

int fromCRT(int a, int b,int p,int q) {
	if (a < b) {
		while (a != b) {
			while (a < b) {
				a += p;
				if (b == a)return a;
			}
			while (a > b) {
				b += q;
				if (b == a)return a;
			}
		}
		return a;
	}
	
}


int main() {
	//setlocale(LC_ALL, "RUSSIAN");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);


	string msg;
	printf("Введите сообщение\n");
	//cin >> msg;
	getline(cin, msg, '\n');
	cout << endl << "Введено " << msg << endl;
	printf("Число: ");
	string num = to_number(msg);
	int numberc = atoi(num.c_str());
	cout << num << endl;


	int p, q, n, Nokpq, e, a, b, phi, c;
	p = simple(num.size() * 10);
	q = simple(p + 1);
	n = p * q;

	while (n < numberc || NodEuclidean(n, numberc) != 1)
	{
		p = simple(q + 1);
		q = simple(p + 1);
		n = p * q;
	}

	printf("Простые числа p = %d   q = %d \n", p, q);
	printf("n = %d\n", n);
	
	phi = (p - 1) * (q - 1);
	e = findE(p / 2, phi);
	printf("Число e = %d \n", e);
	Nokpq = Nok(p - 1, q - 1);
	
	int st = e;
	while (st - Nokpq > 0) {  //a^st = 1
		st -= Nokpq;
	}
	st += Nokpq;
	a = numberc % p;
	b = numberc % q;

	int as = DegreeRemainder2(a, st, p);
	int bs = DegreeRemainder2(b, st, q);

	printf("CRT представление ш: (%d,%d)\n", as, bs);
	 //c = DegreeRemainder2(atoi(num.c_str()), e, n);
	printf("Передаваемое сообщение: (%d,%d,%d)\n", fromCRT(as, bs, p, q), e, n);

	return 0;
}