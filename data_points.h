//
// Created by leonsht on 2/25/16.
//

#ifndef STRESS_REC_REFACTORED_DATA_POINTS_H
#define STRESS_REC_REFACTORED_DATA_POINTS_H

#include <complex>
#include <string>
#include <vector>
#include <fstream>
#include <random>

#include "useful.h"

using namespace std;



class data_point
{
public:
    data_point() : X(0.0), Y(0.0) { }
    data_point(ifstream &data_stream);
    data_point(double x, double y);
    double X, Y;
    cd complex_coordinates;
};

class data_point_with_azimuth_3d : public data_point
{
public:
    double Z, Azimuth, Azimuth_error;
    data_point_with_azimuth_3d(double x, double y, double z, double azimuth, double azimuth_error);
    data_point_with_azimuth_3d(ifstream &data_stream);
};

class data_point_with_stress_3d : public data_point_with_azimuth_3d
{
public:
    double Stress;
    data_point_with_stress_3d(double x, double y, double z, double azimuth, double azimuth_error, double stress);
    data_point_with_stress_3d(ifstream &data_stream);
};

class data_point_with_azimuth : public data_point
{
public:
    double Azimuth, Azimuth_error;
    data_point_with_azimuth(double x, double y, double azimuth, double azimuth_error);
    data_point_with_azimuth(ifstream &data_stream);
};

class data_point_with_stress : public data_point_with_azimuth
{
public:
    double Stress;
    data_point_with_stress(ifstream &data_stream);
    data_point_with_stress(double x, double y, double azimuth, double azimuth_error, double stress);
};

class collocation_point: public data_point
{
public:
    pair<string, string> areas;
    int equation_num;
    collocation_point(ifstream &data_stream, int en = 0);
};

template <typename T> class data_points {
public:
    int number_of_points;
    string tag;
    data_points(string &filename, int en = 0);
    data_points(vector<T> &D, string t = "");
    data_points<T> get_randomized_part(double per);
    int equation_num;
    vector<T> data;
};


template <typename T>
data_points<T>::data_points(string &filename, int en){
    int N = 0;
    equation_num = en;
    ifstream stream_data(filename);
    stream_data >> tag;
    while(!stream_data.eof())
    {
        T tmp(stream_data);
        data.push_back(tmp);
        N++;
    }
    number_of_points = N;

};

template <typename T>
data_points<T>::data_points(vector<T> &D, string t): data(D)
{
    number_of_points = int(D.size());
    equation_num = 0;
    tag = t;
};

template <typename T>
data_points<T> data_points<T>::get_randomized_part(double per)
{
    vector<T>::iterator i;
    vector<T> to_ret;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    for(i = data.begin(); i != data.end(); ++i)
    {
        double chance = dis(gen);
        if(chance >= per)
        {
            to_ret.push_back((*i));
        }
    }
    return data_points<T>(to_ret, to_string(dis(gen)));

}

#endif //STRESS_REC_REFACTORED_DATA_POINTS_H
