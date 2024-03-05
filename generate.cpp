#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>

#include "pazymiai.h"

void generuotiFailus() {
    int eilSk[5] {1000, 10000, 100000, 1000000, 1000000};
    int ndSk;
    pasirinktiEiga("Kiek namų darbų generuoti?: ", &ndSk, 30);
    double bendras;

    srand(time(nullptr));
    for(int n = 0; n < 2; n++) {
        Timer generuoti;

        ofstream generuotas;
        generuotas.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");

        generuotas << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
        for (int nd = 1; nd <= ndSk; nd++) generuotas << left << setw(10) << to_string(nd) + "ND";
        generuotas << left << setw(10) << "Egz.";

        for(int eil = 0; eil < eilSk[n]; eil++) {
            generuotas << endl << left << setw(24) << "Vardas" + to_string(eil+1) << left << setw(24) << "Pavardė" + to_string(eil+1);
            for (int nd = 0; nd <= ndSk; nd++) generuotas << left << setw(10) << 1 + rand()%10;
        }
        generuotas.close();

        double t = generuoti.elapsed();
        bendras += t;
        cout << "Sugeneruoti " << eilSk[n] << " eilučių failą užtruko: " << generuoti.elapsed() << "s" << endl;
    }
    
    cout << "Bendras programos veikimo laikas: " << bendras << "s" << endl;
}