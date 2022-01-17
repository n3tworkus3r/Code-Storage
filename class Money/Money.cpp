#include "Money.h" 

pair<int, double> Money::calc_pence(double amount) {
	double remainder = int(amount) % 12;
	double i_remainder = ((int(amount * 10)) % 10);
	remainder += i_remainder /= 10;
	double shilling_part = (amount - remainder) / 12;
	return pair<int, double>(shilling_part, remainder);
}

pair<int, double> Money::calc_shilling(double amount) {
	double remainder = int(amount) % 20;
	double pound_part = (amount - remainder) / 20;
	return pair<int, double>(pound_part, remainder);
}

Money Money::operator + (Money& other) {
	this->pound, other.getPound(), this->shilling, other.shilling, this->pence, other.pence;
	double amount_pence = other.pence + this->pence;
	other.shilling = calc_pence(amount_pence).first + other.shilling;
	other.pence = calc_pence(amount_pence).second;
	double amount_shilling = other.shilling + this->shilling;
	other.pound = this->pound + other.pound + calc_shilling(amount_shilling).first;
	other.shilling = calc_shilling(amount_shilling).second;
	return other;
}

Money Money::operator - (Money& other) {
	double amount_pence = this->pence - other.pence;
	double amount_shilling = this->shilling - other.shilling;
	other.shilling = calc_pence(amount_pence).first + other.shilling;
	other.pence = calc_pence(amount_pence).second;
	other.shilling = calc_shilling(amount_shilling).second;
	other.pound = this->pound - other.pound - calc_shilling(amount_shilling).first;
	if (amount_pence < 0) {
		other.shilling = other.shilling-1;
		other.pence =  other.pence+12;
	}
	if (other.shilling < 0) {
		other.pound = other.pound - 1;
		other.shilling = other.shilling+20;
	}
	return other;
}

Money::Money() {
	pound = 0;
	shilling = 0;
	pence = 0;
}
void Money::out()  {
	if (pound != 0)
		cout << pound << "pd. ";
	
	if (shilling != 0)
		cout << shilling << "sh. ";

	if (pence != 0) 
		cout << pence << "p. ";

	if (pound == 0 && shilling == 0 && pence == 0) 
		cout << "0p.";
}

Money::Money(double new_pound, double new_shilling, double new_pence) {
	pound = new_pound;
	shilling = new_shilling;
	pence = new_pence;
	const int max_pound = 1000000000;
	if (pound >= max_pound)
		throw exception("the number of pences can't be more than 1000000000");

	if (shilling >= 20) 
		throw exception("the number of pences can't be more than 12");
	
	if (pence >= 12)
		throw exception("the number of pences can't be more than 12");
}

void Money::setPound(double new_pound) {
	pound = new_pound;
}

void Money::setShilling(double new_shilling) {
	shilling = new_shilling;
}

void Money::setPence(double new_pence) {
	pence = new_pence;
}

int Money::getPound() const {
	return pound;
}

double Money::getPence() const {
	return pence;
}

int Money::getShilling() const {
	return shilling;
}

double Money::Sum_in_pences() const {
	return pence + shilling * 12 + pound * 240;
}

Money Money::operator += (  Money& other) {
	other = *this + other;
	return other;
}

Money Money::operator -= ( Money& other) {
	other = *this - other;
	return other;
}

Money Money::operator - () {
	return Money(-1*pound, shilling, pence );
}

bool Money::operator > ( Money secondMoney) const {
	return this->Sum_in_pences() > secondMoney.Sum_in_pences();
}

bool Money::operator < (Money secondMoney) const {
	return this->Sum_in_pences() < secondMoney.Sum_in_pences();
}

bool Money::operator >= (Money secondMoney) const {
	return this->Sum_in_pences() >= secondMoney.Sum_in_pences();
}

bool Money::operator <= (Money secondMoney) const {
	return this->Sum_in_pences() <= secondMoney.Sum_in_pences();
}

bool Money::operator == (Money secondMoney) const {
	return this->Sum_in_pences() == secondMoney.Sum_in_pences();
}

bool Money::operator != (Money secondMoney) const {
	return this->Sum_in_pences() != secondMoney.Sum_in_pences();
}
