//
// Created by leonsht on 2/25/16.
//

#ifndef STRESS_REC_REFACTORED_INIT_DATA_H
#define STRESS_REC_REFACTORED_INIT_DATA_H


#include <string>
#include <complex>
#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>
#include <map>

#include "data_points.h"

using namespace std;

typedef complex<double> cd;

class simple_data
{
public:
    simple_data(string& i_data);
    map<string, data_points<data_point_with_azimuth> > data_points_collection;
    string files_w_data;
    int num_of_zones;
    int total_num_of_points;
};


class init_data:public simple_data {
public:
    init_data(string& i_data, string& i_cpoints);
    multimap<pair<string, string>, collocation_point> cpoints;
    multimap<string, collocation_point> key1_cpoints;
    int num_of_collocation_points;
    string files_w_cpoints;
};

class stress_data
{
public:
    stress_data(string& i_sdata);
    map<string, data_points<data_point_with_stress> > data_points_collection;
    int num_of_zones;
    int total_num_of_points;
    string files_w_data;
};

#endif //STRESS_REC_REFACTORED_INIT_DATA_H
