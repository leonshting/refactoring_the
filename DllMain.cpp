//
// Created by Леонид Штанько on 03.06.16.
//

#include "DllMain.h"
#include "settings.h"
#include "d3_zone.h"
#include "data_points.h"

#include <vector>
#include <string>
using namespace std;

MODULE_API static d3_zone * letssaveit;
MODULE_API static string letsaveittoo;


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
    letssaveit->init_pressures(upper_pressures, densities);
    letssaveit->cut_to_layers();
}

MODULE_API void exec_initial()
{
    letssaveit->layer_exec();
}

MODULE_API double get_stress(double x, double y, double z, double azimuth) {
    return letssaveit->get_planar(x,y,z,azimuth);
}

MODULE_API int get_crack_stress(double x, double y, double z, Stensor *ret) {
    ret->xx = 1.0;
    ret->yy = 0.0;
    ret->zz = 1.1;
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



