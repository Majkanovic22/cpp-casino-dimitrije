#ifndef __KAZINO_H__
#define __KAZINO_H__
#include <iostream>
#include "Igra.h"
#include "Izuzeci.h"

class Kazino {
public:
    Kazino(double budzet = 0.0);
    ~Kazino();

    double dohvatiBudzet() const { return budzet_; }

    void dodajIgru(Igra* igra);
    int brojIgara() const { return brojIgara_; }
    Igra& igraNaIndeksu(int indeks);

    void ispisiIgre() const;
    void uplatiIgracu(Igrac& igrac, double iznos);
    void igraj(int indeks, Igrac& igrac);

private:
    enum { MAX_IGARA = 10 };
    double budzet_;
    Igra* igre_[MAX_IGARA];
    int brojIgara_;
};

#endif