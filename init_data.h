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



class init_data {
public:
    init_data(string& i_data, string& i_cpoints);
    map <string, data_points<data_point_with_azimuth> > data_points_collection;
    multimap<pair<string, string>, collocation_point> cpoints;
    multimap<string, collocation_point> key1_cpoints;
    int num_of_collocation_points;
private:
    string files_w_data, files_w_cpoints;
};


#endif //STRESS_REC_REFACTORED_INIT_DATA_H
