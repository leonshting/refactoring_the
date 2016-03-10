//
// Created by leonsht on 01.03.16.
//
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Dense>
#include <tuple>

#include "init_data.h"
#include "settings.h"
#include "useful_linear_algebra.h"

using namespace Eigen;
using namespace aux_stuff;

#ifndef STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H
#define STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H

// !!!ORDER from settings


class SRSolver {
public:
    enum potentials {Xi = 2, Phi =1};
    MatrixXcd ABlock, AcBlock, CBlock, AResult, DSR_block, V, V_conj;
    MatrixXd dDSR_block, dAResult, dEQU_part;
    MatrixXcd EQU_part;
    VectorXd dCoef;
    VectorXd RHS;
    SRSolver(init_data &data);
    SRSolver(init_data &data, settings &S);
    map< tuple<string, string, int>, int> colloc_enum;
    void build_matrices();
    void LSM_solve();


private:
    VectorXcd Vandermonde(calc f, cd z, int ORDER);
    VectorXcd Ac(string key1, string key2, int num);
    VectorXcd C(string key1, string key2, int num);
    VectorXcd Dsrep(calc f, data_point_with_azimuth z, int ORDER);

    MatrixXcd Vandermonde_for_cell(string key, int ORDER);
    MatrixXcd Vandermonde_complete();
    MatrixXcd Ac_complete();
    MatrixXcd C_complete();
    MatrixXcd Dsrep_for_cell(calc f, string key, int ORDER);
    MatrixXcd Dsrep_complete(calc f);
    MatrixXcd build_norm();
    VectorXcd get_norm(int key);
    VectorXd construct_RHS();
    map<int, VectorXcd> norm;
    inline void update_enums(multimap<string,collocation_point>::iterator, string&);
    inline void update_norm(VectorXcd &to_add, int eq_num);
    init_data initData; settings Settings;
    int values;

};


#endif //STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H
