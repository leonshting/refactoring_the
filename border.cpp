//
// Created by leonsht on 2/25/16.
//
/*
#include "border.h"

border::border(string filename) {
    ifstream border_stream(filename);

    string S;
    while(!border_stream.eof())
    {
        side tmp(border_stream);
        S = tmp.tag;
        sides.push_back(tmp);
    }

}
bool border::is_inside(double x, double y)
{
    vector<side>::iterator i;
    for(i = sides.begin(); i != sides.end(); ++i)
    {
        if(!(*i).is_true(x,y))
            return false;
    }
    return true;
}

side::side(ifstream &side_stream, ifstream &bool_stream) {
    data_point tmp1(side_stream), tmp2(side_stream);
    init_points.push_back(tmp1); init_points.push_back(tmp2);
    make_equation_from_points();
    string tmp_string;
    bool_stream << greater_lower << tmp_string;
}

void side::make_equation_from_points()
{
    double c = 1;
    double a = ((-1 + init_points[1].Y/init_points[0].Y)/
            (init_points[1].X - init_points[0].X * init_points[1].Y/init_points[0].Y));
    double b = ((-1 + init_points[1].X/init_points[0].X)/
                (init_points[1].Y - init_points[0].Y * init_points[1].X/init_points[0].X));
    equation.push_back(a); equation.push_back(b); equation.push_back(c);
}

bool side::is_true(double x, double y)
{
    if((equation[0] * x + equation[1] * y + equation[2] > 0) == greater_lower)
        return true;
    else
        return false;
}
*/