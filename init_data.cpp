//
// Created by leonsht on 2/25/16.
//

#include <fstream>
#include "init_data.h"

init_data::init_data(string i_data, string i_borders):files_w_data(i_data), files_w_borders(i_borders)
{
    ifstream stream_data(i_data);
    ifstream stream_borders(i_borders);
    while(!stream_data.eof() && !stream_borders.eof())
    {
        string tmp_data,tmp_borders;
        stream_data >> tmp_data;
        stream_borders >> tmp_borders;
        f_data.push_back(tmp_data);
        f_borders.push_back(tmp_borders);
    }

}
