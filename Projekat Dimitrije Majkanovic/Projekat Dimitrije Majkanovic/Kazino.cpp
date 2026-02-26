#include "Kazino.h"

Kazino::Kazino(double budzet) : budzet_(budzet), brojIgara_(0) {
    for (int i = 0;i < MAX_IGARA;i++) igre_[i] = 0;
}

Kazino::~Kazino() {
    for (int i = 0;i < brojIgara_;i++) {
        delete igre_[i];
        igre_[i] = 0;
    }
    brojIgara_ = 0;
}

void Kazino::dodajIgru(Igra* igra) {
    if (!igra) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Pokusaj dodavanja prazne igre.");
    if (brojIgara_ >= MAX_IGARA) { delete igra; throw IzuzetakKazino(STANJE_IGRE, "Prekoracenje kapaciteta igara."); }
    igre_[brojIgara_++] = igra;
}

Igra& Kazino::igraNaIndeksu(int indeks) {
    if (indeks < 0 || indeks >= brojIgara_) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Neispravan izbor igre.");
    return *igre_[indeks];
}

void Kazino::ispisiIgre() const {
    std::cout << "\n--- LISTA IGARA ---\n";
    for (int i = 0;i < brojIgara_;i++) {
        std::cout << (i + 1) << ") " << igre_[i]->dohvatiNaziv() << "\n";
    }
}

void Kazino::uplatiIgracu(Igrac& igrac, double iznos) {
    if (iznos <= 0) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Iznos mora biti pozitivan.");
    if (budzet_ < iznos) throw IzuzetakKazino(MALI_BUDZET, "Kazino nema dovoljno budzeta za uplatu.");
    budzet_ -= iznos;
    igrac.promeniBalans(iznos);
}

void Kazino::igraj(int indeks, Igrac& igrac) {
    if (budzet_ <= 500) throw IzuzetakKazino(MALI_BUDZET, "Budzet kazina mora biti veci od 500.");
    if (igrac.dohvatiBalans() <= 10) throw IzuzetakKazino(MALI_BALANS, "Balans igraca mora biti veci od 10.");
    igraNaIndeksu(indeks).pokreni(igrac, budzet_);
}
