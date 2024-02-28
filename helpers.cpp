#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>

# include "pazymiai.h"

string atnaujintiMasyvaUzklausa(string uzklausa) {
    cout << uzklausa;
    string ats = "";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, ats);
    transform(ats.begin(), ats.end(), ats.begin(), ::tolower); //convert to lowerCase

    return ats;
}

void atnaujintiMasyva(vector<studentas> &studentai, int stud_sk, int nd_sk) {
    studentas tuscias;
    for(int i = 0; i < stud_sk - studentai.size(); i++) studentai.push_back(tuscias);
    for(auto &stud: studentai) {
        int diff = nd_sk - stud.nd.size();
        for (int i = 0; i < diff; i++) stud.nd.push_back(0);
    }
}

void atspauzdintiMasyvoInfo(vector<studentas> &studentai) {
    cout << "\n\nMasyvo dumenys:\n";
    cout << "Vardas        Pavardė       NdPažymiai         Egzaminas" << endl;
    for(int y = 0; y < studentai.size(); y++) {
        cout << left << setw(14)<< studentai[y].vardas << left << setw(14) << studentai[y].pavarde;
        cout << "[ "; 
        for(int x = 0; x < studentai[y].nd.size(); x++) cout << left << setw(2) << studentai[y].nd[x] << " ";
        cout << "]";

        cout << "       " << studentai[y].egz << endl;
    }
}

bool palygintiPagalVarda(const studentas &a, const studentas &b) {
    return a.vardas < b.vardas;
}

bool palygintiPagalPavarde(const studentas &a, const studentas &b) {
    return a.pavarde < b.pavarde;
}

bool palygintiPagalVidurki(const studentas &a, const studentas &b) {
    return a.vidurkis < b.vidurkis;
}

bool palygintiPagalMediana(const studentas &a, const studentas &b) {
    return a.mediana < b.mediana;
}