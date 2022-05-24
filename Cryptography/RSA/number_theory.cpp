#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long int Factorization(long long int n, vector<long long int>& mas) {
	long long int k = 2; long long int i = 0;
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

long long int EilerFunction(long long int m) {
	vector<long long int> factorization = vector<long long int>();
	Factorization(m, factorization);
	double phi = m;
	long long int repeat = -1;
	for (long long int i = 0; i < factorization.size(); i++) {
		if (repeat != factorization.at(i)) {
			phi *= 1.0 - (1.0 / factorization.at(i));
			repeat = factorization.at(i);
		}
	}
	return (long long int)phi;
}

long long int NODEuclidean(long long int a, long long int b) {
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

long long int IdentityBezu(long long int a, long long int b, long long int& u, long long int& v) {
	long long int q, i;
	vector<long long int> r = vector<long long int>();
	vector<long long int> ciphertext = vector<long long int>();
	vector<long long int> t = vector<long long int>();
	r.push_back(a); r.push_back(b);
	ciphertext.push_back(1); ciphertext.push_back(0);
	t.push_back(0); t.push_back(1);
	for (i = 1; r.at(i) != 0; i++) {
		q = r.at(i - 1) / r.at(i);
		r.push_back(r.at(i - 1) - q * r.at(i));
		ciphertext.push_back(ciphertext.at(i - 1) - q * ciphertext.at(i));
		t.push_back(t.at(i - 1) - q * t.at(i));
	}
	u = ciphertext.at(i - 1);
	v = t.at(i - 1);
	long long int res = r.at(i - 1);
	r.~vector();
	ciphertext.~vector();
	t.~vector();
	return res;
}

long long int InverseClass(long long int n, long long int mod) {
	if (NODEuclidean(n, mod) != 1) {
		printf("N not invertible in the ring of the residue class mod %d\n", mod);
		return 0;
	}
	for (long long int i = 0; i < mod; i++) {
		if ((n * i) % mod == 1) return i;
	}
	return -1;
}

long long int InverseBezu(long long int n, long long int mod) {
	long long int u, v;
	if (IdentityBezu(n, mod, u, v) != 1) {
		printf("N not invertible in the ring of the residue class mod %d\n", mod);
		return NULL;
	}
	while (u < 0) {
		u += mod;
	}
	return u;
}

long long int DegreeRemainder1(long long int a, long long int m, long long int n) {
	vector<long long int> res = vector<long long int>();
	res.push_back(a % n); long long int i = 1;
	while (pow(2, i) < m)
	{
		res.push_back((res.at(i - 1) * res.at(i - 1)) % n);
		i++;
	} i = 0;
	long long int pr = 1; bool tr = false;
	while (pow(2, i) < m)
	{
		if ((long long int)pow(2, i) & m) {
			tr = true;
			pr *= res.at(i);
			pr %= n;
		}
		i++;
	}
	res.~vector();
	if (tr == false) { return 0; }
	return pr;
}

long long int DegreeRemainder2(long long int a, long long int ciphertext, long long int n)
{
	if (ciphertext == 0) {
		return 1;
	}
	if (ciphertext == 1) {
		return a % n;
	}
	if (ciphertext > 0 && ciphertext % 2 == 0) {
		return (DegreeRemainder2(a, ciphertext >> 1, n) % n * DegreeRemainder2(a, ciphertext >> 1, n) % n) % n; //%n после каждого вызова, чтобы не вызвать переполнения long long int'a

	}
	if (ciphertext > 0 && ciphertext % 2 != 0) {
		return (DegreeRemainder2(a, ciphertext >> 1, n) % n * DegreeRemainder2(a, ciphertext >> 1, n) % n * DegreeRemainder2(a, (long long int)1, n)) % n;
	}
}
