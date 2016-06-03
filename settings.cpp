//
// Created leonsht on 02.03.16.
//

#include "settings.h"


settings::settings(string &filename) {
    default_order = 3; int count = 0; num_of_validations = 5;
    upper_order = 10; sizes_set = false;
    ifstream i_some(filename);
    string keyword, tag; int order; cd zero, pole;
    double tmp1, tmp2;
    while(!i_some.eof())
    {
        i_some >>keyword;
        if(keyword == "ORDER")
        {
            i_some >> tag >> order;
            ORDERS.insert({tag, order});
            STARTS.insert({tag, count});
            count += order + 1;
        }
        else if(keyword == "ZERO")
        {
            i_some >> tag >> tmp1 >> tmp2;
            zero = cd (tmp1, tmp2);
            ZEROES.insert({tag, zero});
        }
        else if(keyword == "POLE")
        {
            i_some >> tag >> tmp1 >> tmp2;
            pole = cd (tmp1, tmp2);
            POLES.insert({tag, pole});
            POLES_X.insert({tag, true});
        }
        else if(keyword == "SIZES")
        {
            sizes_set = true;
            i_some >> tag >> X0 >> Y0 >> X1 >> Y1;
            default_zero_X = (X1+X0)/2.0;
            default_zero_Y = (Y1+Y0)/2.0;
        }
        else if(keyword == "LAYERS")
            i_some >> num_of_layers;
        else if(keyword == "UPPERORDER")
            i_some >> upper_order;
        else if(keyword == "VALIDATIONS")
            i_some >> num_of_validations;

    }
}

settings::settings() {
    default_order = 3;int count = 0; num_of_validations = 5;
    upper_order = 10; sizes_set = false;
}

int settings::get_order(string &key) {
    auto search = ORDERS.find(key);
    if(search == ORDERS.end())
        return default_order;
    else
        return search->second;
}

int settings::get_start(string &key) {
    auto search = STARTS.find(key);
    if(search == STARTS.end())
        return 0;
    else
        return search->second;
}

cd settings::get_pole(string &key) {
    auto search = POLES.find(key);
    if(search == POLES.end())
        return BLANK_CD;
    else
        return search->second;
}

cd settings::get_zero(string &key) {
    auto search = ZEROES.find(key);
    if(search == ZEROES.end())
        return cd(default_zero_X, default_zero_Y);
    else
        return search->second;
}

bool settings::get_pole_x(string &key) {
    auto search = POLES_X.find(key);
    if(search == POLES_X.end())
        return false;
    else
        return true;
}

void settings::reset_default_order(int Order) {
    default_order = Order;
}

void settings::set_sizes(double x0, double x1, double y0, double y1) {
    X0 = x0; X1 = x1; Y0 = y0; Y1 = y1;
    default_zero_X = (X1+X0)/2.0;
    default_zero_Y = (Y1+Y0)/2.0;
    sizes_set = true;
}


