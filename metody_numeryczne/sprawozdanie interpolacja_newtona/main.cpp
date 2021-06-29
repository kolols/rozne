#include <iostream>
#include <fstream>
using namespace std;




int main() {


    //wczytywanie z pliku
    fstream czytaj;
    int rozmiar, pom;
    czytaj.open("newt.txt");
    czytaj >> rozmiar;                      //ilosc wezlow
    int* wezel = new int[rozmiar];
    float* wrt_wezel = new float[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        czytaj >> pom;
        wezel[i] = pom;
        czytaj >> pom;
        wrt_wezel[i] = pom;
    }
    int min, max;
    min = wezel[0];
    for (int i = 0; i < rozmiar; i++) {
        if (wezel[i] < min)
            min = wezel[i];
    }
    max = wezel[0];
    for (int i = 0; i < rozmiar; i++) {
        if (wezel[i] > max)
            max = wezel[i];
    }
    cout << min << " " << max << endl;
    cout << "Podaj dla jakeigo punktu policzyc" << endl;
    float punkt;
    cin >> punkt;
    if (punkt > max || punkt < min) {
        cout << "podano punkt nienalezacy do przedzialu " << endl;
        return 0;
    }
   
    int pomc=rozmiar;
   // tablica dynamiczna dwuwymiarowa dla ilorazów ró¿nicowych
    float** pk = new float *[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        pk[i] = new float[pomc];
        pomc--;
    }
    //przypisanie w pierwszej kolumnie wrt wezlow
    for (int i = 0; i < rozmiar; i++) {
        pk[0][i] = wrt_wezel[i];
    }
    pomc = rozmiar-1;
    float licznik = 0, mianowanik = 0;
    //obliczenie reszty tablicy
    for (int i = 1; i < rozmiar; i++) {
       
        for (int j = 0; j < pomc; j++) {
            licznik = pk[i - 1][j + 1] - pk[i - 1][j];
            mianowanik = wezel[j + i] - wezel[j];
            pk[i][j] = licznik / mianowanik;
        }
        pomc--;

    }
    pomc = rozmiar;
    float pomm = 1, wrt_konc = pk[0][0]*1;                    // p0 * b0 
    for (int i = 1; i < rozmiar - 1; i++) {
        pomm *= (punkt - wezel[i-1]);
        wrt_konc += pk[i][0] * pomm;
    }

    cout << wrt_konc << endl;




    
    cout << "liczba wezlow: " << rozmiar << endl;
    cout << "wezly: ";
    for (int i = 0; i < rozmiar; i++) {
        cout << wezel[i] << " ";
    }
    cout << endl;
    cout << "wartosc wezlow: ";
    for (int i = 0; i < rozmiar; i++) {
        cout << wrt_wezel[i] << " ";
    }
    cout << endl;
    cout << "Wartosc wielomianu Newtona w punkcie " << punkt << " wynosi " << wrt_konc << endl;

    cout << endl << "Kolejne wspolczynniki wielomianu Newtona bk :" << endl;
    for (int i = 0; i < rozmiar; i++) {
       
            cout << pk[i][0] << " ";
        
        pomc--;
        cout << endl;
    }

    delete[] wezel;
    delete[] wrt_wezel;
    for (int i = 0; i < rozmiar; i++) {
        delete[] pk[i];
    }
    delete[] pk;
	return 0;
}