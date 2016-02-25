//
// Created by leonsht on 2/25/16.
//

#ifndef STRESS_REC_REFACTORED_INIT_DATA_H
#define STRESS_REC_REFACTORED_INIT_DATA_H


#include <string>
#include <complex>
#include <vector>

#include "data_points.h"

using namespace std;

typedef complex<double> cd;



class init_data {
public:
    init_data(string i_data, string i_borders);
    vector<data_point> a_data;

private:
    string files_w_data, files_w_borders;
    vector <string> f_data, f_borders;
};


#endif //STRESS_REC_REFACTORED_INIT_DATA_H
