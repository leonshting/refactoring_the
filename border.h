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

/*class side
{
public:
    side(ifstream &side_stream, ifstream &bool_stream);
    bool is_true(double x, double y);
private:
    void make_equation_from_points();
    string tag;
    vector<double> equation;
    vector<data_point> init_points;
    bool greater_lower;
};

class border {
public:
    border(string filename);
    bool is_inside(double x, double y);
private:
    vector<side> sides;
    vector<string> tags;
};

*/
#endif //STRESS_REC_REFACTORED_BORDER_H
