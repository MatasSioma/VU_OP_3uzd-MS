#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>
#include <sstream>

#include "pazymiai.h"

using namespace std;

int main() {
    srand(time(nullptr));
    //inicijuojam masyva
    vector<Studentas> studentai;

    if(!taipArNe("Ar norėsite generuoti failus? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
        int eilSk[5] {1'000, 10'000, 100'000, 1'000'000, 10'000'000};
        int ndSk, rikiavimas;
        pasirinktiEiga("Kiek namų darbų generuoti?: ", &ndSk, 30);

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
        return 0;
    }

    if(!taipArNe("Ar vygdyti studentų skirtymą į konteinerius? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
        int eilSk[2] {100'000, 1'000'000};
        int ndSk, rikiavimas, strategija;
        pasirinktiEiga("Kiek ND yra failuose?: ", &ndSk, 30);
        pasirinktiEiga("Kurią studentų paskirstymo į konteinerius strategiją naudoti? 1-ąją, 2-ąją, 3-ąją: ", &strategija, 3);
        pasirinktiEiga("Konteineriuose studentus rikiuoti pagal: 1 - Vardą, 2 - Pavardę, 3 - Vidurkį, 4 - Medianą: ", &rikiavimas, 4);

        for(int n = 0; n < 2; n++) {
            double bendrasLaikas = 0;
            for(int bandymas = 0; bandymas < 5; bandymas++) {
            // Paskirstymas i du failus
            Timer bendrasVienas;

            cout << endl;
            ifstream bendras;
            stringstream buffer;
            
            bendras.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");
            buffer << bendras.rdbuf();
            bendras.close();

            vector<Studentas> studentai;
            // Timer nuskaityi;
            buffer.ignore(numeric_limits<streamsize>::max(), '\n');
            string line;
            for (int i = 0; i < eilSk[n]; i++) {
                getline(buffer, line);
                istringstream lineStream(line);
                studentai.push_back(Studentas(lineStream, ndSk));
            }
            buffer.clear();
            // cout << "Nuskaityti " << eilSk[n] << " eilučių bendrą failą užtruko: " << nuskaityi.elapsed() << "s" << endl;

            // Timer sortinti;
            rikiuotiPagalParametra(studentai, 3);
            // cout << "Išdėstyti " << eilSk[n] << " eilučių didėjimo tvarka užtruko: " << sortinti.elapsed() << "s" << endl;

            // Timer surusioti;
            if (strategija == 1) {
                vector<Studentas> kietekai, vargsiukai;
                for(auto &stud : studentai) {
                    if(stud.getVidurkis() < 5) vargsiukai.push_back(stud);
                    else kietekai.push_back(stud);
                }
                sortAndAddToFile(kietekai, vargsiukai, rikiavimas);

            } else if(strategija == 2) {
                vector<Studentas> vargsiukai;
                int i = 0;
                for(auto it = studentai.rbegin(); it != studentai.rend(); it++) {
                    Studentas &stud = *it;
                    if(stud.getVidurkis() < 5) {
                        vargsiukai.push_back(stud);
                        i++;
                    } else {
                        break;
                    }
                }
                studentai.resize(studentai.size() - i);
                // studentai.shrink_to_fit();
                sortAndAddToFile(studentai, vargsiukai, rikiavimas);
            } else {
                vector<Studentas> vargsiukai;
                auto isVargsas = [](Studentas &a){return a.getVidurkis() >= 5;};
                auto it = partition(studentai.begin(), studentai.end(), isVargsas);
                int index = distance(studentai.begin(), it);
                while (it != studentai.end()) {
                    vargsiukai.push_back(move(*it));
                    ++it;
                }
                studentai.resize(index);
                // copy_if(studentai.begin(), studentai.end(), back_inserter(vargsiukai), isVargsas);
                // studentai.erase(remove_if(studentai.begin(), studentai.end(), isVargsas), studentai.end());
                sortAndAddToFile(studentai, vargsiukai, rikiavimas);
            }
            bendrasLaikas += bendrasVienas.elapsed();
            }
            // cout << "Surušiuoti ir išvesti " << eilSk[n] << " eilučių failą į konteinerius užtruko: " << surusioti.elapsed() << "s, " << strategija << "-oji strategija."<< endl;
            cout << "Bendras laikas suskirstyti "<< eilSk[n] << " studentus 5 į konteinerius, naudojant " << strategija << " - strategija ir vector tipo konteinerius: " << bendrasLaikas/5.0 << "(5 bandymų vidurkis)" << endl;
        }
    }
}