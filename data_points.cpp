//
// Created by leonsht on 2/25/16.
//

#include "data_points.h"

#include <fstream>


/*parent class*/
data_point::data_point(double x, double y): X(x), Y(y)
{
    complex_coordinates = cd(X, Y);
}

data_point::data_point(fstream &data_stream) {
    data_stream >> X >> Y;
    complex_coordinates = cd(X, Y);
}


/*ancestor class*/
data_point_with_azimuth::data_point_with_azimuth(fstream &data_stream) {
    data_stream >> X >> Y >> Azimuth >> Azimuth_error;
    complex_coordinates = cd(X, Y);
}

data_point_with_azimuth::data_point_with_azimuth(double x, double y, double azimuth, double azimuth_error):
        X(x), Y(y), Azimuth(azimuth), Azimuth_error(azimuth_error)
{
    complex_coordinates = cd(X, Y);
}


/*container class*/
template <typename T>
data_points::data_points(string filename)
{
    int N = 0;
    ifstream stream_data(filename);
    while(!stream_data.eof())
    {
        T tmp(stream_data);
        data.push_back(tmp);
        N++;
    }
    number_of_points = N;

};


