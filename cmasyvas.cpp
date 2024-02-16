#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>

#include <random>
#include <ctime>
#include <cctype>

using namespace std;

// #define n 3 //nd uzduociu kiekis
// const int stud_sk = 1;

struct studentas {
    string vardas;
    string pavarde;
    int* nd;
    int egz;
};

studentas* atnaujintiMasyva(studentas* senas, int Nstud_sk, int Nnd_sk, int Sstud_sk, int Snd_sk) {
    studentas tuscias;
    studentas* naujas = new studentas[Nstud_sk];
    for (int i = 0; i < Sstud_sk; i++) naujas[i] = senas[i];
    if(Nstud_sk != Sstud_sk) naujas[Nstud_sk] = tuscias;

    for (int i = 0; i < Sstud_sk; i++) {
        naujas[i].nd = new int[Nnd_sk];
        for (int b = 0; b < Snd_sk; b++) {
            naujas[i].nd[b] = senas[i].nd[b];
        }
        delete []senas[i].nd;
        if(Nnd_sk != Snd_sk) naujas[i].nd[Nnd_sk] = 0;
    }
    
    return naujas;
}

int main() {
    srand(time(nullptr));
    int stud_sk = 1, nd_sk = 1;
    string option;

    //inicijuojam masyva
    studentas *studentai = new studentas[stud_sk], stud, *tmp = nullptr;
    studentai[0].nd = new int[nd_sk];

    do {
        cout << "Meniu: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus: ";
        getline(cin, option);

    } while(option != "1" && option != "2" && option != "3");
    
    string more = "";
    while(true) {
        stud = studentai[stud_sk-1];
        cout << stud_sk << "-ojo studento duomenys ";
        if (option == "3" || option == "2") {
            for (int grade = 0; grade < nd_sk; grade++) stud.nd[grade] = rand() % 11;
            stud.egz = rand() % 11;
        }
        if (option == "1" || option == "2") {
            cout << endl;
            cout << "Vardas: ";
            cin >> stud.vardas;

            cout << "Pavarde: ";
            cin >> stud.pavarde;
        }

        if (option == "3") {
            stud.vardas = "Vardenis_" + to_string(stud_sk+1);
            stud.pavarde = "Pavardenis_" + to_string(stud_sk+1);

            cout << "sugeneruoti" << endl;
            
        } else { // pazymiu rankine ivestis
            for (int gradeNum = 0; gradeNum < nd_sk; gradeNum++) { // nd skaicius + 1 (egzamino ivertinimas)
                while(true) {
                    int grade;
                    if (gradeNum < nd_sk) {
                        cout << gradeNum + 1 << " ND įvertinimas (0-10): ";
                        cin >> grade;
                        stud.nd[gradeNum] = grade;
                    } else {
                        cout << "Egzamino įvertinimas: ";
                        cin >> grade;
                        stud.egz = grade;
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
                cout << "Pridėti dar vieną namų darbą? (ENTER - Taip, 'Ne'/'N' - Ne): ";
                getline(cin, more);
                transform(more.begin(), more.end(), more.begin(), ::tolower); //convert to lowerCase
                if(more == "ne" || more == "n") break;
                tmp = atnaujintiMasyva(studentai, stud_sk, nd_sk+1, stud_sk, nd_sk);
                delete []studentai;
                studentai = tmp;
                nd_sk += 1;
            }

            cout << "Ar norite įvesti dar vieną studentą? (ENTER - Taip, 'Ne'/'N' - Ne): ";
            getline(cin, more);
            transform(more.begin(), more.end(), more.begin(), ::tolower); //convert to lowerCase
            if(more == "ne" || more == "n") break;
            tmp = atnaujintiMasyva(studentai, stud_sk+1, nd_sk, stud_sk, nd_sk);
            delete []studentai;
            studentai = tmp;
            stud_sk += 1;
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
        stud = studentai[i];
        cout << left << setw(14) << stud.vardas << left << setw(14) << stud.pavarde;

        if (option == "1") { //vidurkis
            for (int gradeNum = 0; gradeNum < nd_sk; gradeNum++) {
                agreguotas += stud.nd[gradeNum];
            }
            agreguotas /= nd_sk;
        } else { //mediana
            sort(stud.nd, stud.nd + nd_sk);
            agreguotas = nd_sk % 2 == 0 ? (stud.nd[nd_sk / 2 - 1] + stud.nd[nd_sk / 2]) / 2.0 : stud.nd[nd_sk / 2];
        }

        galutinis = agreguotas * 0.4 + stud.egz * 0.6;
        cout << fixed << setprecision(2) << galutinis << endl;
    }
}