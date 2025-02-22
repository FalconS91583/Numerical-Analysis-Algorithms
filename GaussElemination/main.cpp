#include <iostream>
#include <cmath>

const double EPSILON = 1e-16; // Precyzja porównania z zerem

void printMatrix(double A[4][5], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void gaussElimination(double A[4][5], int n) {
    for (int i = 0; i < n; ++i) {
        // Szukanie głównego elementu
        int mainRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(A[k][i]) > std::abs(A[mainRow][i])) {
                mainRow = k;
            }
        }

        // Zamiana wierszy, jeśli potrzeba
        if (mainRow != i) {
            for (int k = i; k < n + 1; ++k) {
                std::swap(A[i][k], A[mainRow][k]);
            }
        }

        // Sprawdzenie czy macierz jest osobliwa
        if (std::abs(A[i][i]) < EPSILON) {
            std::cout << "Macierz osobliwa - dzielenie przez zero!" << std::endl;
            return;
        }

        // Wykonanie eliminacji Gaussa
        for (int k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n + 1; ++j) {
                if (j == i) {
                    A[k][j] = 0;
                } else {
                    A[k][j] -= factor * A[i][j];
                }
            }
        }
    }

    // Wyliczenie wyników
    double x[n];
    for (int i = n - 1; i >= 0; --i) {
        x[i] = A[i][n] / A[i][i];
        for (int k = i - 1; k >= 0; --k) {
            A[k][n] -= A[k][i] * x[i];
        }
    }

    // Wyświetlenie wyników
    std::cout << "Rozwiazanie ukladu równan:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "x[" << i << "] = " << x[i] << std::endl;
    }
}

int main() {
    double A[4][5] = {{2, 4, 2, 0, 4},
                      {1, 0, -1, 1, 2},
                      {0, 1, 3, -1, 0},
                      {2, 1, 2, 1, 6}};

    int n = 4; // Rozmiar macierzy A

    std::cout << "Macierz A:" << std::endl;
    printMatrix(A, n);

    gaussElimination(A, n);

    return 0;
}
