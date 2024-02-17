#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

#include <random>
#include <ctime>
#include <cctype>

using namespace std;

struct studentas {
    string vardas = "vardas";
    string pavarde = "pavarde";
    vector<int> nd = {0};
    int egz = 0;
};

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

int main() {
    srand(time(nullptr));
    int stud_sk = 1, nd_sk = 1;
    string option;

    //inicijuojam masyva
    vector<studentas> studentai(1);

    do {
        cout << "Meniu: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus: ";
        getline(cin, option);

    } while(option != "1" && option != "2" && option != "3");
    
    string more = "";
    while(true) {
        cout << stud_sk << "-ojo studento duomenys";

        // cout << "\n " << stud_sk-1 << "- student index "<< stud.vardas << " stud_sk: " << stud_sk << " nd_sk: " << nd_sk << endl;
        if (option == "1") {
            int i = 0;
            while (true) {
                while(true) {
                    int grade = -1;
                    if (i < nd_sk) {
                        cout << "\n" << i + 1 << " ND įvertinimas (0-10): ";
                        cin >> grade;
                        studentai[stud_sk-1].nd[i] = grade;
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
                if (i + 1 == nd_sk) {
                    more = atnaujintiMasyvaUzklausa("Pridėti dar vieną namų darbą? (ENTER - Taip, 'Ne'/'N' - Ne): ");
                    if(more == "ne" || more == "n") {
                        while (true)
                        {
                            int grade = -1;
                            cout << "Egzamino įvertinimas: ";
                            cin >> grade;
                            studentai[stud_sk-1].egz = grade;
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
                        
                        break;
                    }
                    nd_sk += 1;
                    atnaujintiMasyva(studentai, stud_sk, nd_sk);
                }
                i++;
            }
        }
        if (option == "3" || option == "2") {
            int i = 0;
            while (true) {
                studentai[stud_sk-1].nd[i] = rand() % 11;
                cout << "\n" << i+1 << " Namų darbo rezultatas sugeneruotas";
                if (i + 1 == nd_sk) {
                    more = atnaujintiMasyvaUzklausa("\nPridėti dar vieną namų darbą? (ENTER - Taip, 'Ne'/'N' - Ne): ");
                    if(more == "ne" || more == "n") break;
                    nd_sk += 1;
                    atnaujintiMasyva(studentai, stud_sk, nd_sk);
                }
                i++;
            }
            studentai[stud_sk-1].egz = rand() % 11;
        }
        if (option == "1" || option == "2") {
            cout << endl;
            cout << "Vardas: ";
            cin >> studentai[stud_sk-1].vardas;

            cout << "Pavarde: ";
            cin >> studentai[stud_sk-1].pavarde;
        }

        if (option == "3") {
            studentai[stud_sk-1].vardas = "Vardenis_" + to_string(stud_sk);
            studentai[stud_sk-1].pavarde = "Pavardenis_" + to_string(stud_sk);

            cout << "Vardas bei pavardė sugeneruoti" << endl;
            
        }
        more = atnaujintiMasyvaUzklausa("Ar norite įvesti dar vieną studentą? (ENTER - Taip, 'Ne'/'N' - Ne): ");
        if(more == "ne" || more == "n") break;
        stud_sk += 1;
        atnaujintiMasyva(studentai, stud_sk, nd_sk);
        // cout << studentai << " stud_sk: " << stud_sk << " nd_sk: " << nd_sk << endl;
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
        cout << left << setw(14) << studentai[i].vardas << left << setw(14) << studentai[i].pavarde;

        if (option == "1") { //vidurkis
            for (int gradeNum = 0; gradeNum < nd_sk; gradeNum++) {
                agreguotas += studentai[i].nd[gradeNum];
            }
            agreguotas /= nd_sk;
        } else { //mediana
            sort(studentai[i].nd.begin(), studentai[i].nd.end());
            agreguotas = nd_sk % 2 == 0 ? (studentai[i].nd[nd_sk / 2 - 1] + studentai[i].nd[nd_sk / 2]) / 2.0 : studentai[i].nd[nd_sk / 2];
        }

        galutinis = agreguotas * 0.4 + studentai[i].egz * 0.6;
        cout << fixed << setprecision(2) << galutinis << endl;
    }
}