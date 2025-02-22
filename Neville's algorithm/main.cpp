#include <iostream>

double neville(int n, double x[], double y[], double c) {
    double q[n][n];

    // Inicjalizacja tablicy q z wartościami y
    for (int i = 0; i < n; i++) {
        q[i][0] = y[i];
    }

    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n - k; i++) {
            // Obliczanie q[i][k] za pomocą wzoru Neville'a
            q[i][k] = ((c - x[i + k]) * q[i][k - 1] - (c - x[i]) * q[i + 1][k - 1]) / (x[i] - x[i + k]);
        }
    }

    return q[0][n - 1]; // Wartość wielomianu w punkcie c
}

int main() {
    //Przykładowe dane
    int n = 4; // Liczba węzłów interpolacji
    double x[] = {1.0, 2.0, 3.0, 4.0}; // Węzły interpolacji
    double y[] = {2.0, 3.0, 5.0, 8.0}; // Wartości funkcji w węzłach
    double c = 2.5; // Wartość c, w której obliczamy wielomian

    double result = neville(n, x, y, c);
    std::cout << "Wartosc wielomianu w punkcie " << c << " wynosi: " << result << std::endl;

    return 0;
}
