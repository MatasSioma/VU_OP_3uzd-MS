#ifndef PAZYMIAI_H
#define PAZYMIAI_H

#include <string>
#include <vector>

using namespace std;

struct studentas {
    string vardas = "vardas";
    string pavarde = "pavarde";
    vector<int> nd = {0};
    int egz = 0;
    double vidurkis = 0;
    double mediana = 0;
};

string atnaujintiMasyvaUzklausa(string uzklausa);
void atnaujintiMasyva(vector<studentas> &studentai, int stud_sk, int nd_sk);
void atspauzdintiMasyvoInfo(vector<studentas> &studentai);
void pasirinktiEiga(string msg, int* option, int max);

bool palygintiPagalVarda(const studentas &a, const studentas &b);
bool palygintiPagalPavarde(const studentas &a, const studentas &b);
bool palygintiPagalVidurki(const studentas &a, const studentas &b);
bool palygintiPagalMediana(const studentas &a, const studentas &b);

#endif