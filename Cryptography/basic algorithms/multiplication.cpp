#include <iostream>

using namespace std;

/*
	Создать программу, реализующую умножение "длинного" целого числа на произвольное целое.
*/

int main() {
    setlocale(LC_ALL, "");

    string a = "";
    string b = "";
    //string c = "";

    cout << "Введите длинное целое число (u): ", cin >> a;
    cout << "Введите число любое целое (v): ", cin >> b;

    int k = a.length();
    int l = b.length();
    int w_length = a.length() + b.length();

    int* u = new int[k];
    for (int i = 0; i < k; i++)
        u[i] = ((int)a[i]) - 48;
    

    int* v = new int[l];
    for (int i = 0; i < l; i++) 
        v[i] = ((int)b[i]-48);
    

    int* w = new int[w_length];

    // 1) FOR i = 0, ..., k+l-1     Wi <-- 0
    for (int i = 0; i < w_length; i++) {
        w[i] = 0;
    }
 
    // 2) FOR i = 0, ..., l-1 
    for (int i = 0; i < l; i++) {
        // 2a) C <-- 0
        int c = 0;
        // 2б) j = 0, ... k-1  
        for (int j = 0; j < k; j++) {
            int xy = w[i + j] + u[j] * v[i] + c;

            // Wi <-- Y
            w[i + j] = xy % 10;
            // C <-- X
            c = xy / 10;
        }
        // Wi+k <-- C
        w[i + k] = c;
    }
   

    for (int i = 0; i < w_length; i++)
        cout << w[i];




    

	return 0;
}