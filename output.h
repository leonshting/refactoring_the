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
using namespace aux_stuff;
class output
{
public:
    output(VectorXd &answer, settings &S, init_data &it);
    output(VectorXd &answer, settings &S, init_data &it, init_data &pt);
    void make_polynoms(sub_pol, sub_pol);
    void update_part_data(init_data &pD);
    string get_polynom(string & key);
    string get_formatted_output();
    cd getD(cd z, string &tag);
    cd getP(cd z, string &tag);
    cd get_full(cd z, double azimuth, string &tag);
    double get_normal(cd z, double azimuth, string &tag);
    double get_shear(cd z, double azimuth, string &tag);
    double get_disrepancy_over_principals();
    double get_orientation(cd z, string &tag);
    Vector2d finAnswer;
    bool fin_ISREADY;
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
    VectorXd Answer;
    VectorXcd cAnswer;
    settings Settings;
    init_data initData;
    init_data *partData;
    VectorXcd cAnswer_fromD(VectorXd &answer);
    map<string, string> tag_to_Dpolynom;
    map<string, string> tag_to_Ppolynom;
    string make_Dpolynom(data_points<data_point_with_azimuth> &subj, sub_pol, sub_pol);
    string make_Ppolynom(data_points<data_point_with_azimuth> &subj, sub_pol, sub_pol);
};

#endif //STRESS_REC_REFACTORED_TEXT_OUTPUT_H
