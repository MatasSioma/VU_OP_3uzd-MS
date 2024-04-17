#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>
#include <sstream>

#include "pazymiai.h"

using namespace std;

int main() {
    srand(time(nullptr));
    vector<Studentas> studentai;
    string inFileName = "";

    if(!taipArNe("Ar norėsite generuoti failus? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
        int eilSk[5] {1'000, 10'000, 100'000, 1'000'000, 10'000'000};
        int ndSk, rikiavimas;
        pasirinktiEiga("Kiek namų darbų generuoti?: ", &ndSk, 30);

        for(int n = 0; n < 5; n++) {
            Timer generuoti;

            // Failo generavimas
            ofstream generuotas;
            generuotas.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");
            stringstream buffer;
            buffer << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
            for (int nd = 1; nd <= ndSk; nd++) buffer << left << setw(10) << to_string(nd) + "ND";
            buffer << "Egz.";

            for(int eil = 0; eil < eilSk[n]; eil++) {
                buffer << endl << left << setw(24) << "Vardenis" + to_string(eil+1) << left << setw(24) << "Pavardenis" + to_string(eil+1);
                for (int nd = 0; nd < ndSk; nd++) buffer << left << setw(10) << 1 + rand()%10;
                buffer << 1 + rand()%10; // egz
            }

            generuotas << buffer.str();
            generuotas.close();
            buffer.clear();
            double t = generuoti.elapsed();
            cout << "Sugeneruoti " << eilSk[n] << " eilučių failą užtruko: " << t << "s" << endl;
        }
        return 0;
    }

    vector<Studentas> studentai;
    int stud_sk = 1, ndSk = 1;
    int option, rikiavimas;
    pasirinktiEiga("Meniu: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus, 4 - Nuskaityti iš failo (turi būti bent 1 ND laukas): ", &option, 4);
    
    if (option != 4) {
        while(true) {
            cout << stud_sk << "-ojo studento duomenys";
            if (option == 1) {
                int grade, i = 0;
                while (true) {
                    while(true) {
                        if (i < ndSk) {
                        try {
                            cout << "\n" << i + 1 << " ND įvertinimas (0-10): ";
                            cin >> grade;
                            if(!cin.good() || grade < 1 || grade > 10) {
                                throw invalid_argument("Netinkama įvestis. Įveskite skaičių nuo 1 iki 10");
                            }
                            studentai[stud_sk-1].nd.push_back(grade);
                            break;
                        } catch(invalid_argument &e) {
                            cerr << e.what() << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        }
                    }
                    if (i + 1 == ndSk) {
                        if(taipArNe("Pridėti dar vieną namų darbą? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
                            while (true) {   
                                try {
                                    cout << "Egzamino įvertinimas: ";
                                    cin >> grade;
                                    if(!cin.good() || grade < 1 || grade > 10) {
                                        throw invalid_argument("Netinkama įvestis. Įveskite skaičių nuo 1 iki 10");
                                    }
                                    studentai[stud_sk-1].egz = grade;
                                    break;
                                } catch(invalid_argument &e) {
                                    cerr << e.what() << endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    continue;
                                }
                            }
                            
                            break;
                        }
                        ndSk += 1;
                        atnaujintiMasyva(studentai, stud_sk, nd_sk);
                    }
                    i++;
                }
            }
            if (option == 3 || option == 2) {
                int i = 0;
                while (true) {
                    studentai[stud_sk-1].nd[i] = rand() % 11;
                    cout << "\n" << i+1 << " Namų darbo rezultatas sugeneruotas";
                    if (i + 1 == nd_sk) {
                        if(taipArNe("\nPridėti dar vieną namų darbą? (ENTER - Taip, 'Ne'/'N' - Ne): ")) break;
                        nd_sk += 1;
                        atnaujintiMasyva(studentai, stud_sk, nd_sk);
                    }
                    i++;
                }
                studentai[stud_sk-1].egz = rand() % 11;
            }
            if (option == 1 || option == 2) {
                cout << endl;
                cout << "Vardas: ";
                cin >> studentai[stud_sk-1].vardas;

                cout << "Pavarde: ";
                cin >> studentai[stud_sk-1].pavarde;
            }

            if (option == 3) {
                studentai[stud_sk-1].vardas = "Vardenis_" + to_string(stud_sk);
                studentai[stud_sk-1].pavarde = "Pavardenis_" + to_string(stud_sk);

                cout << "Vardas bei pavardė sugeneruoti" << endl;
                
            }
            if(taipArNe("Ar norite įvesti dar vieną studentą? (ENTER - Taip, 'Ne'/'N' - Ne): ")) break;
            stud_sk += 1;
            atnaujintiMasyva(studentai, stud_sk, nd_sk);
            // cout << studentai << " stud_sk: " << stud_sk << " nd_sk: " << nd_sk << endl;
        }
    }

    else { // option == 4
        string line = "";
        ifstream is;
        char a;
        
        while(true) {
            try {
                cout << "Įveskite failo pavadinimą: ";
                cin >> inFileName;
                is.open(inFileName);
                if (is.fail()) throw invalid_argument("Failas nerastas.");
                break;
            } catch (exception &e) {
                cerr << e.what() << endl;
            }
        }

        stringstream buffer;
            
        buffer << is.rdbuf();
        is.close();

        string line;
        // Timer nuskaityi;
        getline(buffer, line);
        ndSk = countNd(line);

        while (getline(buffer, line)) {
            istringstream lineStream(line);
            studentai.push_back(Studentas(lineStream, ndSk));
        }
        buffer.clear();

        // cout << "Duomenu skaitymas uztruko: "<< skaitymas.elapsed() << "s" << endl;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < stud_sk; i++) {
        studentai.at(i).vidurkis = skaiciuotiVidurki(studentai.at(i), nd_sk);
        studentai.at(i).mediana = skaiciuotiMediana(studentai.at(i), nd_sk);
    }
    
    pasirinktiEiga("Išvestyje studentus rikiuoti pagal: 1 - Vardą, 2 - Pavardę, 3 - Vidurkį, 4 - Medianą: ", &rikiavimas, 4);
    // rikiuotiPagalParametra(studentai, option);

    pasirinktiEiga("1 - Spauzdinti į konsolę 2 - Įrašyti į failą?:", &option, 2);

    if (option == 1) {
        cout << "Kiek studentų atspauzdinti? (ENTER - visus): ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string answer = "";
        int print_sk;
        getline(cin, answer);
        if (answer == "") {
            print_sk = stud_sk;
        } else {
            while (true) {
                try {
                    print_sk = stoi(answer);
                    if(print_sk >= 1 && print_sk <= stud_sk) break;
                    throw invalid_argument(to_string(print_sk));
                } catch (exception &e) {
                    cerr << "Netinkama įvestis. Įveskite skaičių nuo 1 iki " << stud_sk << ": ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, answer);
                }
            }
        }

        rikiuotiPagalParametra(studentai, option);

        cout << "Vardas                  Pavardė                 Vid.      Med.";
        cout << "--------------------------------------------" << endl;

        for (int i = 0; i < print_sk; i++) {
            cout << left << setw(24) << studentai[i].vardas << left << setw(24) << studentai[i].pavarde << fixed << setw(10) << studentai[i].vidurkis << fixed << studentai[i].mediana;
        }
    } else {
        pasirinktiEiga("1 - Sukurti atskirus konteineriu kietekam ir vargšiems, 2 - Viską išvesti viename faile: ", &option, 2);
        if (option == 1) {
            vector<Studentas> vargsiukai;
            auto isVargsas = [](Studentas &a){return a.getVidurkis() >= 5;};
            auto it = partition(studentai.begin(), studentai.end(), isVargsas);
            int index = distance(studentai.begin(), it);
            while (it != studentai.end()) {
                vargsiukai.push_back(move(*it));
                ++it;
            }
            studentai.resize(index);
            // copy_if(studentai.begin(), studentai.end(), back_inserter(vargsiukai), isVargsas);
            // studentai.erase(remove_if(studentai.begin(), studentai.end(), isVargsas), studentai.end());
            sortAndAddToFile(studentai, vargsiukai, rikiavimas);
        } else {
            rikiuotiPagalParametra(studentai, option);
            ofstream konteineris;
            if(inFileName != "") konteineris.open("output/" + inFileName + "-Apdorota.txt");
            else konteineris.open("output/" + "rankiniaiDuomenys-Apdorota.txt");
            
            for (auto &stud : studentai) addLineToFile(konteineris, stud);
            konteineris.close();
        }
    }
}