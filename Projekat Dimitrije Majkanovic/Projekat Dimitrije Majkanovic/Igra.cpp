#include "Igra.h"

static void proveriNaziv(const char* n) {
    if (!n) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Naziv igre ne sme biti null.");
    int len = duzina(n);
    if (len <= 0) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Naziv igre ne sme biti prazan.");
    if (len > 30) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Naziv igre je duzi od 30 karaktera.");
}

Igra::Igra(const char* naziv) : brojSkorova_(0) {
    proveriNaziv(naziv);
    kopiraj(naziv_, 31, naziv);
    for (int i = 0;i < MAX_SKOROVA;i++) skorovi_[i] = 0;
}

Igra::~Igra() {
    for (int i = 0;i < brojSkorova_;i++) {
        delete skorovi_[i];
        skorovi_[i] = 0;
    }
    brojSkorova_ = 0;
}

Igra& Igra::operator+=(Skor* s) {
    if (!s) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Pokusaj dodavanja praznog skora.");
    if (brojSkorova_ >= MAX_SKOROVA) { delete s; throw IzuzetakKazino(STANJE_IGRE, "Prekoracenje kapaciteta liste skorova."); }
    skorovi_[brojSkorova_++] = s;
    return *this;
}

const Skor* Igra::operator-(double vrednost) const {
    for (int i = 0;i < brojSkorova_;i++) {
        if (skorovi_[i] && skorovi_[i]->dohvatiRezultat() == vrednost) return skorovi_[i];
    }
    return 0;
}

static void zameni(Skor*& a, Skor*& b) { Skor* t = a; a = b; b = t; }

void Igra::sortirajRastuce() {
    for (int i = 0;i < brojSkorova_ - 1;i++) {
        int best = i;
        for (int j = i + 1;j < brojSkorova_;j++) {
            if (skorovi_[j]->dohvatiRezultat() < skorovi_[best]->dohvatiRezultat()) best = j;
        }
        if (best != i) zameni(skorovi_[i], skorovi_[best]);
    }
}

void Igra::sortirajOpadajuce() {
    for (int i = 0;i < brojSkorova_ - 1;i++) {
        int best = i;
        for (int j = i + 1;j < brojSkorova_;j++) {
            if (skorovi_[j]->dohvatiRezultat() > skorovi_[best]->dohvatiRezultat()) best = j;
        }
        if (best != i) zameni(skorovi_[i], skorovi_[best]);
    }
}

void Igra::transfer(Igrac& igrac, double delta, double& budzetKazina) {
    if (delta > 0) {
        if (budzetKazina < delta) throw IzuzetakKazino(MALI_BUDZET, "Kazino nema dovoljno budzeta za isplatu.");
        budzetKazina -= delta;
        igrac.promeniBalans(delta);
    }
    else if (delta < 0) {
        double need = -delta;
        if (igrac.dohvatiBalans() < need) throw IzuzetakKazino(MALI_BALANS, "Igrac nema dovoljno balansa.");
        igrac.promeniBalans(delta);
        budzetKazina += need;
    }
}

void Igra::dodajSkor(const Igrac& igrac, double rezultat) {
    Skor* s = new Skor(igrac, rezultat);
    (*this) += s;
}

void Igra::ispisi(std::ostream& os) const {
    os << "Igra: " << naziv_ << "\n";
    os << "Skorovi:\n";
    ispisiPoravnato("RB", 6); ispisiPoravnato("ID", 8); ispisiPoravnato("Ime", 22); ispisiPoravnato("Rezultat", 12); os << "\n";
    linija(48);
    for (int i = 0;i < brojSkorova_;i++) {
        const Skor* s = skorovi_[i];
        ispisiIntPoravnato(i + 1, 6);
        ispisiIntPoravnato(s->dohvatiIgraca().dohvatiId(), 8);
        char tmp[22];
        kopiraj(tmp, 22, s->dohvatiIgraca().dohvatiIme());
        ispisiPoravnato(tmp, 22);
        os << s->dohvatiRezultat() << "\n";
    }
}
