//
// Created by bigbrother on 01.03.16.
//
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Dense>

#include "init_data.h"

using namespace Eigen;

#ifndef STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H
#define STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H



class SRSolver {
public:
    MatrixXcd ABlock, AcBlock, CBlock;
    SRSolver(init_data &data);
private:
    VectorXcd Vandermonde(cd z, int ORDER);
    MatrixXcd Vandermonde_for_cell(string& key, int ORDER);
    MatrixXcd Ac_for_cell(string &key, )
    init_data initData;
};


#endif //STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H
