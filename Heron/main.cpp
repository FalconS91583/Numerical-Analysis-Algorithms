#include <iostream>
#include <cmath>

double heron_sqrt(double a) {
    double x0;

    if (a >= 1) {
        x0 = a;
    } else {
        x0 = 1;
    }

    double xi = x0;
    double xi1 = 0.5 * (xi + a / xi);
    const double eps = 1E-8;

    while (std::abs(xi - xi1) > eps) {
        xi = xi1;
        xi1 = 0.5 * (xi + a / xi);
    }

    return xi1;
}

int main() {
    double a;
    std::cout << "Podaj nieujemna liczbe a: ";
    std::cin >> a;

    if (a < 0) {
        std::cout << "Blad: Podana liczba musi być nieujemna." << std::endl;
        return 1;
    }

    double result = heron_sqrt(a);

    std::cout << "Pierwiastek kwadratowy z " << a << " wynosi: " << result << std::endl;

    return 0;
}
