#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Circle {
	double a;
	double b;
	double r;
	double range;
	
public:
	Circle() {
		a = 1;
		b = 1;
		r = 1;
		range = 1;
	}

	Circle(double new_a, double new_b, double new_r) {
		a = new_a;
		b = new_b;
		r = new_r;
		range = sqrt(a*a + b*b);
	}

	friend ostream& operator<< (ostream& out, const Circle& X) {
		//out << X.a << " " << X.b << " " << X.r << " range - " << X.range << endl;
		out << X.a << " " << X.b << " " << X.r << endl;

		return out;
	}

	void bubble_sort(Circle* arr, int size) {
		for (int i = 0; i < size - 1; i++) {
			for (int j = 0; j < size - i - 1; j++) {

				if (arr[j].range == arr[j + 1].range) 
					if (arr[j].r > arr[j + 1].r) 
						swap(arr[j], arr[j + 1]);
				
				if (arr[j].range < arr[j + 1].range)
					swap(arr[j], arr[j + 1]);

			}
		}
	}
};


int main() {
  
	setlocale(LC_ALL, "");
	int n;

	fstream f;
	f.open("in.txt", ios_base::in);
	if (!f)
		cout << "FSTREAM ERROR!\n";
	f >> n;

	Circle* array = new Circle[n];
	double temp_a, temp_b, temp_r;
	for (int i = 0; i < n; i++) {
		f >> temp_a >> temp_b >> temp_r;
		Circle X(temp_a, temp_b, temp_r);
		array[i] = X;
	}
	
	f.close();

	for (int i = 0; i < n; i++) 
		cout << array[i];
	
	cout << endl;

	array[0].bubble_sort(array, n);

	for (int i = 0; i < n; i++)
		cout << array[i];
	f.open("out.txt", ios_base::out);
	if (!f)
		cout << "FSTREAM ERROR!\n";
	for (int i = 0; i < n; i++)
		f << array[i];

	return 0;
}

