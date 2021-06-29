#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;




void gaus_bez(float** mac, int rozmiar) {
	float stala = 0.0f;
	for (int k = 0; k < rozmiar - 1; k++) {

		for (int i = k + 1; i < rozmiar; i++) {
			if (mac[k][k] == 0) {
				cout << "Wystapilo 0 na przekatnej przerwano obliczanie" << endl;
				return;
			}
			stala = mac[i][k] / mac[k][k];
			for (int j = k; j < rozmiar + 1; j++) {
				mac[i][j] -= stala * mac[k][j];

			}
		}
	}
}

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
	fstream czytaj;
	int rozmiar;
	czytaj.open("macierz.txt");
	czytaj >> rozmiar;			//rozmiar macierzy n x n
	float pom;
	float** mac = new float* [rozmiar];		//tablica dla macierzy rozszerzonej n+1 x n
	for (int i = 0; i < rozmiar; i++) {
		mac[i] = new float[rozmiar+1];
	}
	for (int i = 0; i < rozmiar; i++) {		//wczytanie macierzy
		for (int j = 0; j < rozmiar+1; j++) {
			czytaj >> pom;
			mac[i][j] = pom;
		}
	}



	for (int i = 0; i < rozmiar; i++) { //wypisanie  przed obliczeniami
		for (int j = 0; j < rozmiar + 1; j++) {
			cout << mac[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//gaus_pivot(mac, rozmiar);

	
	gaus_bez(mac, rozmiar);

	for (int i = 0; i < rozmiar; i++) {
		if (mac[i][i] == 0) {
			cout << "Wystapilo 0 na przekatnej nie mozna obliczyc" << endl;
			return 0;
		}
	}

	float* wynik = new float[rozmiar];
	for (int i = 0; i < rozmiar; i++) {
		wynik[i] = 1;
	}

	float zlicz = 0;
	for (int i = rozmiar-1; i >= 0; i--) {
		zlicz = mac[i][rozmiar];
		for (int j = rozmiar-1; j > i; j--) {
			zlicz -= mac[i][j] * wynik[j];
		}
		wynik[i] = zlicz/mac[i][i];
	}



	for (int i = 0; i < rozmiar ; i++) {
		for (int j = 0; j < rozmiar+1; j++) {
			cout << mac[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < rozmiar; i++) {
		cout << "x" << i << ": " << wynik[i] << endl;
	}

	for (int i = 0; i < rozmiar; i++) {
		delete[] mac[i];
	}
	delete[] mac;
	delete[] wynik;
	return 0;
}