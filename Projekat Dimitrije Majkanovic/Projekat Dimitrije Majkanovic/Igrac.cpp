#include "Igrac.h"

int Igrac::sledeciId_ = 1;

static void proveriIme(const char* s) {
    if (!s) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Ime ne sme biti null.");
    int n = duzina(s);
    if (n <= 0) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Ime ne sme biti prazno.");
    if (n > 80) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Ime je duze od 80 karaktera.");
}

Igrac::Igrac(const char* ime, double balans)
    : id_(sledeciId_++), balans_(balans) {
    proveriIme(ime);
    kopiraj(ime_, 81, ime);
}

void Igrac::postaviIme(const char* ime) {
    proveriIme(ime);
    kopiraj(ime_, 81, ime);
}

std::istream& operator>>(std::istream& is, Igrac& i) {
    char buf[81];
    double b;

    is >> std::ws;
    is.getline(buf, 81);
    if (!is) return is;

    is >> b;
    if (!is) return is;

    i.postaviIme(buf);
    i.postaviBalans(b);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Igrac& i) {
    os << "Igrac { id=" << i.id_ << ", ime=\"" << i.ime_ << "\", balans=" << i.balans_ << " }";
    return os;
}
