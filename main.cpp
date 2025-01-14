#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>
#include <sstream>

// // Windows lietuviskos raides 
// #include <windows.h>
// // x86_64-w64-mingw32-g++ -c -o main.o main.cpp

#include "pazymiai.h"

using namespace std;

int ndSk, studSk, inputOption;

int main() {
    // // Windows lietuviskos raides 
    // SetConsoleOutputCP(CP_UTF8);
    // setvbuf(stdout, nullptr, _IOFBF, 1000);
    // // x86_64-w64-mingw32-g++ -c -o main.o main.cpp

    srand(time(nullptr));
    // unsigned int reallocation = 0;
    double vectorSparta = 0;

    if(!taipArNe("Ar norėsite generuoti failus? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
        int eilSk[5] {1'000, 10'000, 100'000, 1'000'000, 10'000'000};
        int ndSk, rikiavimas;
        pasirinktiEiga("Kiek namų darbų generuoti?: ", &ndSk, 30);

        for(int n = 0; n < 5; n++) {
            Timer generuoti;

            // Failo generavimas
            ofstream generuotas;
            generuotas.open("duomenys/" + to_string(eilSk[n]) + "bendras.txt");
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
    }

    /*

    ĮVESTIS

    */
    Container<Studentas> studentai;
    Studentas stud;
    int option, rikiavimas;
    string inFileName;
    studSk = 1;
    ndSk = 1;
    pasirinktiEiga("įvesties būdas: 1 - Įvesti duomenis ranka, 2 - Generuoti pažymius, 3 - Generuoti pažymius ir vardus, 4 - Nuskaityti iš failo (turi būti bent 1 ND laukas): ", &inputOption, 4);
    
    if (inputOption != 4) {
        while(true) {
            cout << studSk << "-ojo studento duomenys";
            cin >> stud;
            studentai.push_back(move(stud));
            if (studSk == studentai.size()) {
                if(taipArNe("Ar norite įvesti dar vieną studentą? (ENTER - Taip, 'Ne'/'N' - Ne): ")) break;
                studSk++;
            }
        }
        equalOutNdSk(studentai, ndSk);
    } else { // option == 4
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

        // Timer nuskaityi;
        getline(buffer, line);
        ndSk = countNd(line);

        Timer nuskaityti;
        while (getline(buffer, line)) {
            istringstream lineStream(line);
            lineStream >> stud;
            // if (studentai.capacity() == studentai.size()) reallocation++;
            studentai.push_back(move(stud));
        }
        studentai.shrink_to_fit();
        vectorSparta += nuskaityti.elapsed();

        buffer.clear();

        // cout << "Duomenu skaitymas uztruko: "<< skaitymas.elapsed() << "s" << endl;
    }

    studentai.shrink_to_fit();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    /*

    IŠVESTIS

    */

    pasirinktiEiga("Išvestyje studentus rikiuoti pagal: 1 - Vardą, 2 - Pavardę, 3 - Vidurkį, 4 - Medianą: ", &rikiavimas, 4);

    pasirinktiEiga("1 - Spauzdinti į konsolę 2 - Įrašyti į failą?: ", &option, 2);

    while (true) {
        auto delimiterIndex = inFileName.find("/");
        if(delimiterIndex == std::string::npos) break;
        inFileName = inFileName.substr(delimiterIndex + 1);
    }


    if (option == 1) {
        cout << "Kiek studentų atspauzdinti? (ENTER - visus): ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string answer = "";
        int print_sk;
        getline(cin, answer);
        if (answer == "") {
            print_sk = studSk;
        } else {
            while (true) {
                try {
                    print_sk = stoi(answer);
                    if(print_sk >= 1 && print_sk <= studSk) break;
                    throw invalid_argument(to_string(print_sk));
                } catch (exception &e) {
                    cerr << "Netinkama įvestis. Įveskite skaičių nuo 1 iki " << studSk << ": ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, answer);
                }
            }
        }

        rikiuotiPagalParametra(studentai, rikiavimas);

        cout << endl;
        cout << "Vardas                  Pavardė                 Vid.      Med." << endl;
        cout << "--------------------------------------------------------------" << endl;

        for (auto &stud : studentai) cout << stud << endl;

    } else {
        pasirinktiEiga("1 - Sukurti atskirus konteineriu kietekam ir vargšiems, 2 - Viską išvesti viename faile: ", &option, 2);
        Timer isvesti;
        if (option == 1) {
            Container<Studentas> vargsiukai;
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
            rikiuotiPagalParametra(studentai, rikiavimas);
            ofstream konteineris;
            if(inFileName != "") konteineris.open("output/" + inFileName + "-Apdorota.txt");
            else konteineris.open("output/rankiniaiDuomenys-Apdorota.txt");

            konteineris << "Vardas                  Pavardė                 Vid.      Med." << endl;
            konteineris << "--------------------------------------------------------------" << endl;
            
            for (auto &stud : studentai) konteineris << stud << endl;
            konteineris.close();
        }
        vectorSparta += isvesti.elapsed();
    }
    // cout << "Konteineris buvo padidintas: " << reallocation << " kartų" << endl;
    atspauzdintiMasyvoInfo(studentai);
    cout << "Visos operacijos su vektoriais užtruko: " << vectorSparta << "s" << endl;
    cout << "Programa baigta. Pauspauskite betkokį mygtuką kad išeiti...";
    cin.get();
}