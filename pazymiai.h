#ifndef PAZYMIAI_H
#define PAZYMIAI_H

#include <string>
#include <vector>
#include "timer.h"

using namespace std;

struct studentas {
    string vardas = "vardas";
    string pavarde = "pavarde";
    vector<int> nd = {0};
    int egz = 0;
    double vidurkis = 0;
    double mediana = 0;
};

double skaiciuotiVidurki(const studentas &stud, int ndSk);
double skaiciuotiMediana(const studentas &stud, int ndSk);

void atnaujintiMasyva(vector<studentas> &studentai, int stud_sk, int nd_sk);
void atspauzdintiMasyvoInfo(vector<studentas> &studentai);
void rikiuotiPagalParametra(vector<studentas> &studentai, int option);
void pasirinktiEiga(string msg, int* option, int max);
bool taipArNe(string uzklausa);

void generuotiFailus();

#endif