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