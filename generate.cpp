#include <iostream>
#include <sstream>
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

        // Failo generavimas
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

        // Paskirstymas i du failus
        ifstream bendras;
        ofstream konteineriai[2];
        string vardas, pavarde, data;
        ostringstream line;
        
        bendras.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");
        konteineriai[0].open("sugeneruoti/" + to_string(eilSk[n]) + "geri.txt");
        konteineriai[1].open("sugeneruoti/"+ to_string(eilSk[n]) + "blogi.txt");

        for(int i = 0; i < 2; i++) {
            konteineriai[i] << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
            for (int nd = 1; nd <= ndSk; nd++) konteineriai[i] << left << setw(10) << to_string(nd) + "ND";
            konteineriai[i] << left << setw(10) << "Egz." << left << setw(12) << "Galutinis(Vid.)";
        }

        bendras.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int stud = 0; stud < eilSk[n]; stud++) {
            line.str("");
            bendras >> vardas >> pavarde;
            line << left << setw(24) << vardas << left << setw(24) << pavarde;
            int agreguotas = 0;
            double galutinis;
            for(int nd = 0; nd < ndSk; nd++) {
                bendras >> data;
                line << left << setw(10) << data;
                agreguotas += stoi(data);
            }
            bendras >> data;
            line << left << setw(10) << data;

            galutinis = agreguotas/ndSk * 0.4 + stoi(data) * 0.6;
            line << left << setw(12) << galutinis;

            if (galutinis >= 5.0) konteineriai[0] << endl << line.str();
            else konteineriai[1] << endl << line.str();
        }

        bendras.close();
        konteineriai[0].close();
        konteineriai[1].close();
    }
    
    cout << "Bendras programos veikimo laikas: " << bendras << "s" << endl;
}