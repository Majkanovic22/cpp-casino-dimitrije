#ifndef __PSEUDORULET_H__
#define __PSEUDORULET_H__
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Igra.h"

class PseudoRulet : public Igra {
public:
    PseudoRulet();
    void pokreni(Igrac& igrac, double& budzetKazina);

    PseudoRulet& operator+=(int broj);
    bool& operator[](int broj);
    PseudoRulet& operator*=(char boja);
    PseudoRulet& operator/=(bool parni);
    PseudoRulet& operator-=(bool);

private:
    void resetuj();
    void generisiIshod();
    bool ishodParan() const;
    bool ishodCrven() const;
    int izracunajDeltu() const;

    int ishod_;
    bool brojevi_[36];
    char boja_;
    bool parni_;
};

#endif