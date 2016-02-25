//
// Created by leonsht on 2/25/16.
//

#ifndef STRESS_REC_REFACTORED_DATA_POINTS_H
#define STRESS_REC_REFACTORED_DATA_POINTS_H

#include <complex>
using namespace std;


typedef complex<double> cd;

class data_point {
public:
    double Azimuth, X, Y;
    data_point(double i_x, double i_y, double i_azimuth);
    cd get_complex();
};


#endif //STRESS_REC_REFACTORED_DATA_POINTS_H
