#ifndef __BLEKDZEK_H__
#define __BLEKDZEK_H__
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Igra.h"

class Blekdzek : public Igra {
public:
    Blekdzek();
    void pokreni(Igrac& igrac, double& budzetKazina);

private:
    void resetuj();
    void napuniSpil();
    void izmesajSpil();
    int izvuciKartu();
    int ukupno() const;
    bool dodajUReku(int karta);

    int spil_[52];
    int ruka_[9];
    int pozicija_;
};

#endif