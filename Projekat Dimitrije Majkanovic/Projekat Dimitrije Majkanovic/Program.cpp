#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "Kazino.h"
#include "PseudoRulet.h"
#include "Blekdzek.h"
#include "Izuzeci.h"

static void meni() {
    std::cout << "\n========== KAZINO ==========\n";
    std::cout << "1) Prikazi igraca\n";
    std::cout << "2) Prikazi igre\n";
    std::cout << "3) Igraj\n";
    std::cout << "4) Prikazi skorove igre\n";
    std::cout << "5) Sortiraj skorove (rastuće)\n";
    std::cout << "6) Sortiraj skorove (opadajuće)\n";
    std::cout << "7) Nadji skor po vrednosti\n";
    std::cout << "8) Uplati igracu balans\n";
    std::cout << "0) Izlaz\n";
    std::cout << "Izbor: ";
}

static int izaberiIgru(Kazino& k) {
    k.ispisiIgre();
    std::cout << "Izaberi igru (1.." << k.brojIgara() << "): ";
    int x; std::cin >> x;
    if (!std::cin || x < 1 || x > k.brojIgara())
        throw IzuzetakKazino(NEISPRAVAN_UNOS, "Neispravan izbor igre.");
    return x - 1;
}

int main() {
    std::srand((unsigned)std::time(0));

    try {
        Kazino kazino(10000.0);
        kazino.dodajIgru(new PseudoRulet());
        kazino.dodajIgru(new Blekdzek());

        Igrac igrac("Dimitrije", 100.0);

        while (true) {
            meni();
            int izbor;
            if (!(std::cin >> izbor)) break;

            try {
                switch (izbor) {
                case 0:
                    std::cout << "Pozdrav!\n";
                    return 0;
                case 1:
                    std::cout << igrac << "\n";
                    std::cout << "Budzet kazina: " << kazino.dohvatiBudzet() << "\n";
                    break;
                case 2:
                    kazino.ispisiIgre();
                    break;
                case 3: {
                    int i = izaberiIgru(kazino);
                    kazino.igraj(i, igrac);
                    break;
                }
                case 4: {
                    int i = izaberiIgru(kazino);
                    kazino.igraNaIndeksu(i).ispisi(std::cout);
                    break;
                }
                case 5: {
                    int i = izaberiIgru(kazino);
                    kazino.igraNaIndeksu(i).sortirajRastuce();
                    kazino.igraNaIndeksu(i).ispisi(std::cout);
                    break;
                }
                case 6: {
                    int i = izaberiIgru(kazino);
                    kazino.igraNaIndeksu(i).sortirajOpadajuce();
                    kazino.igraNaIndeksu(i).ispisi(std::cout);
                    break;
                }
                case 7: {
                    int i = izaberiIgru(kazino);
                    double v;
                    std::cout << "Unesi vrednost rezultata: ";
                    std::cin >> v;
                    const Skor* s = (kazino.igraNaIndeksu(i) - v);
                    if (!s) std::cout << "Nije pronadjen.\n";
                    else std::cout << "Pronadjen: " << *s << "\n";
                    break;
                }
                case 8: {
                    double iznos;
                    std::cout << "Iznos uplate: ";
                    std::cin >> iznos;
                    kazino.uplatiIgracu(igrac, iznos);
                    std::cout << "Uplata uspesna.\n";
                    break;
                }
                default:
                    std::cout << "Nepoznata opcija.\n";
                }
            }
            catch (const IzuzetakKazino& e) {
                std::cout << "Greska: " << e.sta() << "\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
        }
    }
    catch (const IzuzetakKazino& e) {
        std::cout << "Fatalna greska: " << e.sta() << "\n";
        return 1;
    }
    return 0;
}
