//
// Created by leonsht on 21.03.16.
//

#ifndef STRESS_REC_REFACTORED_FINALPSOLVER_H
#define STRESS_REC_REFACTORED_FINALPSOLVER_H

#include <string>

#include "output.h"
#include "init_data.h"
#include "useful.h"

using namespace std;
using namespace Eigen;

class FinalPSolver {
public:
    FinalPSolver(stress_data &stressData, output &O);
    stress_data StressData;
    output Output;
    MatrixXd A;
    VectorXd RHS;
    VectorXd Answer;
private:
    cd full_stress(cd z, double azimuth, string &key);
    double normal_stress(cd z, double azimuth, string &key);
    double shear_stress(cd z, double azimuth, string &key);
    void compose();
    void solve();
};


#endif //STRESS_REC_REFACTORED_FINALPSOLVER_H
