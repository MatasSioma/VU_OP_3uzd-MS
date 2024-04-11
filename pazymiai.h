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
        Studentas(string vardas = "", string pavarde = "", int egz = 0, double vidurkis = 0, double mediana = 0, vector<int> nd = {}) : 
            vardas(vardas), pavarde(pavarde), egz(egz), vidurkis(vidurkis), mediana(mediana), nd(nd) {}
        Studentas(istringstream& is, int ndSk);
        inline string getVardas() const {return vardas;}
        inline string getPavarde() const {return pavarde;}
        inline double getVidurkis() const {return vidurkis;}
        inline double getMediana() const {return mediana;}

        void ndAppend(int balas) {nd.push_back(balas);} //prideda viena namu darba.
        void ndResize(int size) {nd.resize(size);}
        inline int ndSk() {return nd.size();}
};

void pasirinktiEiga(string msg, int* option, int max);
bool taipArNe(string uzklausa);

void rikiuotiPagalParametra(vector<Studentas> &studentai, int option);
void addLineToFile(ofstream &konteineris, Studentas &stud);
void sortAndAddToFile(vector<Studentas> &kietekai, vector<Studentas> &vargsiukai, int option);

#endif