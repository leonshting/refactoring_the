//
// Created by leonsht on 2/25/16.
//

#include "init_data.h"

init_data::init_data(string& i_data, string& i_cpoints):files_w_data(i_data), files_w_cpoints(i_cpoints)
{
    ifstream stream_data(files_w_data);
    ifstream stream_cpoints(files_w_cpoints);
    int ct = 0;
    while(!stream_data.eof())
    {
        string tmp_string;
        stream_data >> tmp_string;
        data_points<data_point_with_azimuth> tmp_data(tmp_string, ct++);
        data_points_collection.insert({tmp_string, tmp_data});
    }
    ct = 0;
    while(!stream_cpoints.eof())
    {
        collocation_point tmp(stream_cpoints, ct++);
        cpoints.insert({tmp.areas, tmp});
        cpoints.insert({{tmp.areas.second, tmp.areas.first}, tmp});
        key1_cpoints.insert({tmp.areas.first, tmp});
        key1_cpoints.insert({tmp.areas.second, tmp});
    }
    num_of_collocation_points = ct;
}
