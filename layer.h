//
// Created by Леонид Штанько on 25.04.16.
//

#ifndef STRESS_REC_REFACTORED_LAYER_H
#define STRESS_REC_REFACTORED_LAYER_H

#include "border.h"
#include "data_points.h"
#include "settings.h"
#include "output.h"

#include <string>


using namespace std;

class rect_layer{
public:
    rect_layer(data_points<data_point_with_azimuth> &D,
                data_points<data_point_with_stress> &St, settings &S, double z0, double z1);
    double X0, X1;
    double Y0, Y1;
    double Z0, Z1;
    int num_of_points;
    data_points<data_point_with_azimuth> Data;
    data_points<data_point_with_stress> Stress;
    settings Sets;
    output * out;
    void init_solver();
    void init_full_solver();
    void get_best();
private:

};
/*
class layer {
public:
    layer(string borders);
    double get_density(double x, double y);
    double get_upper_pressure(double x, double y);

private:
    vector<border> Bs;
    vector<double> densities;
    double z0;
    double thickness;
    vector<double> upper_pressures;
};
*/

#endif //STRESS_REC_REFACTORED_LAYER_H
