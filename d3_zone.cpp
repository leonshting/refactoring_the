//
// Created by Леонид Штанько on 17.05.16.
//
#include <limits>
#include "d3_zone.h"

d3_zone::d3_zone(string &input, string &stress, settings & S):Sets(S), Data(input), Stress(stress), Input(input) {
    num_of_layers = Sets.num_of_layers;
    get_max_min();
    sort(Data.data.begin(), Data.data.end(), compare_by_Z);
    sort(Stress.data.begin(), Stress.data.end(), compare_by_Z_stress);
    cut_to_layers();

}

void d3_zone::get_max_min() {
    double maxn = std::numeric_limits<double>::max();
    double minn = std::numeric_limits<double>::min();
    vector<double> max(3, minn);
    vector<double> min(3, maxn);
    vector<data_point_with_azimuth_3d>::iterator i;
    for(i = Data.data.begin(); i != Data.data.end(); ++i)
    {
        if((*i).X > max[0])
            max[0] = (*i).X;
        else if((*i).X < min[0])
            min[0] = (*i).X;
        if((*i).Y > max[1])
            max[1] = (*i).Y;
        else if((*i).Y < min[1])
            min[1] = (*i).Y;
        if((*i).Z > max[2])
            max[2] = (*i).Z;
        else if((*i).Z < min[2])
            min[2] = (*i).Z;
    }
    X0 = min[0]; Y0 = min[1]; Z0 = min[2];
    X1 = max[0]; Y1 = max[1]; Z1 = max[2];
    dX = X1-X0; dY = Y1-Y0; dZ = Z1-Z0;
    if(!Sets.sizes_set)
    {
        Sets.set_sizes(X0, X1, Y0, Y1);
    }
    else
    {
        X0 = Sets.X0; X1 = Sets.X1;
        Y0 = Sets.Y0; Y1 = Sets.Y1;
    }
}

bool compare_by_Z(data_point_with_azimuth_3d &first, data_point_with_azimuth_3d &second)
{
    return (first.Z < second.Z);
}

void d3_zone::cut_to_layers()
{
    int num = Data.number_of_points;

    vector<data_point_with_azimuth_3d>::iterator old = Data.data.begin();
    vector<data_point_with_stress_3d>::iterator old2 = Stress.data.begin();
    for(int i = 0; i< num_of_layers; i++)
    {
        vector<data_point_with_azimuth> tmp;
        vector<data_point_with_stress> tmp2;
        double upper_z = Z0 + (Z1 - Z0)/num_of_layers * (i);
        double lower_z = Z0 + (Z1 - Z0)/num_of_layers * (i+1);
        vector<data_point_with_azimuth_3d>::iterator j;
        vector<data_point_with_stress_3d>::iterator k;
        for(j = old; j != Data.data.end(); ++j)
        {
            if((*j).Z > lower_z)
                break;
            else
            {
                tmp.push_back(data_point_with_azimuth((*j).X, (*j).Y, (*j).Azimuth, (*j).Azimuth_error));
            }
        }
        for(k = old2; k != Stress.data.end(); ++k)
        {
            if((*k).Z > lower_z)
                break;
            else
            {
                tmp2.push_back(data_point_with_stress((*k).X, (*k).Y, (*k).Azimuth, (*k).Azimuth_error, (*k).Stress));
            }
        }
        data_points<data_point_with_azimuth> DP(tmp, Data.tag);
        data_points<data_point_with_stress> DP2(tmp2, Data.tag);
        old = j;
        old2 = k;
        layers.push_back(rect_layer(DP, DP2, Sets, upper_z, lower_z));
    }
}

void d3_zone::layer_exec() {
    vector<rect_layer>::iterator i;
    for(i = layers.begin(); i != layers.end(); ++i)
    {
        (*i).get_best();
        (*i).init_full_solver();
    }
}

int d3_zone::get_layer_num(double x, double y, double z) {
    vector<rect_layer>::iterator i;
    int j = 0;
    for(i = layers.begin(); i!=layers.end(); ++i)
    {
        if(z > (*i).Z0 && z<(*i).Z1)
            return j;
        j++;
    }
    return  -1;
}

void d3_zone::init_pressures(string &upper_weigths, string &densities) {
    p = new pressures(upper_weigths, densities, Sets);
}

double d3_zone::get_planar(double x, double y, double z, double Azimuth) {
    int numz = get_layer_num(x, y, z);
    if(layers[numz].out->fin_ISREADY)
    {
        return layers[numz].out->get_normal(cd(x, y), Azimuth, layers[numz].Data.tag);
    }
    else
    {
        throw("Reconstruction is incomplete\n");
    }
}

void d3_zone::update_stresses(data_points<data_point_with_stress_3d> &some) {
    Stress = some;
    cut_to_layers();
    rerun_stress();
}

void d3_zone::rerun_stress() {
    vector<rect_layer>::iterator i;
    for(i = layers.begin(); i != layers.end(); ++i)
    {
        (*i).init_full_solver();
    }
}


bool compare_by_Z_stress(data_point_with_stress_3d &first, data_point_with_stress_3d &second) {
    return (first.Z < second.Z);
}
















