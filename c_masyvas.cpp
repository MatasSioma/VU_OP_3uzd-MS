#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

#define n 2 //nd uzduociu kiekis
const int stud_sk = 2;

struct studentas {
    string vardas;
    string pavarde;
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
            for (int i = 0; i < stud_sk; i++) {
                cout << i+1 << "-ojo studento duomenys" << endl;

                cout << "Vardas: ";
                cin >> studentai[i].vardas;

                cout << "Pavarde: ";
                cin >> studentai[i].pavarde;

                for(int gradeNum = 0; gradeNum < n + 1; gradeNum++) { // nd skaicius + 1 (egzamino ivertinimas)
                    while(true) {
                        int grade;
                        if (gradeNum < n) {
                            cout << gradeNum + 1 << " ND įvertinimas (0-10): ";
                            cin >> grade;
                            studentai[i].nd[gradeNum] = grade;
                        } else {
                            cout << "Egzamino įvertinimas: ";
                            cin >> grade;
                            studentai[i].egz = grade;
                        }
                        if (cin.fail()) { // Vartotojas iveda ne skaiciu
                            cout << "Įveskite sveiką skaičių nuo 0 iki 10." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (grade >= 0 && grade <= 10) {
                            break;
                        }
                    }
                }
            }
            break;
        case 2:
            cout << "Funkcija dar nesukurta" << endl;
            exit(1);
        case 3:
            cout << "Funkcija dar nesukurta" << endl;
            exit(1);
        default:
            cout << "Blogai įvestas meniu pasirinkimas" << endl;
            exit(1);
    }

    cout << "Vardas        Pavardė       Galutinis (Vid.) / Galutinis (Med.)" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < stud_sk; i++) {
        // printf("%-14s%-14s\n", studentai[i].vardas.c_str(), studentai[i].pavarde.c_str());
        cout << left << setw(14) << studentai[i].vardas << left << setw(14) <<studentai[i].pavarde << studentai[i].nd[0] << studentai[i].nd[1] << studentai[i].egz << endl;
    }
}