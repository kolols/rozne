#include <iostream>
#include <fstream>
#include <cmath>

double funk(double x) {

	//return sin(x);
	//return (x * x) + (2 * x) + 5;
	return exp(x);
}

using namespace std;

int main() {


	double a, b;
	a = 0.5;
	b = 5;

	//schemat dwu wezlowy
	double wezel_dwu[2];
	wezel_dwu[0] = -0.57735;
	wezel_dwu[1] = 0.57735;

	double wrt_dwu[2];
	wrt_dwu[0] = 1;
	wrt_dwu[1] = 1;

	double ti_dwu[2];
	for (int i = 0; i < 2; i++) {
		ti_dwu[i] = (a + b) / 2 + (b - a) / 2 * wezel_dwu[i];
	}

	double zlicz_dwu = 0;
	for (int i = 0; i < 2; i++) {
		zlicz_dwu += wrt_dwu[i] * funk(ti_dwu[i]);
	}
	zlicz_dwu *= ((b - a) / 2);


	//schemat cztero wezlowy

	double wezel_cztery[4];
	wezel_cztery[0] = -0.861136;
	wezel_cztery[1] = -0.339981;
	wezel_cztery[2] = 0.339981;
	wezel_cztery[3] = 0.861136;

	double wrt_cztery[4];

	wrt_cztery[0] = 0.347855;
	wrt_cztery[1] = 0.652145;
	wrt_cztery[2] = 0.652145;
	wrt_cztery[3] = 0.347855;

	double ti_cztery[4];
	for (int i = 0; i < 4; i++) {
		ti_cztery[i] = (a + b) / 2 + (b - a) / 2 * wezel_cztery[i];
	}


	double zlicz_cztery = 0;
	for (int i = 0; i < 4; i++) {
		zlicz_cztery += wrt_cztery[i] * funk(ti_cztery[i]);
	}
	zlicz_cztery *= ((b - a) / 2);


	if (funk(b) == sin(b)) {
		cout << "Wzor calkowanej funkcji  sin(x)" << endl;
	}
	else if (funk(b) == exp(b)) {
		cout << "Wzor calkowanej funkcji  exp(x)" << endl;
	}
	else if (funk(b) == (b * b + 2 * b + 5))
	{
		cout << "Wzor calkowanej funkcji  x^2 + x + 5" << endl;
	}

	cout << endl;
	cout << "Dla schematu dwu wezlowego: " << endl;
	cout << endl;
	cout << zlicz_dwu << endl;


	cout << endl;
	cout << "Dla schemtau cztero wezlowego: " << endl;
	cout << endl;
	cout << zlicz_cztery << endl;

	return 0;
}