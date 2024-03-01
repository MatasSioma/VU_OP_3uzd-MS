#include <iostream>
#include <iomanip>
#include <fstream>
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
    double vidurkis = 0;
    double mediana = 0;
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

int main() {
    srand(time(nullptr));
    int stud_sk = 1, nd_sk = 1;
    string option;
    studentas tuscias;

    //inicijuojam masyva
    vector<studentas> studentai(1);

    do {
        cout << "Meniu: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus, 4 - Nuskaityti iš failo (turi būti bent 1 ND laukas): ";
        getline(cin, option);

    } while(option != "1" && option != "2" && option != "3" && option != "4");
    
    string more = "";
    if (option != "4") {
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
    }
    else {
        string fname, line = "";
        ifstream is;
        char a;

        do {
            cout << "Įveskite failo pavadinimą: ";
            cin >> fname;
            is.open(fname);
        } while(is.fail());

        is.ignore(numeric_limits<streamsize>::max(), '\n');

        int i = -2;
        while(!is.eof()) {
            is.get(a);
            line += a;
            if(a == ' ') {
                line.pop_back();
                if(line != "") {
                    // cout << i << " " << line << endl;
                    if(i == -2) studentai[stud_sk-1].vardas = line;
                    else if(i == -1) studentai[stud_sk-1].pavarde = line;
                    else {
                        if (i+1 > nd_sk) nd_sk += 1;
                        studentai[stud_sk-1].nd.push_back(stoi(line));
                    }
                    i++;
                }
                line = "";
            }
            
            if (a == '\n') {
                line.pop_back();
                studentai[stud_sk-1].egz = stoi(line);
                stud_sk += 1;
                studentai.push_back(tuscias);
                line = "";
                i = -2;
            }
        }

        is.close();
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    double agreguotas = 0;
    for (int i = 0; i < stud_sk; i++) {
        // vidurkis
        for (int gradeNum = 0; gradeNum < nd_sk; gradeNum++) agreguotas += studentai[i].nd[gradeNum];
        agreguotas /= (double)nd_sk;
        agreguotas = ceil(agreguotas * 100.0) / 100.0;
        studentai[i].vidurkis = agreguotas * 0.4 + studentai[i].egz * 0.6;

        // mediana
        sort(studentai[i].nd.begin(), studentai[i].nd.end());
        agreguotas = nd_sk % 2 == 0 ? (studentai[i].nd[nd_sk / 2 - 1] + studentai[i].nd[nd_sk / 2]) / 2.0 : studentai[i].nd[nd_sk / 2];
        agreguotas = ceil(agreguotas * 100.0) / 100.0;
        studentai[i].mediana = agreguotas * 0.4 + studentai[i].egz * 0.6;
    }

    do {
        cout << "1 - Rikiuoti pagal vardą, 2 - Rikiuoti pagal pavardę, 3 - Rikiuoti pagal vidurkį, 4 - Rikiuoti pagal medianą: ";
        getline(cin, option);
    } while(option != "1" && option != "2" && option != "3" && option != "4");

    switch (stoi(option)) {
    case 1:
        sort(studentai.begin(), studentai.end(), palygintiPagalVarda);
        break;
    case 2:
        sort(studentai.begin(), studentai.end(), palygintiPagalPavarde);
        break;
    case 3:
        sort(studentai.begin(), studentai.end(), palygintiPagalVidurki);
        break;
    case 4:
        sort(studentai.begin(), studentai.end(), palygintiPagalMediana);
        break;
    default:
        break;
    }

    cout << "Kiek studentų atspauzdinti? (ENTER - visus): ";

    string answer = "";
    int print_sk;
    while (true) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, answer);
        if (answer == "") { // Vartotojas iveda ne skaiciu
            print_sk = stud_sk;
        }
        if (print_sk >= 1 && print_sk <= stud_sk) break;
        cout << "Įveskite sveiką skaičių nuo 1 iki " << stud_sk << " (studentų skaičiaus)." << endl;

    }

    // do {
    //     cout << "Rodyti rezultatus: 1 - vidurkį, 2 - medianą: ";
    //     getline(cin, option);
    // } while(option != "1" && option != "2");

    cout << "Vardas             Pavardė            Galutinis(Vid.)    Galutinis(Med.)  " << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < print_sk; i++) {
        cout << left << setw(19) << studentai[i].vardas << left << setw(19) << studentai[i].pavarde;
        cout << left << setw(19) << fixed << setprecision(2) << studentai[i].vidurkis;
        cout << left << setw(19) << fixed << setprecision(2) << studentai[i].mediana << endl;
    }

    // atspauzdintiMasyvoInfo(studentai);
}