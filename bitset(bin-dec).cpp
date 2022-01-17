/*
	#Convert binary to decimal and vice versa using bitset
	#Преобразовать двоичное в десятичное и наоборот при помощи bitset
*/

#include <iostream>
#include <sstream>
#include <bitset>
using namespace std;

void decimal_to_binary(string dec) {
	double number = 0.0;
	stringstream ss(dec);
	ss >> number;
	bitset<8> bitset = number;
	cout <<"Binary number: " << bitset << endl;
}

void binary_to_decimal(string bin) {
	cout <<"Decimal number:" << bitset<32>(bin).to_ulong() << endl;
}

int main() {
	decimal_to_binary("7");
	binary_to_decimal("111");
	return 0;
}