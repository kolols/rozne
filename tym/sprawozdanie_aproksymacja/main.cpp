#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
void gaus_pivot(float** mac, int rozmiar) {

	for (int k = 0; k < rozmiar - 1; k++) {
		int nrwier = k;
		float maks = abs(mac[k][k]);
		for (int i = k + 1; i < rozmiar; i++) {		//szukanie maks bezwzglednego
			if (abs(mac[i][k]) > maks) {
				maks = abs(mac[i][k]);
				nrwier = i;
			}
		}
		if (maks == 0) {
			cout << "nie mozna rozwiazac" << endl;
			return;
		}
		if (nrwier != k) {				//zamiana wierszy jesli sa rozne
			float p;
			for (int i = 0; i < rozmiar + 1; i++) {			//k aktualny wiersz nrwier zmieniany
				p = mac[k][i];
				mac[k][i] = mac[nrwier][i];
				mac[nrwier][i] = p;
			}
		}

		float stala;							//kopia bez pivota
		for (int i = k + 1; i < rozmiar; i++) {
			stala = mac[i][k] / mac[k][k];
			for (int j = k; j < rozmiar + 1; j++) {
				mac[i][j] -= stala * mac[k][j];

			}
		}

	}
}

int main() {

	float punkt[8] = { 1,2,3,4,5,6,7,8 };		//x
	float wart[8] = { 2,4,3,5,6,9,11,11 }; // funkcja wagowa		y

	float funk_wagowa = 1;
	int rozmiar = 2;			// 2 bo funkcja liniowa
	float tab[8][8];

	float* f_k = new float[rozmiar];
	
									// 2 bo funkcja liniowa
	for (int k = 0; k < rozmiar; k++) {		//g kj
		for (int j = 0; j < rozmiar; j++){
			float zlicz = 0;

			for (int i = 0; i < 8; i++) {
				zlicz += pow(punkt[i], k) * pow(punkt[i], j) * funk_wagowa;
			}
			tab[k][j] = zlicz;
		}

	}

	for (int k = 0; k < rozmiar; k++) {
		float zlicz = 0;
		for (int i = 0; i < 8; i++) {
			zlicz += pow(punkt[i], k) * wart[i] * funk_wagowa;
		}
		f_k[k] = zlicz;
	}

	float** mac = new float* [rozmiar];		//tablica dla macierzy rozszerzonej 
	for (int i = 0; i < rozmiar; i++) {
		mac[i] = new float[rozmiar + 1];
	}

	for (int i = 0; i < rozmiar; i++) {		//uzupelnie macierzy rozszerzonej dla gausa
		for (int j = 0; j < rozmiar + 1; j++){
			if (j == rozmiar) {
				mac[i][j] = f_k[i];
			}
			else {
				mac[i][j] = tab[i][j];
			}
		}
	}

	gaus_pivot(mac, 2);
											//z guasa
	float* wynik = new float[rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		wynik[i] = 1;
	}

	float zlicz = 0;
	for (int i = rozmiar - 1; i >= 0; i--) {
		zlicz = mac[i][rozmiar];
		for (int j = rozmiar - 1; j > i; j--) {
			zlicz -= mac[i][j] * wynik[j];
		}
		wynik[i] = zlicz / mac[i][i];
	}


	/*

	for (int i = 0; i < 2; i++) {			// tablica g
		for (int j = 0; j < 2; j++) {
			cout << tab[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 2; i++) {
		cout << f_k[i] << endl;
	}
	cout << endl;*/
	cout << "Wspolczyniki wielomianu aproksumujacego" << endl;
	for (int i = 0; i < rozmiar; i++) {		//wypisanie wyniku
		cout << wynik[i] << endl;
	}
	cout << endl;
	cout << "liczba wezlow: " << 8 << endl << endl;
	
	cout << "Wezly oraz wartosci funkcji aproksymujace w wezlach:" << endl << endl;

	float wart_wpunkt = 0;
	for (int i = 0; i < 8; i++) {
		wart_wpunkt = 0;

		for (int j = 0; j < rozmiar; j++) {
			wart_wpunkt += pow(punkt[i], j) * wynik[j];
		}
		cout << punkt[i]<<" "<<wart[i] << " " << wart_wpunkt << endl;
	
	}

	return 0;
}