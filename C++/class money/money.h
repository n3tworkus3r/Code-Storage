#pragma once
#include <iostream>
#include <cmath>
#include <exception>
using namespace std;
class Money {
private:
	int pound;
	int shilling;
	double pence;
	pair<int, double> calc_pence(double);
	pair<int, double> calc_shilling(double);
public:
	Money();
	Money(double, double, double);
	void setPound(double);
	void setShilling(double);
	void setPence(double);
	int getPound() const;
	int getShilling() const;
	double getPence() const;
	double Sum_in_pences() const;
	void out();
	Money operator + (Money&);
	Money operator - (Money&);
	Money operator += ( Money&);
	Money operator -= ( Money&);
	Money operator - ();
	bool operator > (Money) const;
	bool operator < (Money) const;
	bool operator >= (Money) const;
	bool operator <= (Money)const;
	bool operator == (Money)const;
	bool operator != (Money)const;
};
