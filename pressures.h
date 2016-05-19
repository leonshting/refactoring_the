//
// Created by Леонид Штанько on 18.05.16.
//

#ifndef STRESS_REC_REFACTORED_PRESSURES_H
#define STRESS_REC_REFACTORED_PRESSURES_H

#include <string>
#include <vector>

#include "settings.h"

using namespace std;

class pressures {
public:
    pressures(string & upper_weights, string & densities, settings & sets);
    vector< vector <double > > upperW;
    double get_density(double x, double y, double z);
    settings Sets;
    int steps_num;
    int meshgridX, meshgridY;
    double get_pressure(double x, double y, double z);
};


#endif //STRESS_REC_REFACTORED_PRESSURES_H
