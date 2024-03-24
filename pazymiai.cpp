#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cmath>
#include <fstream>

# include "pazymiai.h"

void pasirinktiEiga(string msg, int* option, int max) {
    while (true) {
        try {
            cout << msg;
            cin >> *option;
            if(!cin.good() || *option < 1 || *option > max) {
                throw invalid_argument("Netinkama įvestis. Įveskite skaičių nuo 1 iki " + to_string(max));
            }
            break;
        } catch(invalid_argument &e) {
            cerr << e.what() << endl;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool taipArNe(string uzklausa) {
    cout << uzklausa;
    string ats = "";

    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, ats);
    transform(ats.begin(), ats.end(), ats.begin(), ::tolower); //convert to lowerCase

    if (ats == "n" || ats == "ne") {
        return true;
    } else {
        return false;
    }
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

double skaiciuotiVidurki(const studentas &stud, int ndSk) {
    double agreguotas = 0;

    for (int nd = 0; nd < ndSk; nd++) agreguotas += stud.nd.at(nd);
    agreguotas /= (double)ndSk;
    agreguotas = round(agreguotas * 100.0) / 100.0; // iki simtuju
    agreguotas = agreguotas * 0.4 + stud.egz * 0.6;
    return round(agreguotas * 100.0) / 100.0;
}

double skaiciuotiMediana(const studentas &stud, int ndSk) {
    double vidurys;
    vector<int> ndCopy(ndSk);
    ndCopy = stud.nd;

    sort(ndCopy.begin(), ndCopy.end());
    vidurys = ndSk % 2 == 0 ? (ndCopy[ndSk / 2 - 1] + ndCopy[ndSk / 2]) / 2.0 : ndCopy[ndSk / 2];
    vidurys = round(vidurys * 100.0) / 100.0;
    vidurys = vidurys * 0.4 + stud.egz * 0.6;
    return vidurys;
}

void rikiuotiPagalParametra(list<studentas> &studentai, int option) {
    switch (option) {
    case 1:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.vardas > b.vardas;});
        break;
    case 2:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.pavarde > b.pavarde;});
        break;
    case 3:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.vidurkis > b.vidurkis;});
        break;
    case 4:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.mediana > b.mediana;});
        break;
    case 5:
        break;
    default:
        break;
    }
}

void addLineToFile(ofstream &konteineris, studentas stud) {
    konteineris << endl << left << setw(24) << stud.vardas << left << setw(24) << stud.pavarde;
    konteineris << left << setw(10) << stud.vidurkis << left << setw(10) << stud.mediana;
}