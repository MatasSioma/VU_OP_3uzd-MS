#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <random>

#include "pazymiai.h"

double generuotiFailus() {
    srand(time(nullptr));
    cout << rand() << endl;
    return 1.0;
}