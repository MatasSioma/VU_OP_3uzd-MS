#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>

#include <random>
#include <ctime>
#include <cctype>

using namespace std;

struct studentas {
    string vardas = "vardas";
    string pavarde = "pavarde";
    int* nd = nullptr;
    int egz = 0;
};

studentas* atnaujintiMasyva(studentas* senas, int Nstud_sk, int Nnd_sk, int Sstud_sk, int Snd_sk) {
    studentas tuscias;
    studentas* naujas = new studentas[Nstud_sk];
    for (int i = 0; i < Sstud_sk; i++) {
        naujas[i].vardas = senas[i].vardas;
        naujas[i].pavarde = senas[i].pavarde;
        naujas[i].egz = senas[i].egz;
    }
    if(Nstud_sk > Sstud_sk) {
        naujas[Sstud_sk] = tuscias;
        naujas[Sstud_sk].nd = new int[Nnd_sk] {0};
    }

    for (int i = 0; i < Sstud_sk; i++) {
        naujas[i].nd = new int[Nnd_sk];
        // cout << naujas[i].nd << " length: " << Nnd_sk << endl;
        for (int b = 0; b < Snd_sk; b++) {
            naujas[i].nd[b] = senas[i].nd[b];
        }
        if(Nnd_sk > Snd_sk) naujas[i].nd[Snd_sk] = 0;
        delete []senas[i].nd;
    }

    return naujas;
}

void atspauzdintiMasyvoInfo(studentas* studentai, int stud_sk, int nd_sk) {
    cout << "\n\nMasyvo dumenys:\n";
    cout << "Vardas        Pavardė       NdPažymiai         Egzaminas" << endl;
    for(int y = 0; y < stud_sk; y++) {
        cout << left << setw(14)<< studentai[y].vardas << left << setw(14) << studentai[y].pavarde;
        cout << "[ "; 
        for(int x = 0; x < nd_sk; x++) cout << left << setw(2) << studentai[y].nd[x] << " ";
        cout << "]";

        cout << "       " << studentai[y].egz << endl;
    }
}

string atnaujintiMasyvaUzklausa(string uzklausa) {
    cout << uzklausa;
    string ats = "";

    
    getline(cin, ats);
    transform(ats.begin(), ats.end(), ats.begin(), ::tolower); //convert to lowerCase
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return ats;
}

int main() {
    srand(time(nullptr));
    int stud_sk = 1, nd_sk = 1;
    string option;

    //inicijuojam masyva
    studentas *studentai = new studentas[stud_sk], *tmp = nullptr;
    studentai[0].nd = new int[nd_sk];

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
                    tmp = atnaujintiMasyva(studentai, stud_sk, nd_sk+1, stud_sk, nd_sk);
                    delete []studentai;
                    studentai = tmp;
                    nd_sk += 1;
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
                    tmp = atnaujintiMasyva(studentai, stud_sk, nd_sk+1, stud_sk, nd_sk);
                    delete []studentai;
                    studentai = tmp;
                    nd_sk += 1;
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
        tmp = atnaujintiMasyva(studentai, stud_sk+1, nd_sk, stud_sk, nd_sk);
        delete []studentai;
        studentai = tmp;
        stud_sk += 1;
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
            sort(studentai[i].nd, studentai[i].nd + nd_sk);
            agreguotas = nd_sk % 2 == 0 ? (studentai[i].nd[nd_sk / 2 - 1] + studentai[i].nd[nd_sk / 2]) / 2.0 : studentai[i].nd[nd_sk / 2];
        }

        galutinis = agreguotas * 0.4 + studentai[i].egz * 0.6;
        cout << fixed << setprecision(2) << galutinis << endl;
    }

    // atspauzdintiMasyvoInfo(studentai, stud_sk, nd_sk);
}