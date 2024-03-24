#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>

#include "pazymiai.h"

void generuotiFailus() {
    int eilSk[5] {1'000, 10'000, 100'000, 1'000'000, 10'000'000};
    int ndSk, rikiavimas;
    pasirinktiEiga("Kiek namų darbų generuoti?: ", &ndSk, 30);

    srand(time(nullptr));

    for(int n = 0; n < 5; n++) {
        Timer generuoti;

        // Failo generavimas
        ofstream generuotas;
        generuotas.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");
        stringstream buffer;
        buffer << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
        for (int nd = 1; nd <= ndSk; nd++) buffer << left << setw(10) << to_string(nd) + "ND";
        buffer << "Egz.";

        for(int eil = 0; eil < eilSk[n]; eil++) {
            buffer << endl << left << setw(24) << "Vardenis" + to_string(eil+1) << left << setw(24) << "Pavardenis" + to_string(eil+1);
            for (int nd = 0; nd < ndSk; nd++) buffer << left << setw(10) << 1 + rand()%10;
            buffer << 1 + rand()%10; // egz
        }

        generuotas << buffer.str();
        generuotas.close();
        buffer.clear();
        double t = generuoti.elapsed();
        cout << "Sugeneruoti " << eilSk[n] << " eilučių failą užtruko: " << t << "s" << endl;
    }
}