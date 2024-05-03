#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "pazymiai.h"

using namespace std;
//default
Studentas::Studentas() : Zmogus(),
    egz(0),
    nd({0}),
    vidurkis(0.0),
    mediana(0.0) {}

Studentas::Studentas(const string &vardas, const string &pavarde) : Zmogus(vardas, pavarde) {
    egz = 0;
    nd = {0};
    vidurkis = 0.0;
    mediana = 0.0;
}

Studentas::Studentas(const Studentas &tmpStud) : Zmogus(tmpStud.vardas, tmpStud.pavarde) {
    nd = tmpStud.nd;
    egz = tmpStud.egz;
    mediana = tmpStud.mediana;
    vidurkis = tmpStud.vidurkis;
    // cout << "Kopijavimo konstruktorius suveike" << endl;
}

Studentas::Studentas(Studentas &&tmpStud) noexcept : Zmogus(move(tmpStud.vardas), move(tmpStud.pavarde)) {
    nd = move(tmpStud.nd);
    egz = move(tmpStud.egz);
    mediana = move(tmpStud.mediana);
    vidurkis = move(tmpStud.vidurkis);

    tmpStud.clearEverything();
    // cout << "Perkelimo konstruktorius suveike" << endl;
}

Studentas& Studentas::operator=(const Studentas &tmpStud) {
    if(this != &tmpStud){
        vardas = tmpStud.vardas;
        pavarde = tmpStud.pavarde;
        nd = tmpStud.nd;
        egz = tmpStud.egz;
        mediana = tmpStud.mediana;
        vidurkis = tmpStud.vidurkis;
    }
    // cout << "Priskyrimo operatorius suveike" << endl;
    return *this;
}

Studentas& Studentas::operator=(Studentas &&tmpStud){
    if(this != &tmpStud) {
        vardas = move(tmpStud.vardas);
        pavarde = move(tmpStud.pavarde);
        nd = move(tmpStud.nd);
        egz = move(tmpStud.egz);
        mediana = move(tmpStud.mediana);
        vidurkis = move(tmpStud.vidurkis);
        tmpStud.clearEverything();
    }
    // cout << "Perkelimo operatorius suveike" << endl;
    return *this;
}

