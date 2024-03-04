#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>

#include "pazymiai.h"

double generuotiFailus() {
    int eilSk[5] {1000, 10000, 100000, 1000000, 1000000};
    int ndSk;
    pasirinktiEiga("Kiek namų darbų generuoti?: ", &ndSk, 30);
    Timer bendras;

    srand(time(nullptr));
    for(int n = 0; n < 5; n++) {
        ofstream generuotas;
        generuotas.open("sugeneruoti/bendras" + to_string(eilSk[n]) + ".txt");
    }

    return bendras.elapsed();
}