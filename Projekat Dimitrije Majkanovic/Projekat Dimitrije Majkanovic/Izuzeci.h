#ifndef __IZUZECI_H__
#define __IZUZECI_H__
#include <iostream>

enum TipGreske {
    NEISPRAVAN_UNOS,
    NEISPRAVNA_OKLADA,
    MALI_BUDZET,
    MALI_BALANS,
    STANJE_IGRE
};

class IzuzetakKazino {
public:
    IzuzetakKazino(TipGreske tip, const char* poruka)
        : tip_(tip), poruka_(poruka) {
    }

    const char* sta() const { return poruka_; }
    TipGreske tip() const { return tip_; }

private:
    TipGreske tip_;
    const char* poruka_;
};

#endif