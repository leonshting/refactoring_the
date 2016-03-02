//
// Created by leonsht on 01.03.16.
//
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Dense>

#include "init_data.h"
#include "settings.h"
#include <tuple>

using namespace Eigen;
typedef cd (*calc)(cd, int);

#ifndef STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H
#define STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H

cd powZ(cd z, int n);
cd powZ_conj(cd z, int n);


class SRSolver {
public:
    MatrixXcd ABlock, AcBlock, CBlock;
    SRSolver(init_data &data);
    SRSolver(init_data &data, settings &S);
    map< tuple<string, string, int>, int> colloc_enum;
    vector<string> zones_enum;
private:
    VectorXcd Vandermonde(calc f, cd z, int ORDER);
    VectorXcd Ac(string key1, string key2, int num);
    VectorXcd C(string key1, string key2, int num);

    MatrixXcd Vandermonde_for_cell(string key, int ORDER);
    MatrixXcd Vandermonde_complete();
    MatrixXcd Ac_complete();
    MatrixXcd C_complete();

    inline void update_enums(multimap<string,collocation_point>::iterator, string&);
    init_data initData; settings Settings;
    int values;

};


#endif //STRESS_REC_REFACTORED_SUBFIELD_REC_SOLVER_H
