//
// Created by leonsht on 2/25/16.
//

#include "border.h"

template <typename T>
border::border(string filename) {
    ifstream border_stream(filename);
    while(!border_stream.eof())
    {
        T tmp(&border_stream);
        sides.push_back(tmp);
    }
}

side::side(fstream &side_stream) {
    data_point tmp1(side_stream), tmp2(side_stream);
    verteces.push_back(tmp1); verteces.push_back(tmp2);
}
