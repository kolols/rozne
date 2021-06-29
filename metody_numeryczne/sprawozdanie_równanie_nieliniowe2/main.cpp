#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

float funk(float x) {
	
	//return cos(x * x * x - 2 * x);
	//return -x * x * x + 5 * x - 7;
	//return sin(x * x + 3);
	return -0.5 * x * x * x + 3 * x * x - 5;
}


int main() {



	float e = 0.0001f;
	float a, b, x0, x1;
	//ustaw przedzial
	float af, bf;
	//dla mojej piet -5 i 0 dla drugiej 1 i 2
	af = a = 5.0f;
	bf = b = 7.0f;
	//cout << "Obliczana funkcja -x^3+5x-7" << endl << endl;
	cout << fixed;
	cout << setprecision(5);
	//metoda bisekcji
	x0 = (a + b) / 2;
	int iter = 1;	
	cout << "Metoda bisekcji" << endl;
	//cout << "	a	b	f(a)	   f(b)	     x0	      f(x0)	   f(a)*f(x0)" << endl;
	//cout << iter << "   " << a << "   " << b << "   " << funk(a) << "   " << funk(b) << "   " << x0 << "   " << funk(x0) << "   " << funk(a) * funk(x0) << endl;

	while (abs(funk(x0)) >= e)
	{
		if (funk(a) * funk(x0) < 0) {
			b = x0;
		}
		else {
			a = x0;
		}
		x0 = (a + b) / 2;
		iter++;
		//cout << iter << "   " << a << "   " << b << "   " << funk(a) << "   " << funk(b) << "   " << x0 << "   " << funk(x0) << "   " << funk(a) * funk(x0) << endl;
		cout << x0 << endl;
	}

	//metoda fa³szywej linii
	cout << endl;
	cout << "Metoda falszywej linii" << endl;
	cout << "	a	b	f(a)	   f(b)	     x1	      f(x1)	   f(a)*f(x1)" << endl;
	x1 = af - (funk(af) * (bf - af)) / (funk(bf) - funk(af));
	iter = 1;
	cout << iter << "   " << af << "   " << bf << "   " << funk(af) << "   " << funk(bf) << "   " << x1 << "   " << funk(x1) << "   " << funk(af) * funk(x1) << endl;

	while (abs(funk(x1)) >= e) {

		if (funk(af) * funk(x1) < 0) {
			bf = x1;
		}
		else {
			af = x1;
		}
		x1 = af - (funk(af) * (bf - af)) / (funk(bf) - funk(af));
		iter++;
		cout << iter << "   " << af << "   " << bf << "   " << funk(af) << "   " << funk(bf) << "   " << x1 << "   " << funk(x1) << "   " << funk(af) * funk(x1) << endl;

	}


	


	return 0;
}
