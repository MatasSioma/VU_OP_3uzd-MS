#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>

#include "pazymiai.h"

void generuotiFailus() {
    int eilSk[5] {1000, 10000, 100000, 1000000, 1000000};
    int ndSk, rikiavimas = 0;
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
            generuotas << endl << left << setw(24) << "Vardenis" + to_string(eil+1) << left << setw(24) << "Pavardenis" + to_string(eil+1);
            for (int nd = 0; nd <= ndSk; nd++) generuotas << left << setw(10) << 1 + rand()%10;
        }
        generuotas.close();

        double t = generuoti.elapsed();
        bendras += t;
        cout << "Sugeneruoti " << eilSk[n] << " eilučių failą užtruko: " << generuoti.elapsed() << "s" << endl;

        // Paskirstymas i du failus
        ifstream bendras;
        ofstream konteineriai[2];
        // ostringstream line;
        vector<studentas> studentai;
        studentas naujas;
        
        bendras.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");
        konteineriai[0].open("sugeneruoti/" + to_string(eilSk[n]) + "geri.txt");
        konteineriai[1].open("sugeneruoti/"+ to_string(eilSk[n]) + "blogi.txt");

        for(int i = 0; i < 2; i++) {
            konteineriai[i] << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
            for (int nd = 1; nd <= ndSk; nd++) konteineriai[i] << left << setw(10) << to_string(nd) + "ND";
            konteineriai[i] << left << setw(10) << "Egz.";
        }

        bendras.ignore(numeric_limits<streamsize>::max(), '\n');
        studentai.resize(eilSk[n]);
        for (int stud = 0; stud < eilSk[n]; stud++) {
            bendras >> naujas.vardas >> naujas.pavarde;

            int agreguotas = 0, pazimys = 0;
            // naujas.nd.clear();
            naujas.nd.resize(ndSk);
            for(int nd = 0; nd < ndSk; nd++) {
                bendras >> pazimys;
                agreguotas += pazimys;
                naujas.nd.at(nd) = pazimys;
            }
            // cout << "nd size(): " << naujas.nd.size() << " ndSk: " << ndSk << endl;
            agreguotas /= (double)ndSk;
            agreguotas = ceil(agreguotas * 100.0) / 100.0;
            bendras >> naujas.egz;
            naujas.vidurkis = agreguotas * 0.4 + naujas.egz * 0.6;
            
            sort(naujas.nd.begin(), naujas.nd.end());
            agreguotas = ndSk % 2 == 0 ? (naujas.nd[ndSk / 2 - 1] + naujas.nd[ndSk / 2]) / 2.0 : naujas.nd[ndSk / 2];
            agreguotas = ceil(agreguotas * 100.0) / 100.0;
            naujas.mediana = agreguotas * 0.4 + naujas.egz * 0.6;

            studentai.at(stud) = naujas;
        }

        if (rikiavimas == 0) pasirinktiEiga("1 - Rikiuoti pagal vardą, 2 - Rikiuoti pagal pavardę, 3 - Rikiuoti pagal vidurkį, 4 - Rikiuoti pagal medianą: ", &rikiavimas, 4);
        
        switch (rikiavimas) {
        case 1:
            sort(studentai.begin(), studentai.end(), palygintiPagalVarda);
            break;
        case 2:
            sort(studentai.begin(), studentai.end(), palygintiPagalPavarde);
            break;
        case 3:
            sort(studentai.begin(), studentai.end(), palygintiPagalVidurki);
            break;
        case 4:
            sort(studentai.begin(), studentai.end(), palygintiPagalMediana);
            break;
        default:
            break;
        }

        for(auto &stud : studentai) {
            int index = 0;
            // cout << "nd size(): " << naujas.nd.size() << " ndSk: " << ndSk << endl;
            if(stud.vidurkis < 5) index = 1;
            konteineriai[index] << endl << left << setw(24) << stud.vardas << left << setw(24) << stud.pavarde;
            for(int i = 0; i < ndSk; i++) konteineriai[index] << left << setw(10) << stud.nd.at(i);
            konteineriai[index] << left << setw(10) << stud.egz;
        }

        bendras.close();
        konteineriai[0].close();
        konteineriai[1].close();
        cout << "Files closed" << endl;
    }
    
    cout << "Bendras programos veikimo laikas: " << bendras << "s" << endl;
}