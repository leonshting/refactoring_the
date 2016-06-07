//
// Created by Леонид Штанько on 03.06.16.
//

#include "DllMain.h"
#include "settings.h"
#include "d3_zone.h"
#include "data_points.h"

#include <vector>
#include <string>

#ifdef WIN32
#define _USE_MATH_DEFINES
#include <math.h>
#else
#define _USE_MATH_DEFINES
#include <cmath>
#endif

using namespace std;

static d3_zone * letssaveit;
static string letsaveittoo;


MODULE_API void load_initial(char *orientations, char *stresses) {
    string azimuth_data(orientations);
    letsaveittoo = string(azimuth_data);
    string stress_data(stresses);
    settings Settings;
    d3_zone d3Zone(azimuth_data, stress_data, Settings);
    letssaveit = new d3_zone(d3Zone);
}

MODULE_API void load_pressures(char * upper_pressures, char * densities)
{
    string UW(upper_pressures);
    string Dens(densities);
    letssaveit->init_pressures(UW, Dens);
    letssaveit->cut_to_layers();
}

MODULE_API void exec_initial()
{
    letssaveit->layer_exec();
}

MODULE_API double get_stress(double x, double y, double z, double azimuth) {
    return letssaveit->get_planar(x,y,z,azimuth);
}

MODULE_API int get_crack_stress(double x, double y, double z, double planar_angle, Stensor *ret) {
    Stensor diag;
    double xx_az = letssaveit->get_orientation(x,y,z);
    diag.xx = letssaveit -> get_planar(x,y,z,xx_az);
    diag.yy = letssaveit -> get_planar(x,y,z,xx_az + M_PI/2.0);
    diag.zz = letssaveit -> p->get_pressure(x,y,z);
    //rotating tensors :)
    ret->xx = diag.xx * pow(sin(planar_angle),2) + diag.yy * pow(cos(planar_angle),2);
    ret->yy = diag.xx * pow(cos(planar_angle),2) + diag.yy * pow(sin(planar_angle),2);
    ret->zz = letssaveit->p->get_pressure(x,y,z);
    ret->xz = 0.0;
    ret->yz = 0.0;
    ret->xy = abs((diag.xx-diag.yy) * sin(2*planar_angle)/2);
    return 1;
}



MODULE_API void init_crack(double *x, double *y, double *z, double *azimuths, double *pressures, int num) {
    vector<data_point_with_stress_3d> tmp;
    for(int i = 0; i < num; i++)
    {
        data_point_with_stress_3d dp(x[i], y[i], z[i], azimuths[i], 0.0, pressures[i]);
        tmp.push_back(dp);
    }
    data_points<data_point_with_stress_3d> dps(tmp);
    letssaveit->update_stresses(dps);
    letssaveit->rerun_stress();
}



