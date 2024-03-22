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
    pasirinktiEiga("Konteineriuose studentus rikiuoti pagal: 1 - Vardą, 2 - Pavardę, 3 - Vidurkį, 4 - Medianą: ", &rikiavimas, 4);
    double bendrasLaikas;

    srand(time(nullptr));

    for(int n = 0; n < 5; n++) {
        cout << endl;
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
        bendrasLaikas += t;
        cout << "Sugeneruoti " << eilSk[n] << " eilučių failą užtruko: " << t << "s" << endl;

        // Paskirstymas i du failus
        ifstream bendras;
        ofstream konteineriai[2];
        // ostringstream line;
        
        bendras.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");
        buffer << bendras.rdbuf();
        bendras.close();
        konteineriai[0].open("sugeneruoti/" + to_string(eilSk[n]) + "geri.txt");
        konteineriai[1].open("sugeneruoti/"+ to_string(eilSk[n]) + "blogi.txt");

        for(int i = 0; i < 2; i++) {
            konteineriai[i] << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
            for (int nd = 1; nd <= ndSk; nd++) konteineriai[i] << left << setw(10) << to_string(nd) + "ND";
            konteineriai[i] << left << setw(10) << "Egz.";
        }

        vector<studentas> studentai;
        studentas naujas;
        Timer nuskaityi;
        buffer.ignore(numeric_limits<streamsize>::max(), '\n');
        studentai.resize(eilSk[n]);
        for (int stud = 0; stud < eilSk[n]; stud++) {
            buffer >> naujas.vardas >> naujas.pavarde;

            // naujas.nd.clear();
            naujas.nd.resize(ndSk);
            for(int nd = 0; nd < ndSk; nd++) {
                buffer >> naujas.nd.at(nd);
            }
            // cout << "nd size(): " << naujas.nd.size() << " ndSk: " << ndSk << endl;
            buffer >> naujas.egz;
            naujas.vidurkis = skaiciuotiVidurki(naujas, ndSk);
            naujas.mediana = skaiciuotiMediana(naujas, ndSk);

            studentai.at(stud) = naujas;
        }

        t = nuskaityi.elapsed();
        bendrasLaikas += t;
        cout << "Nuskaityti " << eilSk[n] << " eilučių bendrą failą užtruko: " << t << "s" << endl;

        rikiuotiPagalParametra(studentai, rikiavimas);

        Timer surusioti;
        for(auto &stud : studentai) {
            int index = 0;
            // cout << "nd size(): " << naujas.nd.size() << " ndSk: " << ndSk << endl;
            if(stud.vidurkis < 5) index = 1;
            konteineriai[index] << endl << left << setw(24) << stud.vardas << left << setw(24) << stud.pavarde;
            for(int i = 0; i < ndSk; i++) konteineriai[index] << left << setw(10) << stud.nd.at(i);
            konteineriai[index] << stud.egz;
        }

        konteineriai[0].close();
        konteineriai[1].close();
        buffer.clear();

        t = surusioti.elapsed();
        bendrasLaikas += t;
        cout << "Surušiuoti ir išvesti " << eilSk[n] << " eilučių failą į konteinerius užtruko: " << t << "s" << endl;
    }
    
    cout << "\nBendras programos veikimo (skaičiavimų) laikas: " << bendrasLaikas << "s" << endl;
}