#ifndef __IGRA_H__
#define __IGRA_H__
#include <iostream>
#include <cmath>
#include "Skor.h"
#include "Alati.h"
#include "Izuzeci.h"

class Igra {
public:
    Igra(const char* naziv = "Igra");
    virtual ~Igra();

    const char* dohvatiNaziv() const { return naziv_; }

    Igra& operator+=(Skor* s);
    const Skor* operator-(double vrednost) const;

    void sortirajRastuce();
    void sortirajOpadajuce();

    virtual void pokreni(Igrac& igrac, double& budzetKazina) = 0;

    static void transfer(Igrac& igrac, double delta, double& budzetKazina);

    virtual void ispisi(std::ostream& os) const;

protected:
    void dodajSkor(const Igrac& igrac, double rezultat);

    enum { MAX_SKOROVA = 200 };

private:
    char naziv_[31];
    Skor* skorovi_[MAX_SKOROVA];
    int brojSkorova_;
};

#endif