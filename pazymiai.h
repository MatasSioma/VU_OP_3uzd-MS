#ifndef Container
#define Container std::vector
#endif

#ifndef PAZYMIAI_H
#define PAZYMIAI_H

#include <string>
#include <vector>
// #include <list>
// #include <deque>
#include "timer.h"

extern int ndSk, studSk, inputOption;

using namespace std;

class Zmogus {
    protected:
        string vardas, pavarde;
    public:  
        Zmogus() : vardas("BeVardis"), pavarde("BePavardis") {}
        Zmogus(const string &vard, const string &pavard) : vardas(vard), pavarde(pavard) {}
        virtual ~Zmogus() {vardas.clear(); pavarde.clear();}
        
        inline string getVardas() const { return vardas; }
        inline string getPavarde() const { return pavarde; } 
        void setVardas(string vard) { this->vardas = vard; }
        void setPavarde(string pav) { this->pavarde = pav; }
        virtual void whoAmI() = 0;
};

class Studentas : public Zmogus {
    private:
        int egz;
        double vidurkis;
        double mediana;
        vector<int> nd;
    public:
        Studentas();
        Studentas(const string &vardas, const string &pavarde);
        Studentas(const string &vardas, const string &pavarde, int egz, double vidurkis, double mediana, vector<int> nd) : Zmogus(vardas, pavarde),
            egz(egz), vidurkis(vidurkis), mediana(mediana), nd(nd) {}
        Studentas(const Studentas &tmpStud);
        Studentas(Studentas &&tmpStud) noexcept;

        void ndAppend(int balas) {nd.push_back(balas);} //prideda viena namu darba.
        void ndResize(int size) {nd.resize(size);}
        inline int ndSk() {return nd.size();}
        inline int getNd(int index) {return nd.at(index);}
        void setNd(int index, int value);

        void lastNdtoEgz();

        inline void setEgz(int value) {egz = value;}
        inline double getEgz() const {return egz;}


        inline double getVidurkis() const {return vidurkis;}
        inline double getMediana() const {return mediana;}
        void skaiciuotiVid();
        void skaiciuotiMed();

        ~Studentas() {
            nd.clear();
        }

        inline void clearEverything() { this->vardas.clear(); this->pavarde.clear(); this->nd.clear(); this->egz = 0; this->mediana = 0.0; this->vidurkis = 0.0; }

        Studentas& operator=(const Studentas &tmpStud);
        Studentas& operator=(Studentas &&tmpStud);
        friend istringstream& operator>>(istringstream& filename, Studentas &tmpStud);
        friend istream& operator>>(istream& manual, Studentas &tmpStud);
        friend ostream& operator<<(ostream& console, const Studentas &tmpStud);
        friend ofstream& operator<<(ofstream& filename, const Studentas &tmpStud);

        virtual void whoAmI() {cout << "Studentas klasė" << endl;}
};

void pasirinktiEiga(string msg, int* option, int max);
bool taipArNe(string uzklausa);
int countNd(string &line);

void rikiuotiPagalParametra(Container<Studentas> &studentai, int option);
void equalOutNdSk(Container<Studentas> &studentai, int ndSk);
void sortAndAddToFile(Container<Studentas> &kietekai, Container<Studentas> &vargsiukai, int option);
void atspauzdintiMasyvoInfo(Container<Studentas> &studentai);

#endif