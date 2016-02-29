//
// Created by leonsht on 2/25/16.
//

#ifndef STRESS_REC_REFACTORED_DATA_POINTS_H
#define STRESS_REC_REFACTORED_DATA_POINTS_H

#include <complex>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

typedef complex<double> cd;

class data_point
{
public:
    data_point() : X(0.0), Y(0.0) { }
    data_point(ifstream &data_stream);
    data_point(double x, double y);
    double X, Y;
    cd complex_coordinates;
};

class data_point_with_azimuth : public data_point
{
public:
    double Azimuth, Azimuth_error;
    data_point_with_azimuth(double x, double y, double azimuth, double azimuth_error);
    data_point_with_azimuth(ifstream &data_stream);
};

template <typename T> class data_points {
public:
    int number_of_points;
    string tag;
    data_points(string &filename);


private:
    vector<T> data;
};

template <typename T>
data_points<T>::data_points(string &filename){
    int N = 0;
    ifstream stream_data(filename);
    tag = filename;
    while(!stream_data.eof())
    {
        T tmp(stream_data);
        data.push_back(tmp);
        N++;
    }
    number_of_points = N;

};


#endif //STRESS_REC_REFACTORED_DATA_POINTS_H
