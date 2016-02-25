//
// Created by leonsht on 2/25/16.
//

#include "data_points.h"

data_point::data_point(double i_x, double i_y, double i_azimuth):Azimuth(i_azimuth),X(i_x), Y(i_y)
{
};

cd data_point::get_complex()
{
    return complex<double>(X, Y);
};
