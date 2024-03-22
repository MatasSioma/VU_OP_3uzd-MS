# VU_OP_1uzd-MS

## v.pradinė
### v.pradine.cpp
Studentų ir nd kiekis "hard-coded"\
Naudojami c masyvai\
Pasirenkama tarp 3 būdų įvesti duomenis:
- Įvesti duomenis ranka
- Generuoti pažymius
- Generuoti pažymius ir vardus

## v0.1
Studentų ir nd kiekis dinamiškas\
Masyvų duomenų spauzdinimas\
Pasirinkimas tarp vidurkio ir medianos skaičiavimo
### cmasyvas.cpp
Naudojami tik c masyvai
### vector.cpp
Naudojami <vector> objektai

## v0.2
Galimybė duomenis įvesti per failą\
Išspauzdinamų studnetų kiekio pasirinkimas\
Rikiavimas pagal skirtingus parametrus

## v0.3
Programa paskirstyta į kelis .cpp failus\
Sukurtas programą "apjungentis", struktūras apibrežentis header failas\
Naudojami try-catch blokai vartotojo įvesčiai (sukurta bendra funkcija tai įgyvendinti)

## v0.4
Duomenų (failų) generavimas\
Sugeneruotų studentų išvedimas į du skirtingus konteinerius (geri/blogi)\
Bendras programos veikimo laikas, kai generuojami 5 failai su nurodytasi dydžiais (15Nd): 118.9s (5 testų vidurkis)

## v1.0
trijų tipų konteineriai\
pritaikytos trys strategijos\
Atlikta spartumo diagnostika

![statistika](statistika.png)

Processor             AMD Ryzen 7 7735U with Radeon Graphics 2.70 GHz\
Installed RAM         16,0 GB (13,7 GB usable)\
System type	64-bit    Ubuntu 22.04.3 LTS on Windows 10 x86_64\
Storage               512GB SSD\

Instrukcija kaip paleisti koda UNIX sistemoje:
1. Atidarę sistemos komandinę eilutę šiame aplanke įveskite `nano pazymiai.h`, modifikuokite failą taip, kad pirmos trys programos eilutės atrodytų kaip vienas iš pateiktų pavyzdžių:\
Vector versijai:
```
#ifndef Container
#define Container std::vector
#endif
```
List versijai:
```
#ifndef Container
#define Container std::list
#endif
```
Deque versijai:
```
#ifndef Container
#define Container std::deque
#endif
```
Uždarykite teksto retdaktorių su "Ctrl" ir "C" mygtukais vienu metu, išsaugokite failą (spauskite "Y")
2. Sistemos komandinėje eilutėje įrašykite `make vector` arba `make list` arba `make deque` atitinkamai versijai kurią pasirinkote prieš tai.
3. Kad paleistumėte programą į komadinę eilutę įveskite: `./pazymiai_vector` arba  `./pazymiai_list` arba `./pazymiai_deque`