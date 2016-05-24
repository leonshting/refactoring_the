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
    int default_order, num_of_layers, upper_order, num_of_validations;
    double X0, Y0, X1, Y1;
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
};


#endif //STRESS_REC_REFACTORED_SETTINGS_H
