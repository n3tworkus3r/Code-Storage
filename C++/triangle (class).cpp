#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct Verticle{
	int x;
	int y;
};

struct triangle{
	
	Verticle A;
	Verticle B;
	Verticle C;
	
	string type;

	double perimeter;

	void fill() {
		cout << "А(x,y): ", cin >> this->A.x >> this->A.y;
		cout << "B(x,y): ", cin >> this->B.x >> this->B.y;
		cout << "C(x,y): ", cin >> this->C.x >> this->C.y;
	}

	void print(){
		cout << "\tTriangle:\n";
		cout << "А(" << this->A.x << "," << this->A.y << ")\n";
		cout << "B(" << this->B.x << "," << this->B.y << ")\n";
		cout << "C(" << this->C.x << "," << this->C.y << ")\n\n";
	}

	double* calc_sides() {
		double* sides = new double[3];

		double a = sqrt(((B.x - A.x)*(B.x - A.x)) + (B.y - A.y)*(B.y - A.y));
		double b = sqrt(((C.x - B.x)*(C.x - B.x)) + (C.y - B.y)*(C.y - B.y));
		double c = sqrt(((A.x - C.x)*(A.x - C.x)) + (A.y - C.y)*(A.y - C.y));

		sides[0] = a;
		sides[1] = b;
		sides[2] = c;
		/*
		cout <<"a:\t" << a << endl;
		cout <<"b:\t" << b << endl;
		cout <<"c:\t" << c << endl;
		*/
		return sides;
	}

	void show_type(){

		double* sides = calc_sides();
		double a = sides[0];
		double b = sides[1];
		double c = sides[2];
		delete[] sides;

		double cos_alf = (a*a + b*b - c*c)/(2*a*b);
		double cos_bet = (b*b + c*c - a*a)/(2*b*c);
		double cos_gam = (a*a + c*c - b*b)/(2*a*c);

		double alpha = ((acos(cos_alf))*180)/3.141593;
		double beta = ((acos(cos_bet))*180)/3.141593;
		double gamma = ((acos(cos_gam))*180)/3.141593;

		//cout << cos_alf << " " << cos_bet << " " << cos_gam << endl;
		cout << alpha << " " << beta << " " << gamma << endl;

		if(alpha == 90 || beta == 90 || gamma == 90){
			this->type = "Прямоугольный";
			cout << this->type <<endl;
		} else {

		 if(alpha < 90 && beta < 90 && gamma < 90){
			this->type = "Остроугольный";
			cout << this->type<<endl;
		}
		 else {if(alpha > 90 || beta > 90 || gamma > 90){
			this->type = "Тупоугольный";
			cout << this->type <<endl;
		 }}
			
		}
	}

	void calc_perimeter(){
		double* sides = calc_sides();
		this->perimeter = sides[0]+sides[1]+sides[2];
		cout <<"Периметр: " << this->perimeter << endl;
		delete[] sides;
	}

	
};


void sort_by_type(triangle* array, int n) {
	cout << "\nМассив отсортирован по типу:\n";
	for(int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - 1 - i; j++) {
			if( array[j].type < array[j+1].type)
				swap(array[j],array[j+1]);
		}
	}

	for(int i = 0; i < n;i++){
		array[i].print();
		array[i].show_type();
	}
}

void sort_by_perimeter(triangle* array, int n) {
	cout << "\nМассив отсортирован по периметру:\n";
	for(int i = 0; i < n - 1; i++){
		for (int j = 0; j < n - 1 - i; j++) {
			if( array[j].perimeter < array[j+1].perimeter)
				swap(array[j],array[j+1]);
		}
	}

	for(int i = 0; i < n;i++){
		array[i].print();
		array[i].calc_perimeter();
	}
}

int main()
{
	setlocale(LC_ALL,"");

	// int* array = new int*[N];
	int n =0;
	cout << "Введите размерность массива структур: ", cin >> n;
	triangle* struct_array = new struct triangle [n];

	for(int i = 0; i < n;i++){
		cout<< "Введите координаты вершин треугольника " << i+1 <<":\n";
		struct_array[i].fill();
	}

	for(int i = 0; i < n;i++){
		struct_array[i].print();
		struct_array[i].show_type();
		struct_array[i].calc_perimeter();
	}

	sort_by_type(struct_array, n);
	sort_by_perimeter(struct_array, n);


	system("pause");
	return 0;
}

