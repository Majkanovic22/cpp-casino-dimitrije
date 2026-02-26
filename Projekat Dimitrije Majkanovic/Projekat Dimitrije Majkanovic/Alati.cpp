#include "Alati.h"

int duzina(const char* s) {
    int n = 0;
    while (s && s[n] != '\0') n++;
    return n;
}

void kopiraj(char* dst, int kap, const char* src) {
    if (!dst || kap <= 0) return;
    int i = 0;
    if (src) {
        while (src[i] != '\0' && i < kap - 1) {
            dst[i] = src[i];
            i++;
        }
    }
    dst[i] = '\0';
}

void ispisiPoravnato(const char* s, int sirina) {
    int n = duzina(s);
    std::cout << s;
    for (int i = n; i < sirina; i++) std::cout << ' ';
}

void ispisiIntPoravnato(int v, int sirina) {
    std::cout << v;
    int x = v;
    int cif = (x == 0) ? 1 : 0;
    if (x < 0) { cif++; x = -x; }
    while (x > 0) { cif++; x /= 10; }
    for (int i = cif; i < sirina; i++) std::cout << ' ';
}

void linija(int n) {
    for (int i = 0; i < n; i++) std::cout << '-';
    std::cout << "\n";
}