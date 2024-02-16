#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>

#include <random>
#include <ctime>

using namespace std;

#define n 3 //nd uzduociu kiekis
const int stud_sk = 1;

struct studentas {
    string vardas;
    string pavarde;
    int* nd;
    int egz;
};

studentas* didintiMasyva(studentas* senas, int senasDydis) {
    studentas* naujas = new studentas[senasDydis + 1];
    for (int i = 0; i < senasDydis; i++) naujas[i] = senas[i];
    
    return naujas;
}

int main() {
    srand(time(nullptr));
    int stud_sk = 1;
    studentas *studentai = new studentas[stud_sk];
    string option;

    do {
        cout << "Meniu: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus: ";
        getline(cin, option);

    } while(option != "1" && option != "2" && option != "3");
    
    while (true) {
        cout << stud_sk << "-ojo studento duomenys ";
        if (option == "3") {
            studentai[i].vardas = "Vardenis_" + to_string(i+1);
            studentai[i].pavarde = "Pavardenis_" + to_string(i+1);

            for (int grade = 0; grade < n; grade++) studentai[i].nd[grade] = rand() % 11;
            studentai[i].egz = rand() % 11;

            cout << "sugeneruoti" << endl;
            continue;
        } else {
            cout << endl;
            cout << "Vardas: ";
            cin >> studentai[i].vardas;

            cout << "Pavarde: ";
            cin >> studentai[i].pavarde;
        }
        if (option == "2") {
            for (int grade = 0; grade < n; grade++) studentai[i].nd[grade] = rand() % 11;
            studentai[i].egz = rand() % 11;

            continue;
        } else { // pazymiu rankine ivestis
            for (int gradeNum = 0; gradeNum < n + 1; gradeNum++) { // nd skaicius + 1 (egzamino ivertinimas)
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
    }

    double agreguotas = 0, galutinis;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Naudoti vidurki ar mediana? (1 - Vidurkis, 2 - Mediana): ";
        getline(cin, option);
    } while(option != "1" && option != "2");

    cout << "Vardas        Pavardė       Galutinis ";
    if(option == "1") cout << "(Vid.)" << endl;
    else cout << "(Med.)" << endl;
    cout << "--------------------------------------------" << endl;
    
    for (int i = 0; i < stud_sk; i++) {
        // studentas *stud = &studentai[i];
        cout << left << setw(14) << studentai[i].vardas << left << setw(14) << studentai[i].pavarde;

        if (option == "1") { //vidurkis
            for (int gradeNum = 0; gradeNum < n; gradeNum++) {
                agreguotas += studentai[i].nd[gradeNum];
            }
            agreguotas /= n;
        } else { //mediana
            sort(studentai[i].nd, studentai[i].nd + n);
            agreguotas = n % 2 == 0 ? (studentai[i].nd[n / 2 - 1] + studentai[i].nd[n / 2]) / 2.0 : studentai[i].nd[n / 2];
        }

        galutinis = agreguotas * 0.4 + studentai[i].egz * 0.6;
        cout << fixed << setprecision(2) << galutinis << endl;
    }
}