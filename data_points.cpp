//
// Created by leonsht on 2/25/16.
//

#include "data_points.h"




/*parent class*/
data_point::data_point(double x, double y): X(x), Y(y)
{
    complex_coordinates = cd(X, Y);
}

data_point::data_point(ifstream &data_stream) {
    data_stream >> X >> Y;
    complex_coordinates = cd(X, Y);
}


/*ancestor class*/
data_point_with_azimuth::data_point_with_azimuth(ifstream &data_stream): data_point(data_stream) {
    data_stream >> Azimuth >> Azimuth_error;
}

data_point_with_azimuth::data_point_with_azimuth(double x, double y, double azimuth, double azimuth_error):
        data_point(x,y), Azimuth(azimuth), Azimuth_error(azimuth_error) { }


collocation_point::collocation_point(ifstream &data_stream, int en): data_point(data_stream) {
    data_stream >> areas.first >> areas.second;
    equation_num = en;
}

data_point_with_stress::data_point_with_stress(double x, double y, double azimuth, double azimuth_error,
                                               double stress): data_point_with_azimuth(x,y, azimuth, azimuth_error),
                                                               Stress(stress) { }

data_point_with_stress::data_point_with_stress(ifstream &data_stream):data_point_with_azimuth(data_stream) {
    data_stream >> Stress;
}
