//
// Created by leonsht on 02.03.16.
//
#include <map>
#include <string>
#include <fstream>

using namespace std;

#ifndef STRESS_REC_REFACTORED_SETTINGS_H
#define STRESS_REC_REFACTORED_SETTINGS_H


class settings {
public:
    int default_order;
    settings(string &);
    settings();
    map<string, int> ORDERS;
    int get_order(string &key);
};


#endif //STRESS_REC_REFACTORED_SETTINGS_H
