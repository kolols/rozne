#include <iostream>
#include <fstream>
using namespace std;

int main() {
     
    //wczytywanie z pliku
    fstream czytaj;
    int rozmiar, pom; 
    czytaj.open("inter.txt");
    czytaj >> rozmiar;                      //ilosc wezlow
    int *wezel=new int[rozmiar];
    float *wrt_wezel = new float[rozmiar];
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
    float licznik = 1, mianownik = 1, wrt_konc=0;
    cin >> punkt;
    if (punkt > max || punkt < min) {
        cout << "podano punkt nienalezacy do przedzialu " << endl;
        return 0;
    }
    for (int i = 0; i < rozmiar; i++) {
        licznik = 1;
        mianownik = 1;
        for (int j = 0; j < rozmiar; j++) {
            if (i == j)
                continue;
            licznik *= punkt - wezel[j];
            mianownik *= wezel[i] - wezel[j];
        }
        wrt_konc += wrt_wezel[i] * (licznik / mianownik);
    }

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

    cout << "Punkt w ktorym liczymy wartosc: " << punkt << endl;
    cout << "Wartosc w punkcie: " << wrt_konc << endl;

	return 0;
}