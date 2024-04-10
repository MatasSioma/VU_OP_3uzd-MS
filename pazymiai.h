#ifndef Container
#define Container std::vector
#endif

#ifndef PAZYMIAI_H
#define PAZYMIAI_H

#include <string>
#include <vector>
#include <list>
#include <deque>
#include "timer.h"

using namespace std;

class Studentas {
    private:
        string vardas;
        string pavarde;
        int egz;
        // double vidurkis;
        // double mediana;
        vector<int> nd;
    public:
        Studentas(string vardas = "", string pavarde = "", int egz = 0, vector<int> nd = {}) : 
            vardas(vardas), pavarde(pavarde), egz(egz), nd(nd) {}
        getVidurkis();
        getMediana();
};

double skaiciuotiVidurki(const studentas &stud, int ndSk);
double skaiciuotiMediana(const studentas &stud, int ndSk);

// void atnaujintiMasyva(vector<studentas> &studentai, int stud_sk, int nd_sk);
// void atspauzdintiMasyvoInfo(vector<studentas> &studentai);
void pasirinktiEiga(string msg, int* option, int max);
bool taipArNe(string uzklausa);
void addLineToFile(ofstream &konteineris, Studentas &stud);

void generuotiFailus();


template <typename T>
void sortAndAddToFile(T &kietekai, T &vargsiukai, int option) {
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

void rikiuotiPagalParametra(list<studentas> &studentai, int option);

template <typename T>
void rikiuotiPagalParametra(T&studentai, int option) {
    switch (option) {
    case 1:
        sort(studentai.begin(), studentai.end(), [](studentas &a, studentas&b)->bool{return a.vardas > b.vardas;});
        break;
    case 2:
        sort(studentai.begin(), studentai.end(), [](studentas &a, studentas&b)->bool{return a.pavarde > b.pavarde;});
        break;
    case 3:
        sort(studentai.begin(), studentai.end(), [](studentas &a, studentas&b)->bool{return a.vidurkis > b.vidurkis;});
        break;
    case 4:
        sort(studentai.begin(), studentai.end(), [](studentas &a, studentas&b)->bool{return a.mediana > b.mediana;});
        break;
    case 5:
        break;
    default:
        break;
    }
}

#endif