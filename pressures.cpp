//
// Created by Леонид Штанько on 18.05.16.
//

#include "pressures.h"
#include <fstream>
#include <sstream>

double pressures::get_density(double x, double y, double z) {
    return 1000.0;
}

pressures::pressures(string & upper_weights, string & densities, settings & sets) : Sets(sets) {
    steps_num = 1000;
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





