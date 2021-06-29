#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double funk(double x) {

	//return sin(x);
	//return (x * x) + (2 * x) + 5;
	return exp(x);
}


double calka_protokat(int n, double a, double b) {
	double s = (b - a) / n;
	double x = a, zlicz = 0;
	for (int i = 0; i < n; i++) {
		zlicz += funk(x + 0.5 * s);
		x += s;
	}


	return zlicz * s;
}

double calka_trapez(int n, double a, double b) {
	double s = (b - a) / n;
	double x1 = a, x2 = a + s, zlicz = 0;
	for (int i = 0; i < n; i++) {								// (a+b)*h*0.5
		zlicz += s * ((funk(x1) + funk(x2)))*0.5 ;			//x2-x1=h  a=sin(x1) + b= sin(x2)
		x1 += s;
		x2 += s;
	}
	return zlicz;
}

double calka_simpson(int n, double a, double b) {
	double s = (b - a) / n;
	double x1 = a, x2 = a + s, zlicz = 0;
	for (int i = 0; i < n; i++) {
		zlicz += (s / 6) * (funk(x1) + 4 * funk((x1 + x2) / 2) + funk(x2));

		x1 += s;
		x2 += s;
	}

	return zlicz;
}




int main() {

	int n = 4;
	double a, b;
	a = 0.5;
	b = 5;
    


	if (funk(b) == sin(b)) {
		cout << "Wzor calkowanej funkcji  sin(x)" << endl;
	}
	else if (funk(b) == exp(b)) {
		cout << "Wzor calkowanej funkcji  exp(x)" << endl;
	}else if(funk(b) == (b*b + 2*b + 5))
	{
		cout << "Wzor calkowanej funkcji  x^2 + x + 5" << endl;
	}




	cout << "Przedzial calkowania: " << a << " " << b << endl;
	cout << "Liczba przedzialow: " << n << endl;

	cout << "Wynik dla metody prostokatow: " << endl;
	cout << calka_protokat(n, a, b) << endl;
	cout << endl;
	cout << "Wynik dla metody trapezow: " << endl;
	cout << calka_trapez(n, a, b) << endl;
	cout << endl;
	cout << "Wynik dla metody Simpsona" << endl;
	cout << calka_simpson(n, a, b) << endl;
	cout << endl;

	/*for (int i = 1; i < 11; i++) {
		n = i;
		cout << "wyniki dla danych przedzialow: " << n << endl;

		cout << calka_protokat(n, a, b) << endl;
		cout << endl;
		cout << calka_trapez(n, a, b) << endl;
		cout << endl;
		cout << calka_simpson(n, a, b) << endl;
		cout << endl;
	}*/
	

	return 0;
}