//
// Created by leonsht on 3/10/16.
//

#include "output.h"

output::output(VectorXd &answer, settings &S, init_data &it): Answer(answer), Settings(S), initData(it)
{
    cAnswer = cAnswer_fromD(Answer);
}

VectorXcd output::cAnswer_fromD(VectorXd &answer) {
    int csize = answer.rows()/2;
    VectorXcd ret(csize);
    for(int i = 0 ; i < csize; i++)
       ret(i) = cd(answer(i), answer(csize+i));
    return ret;
}

void output::make_polynoms(sub_pol polPHI, sub_pol polXI) {
    map<string, data_points<data_point_with_azimuth>>::iterator i;
    for(i = initData.data_points_collection.begin(); i!=initData.data_points_collection.end(); ++i)
    {
        tag_to_Dpolynom.insert({i->second.tag, make_Dpolynom(i->second, polPHI, polXI)});
        tag_to_Ppolynom.insert({i->second.tag, make_Ppolynom(i->second, polPHI, polXI)});
    }
}

string output::make_Dpolynom(data_points<data_point_with_azimuth> &subj, sub_pol polPHI, sub_pol polXI) {
    stringstream ret;
    int ORDER = Settings.ORDERS.at(subj.tag);
    for(int i = 0; i <= ORDER; i++)
    {
        ret << polPHI(i, cAnswer(Settings.get_start(subj.tag)), Settings.get_zero(subj.tag),
                      Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag), true);
            ret << " + ";
        ret << polXI(i, cAnswer(ORDER + 1 + Settings.get_start(subj.tag)), Settings.get_zero(subj.tag),
                     Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag), true);
        if(i != ORDER)
            ret << " + ";
    }
    return ret.str();
}

string output::get_polynom(string &key) {
    auto search = tag_to_Dpolynom.find(key);
    return search->second;
}

string output::get_formatted_output() {
    stringstream ret;
    if(tag_to_Dpolynom.empty())
    {
        throw POLYNOMS_ARENT_READY;
    }
    else
    {
        map<string, data_points<data_point_with_azimuth>>::iterator i;
        for (i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i) {
            ret << i->second.tag << ": D: " << tag_to_Dpolynom.at(i->second.tag) << endl;
            ret <<"P: " << tag_to_Ppolynom.at(i->second.tag) << endl;
        }
    }
    return ret.str();
}

string output::make_Ppolynom(data_points<data_point_with_azimuth> &subj, sub_pol polPHI, sub_pol polXI) {
    stringstream ret;
    int ORDER = Settings.ORDERS.at(subj.tag);
    for(int i = 0; i <= ORDER; i++)
    {
        ret << polXI(i, cAnswer(ORDER + 1 + Settings.get_start(subj.tag)), Settings.get_zero(subj.tag),
                     Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag), false);
        if(i != ORDER)
            ret << " + ";
    }
    return ret.str();
}

cd output::getP(cd z, string tag) {

}

cd output::getD(cd z, string tag) {

}
