#ifndef Container
#define Container std::vector
#endif

#ifndef PAZYMIAI_H
#define PAZYMIAI_H

#include <string>
#include <vector>
// #include <list>
// #include <deque>
#include "timer.h"

using namespace std;

class Studentas {
    private:
        string vardas;
        string pavarde;
        int egz;
        double vidurkis;
        double mediana;
        vector<int> nd;
    public:
        Studentas(string vardas = "", string pavarde = "", int egz = 0, vector<int> nd = {}) : 
            vardas(vardas), pavarde(pavarde), egz(egz), nd(nd) {}
        string getVardas() {return vardas;}
        string getPavarde() {return pavarde;}
        double getVidurkis();
        double getMediana();
        void appendNd(int balas) {nd.push_back(balas);} //prideda viena namu darba.
        int ndSk() {return nd.size();}
};

void pasirinktiEiga(string msg, int* option, int max);
bool taipArNe(string uzklausa);
void addLineToFile(ofstream &konteineris, Studentas &stud);

void generuotiFailus();


void sortAndAddToFile(vector &kietekai, vector &vargsiukai, int option) {
    rikiuotiPagalParametra(kietekai, option);
    rikiuotiPagalParametra(vargsiukai, option);

    ofstream konteineriai[2];
    int eilSk = kietekai.size() + vargsiukai.size();
    konteineriai[0].open("sugeneruoti/" + to_string(eilSk) + "geri.txt");
    konteineriai[1].open("sugeneruoti/"+ to_string(eilSk) + "blogi.txt");

    for(int i = 0; i < 2; i++) {
        konteineriai[i] << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
        konteineriai[i] << left << setw(10) << "Vid." << left << setw(10) << "Med.";
    }

    for (auto &stud : kietekai) addLineToFile(konteineriai[0], stud);
    konteineriai[0].close();
    for (auto &stud : vargsiukai) addLineToFile(konteineriai[1], stud);
    konteineriai[1].close();
}

void rikiuotiPagalParametra(vector<Studentas> &studentai, int option);
#endif