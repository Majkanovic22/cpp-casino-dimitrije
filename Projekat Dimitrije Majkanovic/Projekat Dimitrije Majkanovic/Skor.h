#ifndef __SKOR_H__
#define __SKOR_H__
#include <iostream>
#include "Igrac.h"

class Skor {
public:
    Skor(const Igrac& igrac, double rezultat = 0.0);

    Skor(const Skor&) = delete;
    Skor& operator=(const Skor&) = delete;

    const Igrac& dohvatiIgraca() const { return igrac_; }
    double dohvatiRezultat() const { return rezultat_; }

    void postaviRezultat(double r) { rezultat_ = r; }

    friend std::ostream& operator<<(std::ostream& os, const Skor& s);

private:
    double rezultat_;
    Igrac igrac_; 
};

#endif