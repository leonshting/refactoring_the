//
// Created by Леонид Штанько on 18.05.16.
//

#ifndef STRESS_REC_REFACTORED_PRESSURES_H
#define STRESS_REC_REFACTORED_PRESSURES_H

#include <string>
#include <vector>

#include "settings.h"
#include <tuple>

using namespace std;
class density_layer {
public:
    density_layer(double z0, double z1, double density);
    double Z0, Z1, Density;
    bool is_inside(double z);
};

class pressures {
public:
    pressures(string & upper_weights, string & densities, settings & sets);
    vector< vector <double > > upperW;
    vector< density_layer > Densities;
    double get_density(double x, double y, double z);
    settings Sets;
    int steps_num;
    int meshgridX, meshgridY;
    double get_pressure(double x, double y, double z);
    tuple<double, double> get_Zsizes();
};



#endif //STRESS_REC_REFACTORED_PRESSURES_H
