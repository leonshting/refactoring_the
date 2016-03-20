//
// Created by leonsht on 3/10/16.
//

#include "text_output.h"

text_output::text_output(VectorXd &answer, settings &S, init_data &it):Answer(answer), Settings(S), initData(it)
{
    cAnswer = cAnswer_fromD(Answer);
}

VectorXcd text_output::cAnswer_fromD(VectorXd &answer) {
    int csize = answer.rows()/2;
    VectorXcd ret(csize);
    for(int i = 0 ; i < csize; i++)
       ret(i) = cd(answer(i), answer(csize+i));
    return ret;
}

void text_output::make_polynoms(sub_pol polPHI, sub_pol polXI) {
    map<string, data_points<data_point_with_azimuth>>::iterator i;
    for(i = initData.data_points_collection.begin(); i!=initData.data_points_collection.end(); ++i)
    {
        tag_to_cpolynom.insert({i->second.tag, make_polynom(i->second, polPHI, polXI)});
    }
}

string text_output::make_polynom(data_points<data_point_with_azimuth> &subj, sub_pol polPHI, sub_pol polXI) {
    stringstream ret;
    int ORDER = Settings.ORDERS.at(subj.tag);
    for(int i = 0; i <= ORDER; i++)
    {
        ret << polPHI(i, cAnswer(Settings.get_start(subj.tag)), Settings.get_zero(subj.tag),
                      Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag));
            ret << " + ";
        ret << polXI(i, cAnswer(ORDER + 1 + Settings.get_start(subj.tag)), Settings.get_zero(subj.tag),
                     Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag));
        if(i != ORDER)
            ret << " + ";
    }
    return ret.str();
}

string text_output::get_polynom(string &key) {
    auto search = tag_to_cpolynom.find(key);
    return search->second;
}

string text_output::get_formatted_output() {
    stringstream ret;
    if(tag_to_cpolynom.empty())
    {
        throw POLYNOMS_ARENT_READY;
    }
    else
    {
        map<string, data_points<data_point_with_azimuth>>::iterator i;
        for (i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i) {
            ret << i->second.tag << ": " << tag_to_cpolynom.at(i->second.tag) << endl;
        }
    }
    return ret.str();
}
