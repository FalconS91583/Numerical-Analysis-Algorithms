#include <iostream>

using namespace std;

// Funkcja obliczająca tablicę ilorazów różnicowych i zwracająca jej górny wiersz
double* obliczIlorazyRoznicowe(int n, double x[], double y[]) {
    double* ilorazy = new double[n];
    for (int i = 0; i < n; i++) {
        ilorazy[i] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            ilorazy[i] = (ilorazy[i] - ilorazy[i - 1]) / (x[i] - x[i - j]);
        }
    }

    return ilorazy;
}

// Funkcja obliczająca wartość wielomianu interpolacyjnego Newtona za pomocą wzoru Hornera
double obliczWielomianNewtona(int n, double x[], double* ilorazy, double c) {
    double wynik = ilorazy[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        wynik = wynik * (c - x[i]) + ilorazy[i];
    }
    return wynik;
}

int main() {
    int n = 4; // Liczba węzłów

    double x[] = {1.0, 2.0, 3.0, 4.0}; // Wartości węzłów
    double y[] = {2.0, 3.0, 5.0, 7.0}; // Wartości funkcji w węzłach

    double c = 4; // Wartość c

    double* ilorazy = obliczIlorazyRoznicowe(n, x, y);
    double wynik = obliczWielomianNewtona(n, x, ilorazy, c);

    cout << "Wartosc wielomianu w punkcie " << c << " wynosi: " << wynik << endl;

    delete[] ilorazy;

    return 0;
}
