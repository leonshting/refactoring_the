//
// Created by leonsht on 01.03.16.
//

#include "subfield_rec_solver.h"

SRSolver::SRSolver(init_data &data):initData(data)
{
    values = 0;
    ABlock = Vandermonde_complete();
    CBlock = C_complete();
    AcBlock = Ac_complete();
}

SRSolver::SRSolver(init_data &data, settings &S):SRSolver(data)
{
    Settings = S;
}

VectorXcd SRSolver::Vandermonde(calc f, cd z, int ORDER) {
    VectorXcd vandermonde(ORDER+1);
    vandermonde.setZero();
    for(int i = 0; i <= ORDER; i++)
    {
        vandermonde(i) = f(z, i);
    }
    return vandermonde;
}

MatrixXcd SRSolver::Vandermonde_for_cell(string key, int ORDER) {
    MatrixXcd vandermonde; int row_counter = 0;
    vandermonde.conservativeResize(0, ORDER+1); vandermonde.setZero();

    auto search = initData.key1_cpoints.equal_range(key);
    for(multimap<string,collocation_point>::iterator i = search.first; i != search.second; ++i)
    {
        VectorXcd tmp = Vandermonde(powZ, i->second.complex_coordinates, ORDER);
        vandermonde.conservativeResize(++row_counter, NoChange);
        vandermonde.row(row_counter-1) = tmp;
        update_enums(i, key);
    }
    zones_enum.push_back(initData.data_points_collection.find(key)->second.tag);
    return vandermonde;

}

void SRSolver::update_enums(multimap<string,collocation_point>::iterator i, string &key) {
    colloc_enum.insert({{key, (i->second.areas.second != key)? i->second.areas.second: i->second.areas.first, i->second.equation_num}, values++});
    colloc_enum.insert({{(i->second.areas.second != key)? i->second.areas.second: i->second.areas.first, key,  i->second.equation_num}, values++});

}

VectorXcd SRSolver::Ac(string key1, string key2, int num) {
    VectorXcd ac(2 * initData.num_of_collocation_points);
    auto search = colloc_enum.find({key1, key2, num});
    ac.setZero();
    if(search != colloc_enum.end())
    {
        int number = search->second;
        ac(number) = cd(-1.0, 0.0);
    }
    return ac;
}

VectorXcd SRSolver::C(string key1, string key2, int num) {
    VectorXcd c(2 * initData.num_of_collocation_points);
    auto search = colloc_enum.find({key1, key2, num});
    auto search2 = colloc_enum.find({key2, key1, num});
    c.setZero();
    if(search != colloc_enum.end())
    {
        c(search->second) = cd(-1.0, 0.0);
        c(search2->second) = cd(1.0, 0.0);
    }
    return c;
}

MatrixXcd SRSolver::Ac_complete() {
    MatrixXcd ac_complete(2*initData.num_of_collocation_points, 2*initData.num_of_collocation_points);
    int cur_row = 0;
    for(map<pair<string, string>, collocation_point>::iterator i = initData.cpoints.begin(); i != initData.cpoints.end(); ++i)
    {
        ac_complete.row(cur_row++) = Ac(i->first.first, i->first.second, i->second.equation_num);
    }
    return ac_complete;
}

MatrixXcd SRSolver::C_complete() {
    MatrixXcd ac_complete(2*initData.num_of_collocation_points, 2*initData.num_of_collocation_points);
    int cur_row = 0;
    for(map<pair<string, string>, collocation_point>::iterator i = initData.cpoints.begin(); i != initData.cpoints.end(); ++i)
    {
        ac_complete.row(cur_row++) = C(i->first.first, i->first.second, i->second.equation_num);
    }
    return ac_complete;
}

MatrixXcd SRSolver::Vandermonde_complete() {
    MatrixXcd vc(0,0);
    map<string, data_points<data_point_with_azimuth> >::iterator i;
    for(i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i)
    {
        MatrixXcd tmp;
        MatrixXcd old = vc;
        tmp = Vandermonde_for_cell(i->first, 5);
        vc.conservativeResize(old.rows() + tmp.rows(), old.cols() + tmp.cols());
        vc.bottomLeftCorner(old.rows(), 0).setZero();
        vc.topRightCorner(0, old.cols()).setZero();
        vc.bottomRightCorner(tmp.rows(), tmp.cols()) = tmp;
    }
    return vc;
}

complex<double> powZ(complex<double> z, int n) {
    return pow(z,n);
}

complex<double> powZ_conj(complex<double> z, int n) {
    return conj(z)*powZ(z,n);
}
