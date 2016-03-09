//
// Created leonsht on 02.03.16.
//

#include "settings.h"


settings::settings(string &filename) {
    default_order = 3;
    ifstream i_orders(filename);
    string tag; int order;
    while(!i_orders.eof())
    {
        i_orders >> tag >> order;
        ORDERS.insert({tag, order});
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
