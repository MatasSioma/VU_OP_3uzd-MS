#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#define n 2 //nd uzduociu kiekis
const int stud_sk = 3;

struct studentas {
    string vardas = "vardas";
    string pavarde = "pavarde";
    int nd[n];
    int egz;
};

int main() {
    studentas studentai[stud_sk];

    int option;
    cout << "Meniu: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus: ";
    cin >> option;
    switch(option) {
        case 1:
            break;
        default:
            cout << "Blogai įvestas meniu pasirinkimas" << endl;
            exit(1);
    }

    cout << "Vardas        Pavardė       Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < stud_sk; i++) {
        // printf("%-14s%-14s\n", studentai[i].vardas.c_str(), studentai[i].pavarde.c_str());
        cout << left << setw(14) << studentai[i].vardas << studentai[i].pavarde << endl;
    }
}