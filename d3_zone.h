//
// Created by Леонид Штанько on 17.05.16.
//

#ifndef STRESS_REC_REFACTORED_D3_ZONE_H
#define STRESS_REC_REFACTORED_D3_ZONE_H

#include <fstream>
#include <string>
#include <vector>

#include "useful.h"
#include "data_points.h"
#include "init_data.h"
#include "layer.h"
#include "settings.h"
#include "output.h"
#include "pressures.h"

using namespace std;
using namespace aux_stuff;

bool compare_by_Z(data_point_with_azimuth_3d & first, data_point_with_azimuth_3d & second);
bool compare_by_Z_stress(data_point_with_stress_3d & first, data_point_with_stress_3d & second);

class d3_zone {
public:
    d3_zone(string &input, string &stress, settings &S);
    void init_pressures(string &upper_weigths, string &densities);
    data_points<data_point_with_azimuth_3d> Data;
    data_points<data_point_with_stress_3d> Stress;
    vector<rect_layer> layers;
    double X0, Y0, Z0;
    double X1, Y1, Z1;
    double dX, dY, dZ;
    string Input;
    settings Sets;
    int num_of_layers;
    pressures *p;
    void layer_exec();
    void rerun_stress();
    void update_stresses(data_points<data_point_with_stress_3d> &some);
    double get_planar(double x, double y, double z, double Azimuth);
    int get_num_of_layers();
    double get_next_upper();
    double get_next_lower();
    void incr_layer();
    void cut_to_layers();
private:
    void get_max_min();
    int get_layer_num(double x, double y, double z);

protected:
    int layer_counter;
};


#endif //STRESS_REC_REFACTORED_D3_ZONE_H
