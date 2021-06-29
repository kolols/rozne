#include <iostream>
#include <fstream>



using namespace std;	


void rozklad_lu(float** mac, float** lu, int rozmiar) {		    //metoda doolitla

	for (int i = 0; i < rozmiar; i++) {				//zerujemy lu i ustawiamy na przekatnej 1
		for (int j = 0; j < rozmiar; j++) {

			if (i == j) {
				lu[i][j] = 1;
			}
			else
				lu[i][j] = 0;
		}
	}

	float pom = 0;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			pom = 0;
			if (i <= j) {							//dla i<= j 
				for (int k = 0; k <= i - 1; k++) { //tu
					pom += lu[i][k] * lu[k][j];
				}
				lu[i][j] = mac[i][j] - pom;
			}
			else if (i > j) {
				for (int k = 0; k <= j - 1; k++) {
					pom += lu[i][k] * lu[k][j];
				}
				if (lu[j][j] == 0) {
					lu[i][j] = (1 / mac[j][j]) * (mac[i][j] - pom);
				}
				else
					lu[i][j] = (1 / lu[j][j]) * (mac[i][j] - pom);					// co jesli lu[j][j] jest zerem ??????? brak rozwiazania slaba metoda

			}

		}
	}

}

void rozklad_lu_gaus(float** mac, float** lu, int rozmiar, float* wolne) {

	for (int i = 0; i < rozmiar; i++) {				//zerujemy lu 
		for (int j = 0; j < rozmiar; j++) {

				lu[i][j] = 0;
		}
	}
	
	float stala = 0.0f, pom=1;
	int zmn=0, wierszk=0;
	int plu;
	for (int k = 0; k < rozmiar + zmn - 1; k++) {
		pom = 1;
		plu = 1;
		if (mac[wierszk][k] == 0) {									//gdy znajdziemy zero jako liczbe zerujaca
			int nrwier = k+1;
			pom = 0;
			for (int j = k+1; j < rozmiar; j++) {				//wybiera wiersz do zamiany ktory nie ma 0
				if (mac[j][k] != 0) {						// jesli 
					nrwier = j;								//
					pom = 1;
					break;
				}
			}

			if (pom  == 0) {						//jesli cala kolumna jest zerami
				plu = 0;
				zmn++;
				wierszk--;

			}
			else {

				float p;
				for (int l = 0; l < rozmiar; l++) {			//k aktualny wiersz nrwier zmieniany
					p = mac[k][l];							//zamiana wierszy macierzy
					mac[k][l] = mac[nrwier][l];
					mac[nrwier][l] = p;

					p = lu[k][l];							//zamiana wierszy lu dla zachowania spojnosci
					lu[k][l] = lu[nrwier][l];
					lu[nrwier][l] = p;

				}
				p = wolne[k];					//zamiana wyrazow wolnych
				wolne[k] = wolne[nrwier];
				wolne[nrwier] = p;

			}
			
		}

		for (int i = k + 1-zmn; i < rozmiar; i++) {									//zmn wykorzystana tylko gdy cala kolumna jest zerami

																					//wierszk=k chyba ze cala kolumna jest zerami
				stala = mac[i][k] / mac[wierszk][k];							//obliczenie stalej do wyzerowania
				for (int j = wierszk; j < rozmiar; j++) {						//obliczanie wszystkich wierszy
					mac[i][j] -= stala * mac[wierszk][j];

				}
				if (plu == 1) {											//nie przypisujemy wartosci do l gdy zerujemy pusta kolumne
					lu[i][wierszk] = stala;								// wartosci tablicy l sa rowne wspolczynnikowy 
				}
			
		}
		wierszk++;
	}


	for (int i = 0; i < rozmiar; i++) {				//polaczenie tablicy l i u
		for (int j = i; j < rozmiar; j++) {
			lu[i][j] = mac[i][j];
		}
	}

	

}

void oblicz_y(float* wart_y, float** lu, float* wolne, int rozmiar) {
	float pom = 0;
	for (int i = 0; i < rozmiar; i++) {				//obliczanie wartosci y
		pom = 0;
		for (int j = 0; j <= i - 1; j++) {
			pom += lu[i][j] * wart_y[j];
		}
		wart_y[i] = wolne[i] - pom;
	}


	for (int i = rozmiar - 1; i >= 0; i--) {					//obliczanie x sa obliczane od konca
		pom = 0;
		for (int j = i + 1; j <= rozmiar - 1; j++) {
			pom += lu[i][j] * wart_y[j];
		}
		if (lu[i][i] == 0) {
			cout << "Nie mozna rozwiazac ukladu 0 na przekatnej" << endl;
			return;
		}
		wart_y[i] = (1 / lu[i][i]) * (wart_y[i] - pom);
	}

}




int main() {
	fstream czytaj;
	int rozmiar;
	czytaj.open("macierzlu.txt");
	czytaj >> rozmiar;			//rozmiar macierzy 
	float pom;
	float** mac = new float* [rozmiar];		// tablica dla ukladu
	for (int i = 0; i < rozmiar; i++) {
		mac[i] = new float[rozmiar];
	}
	float* wolne = new float[rozmiar];    // tablica dla wyrazow wolnych
	float* wart_y = new float[rozmiar];

	for (int i = 0; i < rozmiar; i++) {		//wczytanie macierzy
		for (int j = 0; j < rozmiar + 1; j++) {
			czytaj >> pom;
			if (j == rozmiar) {
				wolne[i] = pom;
			}
			else
				mac[i][j] = pom;
		}
	}

	float** lu = new float* [rozmiar];			//tablica l i u
	for (int i = 0; i < rozmiar; i++) {
		lu[i] = new float[rozmiar];
	}

	cout << "uklad rownan: " << endl;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			cout << mac[i][j] << " ";
		}
		cout << wolne[i];
		cout << endl;
	}
	
//	rozklad_lu(mac, lu, rozmiar);					//dla metody doolitle nie korzystamy
	
	rozklad_lu_gaus(mac, lu, rozmiar, wolne);
	oblicz_y(wart_y, lu, wolne, rozmiar);




	cout << endl << "Macierz L+U: " << endl;
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++) {
			cout << lu[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < rozmiar; i++) {
		cout << "x" << i << ": " << wart_y[i] << endl;
	}

	/*for (int i = 0; i < rozmiar; i++) {
		cout << wolne[i] << endl;
	}*/


	for (int i = 0; i < rozmiar; i++) {
		delete[] mac[i];
	}
	delete[] mac;
	for (int i = 0; i < rozmiar; i++) {
		delete[] lu[i];
	}
	delete[] lu;
	delete[] wolne;

	return 0;
}