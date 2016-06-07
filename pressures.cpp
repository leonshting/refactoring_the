//
// Created by Леонид Штанько on 18.05.16.
//

#include "pressures.h"
#include <fstream>
#include <sstream>
#include <limits>

double pressures::get_density(double x, double y, double z) {
    vector<density_layer>::iterator i;
    for (i = Densities.begin(); i != Densities.end(); ++i)
    {
        if((*i).is_inside(z))
            return (*i).Density;
    }
}

pressures::pressures(string & upper_weights, string & densities, settings & sets) : Sets(sets) {
    steps_num = Sets.n_pressure_steps;
    ifstream UW(upper_weights);
    while(!UW.eof())
    {
        string tmp;
        getline(UW, tmp);
        stringstream to_split(tmp);
        vector<double> splitted;
        while(!to_split.eof()) {
            double go;
            to_split >> go;
            splitted.push_back(go);
        }
        upperW.push_back(splitted);
        meshgridX = int(splitted.size());
    }
    ifstream D(densities);
    while(!D.eof())
    {
        double z0, z1, density;
        D >> z0 >> z1 >> density;
        Densities.push_back(density_layer(z0, z1, density));
    }
    meshgridY = int(upperW.size());
}

double pressures::get_pressure(double x, double y, double z)
{
    int xn = int(meshgridX*x/(Sets.X1 - Sets.X0));
    int yn = int(meshgridY*y/(Sets.Y1 - Sets.Y0));
    double ret = upperW[yn][xn];
    for(int i = 0; i < steps_num; i++)
    {
        ret+=z/steps_num*get_density(x,y, z+i*(z/steps_num));
    }
    return ret;
}

tuple<double, double> pressures::get_Zsizes() {
    vector<density_layer>::iterator i;
    double max = std::numeric_limits<double>::min();
    double min = std::numeric_limits<double>::max();
    for (i = Densities.begin(); i != Densities.end(); ++i)
    {
        if((*i).Z0 < min)
            min = (*i).Z0;
        if((*i).Z1 > max)
            max = (*i).Z1;
    }
    return {min, max};
}


density_layer::density_layer(double z0, double z1, double density):Z0(z0), Z1(z1), Density(density) {
}

bool density_layer::is_inside(double z) {
    if(z > Z0 && z < Z1)
        return true;
    else
        return false;
}



