/* 4. Program care simuleaza functionarea unui translator stiva nedeterminist cu lambda - tranzitii.
Programul citeste (dintr - un fisier sau de la consola) elementele unui translator stiva nedeterminist cu lambda - tranzitii
oarecare(starile, starea initiala, starile finale, alfabetul de intrare, alfabetul de iesire, alfabetul stivei, simbolul initial
al stivei, tranzitiile).
Programul permite citirea unui nr oarecare de siruri peste alfabetul de intrare al translatorului.
Pentru fiecare astfel de sir se afiseaza toate iesirile(siruri peste alfabetul de iesire) corespunzatoare
(Atentie !pot exista 0, 1 sau mai multe iesiri pt acelasi sir de intrare). */

#include <iostream>
#include "StackParser.h"

using namespace std;

int main()
{
    ifstream in("stackParser2.in");
    ifstream fin("input.in");

    ofstream fout("output.out");

    StackParser parser(in, fin);

    parser.parse(fout);

    in.close();
    fin.close();
    fout.close();

    return 0;
}