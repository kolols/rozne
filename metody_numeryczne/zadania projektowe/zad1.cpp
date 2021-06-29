#include <iostream>
#include <cmath>
using namespace std;


double funk(float x) {
	//return -x * x * x + 10 * x + 5;
	//return x * x * x * x * x - 6 * x + 5;
	//return x * x - 4 * x - 5.4;
	return -0.5*x * x * x + 3 * x * x - 5;
	//return x * x - 10;
}

double poch(float x) {
	//return -3 * x * x + 10;
	//return 5 * x * x * x * x - 6;
	//return 2 * x - 4;
	return -1.5 * x * x + 6*x;
	//return 2 * x;
}

int main() {

	int ilosc;
	double xs, xk;
	cout << "Podaj punkt startowy" << endl;
	cin >> xs;
	cout << "Podaj ilosc iteracji" << endl;
	cin >> ilosc;
	xk = xs;

	//cout << "Funkcja: -x^3 + 10x +5" << endl;
	//cout << "Funkcja: x^5 -6x +5" << endl;
	//cout << "Funkcja: x^2 -4x -5.4" << endl;

	cout << endl << "Dla metody stycznych: " << endl;
	for (int i = 0; i < ilosc; i++) {
		xs = xs - (funk(xs) / poch(xs));

		cout << "Nr iteracji: " << i + 1 << endl;
		cout << "rozwiazanie " << xs << endl << "wartosc funkcji:" << funk(xs) << endl << endl;
	}

	//metoda siecznych
	cout << endl << "Dla metody siecznych: " << endl;
	double pochodna, xk1;
	xk1 = xk;							//xk - k     xk1 = k-1
	xk -= 0.1;
	double eps = 0.00001;
	for (int i = 0; i < ilosc; i++) {

			pochodna = (funk(xk) - funk(xk1)) / (xk - xk1);
			xk1 = xk;
			xk = xk - (funk(xk) / pochodna);					//k+1
			cout << "Nr iteracji: " << i + 1 << endl;
		cout << "rozwiazanie " << xk << endl << "wartosc funkcji:" << funk(xk) << endl << endl;
			
		}
	

	return 0;
}