#include <iostream>

using namespace std;



double f_xy(double x, double y) {

	return x * x + y;
//	return x + y;
}

int main() {
	int ilosc_krokow = 10;				//N
	double punkt = 1;					//b

	//dla warunku poczatkowego
	double a = 0;					// lub x0
	double y_a = 0.1;		//y(a)
	double h = (punkt - a) / ilosc_krokow;


	double x_i = a;	//ustawione na x0
	double y_i =y_a;	//ustawione jako y0

	if (f_xy(5, 3) == 28 ) {
		cout << "Rozwiazanie dla funkcji x^2 +y" << endl;
	}
	else
	{
		cout << "Rozwiazanie dla funkcji x + y" << endl;
	}


	cout << "Warunke poczatkowy y(" << a << ") = " << y_a << endl << endl;
	cout << "Punkt koncowy " << punkt << endl << endl;
	cout << "Ilosc krokow: " << ilosc_krokow << endl;


	for (int i=0; i < ilosc_krokow; i++) {		//dla metody eulera
		y_i += h * f_xy(x_i, y_i);
		x_i += h;
		
	}
	cout << "Rozwiazanie metoda eulera: " << endl;
	cout << y_i << endl << endl;
	
	x_i = a;  //ustawione na x0
	y_i = y_a; //ustawione jako y0
	//dla metody rk2
	double k1;
	double k2;
	for (int i = 0; i < ilosc_krokow; i++) {
		k1 = f_xy(x_i, y_i);
		k2 = f_xy(x_i + h, y_i + h * k1);
		y_i += h * 0.5 * (k1 + k2);
		x_i += h;
	}
	cout << "Rozwiazanie metoda rk2: " << endl;
	cout << y_i << endl << endl;
	x_i = a;  //ustawione na x0
	y_i = y_a; //ustawione jako y0
	//dla metody rk4
	double rk1;
	double rk2;
	double rk3;
	double rk4;
	double sum = 0;
	double ws = 6;
	for (int i = 0; i < ilosc_krokow; i++) {
		rk1 = f_xy(x_i, y_i);
		rk2 = f_xy(x_i + 0.5 * h, y_i + 0.5 * h * rk1);
		rk3 = f_xy(x_i + 0.5 * h, y_i + 0.5 * h * rk2);
		rk4 = f_xy(x_i + h, y_i + h * rk3);
		sum = h * (rk1 + 2 * rk2 + 2 * rk3 + rk4);
		y_i += sum/6;
		x_i += h;
	}
	cout << "Rozwiazanie metoda rk4: " << endl;
	cout << y_i << endl;
	
	return 0;
}