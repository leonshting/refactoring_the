//
// Created by leonsht on 3/10/16.
//
#include <eigen3/Eigen/Dense>
#include <map>
#include <string>

#include "settings.h"
#include "init_data.h"
#include "useful.h"
#include "data_points.h"


#ifndef STRESS_REC_REFACTORED_TEXT_OUTPUT_H
#define STRESS_REC_REFACTORED_TEXT_OUTPUT_H

using namespace std;
using namespace Eigen;

class text_output
{
public:
    text_output(VectorXd &answer, settings &S, init_data &it);
    void make_polynoms(sub_pol, sub_pol);
    string get_polynom(string & key);
    string get_formatted_output();
private:
    VectorXd Answer;
    VectorXcd cAnswer;
    settings Settings;
    init_data initData;
    VectorXcd cAnswer_fromD(VectorXd &answer);
    map<string, string> tag_to_cpolynom;
    string make_polynom(data_points<data_point_with_azimuth> &subj, sub_pol, sub_pol);
};

#endif //STRESS_REC_REFACTORED_TEXT_OUTPUT_H
