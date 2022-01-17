#include "Money.h"
void Change_Sign(Money money) {
	Money p = -money;
	cout << "Change the sign:"; p.out();
}

void operation_Addition(Money first_money, Money second_money) {
	cout << "first_money + second_money = ";
	Money d = first_money + second_money;
	d.out();
	cout << endl;
	Change_Sign(d);
}

void operation_Subtraction(Money first_money, Money second_money) {
	cout << "first_money - second_money = ";
    first_money -= second_money;
	first_money.out();
	Change_Sign(first_money);
}

void operation_plus(Money first_money, Money second_money) {
	cout << "first_money += second_money :";
	Money d = first_money += second_money;
	d.out();
	cout << endl;
	Change_Sign(d);
}

void operation_minus(Money first_money, Money second_money) {
	cout << "first_money -= second_money :";
	Money d = first_money -= second_money;
	d.out();
	cout << endl;
	Change_Sign(d);
}
void operation_Comparison1(Money first_money, Money second_money) {
	if (first_money == second_money)
		cout << "first_money == second_money -- true";
	else
		cout << "first_money == second_money -- false";
}

void operation_Comparison2(Money first_money, Money second_money) {
	if (first_money != second_money)
		cout << "first_money != second_money -- true";
	else
		cout << "first_money != second_money -- false";
}

void operation_Comparison3(Money first_money, Money second_money) {
	if (first_money > second_money)
		cout << "first_money > second_money -- true";
	else
		cout << "first_money > second_money -- false";
}

void operation_Comparison4(Money first_money, Money second_money) {
	if (first_money >= second_money)
		cout << "first_money >= second_money -- true";
	else
		cout << "first_money >= second_money -- false";
}

void operation_Comparison5(Money first_money, Money second_money) {
	if (first_money < second_money)
		cout << "first_money < second_money -- true";
	else
		cout << "first_money < second_money -- false";	
}

void operation_Comparison6(Money first_money, Money second_money) {
	if (first_money <= second_money)
		cout << "first_money <= second_money -- true";
	else
		cout << "first_money <= second_money -- false";
}

int main() {

	double first_number_pounds;
	cout << "Enter the number of pounds in first sum of money:";
	cin >> first_number_pounds;
	double first_number_shillings;
	cout << "Enter the number of shillings in first sum of money:";
	cin >> first_number_shillings;
	double first_number_pences;
	cout << "Enter the number of pences in first sum of money:";
	cin >> first_number_pences;
	if (first_number_pounds < 0 || first_number_shillings < 0 || first_number_pences < 0)
		throw exception("the first sum of money can't be negative");
	
	double second_number_pounds;
	cout << "Enter the number of pounds in second sum of money:";
	cin >> second_number_pounds;
	double second_number_shillings;
	cout << "Enter the number of shillings in second sum of money:";
	cin >> second_number_shillings;
	double second_number_pences;
	cout << "Enter the number of pences in second sum of money:";
	cin >> second_number_pences;
	if (second_number_pounds < 0 || second_number_shillings < 0 || second_number_pences < 0)
		throw exception("the second sum of money can't be negative");
	
	cout << "The first sum of money = ";
	Money first_money(first_number_pounds, first_number_shillings, first_number_pences);
	first_money.out();
	cout << endl;
	cout << "The second sum of money = ";
	Money second_money(second_number_pounds, second_number_shillings, second_number_pences);
	second_money.out();
	cout << endl;
	operation_Addition(first_money, second_money);
	cout << endl;
	operation_Subtraction(first_money, second_money);
	cout << endl;
	operation_plus(first_money, second_money);
	cout << endl;
	operation_minus(first_money, second_money);
	cout << endl;
	operation_Comparison1(first_money, second_money);
	cout << endl;
	operation_Comparison2(first_money, second_money);
	cout << endl;
	operation_Comparison3(first_money, second_money);
	cout << endl;
	operation_Comparison4(first_money, second_money);
	cout << endl;
	operation_Comparison5(first_money, second_money);
	cout << endl;
	operation_Comparison6(first_money, second_money);
	cout << endl;
	return 0;
}