/*
	Create a polygon class, calculate its area.
	# Создать класс многоугольник, подсчитать его площадь.
*/
#include <iostream>
#include <iomanip>

using namespace std;

class Polygon {
	int n;
	double** coordinates;

public:
	Polygon() {
		this->n = 0;
		this->coordinates = new double* [n];
	}

	Polygon(int new_n) {
		this->n = new_n;
		this->coordinates = new double* [n];
		for (int i = 0; i < n; i++) 
			coordinates[i] = new double[2];
	}

	void fill() {
		for (int i = 0; i < n; i++) {
			//cout << "Verticle " << i+1 <<":\n";
			cout << "x,y: ", cin >> coordinates[i][0] >> coordinates[i][1];
			/*
			if(j == 0)
				cout <<"x: ", cin >> coordinates[i][j];
			else
				cout <<"y: ", cin >> coordinates[i][j];*/
		}
	}

	void area() {

		double sum_x = 0;
		for (int i = 0; i < n - 1; i++) {
			double temp = coordinates[i][0] * coordinates[i + 1][1];
			sum_x += temp;
			// temp = 0;
		}
		sum_x += coordinates[n - 1][0] * coordinates[0][1];
		////////////////////////
		double sum_y = 0;
		for (int i = 0; i < n - 1; i++) {
			double temp = coordinates[i][1] * coordinates[i + 1][0];
			sum_y += temp;
			// temp = 0;
		}
		sum_y += coordinates[n - 1][1] * coordinates[0][0];
		////////////////////////
		double area = abs(sum_x - sum_y);
		cout << "The area" << n << "-gon is equal to " << area/2 << endl;
	}
};


int main() {
	setlocale(LC_ALL, "");
	Polygon B(5);
	B.fill();
	B.area();

	system("pause");
	return 0;
}