#include "pazymiai.h"

double Studentas::getVidurkis() {
    int ndSk = this->ndSk();
    double agreguotas = 0;
    for (int nd = 0; nd < ndSk; nd++) agreguotas += nd.at(nd);
    agreguotas /= (double)nd.size();
    agreguotas = round(agreguotas * 100.0) / 100.0; // iki simtuju
    agreguotas = agreguotas * 0.4 + egz * 0.6;
    return round(agreguotas * 100.0) / 100.0;
}

double Studentas::getMediana() {
    int ndSk = this->ndSk();
    double vidurys;
    vector<int> ndCopy(ndSk);
    ndCopy = nd;

    sort(ndCopy.begin(), ndCopy.end());
    vidurys = ndSk % 2 == 0 ? (ndCopy[ndSk / 2 - 1] + ndCopy[ndSk / 2]) / 2.0 : ndCopy[ndSk / 2];
    vidurys = round(vidurys * 100.0) / 100.0;
    vidurys = vidurys * 0.4 + stud.egz * 0.6;
    return vidurys;
}

void rikiuotiPagalParametra(vector<studentas> &studentai, int option) {
    switch (option) {
    case 1:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.vardas > b.vardas;});
        break;
    case 2:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.pavarde > b.pavarde;});
        break;
    case 3:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.vidurkis > b.vidurkis;});
        break;
    case 4:
        studentai.sort([](studentas &a, studentas&b)->bool{return a.mediana > b.mediana;});
        break;
    case 5:
        break;
    default:
        break;
    }
}

void addLineToFile(ofstream &konteineris, Studentas stud) {
    konteineris << endl << left << setw(24) << stud.vardas << left << setw(24) << stud.pavarde;
    konteineris << left << setw(10) << stud.vidurkis << left << setw(10) << stud.mediana;
}