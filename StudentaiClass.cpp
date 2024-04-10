#include "pazymiai.h"

double Studentas::getVidurkis() {
    if (vidurkis != -1) {
        return vidurkis;
    }
    int ndSk = this->ndSk();
    double agreguotas = 0;
    for (int nd = 0; nd < ndSk; nd++) agreguotas += nd.at(nd);
    agreguotas /= (double)nd.size();
    agreguotas = agreguotas * 0.4 + egz * 0.6;
    agreguotas = round(agreguotas * 100.0) / 100.0; // iki simtuju
    vidurkis = agreguotas;
    return vidurkis;
}

double Studentas::getMediana() {
    if (mediana != -1) {
        return mediana;
    }
    int ndSk = this->ndSk();
    double vidurys;
    vector<int> ndCopy(ndSk);
    ndCopy = nd;

    sort(ndCopy.begin(), ndCopy.end());
    vidurys = ndSk % 2 == 0 ? (ndCopy[ndSk / 2 - 1] + ndCopy[ndSk / 2]) / 2.0 : ndCopy[ndSk / 2];
    vidurys = round(vidurys * 100.0) / 100.0;
    vidurys = vidurys * 0.4 + stud.egz * 0.6;
    mediana = vidurys;
    return mediana;
}


void rikiuotiPagalParametra(vector<Studentas> &studentai, int option) {
    switch (option) {
    case 1:
        studentai.sort([](Studentas &a, Studentas&b)->bool{return a.getVardas() > b.getVardas();});
        break;
    case 2:
        studentai.sort([](Studentas &a, Studentas&b)->bool{return a.getPavarde() > b.getPavarde();});
        break;
    case 3:
        studentai.sort([](Studentas &a, Studentas&b)->bool{return a.getVidurkis() > b.getVidurkis();});
        break;
    case 4:
        studentai.sort([](Studentas &a, Studentas&b)->bool{return a.getMediana() > b.getMediana();});
        break;
    case 5:
        break;
    default:
        break;
    }
}

void addLineToFile(ofstream &konteineris, Studentas &stud) {
    konteineris << endl << left << setw(24) << stud.getVardas() << left << setw(24) << stud.getPavarde();
    konteineris << left << setw(10) << stud.getVidurkis() << left << setw(10) << stud.getMediana();
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

    for (auto &stud : kietekai) addLineToFile(konteineriai[0], stud);
    konteineriai[0].close();
    for (auto &stud : vargsiukai) addLineToFile(konteineriai[1], stud);
    konteineriai[1].close();
}