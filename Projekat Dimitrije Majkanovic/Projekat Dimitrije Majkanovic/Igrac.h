#ifndef __IGRAC_H__
#define __IGRAC_H__
#include <iostream>
#include "Alati.h"
#include "Izuzeci.h"

class Igrac {
public:
    Igrac(const char* ime = "Igrac", double balans = 0);

    int dohvatiId() const { return id_; }
    const char* dohvatiIme() const { return ime_; }
    double dohvatiBalans() const { return balans_; }

    void postaviIme(const char* ime);
    void postaviBalans(double b) { balans_ = b; }
    void promeniBalans(double delta) { balans_ += delta; }

    friend std::istream& operator>>(std::istream& is, Igrac& i);
    friend std::ostream& operator<<(std::ostream& os, const Igrac& i);

private:
    static int sledeciId_;
    int id_;
    char ime_[81]; 
    double balans_;
};

#endif