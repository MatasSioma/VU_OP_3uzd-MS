#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <cmath>
#include <fstream>

# include "pazymiai.h"

using namespace std;

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

int countNd(string &line) {
    int count = 0;
    for (int i = 0; i < line.length() - 1; i++) {
        if (line[i] == 'N') {
            count++;
        }
    }
    return count;
}

void equalOutNdSk(vector<Studentas> &studentai, int ndSk) {
    for(auto &stud : studentai) {
        stud.ndResize(ndSk);
        for(int i = -1; i >= stud.ndSk() - ndSk; i--) stud.setNd(i, 0);
    }
}

// void atnaujintiMasyva(vector<studentas> &studentai, int stud_sk, int nd_sk) {
//     studentas tuscias;
//     for(int i = 0; i < stud_sk - studentai.size(); i++) studentai.push_back(tuscias);
//     for(auto &stud: studentai) {
//         int diff = nd_sk - stud.nd.size();
//         for (int i = 0; i < diff; i++) stud.nd.push_back(0);
//     }
// }

void atspauzdintiMasyvoInfo(vector<Studentas> &studentai) {
    cout << "\n\nMasyvo dumenys:\n";
    cout << "Vardas        Pavardė       NdPažymiai         Egzaminas" << endl;
    for(int y = 0; y < studentai.size(); y++) {
        cout << left << setw(14)<< studentai.at(y).getVardas() << left << setw(14) << studentai.at(y).getPavarde();
        cout << "[ "; 
        for(int x = 0; x < studentai.at(y).ndSk(); x++) cout << left << setw(2) << studentai.at(y).getNd(x) << " ";
        cout << "]";

        cout << "       " << studentai.at(y).getEgz() << endl;
    }
}