istream& operator>>(istream& manual, Studentas &tmpStud) {
    string line = "";
    tmpStud.ndResize(ndSk);
    if (inputOption == 2 || inputOption == 3) {
        cout << endl;
        int i = 0;
        while(true) {
            tmpStud.setNd(i, 1 + rand() % 11);
            cout << "Sugeneruotas " << i+1 << "-as namų darbas" << endl;
            i++;
            if (i == ndSk) {
                if(taipArNe("\nPridėti dar vieną namų darbą? (ENTER - Taip, 'Ne'/'N' - Ne): ")) break;
                ndSk += 1;
                tmpStud.ndAppend(0);
            }
        }
        tmpStud.setEgz(rand() % 11);

    }
    if(inputOption == 1 || inputOption == 2) {
        string line;

        cout << endl;
        cout << "Vardas: ";
        manual >> line;
        tmpStud.setVardas(line);

        cout << "Pavarde: ";
        manual >> line;
        tmpStud.setPavarde(line);
    }

    if (inputOption == 1) {
        int i = 0;
        while (true) {
            int grade;
            while(true) {
                try {
                    cout << "\n" << i + 1 << " ND įvertinimas (0-10): ";
                    manual >> grade;
                    if(!cin.good() || grade < 1 || grade > 10) {
                        throw invalid_argument("Netinkama įvestis. Įveskite skaičių nuo 1 iki 10");
                    }
                    tmpStud.setNd(i, grade);
                    break;
                } catch(invalid_argument &e) {
                    cerr << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            }
            i++;
            if (i < ndSk) continue;
            else if(!taipArNe("Pridėti dar vieną namų darbą? (ENTER - Taip, 'Ne'/'N' - Ne): ")) {
                ndSk++;
                tmpStud.ndResize(ndSk);
                continue;
            } else {
                while (true) {   
                    try {
                        cout << "Egzamino įvertinimas: ";
                        manual >> grade;
                        if(!manual.good() || grade < 1 || grade > 10) {
                            throw invalid_argument("Netinkama įvestis. Įveskite skaičių nuo 1 iki 10");
                        }
                        tmpStud.setEgz(grade);
                        break;
                    } catch(invalid_argument &e) {
                        cerr << e.what() << endl;
                        manual.clear();
                        manual.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                }
                break;
            }
        }
    }

    if (inputOption == 3) {
        tmpStud.setVardas("Vardenis_" + to_string(studSk));
        tmpStud.setPavarde("Pavardenis_" + to_string(studSk));

        cout << "Vardas bei pavardė sugeneruoti" << endl;
    }

    tmpStud.skaiciuotiVid();
    tmpStud.skaiciuotiMed();

    return manual;
}

istringstream& operator>>(istringstream& filename, Studentas &tmpStud){ 
    string vardas, pavarde;
    int ndSk;

    if (!(filename >> vardas >> pavarde)) {
        cerr << "Nepavyko nuskaityti vardo ir pavardes" << endl;
    }

    tmpStud.setVardas(vardas);
    tmpStud.setPavarde(pavarde);

    int pazymys;
    while (filename >> pazymys) {
        tmpStud.ndAppend(pazymys);
    }

    tmpStud.lastNdtoEgz();


    tmpStud.skaiciuotiVid();
    tmpStud.skaiciuotiMed();
    //cout << "As esu ivedimo is failo operatoriuje >>" << endl;
    return filename;
}

ostream& operator<<(ostream& console, const Studentas &tmpStud){
    console << left << setw(24) << tmpStud.getVardas() << setw(24) << tmpStud.getPavarde() <<
    setw(10) << fixed << setprecision(2) << tmpStud.getVidurkis() << fixed << setw(10) << tmpStud.getMediana();
    //cout << "As esu isvedimo i konsole operatoriuje <<" << endl;
    return console;

}

ofstream& operator<<(ofstream& filename, const Studentas &tmpStud){
    // stringstream RF;
    filename << left << setw(24) << tmpStud.getVardas() << setw(24) << tmpStud.getPavarde() <<
    setw(10) << fixed << setprecision(2) << tmpStud.getVidurkis() << fixed << setw(10) << tmpStud.getMediana();

    //cout << "As esu isvedimo i faila operatoriuje <<" << endl;
    // filename << RF.str();
    // RF.clear();
    return filename;
}

void Studentas::setNd(int index, int value) {
    if(index > abs((int)this->nd.size())) throw out_of_range("Bondote nustatyti nd elementą už jo ribų");
    else if(index >= 0) this->nd.at(index) = value;
    else this->nd.at((int)this->nd.size() + index) = value;
}

void Studentas::skaiciuotiVid() {
    double agreguotas = 0;
    for(auto &balas : nd) agreguotas += balas;
    agreguotas /= (double)nd.size();
    agreguotas = agreguotas * 0.4 + egz * 0.6;
    agreguotas = round(agreguotas * 100.0) / 100.0; // iki simtuju
    vidurkis = agreguotas;
}

void Studentas::skaiciuotiMed() {
    int ndSk = nd.size();
    double vidurys;
    vector<int> ndCopy(ndSk);
    ndCopy = nd;
    sort(ndCopy.begin(), ndCopy.end());
    vidurys = ndSk % 2 == 0 ? (ndCopy[ndSk / 2 - 1] + ndCopy[ndSk / 2]) / 2.0 : ndCopy[ndSk / 2];
    vidurys = round(vidurys * 100.0) / 100.0;
    vidurys = vidurys * 0.4 + egz * 0.6;
    mediana = vidurys;
}

void rikiuotiPagalParametra(vector<Studentas> &studentai, int option) {
    switch (option) {
    case 1:
        sort(studentai.begin(), studentai.end(), [](Studentas &a, Studentas&b)->bool{return a.getVardas() > b.getVardas();});
        break;
    case 2:
        sort(studentai.begin(), studentai.end(), [](Studentas &a, Studentas&b)->bool{return a.getPavarde() > b.getPavarde();});
        break;
    case 3:
        sort(studentai.begin(), studentai.end(), [](Studentas &a, Studentas&b)->bool{return a.getVidurkis() > b.getVidurkis();});
        break;
    case 4:
        sort(studentai.begin(), studentai.end(), [](Studentas &a, Studentas&b)->bool{return a.getMediana() > b.getMediana();});
        break;
    case 5:
        break;
    default:
        break;
    }
}

void Studentas::lastNdtoEgz() {
    int lastIndex = (int)this->nd.size() - 1;
    egz = nd.at(lastIndex);
    nd.resize(lastIndex);
}

void sortAndAddToFile(vector<Studentas> &kietekai, vector<Studentas> &vargsiukai, int option) {
    rikiuotiPagalParametra(kietekai, option);
    rikiuotiPagalParametra(vargsiukai, option);

    ofstream konteineriai[2];
    int eilSk = kietekai.size() + vargsiukai.size();
    konteineriai[0].open("sugeneruoti/" + to_string(eilSk) + "geri.txt");
    konteineriai[1].open("sugeneruoti/"+ to_string(eilSk) + "blogi.txt");

    for(int i = 0; i < 2; i++) {
        konteineriai[i] << left << setw(24) << "Vardas" << left << setw(24) << "Pavardė";
        konteineriai[i] << left << setw(10) << "Vid." << left << setw(10) << "Med.";
    }

    for (auto &stud : kietekai) konteineriai[0] << stud;
    konteineriai[0].close();
    for (auto &stud : vargsiukai) konteineriai[1] << stud;
    konteineriai[1].close();
}