#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

// Sito Eratostenesa dla zakresu 1 - 1 000 000
std::vector<int> sitoEratostenesa(int n) {
    // Tablica bool: true = liczba pierwsza, false = złożona
    std::vector<bool> jest_pierwsza(n + 1, true);

    jest_pierwsza[0] = false;
    jest_pierwsza[1] = false;

    // Główna pętla sita
    for (int i = 2; i <= static_cast<int>(std::sqrt(n)); ++i) {
        if (jest_pierwsza[i]) {
            // Skreślamy wszystkie wielokrotności i, zaczynając od i*i
            for (int j = i * i; j <= n; j += i) {
                jest_pierwsza[j] = false;
            }
        }
    }

    // Zbieramy liczby pierwsze do wektora
    std::vector<int> liczby_pierwsze;
    liczby_pierwsze.reserve(80000); // Szacunkowa liczba pierwszych < 1 000 000

    for (int i = 2; i <= n; ++i) {
        if (jest_pierwsza[i]) {
            liczby_pierwsze.push_back(i);
        }
    }

    return liczby_pierwsze;
}

int main() {
    const int ZAKRES = 1'000'000;

    std::cout << "╔══════════════════════════════════════════════════╗\n";
    std::cout << "║        SITO ERATOSTENESA  (1 - 1 000 000)       ║\n";
    std::cout << "╚══════════════════════════════════════════════════╝\n\n";

    // Mierzenie czasu wykonania
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> pierwsze = sitoEratostenesa(ZAKRES);

    auto koniec = std::chrono::high_resolution_clock::now();
    auto czas_ms = std::chrono::duration_cast<std::chrono::microseconds>(koniec - start).count();

    // Statystyki
    std::cout << "Zakres:               1 - " << ZAKRES << "\n";
    std::cout << "Znalezionych liczb:   " << pierwsze.size() << "\n";
    std::cout << "Czas wykonania:       " << czas_ms << " μs ("
        << std::fixed << std::setprecision(3)
        << czas_ms / 1000.0 << " ms)\n\n";

    // Pierwsze 20 liczb pierwszych
    std::cout << "Pierwsze 20 liczb pierwszych:\n  ";
    for (int i = 0; i < 20 && i < static_cast<int>(pierwsze.size()); ++i) {
        std::cout << pierwsze[i];
        if (i < 19) std::cout << ", ";
    }
    std::cout << "\n\n";

    // Ostatnie 10 liczb pierwszych
    std::cout << "Ostatnie 10 liczb pierwszych:\n  ";
    int n = pierwsze.size();
    for (int i = std::max(0, n - 10); i < n; ++i) {
        std::cout << pierwsze[i];
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << "\n\n";

    // Rozkład liczb pierwszych w przedziałach co 100 000
    std::cout << "Rozkład w przedziałach:\n";
    std::cout << std::setw(20) << "Przedział"
        << std::setw(15) << "Ilość"
        << std::setw(15) << "Kumulatywnie\n";
    std::cout << std::string(50, '-') << "\n";

    int kumulatywnie = 0;
    int krok = 100'000;
    int idx = 0;

    for (int prog = krok; prog <= ZAKRES; prog += krok) {
        int licznik = 0;
        while (idx < n && pierwsze[idx] <= prog) {
            ++licznik;
            ++idx;
        }
        kumulatywnie += licznik;

        std::cout << std::setw(10) << (prog - krok + 1) << " - "
            << std::setw(7) << prog
            << std::setw(15) << licznik
            << std::setw(15) << kumulatywnie << "\n";
    }

    std::cout << "\n✓ Zakończono pomyślnie.\n";

    return 0;
}
