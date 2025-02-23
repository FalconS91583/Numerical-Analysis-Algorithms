#include <iostream>
#include <cmath>

double f(double x) {
    return sqrt(1 - x * x);
}

double Trapez(double a, double b, int m) {
    double h = (b - a) / m;
    double result = 0.0;
    result += f(a) + f(b);
    for (int i = 1; i < m; ++i) {
        result += 2 * f(a + i * h);
    }
    result *= h / 2;
    return result;
}

double Simpson(double a, double b, int m) {
    double h = (b - a) / m;
    double result = 0.0;
    result += f(a) + f(b);
    for (int i = 1; i < m; ++i) {
        if (i % 2 == 0) {
            result += 2 * f(a + i * h);
        } else {
            result += 4 * f(a + i * h);
        }
    }
    result *= h / 3;
    return result;
}

double TrzyOsme(double a, double b, int m) {
    double h = (b - a) / (3 * m);
    double result = 0.0;
    for (int i = 0; i < m; ++i) {
        double x0 = a + 3 * i * h;
        double x1 = x0 + h;
        double x2 = x1 + h;
        result += (3 * h / 8) * (f(x0) + 3 * f(x1) + 3 * f(x2) + f(x2 + h));
    }
    return result;
}

int main() {
    int m = 1000; // Liczba podziałów

    double pi_trapez = 2 * Trapez(-1, 1, m);
    double pi_simpson = 2 * Simpson(-1, 1, m);
    double pi_trzyosme = 2 * TrzyOsme(-1, 1, m);

    std::cout << "Metoda trapezow: " << pi_trapez << std::endl;
    std::cout << "Metoda Simpsona: " << pi_simpson << std::endl;
    std::cout << "Metoda trzech osmych: " << pi_trzyosme << std::endl;

    return 0;
}
