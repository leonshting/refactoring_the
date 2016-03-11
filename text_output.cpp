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
    VectorXd ret(csize);
    for(int i = 0 ; i < csize; i++)
       ret(i) = complex<double>(answer(i), answer(csize+i));
    return ret;
}

void text_output::make_polynoms() {
    map<string, data_points<data_point_with_azimuth>>::iterator i;
    for(i = initData.data_points_collection.begin(); i!=initData.data_points_collection.end(); ++i)
    {
        tag_to_cpolynom.insert({i->second.tag, });
    }
}

string text_output::make_polynom(data_points<data_point_with_azimuth> &subj) {
    string ret;

}
