#include <iostream>

double hermiteInterpolation(int n, double x[], double y[], double c) {
    double result = 0;

    // Obliczanie różnic dzielonych
    for (int i = 1; i < n; i++) {
        for (int j = n; j >= i; j--) {
            y[j] = (y[j] - y[j - 1]) / (x[j] - x[j - i]);
        }
    }

    // Obliczanie wartości wielomianu Hermite'a dla c
    result = y[n];
    for (int i = n - 1; i >= 0; i--) {
        result = result * (c - x[i]) + y[i];
    }

    return result;
}

int main() {
    // Przykładowe dane wejściowe
    int n = 4; // liczba węzłów
    double x[] = {1.0, 2.0, 3.0, 4.0}; // węzły interpolacji
    double y[] = {2.0, 3.0, 5.0, 8.0}; // wartości funkcji w węzłach
    double c = 2.5; // wartość c

    // Obliczanie wartości wielomianu Hermite'a
    double result = hermiteInterpolation(n, x, y, c);

    // Wyświetlenie wyniku
    std::cout << "Wartosc wielomianu dla c = " << c << " : " << result << std::endl;

    return 0;
}
