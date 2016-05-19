//
// Created by leonsht on 2/25/16.
//

#include "init_data.h"


init_data::init_data(string& i_data, string& i_cpoints):simple_data(i_data), files_w_cpoints(i_cpoints)
{
    ifstream stream_cpoints(files_w_cpoints);
    int ct = 0;
    ct = 0;
    while(!stream_cpoints.eof() && is_file_empty(stream_cpoints))
    {
        collocation_point tmp(stream_cpoints, ct++);
        cpoints.insert({tmp.areas, tmp});
        cpoints.insert({{tmp.areas.second, tmp.areas.first}, tmp});
        key1_cpoints.insert({tmp.areas.first, tmp});
        key1_cpoints.insert({tmp.areas.second, tmp});
    }
    num_of_collocation_points = ct;
}

init_data::init_data(data_points<data_point_with_azimuth> & D):simple_data(D)
{
    num_of_collocation_points = 0;
}

simple_data::simple_data(string &i_data): files_w_data(i_data){
    ifstream stream_data(files_w_data);
    int ct = 0; int tn_points = 0;
    while(!stream_data.eof() && !is_file_empty(stream_data))
    {
        string tmp_string;
        stream_data >> tmp_string;
        data_points<data_point_with_azimuth> tmp_data(tmp_string, ct++);
        data_points_collection.insert({tmp_string, tmp_data});
        tn_points += tmp_data.number_of_points;
    }
    num_of_zones = ct;
    total_num_of_points = tn_points;
}

simple_data::simple_data(data_points<data_point_with_azimuth> & D)
{
    int tn_points = 0;
    data_points_collection.insert({"only", D});
    tn_points += D.number_of_points;
    num_of_zones = 1;
    total_num_of_points = tn_points;
}

stress_data::stress_data(string &i_sdata): files_w_data(i_sdata) {
    ifstream stream_data(files_w_data);
    int ct = 0; int tn_points = 0;
    while(!stream_data.eof() && !is_file_empty(stream_data))
    {
        string tmp_string;
        stream_data >> tmp_string;
        data_points<data_point_with_stress> tmp_data(tmp_string, ct++);
        data_points_collection.insert({tmp_string, tmp_data});
        tn_points += tmp_data.number_of_points;
    }
    num_of_zones = ct;
    total_num_of_points = tn_points;
}

stress_data::stress_data(data_points<data_point_with_stress> &D) {
    num_of_zones = 1;
    total_num_of_points = int (D.data.size());
    data_points_collection.insert({"only", D});
    files_w_data = "";
}


