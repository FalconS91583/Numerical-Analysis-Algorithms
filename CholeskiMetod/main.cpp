#include <iostream>
#include <cmath>
using namespace std;

class TMacierz
{
const int wiersz;
double **A; //macierz
double **C; //macierz L
double *b; //wektor b
double *x; //wynik
public:
TMacierz(int w);
~TMacierz();
void zero_macierz(); //wyzerowanie macierzy C
bool czy_symetryczna(); //sprawdzenie, czy A jest symetryczna
void wczytaj_macierz(); //wczytanie A
void wyswietl_macierz();
void wyswietl_wynik();
void Choleski();
void wyswietl_macierz_C();
void oblicz_y();
void oblicz_x();
 void wczytaj_wektor_b() {
     b = new double[wiersz];
        cout << "Podaj wektor wyrazów wolnych b: " << endl;
        for (int i = 0; i < wiersz; i++) {
            cout << "b[" << i << "]: ";
            cin >> b[i];
        }
    }
};

TMacierz::TMacierz(const int w) : wiersz(w) {
    int kolumna = wiersz + 1;
    A = new double*[wiersz];
    C = new double*[wiersz];
    x = new double[wiersz];
    b = new double[wiersz];
    for (int i = 0; i < wiersz; i++) {
        A[i] = new double[kolumna];
        C[i] = new double[wiersz];
    }
        zero_macierz();
}

TMacierz::~TMacierz() {
    for (int i = 0; i < wiersz; i++) {
        delete [] A[i];
        delete [] C[i];
    }

    delete [] C;
    delete [] A;
    delete [] x;
    delete [] b;
}

bool TMacierz::czy_symetryczna() {
    for(int i=0;i<wiersz; i++) {
        for(int j=0; j<wiersz; j++) {
            if(A[i][j]!=A[j][i]) {
                return false;
            }
        }
    }
    return true;
}
void TMacierz::zero_macierz() {
for(int i=0; i<wiersz; i++) {
    for(int j=0; j<wiersz; j++) {
        C[i][j]=0.0;
    }
}
}

void TMacierz::wczytaj_macierz() {

cout<<"Wczytaj macierz A: "<<endl;
for(int i=0; i<wiersz; i++) {
    for(int j=0; j<wiersz; j++) {
        cout<<"A["<<i<<"]["<<j<<"]:";
        cin>>A[i][j];
    }
}
}
void TMacierz::wyswietl_macierz() {
cout<<"Macierz A:"<<endl;
for(int i=0;i<wiersz; i++) {
    for(int j=0;j<wiersz; j++) {
        cout<<A[i][j]<<"";
    }
    cout<<endl;
}
}
void TMacierz::wyswietl_wynik() {
cout<<"Wynik x"<<endl;
for(int i=0; i<wiersz; i++) {
    cout<<"x["<<i<<"]:"<<x[i]<<endl;
}
}
void TMacierz::Choleski() {
    for(int i =0; i<wiersz; i++) {
        for(int j=0; j<=i; j++) {
            double suma = 0.0;
            if(j==i) {
                for(int k =0; k<j; k++){
                  suma +=  pow(C[j][k],2);
                }
                C[j][j] = sqrt(A[j][j]-suma);
            } else {
            for(int k=0; k<j; k++) {
                suma +=(C[i][k]*C[j][k]);
            }
            C[i][j] =(A[i][j]-suma)/C[j][j];
            }
        }
    }
}
void TMacierz::wyswietl_macierz_C() {
    cout << "Macierz C (macierz L w rozkładzie Choleskiego):" << endl;
    for (int i = 0; i < wiersz; i++) {
        for (int j = 0; j < wiersz; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }
}
void TMacierz::oblicz_y() {
double suma;
for(int i=0;i<wiersz;i++) {
    suma =0.0;
    for(int j=0;j<i; j++) {
        suma+=C[i][j]*b[j];
    }
    b[i]=(b[i]-suma)/C[i][i];
}
}
void TMacierz::oblicz_x() {
    double suma;
for(int i=wiersz -1;i>=0;i--) {
    suma =0.0;
    for(int j=i+1;j<wiersz; j++) {
        suma+=C[j][i]*x[j];
    }
    x[i]=(b[i]-suma)/C[i][i];
}
}
int main()
{
    int rozmiar;
    cout<<"Podaj rozmiar macierzy: ";
    cin>>rozmiar;

    TMacierz m(rozmiar);
    m.wczytaj_macierz();
    if(!m.czy_symetryczna())
    {
         cout<<"Macierz nie jest symetryczna" << endl;
         return 1;
    }
    m.zero_macierz();
m.Choleski();
m.wyswietl_macierz_C();
m.wczytaj_wektor_b();
m.oblicz_x();
m.oblicz_y();
m.wyswietl_wynik();
    return 0;
}
