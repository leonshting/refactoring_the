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
static d3_zone * before;
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

MODULE_API int get_stress_tensor(double x, double y, double z, double planar_angle, Stensor *ret) {
    Stensor diag;
    get_tensor_main(x,y,z,&diag);
    planar_angle -= get_orientation(x,y,z);
    //rotating tensors :)
    ret->xx = diag.xx * pow(sin(planar_angle),2) + diag.yy * pow(cos(planar_angle),2);
    ret->yy = diag.xx * pow(cos(planar_angle),2) + diag.yy * pow(sin(planar_angle),2);
    ret->zz = letssaveit->p->get_pressure(x,y,z);
    ret->xz = 0.0;
    ret->yz = 0.0;
    ret->xy = abs((diag.xx-diag.yy) * sin(2*planar_angle)/2);
    return 1;
}

MODULE_API int get_tensor_xyz(double x, double y, double z, Stensor * ret)
{
    ret->xx = letssaveit -> get_planar(x,y,z,0.0);
    ret->xy = letssaveit -> get_shear(x,y,z,0.0);
    ret->yy = letssaveit -> get_planar(x,y,z,M_PI/2.0);
    ret->zz = letssaveit -> p->get_pressure(x,y,z);
    return 1;
}

MODULE_API int get_tensor_main(double x, double y, double z, Stensor * ret)
{
    ret->xx = letssaveit -> get_planar(x,y,z,letssaveit->get_orientation(x,y,z));
    ret->yy = letssaveit -> get_planar(x,y,z,letssaveit->get_orientation(x,y,z) + M_PI/2.0);
    ret->zz = letssaveit -> p->get_pressure(x,y,z);
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
    before = new d3_zone(*letssaveit);
    letssaveit->update_stresses(dps);
    letssaveit->rerun_stress();
}

MODULE_API double get_orientation(double x, double y, double z)
{
    return letssaveit->get_orientation(x,y,z);
}

MODULE_API void stress_after(double *point, double *direction0, double *direction1, double *direction2, double *sigma) {
    Stensor diag;
    get_tensor_xyz(point[0], point[1], point[2], &diag);
    sigma[0] = (direction0[0]*diag.xx + direction0[1]*diag.xy + direction0[2]*diag.xz) * direction0[0] +
               (direction0[0]*diag.xy + direction0[1]*diag.yy + direction0[2]*diag.yz) * direction0[1] +
               (direction0[0]*diag.xz + direction0[1]*diag.yz + direction0[2]*diag.zz) * direction0[2];
    sigma[1] = (direction1[0]*diag.xx + direction1[1]*diag.xy + direction1[2]*diag.xz) * direction1[0] +
               (direction1[0]*diag.xy + direction1[1]*diag.yy + direction1[2]*diag.yz) * direction1[1] +
               (direction1[0]*diag.xz + direction1[1]*diag.yz + direction1[2]*diag.zz) * direction1[2];
    sigma[2] = (direction2[0]*diag.xx + direction2[1]*diag.xy + direction2[2]*diag.xz) * direction2[0] +
               (direction2[0]*diag.xy + direction2[1]*diag.yy + direction2[2]*diag.yz) * direction2[1] +
               (direction2[0]*diag.xz + direction2[1]*diag.yz + direction2[2]*diag.zz) * direction2[2];
}

MODULE_API void stress_before(double *point, double *direction0, double *direction1, double *direction2, double *sigma) {
    Stensor diag;
    get_tensor_xyz0(point[0], point[1], point[2], &diag);
    sigma[0] = (direction0[0]*diag.xx + direction0[1]*diag.xy + direction0[2]*diag.xz) * direction0[0] +
               (direction0[0]*diag.xy + direction0[1]*diag.yy + direction0[2]*diag.yz) * direction0[1] +
               (direction0[0]*diag.xz + direction0[1]*diag.yz + direction0[2]*diag.zz) * direction0[2];
    sigma[1] = (direction1[0]*diag.xx + direction1[1]*diag.xy + direction1[2]*diag.xz) * direction1[0] +
               (direction1[0]*diag.xy + direction1[1]*diag.yy + direction1[2]*diag.yz) * direction1[1] +
               (direction1[0]*diag.xz + direction1[1]*diag.yz + direction1[2]*diag.zz) * direction1[2];
    sigma[2] = (direction2[0]*diag.xx + direction2[1]*diag.xy + direction2[2]*diag.xz) * direction2[0] +
               (direction2[0]*diag.xy + direction2[1]*diag.yy + direction2[2]*diag.yz) * direction2[1] +
               (direction2[0]*diag.xz + direction2[1]*diag.yz + direction2[2]*diag.zz) * direction2[2];
}

MODULE_API int get_tensor_xyz0(double x, double y, double z, Stensor *ret) {
    ret->xx = before -> get_planar(x,y,z,0.0);
    ret->xy = before -> get_shear(x,y,z,0.0);
    ret->yy = before -> get_planar(x,y,z,M_PI/2.0);
    ret->zz = before -> p->get_pressure(x,y,z);
    return 1;
}







