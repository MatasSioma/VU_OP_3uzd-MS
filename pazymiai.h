#ifndef PAZYMIAI_H
#define PAZYMIAI_H

#include <string>
#include <vector>

using namespace std;

struct studentas {
    std::string vardas = "vardas";
    string pavarde = "pavarde";
    vector<int> nd = {0};
    int egz = 0;
    double vidurkis = 0;
    double mediana = 0;
};

#endif