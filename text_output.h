//
// Created by leonsht on 3/10/16.
//
#include <eigen3/Eigen/Dense>

#include "settings.h"
#include "init_data.h"
#include "useful_linear_algebra.h"

#ifndef STRESS_REC_REFACTORED_TEXT_OUTPUT_H
#define STRESS_REC_REFACTORED_TEXT_OUTPUT_H

using namespace std;
using namespace Eigen;

class text_output
{
public:
    text_output(VectorXd &answer, settings &S, init_data &it);

private:
    VectorXd Answer;
    VectorXcd cAnswer;
    settings Settings;
    init_data initData;
    VectorXcd cAnswer_fromD(VectorXd &answer);
};

#endif //STRESS_REC_REFACTORED_TEXT_OUTPUT_H
