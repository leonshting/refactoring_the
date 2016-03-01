//
// Created by bigbrother on 01.03.16.
//

#include "subfield_rec_solver.h"
#include <iostream>

SRSolver::SRSolver(init_data &data):initData(data)
{

}

VectorXcd SRSolver::Vandermonde(cd z, int ORDER) {
    VectorXcd vandermonde(ORDER+1);
    vandermonde.setZero();
    for(int i = 0; i <= ORDER; i++)
    {
        vandermonde(i) = pow(z, i);
    }
    return vandermonde;
}

MatrixXcd SRSolver::Vandermonde_for_cell(string& key, int ORDER) {
    MatrixXcd vandermonde; int row_counter = 0;
    vandermonde.conservativeResize(0, ORDER+1); vandermonde.setZero();

    auto search = initData.key1_cpoints.equal_range(key);
    for(multimap<string,data_point>::iterator i = search.first; i != search.second; ++i)
    {
        VectorXcd tmp = Vandermonde(i->second.complex_coordinates, ORDER);
        vandermonde.conservativeResize(++row_counter, NoChange);
        vandermonde.row(row_counter-1) = tmp;
    }
    cout << vandermonde;
    return vandermonde;

}
