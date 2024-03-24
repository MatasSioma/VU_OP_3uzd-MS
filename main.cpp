#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>

#include "pazymiai.h"

int main() {
    srand(time(nullptr));
    int stud_sk = 1, nd_sk = 1;
    studentas tuscias;

    //inicijuojam masyva
    vector<studentas> studentai(1);

    if(!taipArNe("Ar norėsite generuoti failus? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
        generuotiFailus();
        return 0;
    }

    if(!taipArNe("Ar vygdyti studentų skirtymą į konteinerius? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
        int eilSk[5] {1'000, 10'000, 100'000, 1'000'000, 10'000'000};
        int ndSk, rikiavimas, strategija;
        pasirinktiEiga("Kiek ND yra failuose?: ", &ndSk, 30);
        pasirinktiEiga("Kurią studentų paskirstymo į konteinerius strategiją naudoti? 1-ąją, 2-ąją, 3-ąją: ", &strategija, 3);
        pasirinktiEiga("Konteineriuose studentus rikiuoti pagal: 1 - Vardą, 2 - Pavardę, 3 - Vidurkį, 4 - Medianą: ", &rikiavimas, 4);

        for(int n = 0; n < 5; n++) {
            // Paskirstymas i du failus
            cout << endl;
            ifstream bendras;
            stringstream buffer;
            
            bendras.open("sugeneruoti/" + to_string(eilSk[n]) + "bendras.txt");
            buffer << bendras.rdbuf();
            bendras.close();

            Container<studentas> studentai;
            studentas naujas;
            Timer nuskaityi;
            buffer.ignore(numeric_limits<streamsize>::max(), '\n');
            // studentai.resize(eilSk[n]);
            for (int i = 0; i < eilSk[n]; i++) {
                buffer >> naujas.vardas >> naujas.pavarde;

                // naujas.nd.clear();
                naujas.nd.resize(ndSk);
                for(int nd = 0; nd < ndSk; nd++) {
                    buffer >> naujas.nd.at(nd);
                }
                // cout << "nd size(): " << naujas.nd.size() << " ndSk: " << ndSk << endl;
                buffer >> naujas.egz;
                naujas.vidurkis = skaiciuotiVidurki(naujas, ndSk);
                naujas.mediana = skaiciuotiMediana(naujas, ndSk);

                naujas.nd.clear();
                naujas.nd.shrink_to_fit();

                studentai.push_back(naujas);
            }
            cout << "Nuskaityti " << eilSk[n] << " eilučių bendrą failą užtruko: " << nuskaityi.elapsed() << "s" << endl;

            Timer sortinti;
            rikiuotiPagalParametra(studentai, 3);
            cout << "Išdėstyti " << eilSk[n] << " eilučių didėjimo tvarka užtruko: " << sortinti.elapsed() << "s" << endl;

            Timer surusioti;
            if (strategija == 1) {
                Container<studentas> kietekai, vargsiukai;
                for(auto &stud : studentai) {
                    if(stud.vidurkis < 5) vargsiukai.push_back(stud);
                    else kietekai.push_back(stud);
                }
                sortAndAddToFile(kietekai, vargsiukai, rikiavimas);

            } else if(strategija == 2) {
                Container<studentas> vargsiukai;
                int i = 0;
                for(auto it = studentai.rbegin(); it != studentai.rend(); it++) {
                    studentas &stud = *it;
                    if(stud.vidurkis < 5) {
                        vargsiukai.push_back(stud);
                        i++;
                    } else {
                        break;
                    }
                }
                studentai.resize(studentai.size() - i);
                studentai.shrink_to_fit();
                sortAndAddToFile(studentai, vargsiukai, rikiavimas);
            } else {
                Container<studentas> vargsiukai;
                auto isVargsas = [](studentas &a){return a.vidurkis >= 5;};
                auto it = partition(studentai.begin(), studentai.end(), isVargsas);
                int index = distance(studentai.begin(), it);
                while (it != studentai.end()) {
                    ++it;
                    vargsiukai.push_back(move(*it));
                }
                studentai.resize(index);
                sortAndAddToFile(studentai, vargsiukai, rikiavimas);
            }

            buffer.clear();

            cout << "Surušiuoti ir išvesti " << eilSk[n] << " eilučių failą į konteinerius užtruko: " << surusioti.elapsed() << "s, " << strategija << "-oji strategija."<< endl;
        }
        return 0;
    }

    int option;
    pasirinktiEiga("Meniu: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus, 4 - Nuskaityti iš failo (turi būti bent 1 ND laukas): ", &option, 4);
    
    if (option != 4) {
        while(true) {
            cout << stud_sk << "-ojo studento duomenys";
            if (option == 1) {
                int grade, i = 0;
                while (true) {
                    while(true) {
                        if (i < nd_sk) {
                        try {
                            cout << "\n" << i + 1 << " ND įvertinimas (0-10): ";
                            cin >> grade;
                            if(!cin.good() || grade < 1 || grade > 10) {
                                throw invalid_argument("Netinkama įvestis. Įveskite skaičių nuo 1 iki 10");
                            }
                            studentai[stud_sk-1].nd[i] = grade;
                            break;
                        } catch(invalid_argument &e) {
                            cerr << e.what() << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        }
                    }
                    if (i + 1 == nd_sk) {
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
                        nd_sk += 1;
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
        string fname, line = "";
        ifstream is;
        char a;
        
        while(true) {
            try {
                cout << "Įveskite failo pavadinimą: ";
                cin >> fname;
                is.open(fname);
                if (is.fail()) throw invalid_argument("Failas nerastas.");
                break;
            } catch (exception &e) {
                cerr << e.what() << endl;
            }
        }

        Timer skaitymas;
        is.ignore(numeric_limits<streamsize>::max(), '\n');

        int i = -2, lineNum = 2;

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
                        try {
                            studentai[stud_sk-1].nd.push_back(stoi(line));
                        } catch (exception &e) {
                            cerr << "Nepavyko nuskaityti Nd įvertinimo eilutėjė " << lineNum << " namų darbo, reikšmė: " << line << endl;
                            line = "";
                            i = -2;
                            continue;
                        }
                    }
                    i++;
                }
                line = "";
            }
            
            if (a == '\n') {
                line.pop_back();
                try {
                    studentai[stud_sk-1].egz = stoi(line);
                } catch (exception &e) {
                    cerr << "Nepavyko nuskaityti egzamino įvertinimo eilutėjė " << lineNum << " egzamino, reikšmė: " << line << endl;
                    line = "";
                    i = -2;
                    continue;
                }
                stud_sk++;
                lineNum++;
                studentai.push_back(tuscias);
                line = "";
                i = -2;
            }
        }

        is.close();
        cout << "Duomenu skaitymas uztruko: "<< skaitymas.elapsed() << "s" << endl;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < stud_sk; i++) {
        studentai.at(i).vidurkis = skaiciuotiVidurki(studentai.at(i), nd_sk);
        studentai.at(i).mediana = skaiciuotiMediana(studentai.at(i), nd_sk);
    }
    
    pasirinktiEiga("1 - Rikiuoti pagal vardą, 2 - Rikiuoti pagal pavardę, 3 - Rikiuoti pagal vidurkį, 4 - Rikiuoti pagal medianą: ", &option, 4);
    rikiuotiPagalParametra(studentai, option);

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
    pasirinktiEiga("Rodyti rezultatus: 1 - vidurkį, 2 - medianą: ", &option, 2);

    cout << "Vardas              Pavardė             Galutinis ";
    if(option == 1) cout << "(Vid.)" << endl;
    else cout << "(Med.)" << endl;
    cout << "--------------------------------------------" << endl;

    for (int i = 0; i < print_sk; i++) {
        cout << left << setw(20) << studentai[i].vardas << left << setw(20) << studentai[i].pavarde;
        if (option == 1) cout << fixed << setprecision(2) << studentai[i].vidurkis << endl;
        else cout << fixed << setprecision(2) << studentai[i].mediana << endl;
    }
}