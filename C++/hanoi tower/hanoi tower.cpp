#include <iostream>

using namespace std;

int steps = 0;

void move(int n,int src, int dest, int aux) {
	if (n > 0) {
		steps++;
		move(n - 1, src, aux, dest); // From source to auxiliary
		cout << src << " " << dest << endl;
		move(n - 1, aux, dest, src); // From auxiliary to source
	}
}

void main() {
	int n;
	cout << "Disks: ", cin >> n;
	move(n, 1, 2, 3);
	cout << "\nSteps:  " << steps << endl;
}
