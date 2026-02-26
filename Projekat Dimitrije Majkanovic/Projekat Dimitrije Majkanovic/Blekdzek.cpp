#include "Blekdzek.h"

static int vrednostKarte(int v) {
    if (v >= 2 && v <= 10) return v;
    if (v >= 11 && v <= 13) return 10;
    return 1;
}

Blekdzek::Blekdzek() : Igra("Blekdzek"), pozicija_(0) {
    resetuj();
}

void Blekdzek::napuniSpil() {
    int idx = 0;
    for (int v = 1; v <= 13; v++) {
        for (int k = 0; k < 4; k++) spil_[idx++] = v;
    }
}

void Blekdzek::izmesajSpil() {
    for (int i = 51; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = spil_[i];
        spil_[i] = spil_[j];
        spil_[j] = t;
    }
}

void Blekdzek::resetuj() {
    napuniSpil();
    izmesajSpil();
    for (int i = 0;i < 9;i++) ruka_[i] = 0;
    pozicija_ = 0;
}

bool Blekdzek::dodajUReku(int karta) {
    for (int i = 0;i < 9;i++) {
        if (ruka_[i] == 0) { ruka_[i] = karta; return true; }
    }
    return false;
}

int Blekdzek::izvuciKartu() {
    while (pozicija_ < 52 && spil_[pozicija_] == 0) pozicija_++;
    if (pozicija_ >= 52) throw IzuzetakKazino(STANJE_IGRE, "Spil je prazan.");
    int karta = spil_[pozicija_];
    spil_[pozicija_] = 0;
    pozicija_++;
    return karta;
}

int Blekdzek::ukupno() const {
    int suma = 0;
    int asovi = 0;
    for (int i = 0;i < 9;i++) {
        int v = ruka_[i];
        if (v == 0) continue;
        if (v == 1) asovi++;
        suma += vrednostKarte(v);
    }
    if (asovi > 0 && suma + 10 <= 21) suma += 10;
    return suma;
}

void Blekdzek::pokreni(Igrac& igrac, double& budzetKazina) {
    resetuj();
    std::cout << "\n--- BLEKDZEK ---\n";
    std::cout << "Komande: (h) izvuci kartu, (s) prekini igru.\n";

    dodajUReku(izvuciKartu());
    dodajUReku(izvuciKartu());

    while (true) {
        int rezultat = ukupno();
        std::cout << "Trenutni rezultat: " << rezultat << "\n";

        if (rezultat > 21) {
            std::cout << "Prekoracenje 21! Kazna: -3\n";
            Igra::transfer(igrac, -3.0, budzetKazina);
            dodajSkor(igrac, (double)rezultat);
            return;
        }

        std::cout << "Unos (h/s): ";
        char cmd;
        std::cin >> cmd;

        if (cmd == 'h' || cmd == 'H') {
            int k = izvuciKartu();
            if (!dodajUReku(k)) throw IzuzetakKazino(STANJE_IGRE, "Ruka je puna (9 karata).");
        }
        else if (cmd == 's' || cmd == 'S') {
            int gen = 15 + (rand() % 11);
            std::cout << "Prekid: generisan broj = " << gen << "\n";

            int cur = ukupno();
            if (gen > cur && gen >= 15 && gen <= 21) {
                std::cout << "Gubitak: -3\n";
                Igra::transfer(igrac, -3.0, budzetKazina);
            }
            else {
                std::cout << "Dobitak: +3\n";
                Igra::transfer(igrac, +3.0, budzetKazina);
            }

            dodajSkor(igrac, (double)cur);
            return;
        }
        else {
            throw IzuzetakKazino(NEISPRAVAN_UNOS, "Nepoznata komanda.");
        }
    }
}
