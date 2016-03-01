//
// Created by leonsht on 2/25/16.
//

#include "init_data.h"
#include <iostream>

init_data::init_data(string& i_data, string& i_cpoints):files_w_data(i_data), files_w_cpoints(i_cpoints)
{
    ifstream stream_data(files_w_data);
    ifstream stream_cpoints(files_w_cpoints);
    while(!stream_data.eof())
    {
        string tmp_string;
        stream_data >> tmp_string;
        data_points<data_point_with_azimuth> tmp_data(tmp_string);
        data_points_collection.push_back(tmp_data);
    }
    int ct = 0;
    while(!stream_cpoints.eof())
    {
        collocation_point tmp(stream_cpoints, ct++);
        cpoints.insert({tmp.areas, tmp});
        key1_cpoints.insert({tmp.areas.first, tmp});
        key1_cpoints.insert({tmp.areas.second, tmp});
    }

}
