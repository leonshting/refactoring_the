//
// Created by leonsht on 2/25/16.
//

#ifndef STRESS_REC_REFACTORED_DATA_POINTS_H
#define STRESS_REC_REFACTORED_DATA_POINTS_H

#include <complex>
#include <string>
#include <vector>

using namespace std;

typedef complex<double> cd;

class data_point
{
public:
    data_point() : X(0.0), Y(0.0) { }
    data_point(fstream &data_stream);
    data_point(double x, double y);
    double X, Y;
    cd complex_coordinates;
};

class data_point_with_azimuth : public data_point
{
public:
    double Azimuth, Azimuth_error;
    data_point_with_azimuth(double x, double y, double azimuth, double azimuth_error);
    data_point_with_azimuth(fstream &data_stream);
};

typedef data_point_with_azimuth dpwa;

template <typename T> class data_points {
public:
    data_points(string filename);
    int number_of_points;

private:
    vector<T> data;
};


#endif //STRESS_REC_REFACTORED_DATA_POINTS_H
