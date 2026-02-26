#include "PseudoRulet.h"

PseudoRulet::PseudoRulet() : Igra("PseudoRulet") {
    resetuj();
}

void PseudoRulet::resetuj() {
    ishod_ = 0;
    for (int i = 0;i < 36;i++) brojevi_[i] = false;
    boja_ = 'r';
    parni_ = false;
}

void PseudoRulet::generisiIshod() {
    ishod_ = rand() % 37; // [0..36]
}

bool PseudoRulet::ishodParan() const {
    return ishod_ != 0 && (ishod_ % 2 == 0);
}

bool PseudoRulet::ishodCrven() const {
    if (ishod_ == 0) return false;
    int n = ishod_;
    if (n >= 1 && n <= 10) return (n % 2 == 1);
    if (n >= 11 && n <= 18) return (n % 2 == 0);
    if (n >= 19 && n <= 28) return (n % 2 == 1);
    if (n >= 29 && n <= 36) return (n % 2 == 0);
    return false;
}

PseudoRulet& PseudoRulet::operator+=(int broj) {
    if (broj < 1 || broj > 36) throw IzuzetakKazino(NEISPRAVNA_OKLADA, "Broj mora biti u opsegu 1..36.");
    brojevi_[broj - 1] = true;
    return *this;
}

bool& PseudoRulet::operator[](int broj) {
    if (broj < 1 || broj > 36) throw IzuzetakKazino(NEISPRAVNA_OKLADA, "Broj mora biti u opsegu 1..36.");
    return brojevi_[broj - 1];
}

PseudoRulet& PseudoRulet::operator*=(char boja) {
    if (boja != 'r' && boja != 'c') throw IzuzetakKazino(NEISPRAVNA_OKLADA, "Boja mora biti 'r' ili 'c'.");
    boja_ = boja;
    return *this;
}

PseudoRulet& PseudoRulet::operator/=(bool parni) {
    parni_ = parni;
    return *this;
}

PseudoRulet& PseudoRulet::operator-=(bool) {
    parni_ = false;
    return *this;
}

int PseudoRulet::izracunajDeltu() const {
    int delta = 0;

    bool imaBrojeva = false;
    for (int i = 0;i < 36;i++) if (brojevi_[i]) { imaBrojeva = true; break; }

    if (imaBrojeva) {
        if (ishod_ >= 1 && ishod_ <= 36 && brojevi_[ishod_ - 1]) delta += 1;
        else delta -= 1;
    }

    // boja uvek vazi
    bool pogodakBoja = false;
    if (ishod_ != 0) {
        bool crven = ishodCrven();
        pogodakBoja = (boja_ == 'r' && crven) || (boja_ == 'c' && !crven);
    }
    delta += pogodakBoja ? 1 : -1;

    if (parni_) delta += ishodParan() ? 1 : -1;

    return delta;
}

void PseudoRulet::pokreni(Igrac& igrac, double& budzetKazina) {
    resetuj();
    std::cout << "\n--- PSEUDO RULET ---\n";
    std::cout << "Unesi brojeve (1..36). 0 zavrsava unos.\n";

    while (true) {
        int n;
        std::cout << "Broj: ";
        if (!(std::cin >> n)) throw IzuzetakKazino(NEISPRAVAN_UNOS, "Neispravan unos.");
        if (n == 0) break;
        (*this) += n;
    }

    char b;
    std::cout << "Boja (r=crvena, c=crna): ";
    std::cin >> b;
    (*this) *= b;

    int p;
    std::cout << "Parni? (1=da, 0=ne): ";
    std::cin >> p;
    (*this) /= (p != 0);

    generisiIshod();
    int delta = izracunajDeltu();

    Igra::transfer(igrac, (double)delta, budzetKazina);

    std::cout << "Ishod: " << ishod_
        << " | boja: " << (ishodCrven() ? "crvena" : "crna")
        << " | parnost: " << (ishodParan() ? "paran" : "neparan/0") << "\n";
    std::cout << "Promena balansa: " << delta << "\n";
    std::cout << "Novi balans: " << igrac.dohvatiBalans() << " | Budzet kazina: " << budzetKazina << "\n";

    dodajSkor(igrac, (double)ishod_);
}
