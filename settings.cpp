//
// Created leonsht on 02.03.16.
//

#include "settings.h"


settings::settings(string &filename) {
    default_order = 3; int count = 0;
    ifstream i_some(filename);
    string keyword, tag; int order; cd zero, pole;
    double tmp1, tmp2;
    while(!i_some.eof())
    {
        i_some >>keyword >> tag;
        if(keyword == "ORDER")
        {
            i_some >> order;
            ORDERS.insert({tag, order});
            STARTS.insert({tag, count});
            count += order + 1;
        }
        else if(keyword == "ZERO")
        {
            i_some >> tmp1 >> tmp2;
            zero = cd (tmp1, tmp2);
            ZEROES.insert({tag, zero});
        }
        else if(keyword == "POLE")
        {
            i_some >> tmp1 >> tmp2;
            pole = cd (tmp1, tmp2);
            POLES.insert({tag, pole});
            POLES_X.insert({tag, true});
        }
    }
}

settings::settings() {
    default_order = 3;
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
        return BLANK_CD;
    else
        return search->second;
}

bool settings::get_pole_x(string &key) {
    auto search = POLES_X.find(key);
    if(search == POLES_X.end())
        return false;
    else
        return search->second;
}
