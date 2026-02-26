#include "Skor.h"

Skor::Skor(const Igrac& igrac, double rezultat)
    : rezultat_(rezultat), igrac_(igrac) {
}

std::ostream& operator<<(std::ostream& os, const Skor& s) {
    os << s.dohvatiIgraca() << " | rezultat=" << s.dohvatiRezultat();
    return os;
}