#include <iostream>
#include <iomanip>
#include <cmath>
#define eps 1e-8
using namespace std;

class TMacierz {
private:
    const int wiersz;     // liczba wierszy
    double **A;           // macierz uzupełniona
    double *x;            // wynik
public:
    TMacierz(int n);
    ~TMacierz();
    bool Gauss_proste();
    bool Gauss_wyb_cz();    // wybór częściowy elementów podstawowych
    void Wczytaj_macierz();
    void Wyswietl_macierz();
    void Wyswietl_wynik();
    int Znajdz_max_kol(int k, int n);
    void Przestaw_wiersze(int w1, int w2);
};

TMacierz::TMacierz(const int w) : wiersz(w) {
    int kolumna = wiersz + 1;
    A = new double*[wiersz];
    x = new double[wiersz];
    for (int i = 0; i < wiersz; i++)
        A[i] = new double[kolumna];
}

TMacierz::~TMacierz() {
    for (int i = 0; i < wiersz; i++)
        delete [] A[i];
    delete [] A;
    delete [] x;
}

void TMacierz::Wyswietl_wynik() {
    cout << "\nWynik: \n";
    for (int i = 0; i < wiersz; i++)
        cout << x[i] << "\t";
    cout << endl;
}

void TMacierz::Wczytaj_macierz() {
    int kolumna = wiersz + 1;
    cout << "Podaj elementy macierzy A|b wierszami\n";
    for (int i = 0; i < wiersz; i++)
        for (int j = 0; j < kolumna; j++)
            cin >> A[i][j];
}

void TMacierz::Wyswietl_macierz() {
    int kolumna = wiersz + 1;
    cout << "Macierz: \n";
    for (int i = 0; i < wiersz; i++) {
        for (int j = 0; j < kolumna; j++)
            cout << A[i][j] << "\t";
        cout << endl;
    }
}

int TMacierz::Znajdz_max_kol(int k, int n) {
    int idx = k;
    double maxVal = abs(A[k][k]);
    for (int i = k + 1; i < n; i++) {
        if (abs(A[i][k]) > maxVal) {
            maxVal = abs(A[i][k]);
            idx = i;
        }
    }
    return idx;
}

void TMacierz::Przestaw_wiersze(int w1, int w2) {
    for (int i = 0; i <= wiersz; i++) {
        double temp = A[w1][i];
        A[w1][i] = A[w2][i];
        A[w2][i] = temp;
    }
}

bool TMacierz::Gauss_proste() {
    for (int k = 0; k < wiersz; k++) {
        int pivot = k;
        for (int i = k + 1; i < wiersz; i++) {
            if (abs(A[i][k]) > abs(A[pivot][k])) {
                pivot = i;
            }
        }
        if (abs(A[pivot][k]) < eps) {
            cout << "Uklad rownan jest sprzeczny lub nieoznaczony." << endl;
            return false;
        }
        if (pivot != k) {
            Przestaw_wiersze(k, pivot);
        }
        for (int i = k + 1; i < wiersz; i++) {
            double f = A[i][k] / A[k][k];
            for (int j = k + 1; j <= wiersz; j++) {
                A[i][j] -= A[k][j] * f;
            }
            A[i][k] = 0;
        }
    }
    for (int i = wiersz - 1; i >= 0; i--) {
        x[i] = A[i][wiersz];
        for (int j = i + 1; j < wiersz; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return true;
}

bool TMacierz::Gauss_wyb_cz() {
    for (int k = 0; k < wiersz; k++) {
        int idx = Znajdz_max_kol(k, wiersz);
        if (abs(A[idx][k]) < eps) {
            cout << "Uklad rownan jest sprzeczny lub nieoznaczony." << endl;
            return false;
        }
        if (idx != k) {
            Przestaw_wiersze(k, idx);
        }
        for (int i = k + 1; i < wiersz; i++) {
            double f = A[i][k] / A[k][k];
            for (int j = k + 1; j <= wiersz; j++) {
                A[i][j] -= A[k][j] * f;
            }
            A[i][k] = 0;
        }
    }
    for (int i = wiersz - 1; i >= 0; i--) {
        x[i] = A[i][wiersz];
        for (int j = i + 1; j < wiersz; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
    return true;
}

int main(int argc, char* argv[]) {
    int w;
    cout << "Podaj liczbe wierszy macierzy A: ";
    cin >> w;
    cout << fixed << setprecision(2);
    TMacierz m(w);
    m.Wczytaj_macierz();
    m.Wyswietl_macierz();
    if (m.Gauss_proste()) {
        cout << "Metoda eliminacji Gaussa (bez wyboru elementu podstawowego):" << endl;
        m.Wyswietl_wynik();
    }

    TMacierz m2(w);
    m2.Wczytaj_macierz();
    m2.Wyswietl_macierz();
    if (m2.Gauss_wyb_cz()) {
        cout << "Metoda eliminacji Gaussa z wyborem czesciowym elementu podstawowego:" << endl;
        m2.Wyswietl_wynik();
    }

    return 0;
}
