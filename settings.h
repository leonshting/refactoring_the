//
// Created by leonsht on 02.03.16.
//
#include <map>
#include <string>
#include <fstream>

#include "useful.h"

using namespace std;

#ifndef STRESS_REC_REFACTORED_SETTINGS_H
#define STRESS_REC_REFACTORED_SETTINGS_H


class settings {
public:
    int default_order, num_of_layers, upper_order, num_of_validations, n_pressure_steps;
    double X0, Y0, X1, Y1, Z0, Z1;
    double default_zero_X, default_zero_Y;
    bool sizes_set; bool Z_set; bool define_z_by_densities;
    bool static_division;
    settings(string &);
    settings();
    map<string, int> ORDERS;
    map<string, int> STARTS;
    map<string, cd> POLES;
    map<string, cd> ZEROES;
    map<string, bool> POLES_X;
    int get_order(string &key);
    int get_start(string &key);
    cd get_zero(string &key);
    cd get_pole(string &key);
    bool get_pole_x(string &key);
    void reset_default_order(int ORDER);
    void set_sizes(double x0, double x1, double y0, double y1);
    void set_Z(double z0, double z1);
};


#endif //STRESS_REC_REFACTORED_SETTINGS_H
