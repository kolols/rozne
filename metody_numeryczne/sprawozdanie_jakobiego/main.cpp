#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


int main() {

	fstream czytaj;
	int rozmiar;
	czytaj.open("mac.txt");
	czytaj >> rozmiar;			//rozmiar macierzy 
	float pom;
	float** mac = new float* [rozmiar];		//tablica dla macierzy rozszerzonej 
	for (int i = 0; i < rozmiar; i++) {
		mac[i] = new float[rozmiar+1];
	}
	for (int i = 0; i < rozmiar; i++) {		//wczytanie macierzy
		for (int j = 0; j < rozmiar+1; j++) {
			czytaj >> pom;
			mac[i][j] = pom;
		}
	}
	float** diago = new float* [rozmiar];		//diagonalna
	for (int i = 0; i < rozmiar; i++) {
		diago[i] = new float[rozmiar];
	}

	float** lu = new float* [rozmiar];		// L+U
	for (int i = 0; i < rozmiar; i++) {
		lu[i] = new float[rozmiar];
	}

	//rozdzielenie
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			if (j == i) {
				diago[i][j] = 1/mac[i][j];
				lu[i][j] = 0;
			}
			else
			{
				lu[i][j] = mac[i][j];
				diago[i][j] = 0;
			}
		}
	}


	float pr, smp, wr2;
	//warunki diagonalnie s³abo dominuj¹cej
	for (int i = 0; i < rozmiar; i++) {
		pr = mac[i][i];
		smp = 0;
		wr2 = 0;
		for (int j = 0; j < rozmiar; j++) {
			if (j == i) {
				continue;
			}
			smp += mac[i][j];
			if (pr > mac[i][j]) {
				wr2 = 1;
			}
		}
		if (pr < smp || wr2==0) {
			cout << "nie jest macierza diagonalnie slabo dominujaca" << endl;
			return 0;
		}

	}


	/*cout << "Podaj ilosc iteracji " << endl;
	int ilosc;
	cin >> ilosc;*/

	//dla zad2 
	int ilosc = 10000;

	float** wynik = new float* [rozmiar];		//tablica z wynikami
	for (int i = 0; i < 2; i++) {
		wynik[i] = new float[rozmiar];
	}

	for (int j = 0; j < rozmiar; j++) {		//ustawienie pierwszych wynikow na 0
		wynik[0][j] = 0;
	}

	float plu, wrtbledu=0.001f, pbl, zmpo;
	for (int k = 0; k < ilosc; k++) {
		for (int i = 0; i < rozmiar; i++) {
			plu = 0;
			for (int j = 0; j < rozmiar; j++) {
				plu += -diago[i][i] * lu[i][j] * wynik[0][j];
			}
			wynik[1][i] = plu + diago[i][i] * mac[i][rozmiar];
		}

		//zad2 
		zmpo = 0;
		for (int i = 0; i < rozmiar; i++) {
			pbl = wynik[1][i] - wynik[0][i];
			if (abs(pbl) > wrtbledu) {
				zmpo = 1;
			}
		}
		if (zmpo == 0) {		//blad jest mniejszy dla kazdego x wychodze
			cout << "Znaleziono blad mniejszy po  "<< k <<" iteracjach" << endl;
			for (int i = 0; i < rozmiar; i++) {
				cout << " dla x" << i << endl;
				cout << wynik[1][i] - wynik[0][i] << endl;
			}
			cout<<endl;
			break;
		}

		//koniec zad2

		//przepisanie wyniku do pozycji wyzerz
		for (int i = 0; i < rozmiar; i++) {
			wynik[0][i] = wynik[1][i];
		}
	}

	cout << "macierz rozszerzona" << endl;
	for (int i = 0; i < rozmiar; i++) { //wypis macierz rozszerzona
		for (int j = 0; j < rozmiar + 1; j++) {
			cout << mac[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "diagonalna odwrotna " << endl;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			cout << diago[i][j] << "	";
		}
		cout << endl;
	}
	cout << endl;
	cout << "L + U" << endl;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			cout << lu[i][j] << "	";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Rozwizanie po " << ilosc << " iteracjach" << endl << endl;
	for (int i = 0; i < rozmiar; i++) {
		cout << "x[" << i << "]: " << wynik[1][i] << "	" << endl;
	}
	

	return 0;
}