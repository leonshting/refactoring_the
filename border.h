//
// Created by leonsht on 2/25/16.
//

#ifndef STRESS_REC_REFACTORED_BORDER_H
#define STRESS_REC_REFACTORED_BORDER_H

#include <vector>
#include <tuple>
#include <string>
#include <fstream>

#include "data_points.h"

using namespace std;

class side
{
public:
    side(fstream &side_stream);
    vector<data_point> verteces;
};

template <typename T> class border {
public:
    border(string filename);
    vector<T> sides;
};


#endif //STRESS_REC_REFACTORED_BORDER_H
