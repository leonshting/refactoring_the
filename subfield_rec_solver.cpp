//
// Created by leonsht on 01.03.16.
//
#include <iostream>
#include "subfield_rec_solver.h"

SRSolver::SRSolver(init_data &data):initData(data)
{
    Settings = settings();
    EQU_part.conservativeResize(0,0);
    EQU_part.setZero();
}

SRSolver::SRSolver(init_data &data, settings &S):initData(data)
{
    Settings = S;
    EQU_part.conservativeResize(0,0);
    EQU_part.setZero();
}

VectorXcd SRSolver::Vandermonde(calc f, cd z, int ORDER, string tag) {
    VectorXcd vandermonde(ORDER+1);
    vandermonde.setZero();
    for(int i = 0; i <= ORDER; i++)
    {
        vandermonde(i) = f(z, i, Settings.get_zero(tag), Settings.get_pole(tag), Settings.get_pole_x(tag));
    }
    return vandermonde;
}

MatrixXcd SRSolver::Vandermonde_for_cell(calc f, string key, int ORDER) {
    MatrixXcd vandermonde; int row_counter = 0;
    vandermonde.conservativeResize(0, ORDER+1); vandermonde.setZero();

    auto search = initData.key1_cpoints.equal_range(key);
    for(multimap<string,collocation_point>::iterator i = search.first; i != search.second; ++i)
    {
        VectorXcd tmp = Vandermonde(f, i->second.complex_coordinates, ORDER);
        vandermonde.conservativeResize(++row_counter, NoChange);
        vandermonde.row(row_counter-1) = tmp;
        update_enums(i, key);
    }
    return vandermonde;
}

void SRSolver::update_enums(multimap<string,collocation_point>::iterator i, string &key) {
    colloc_enum.insert({make_tuple(key, (i->second.areas.second != key)? i->second.areas.second: i->second.areas.first, i->second.equation_num), values++});
    colloc_enum.insert({make_tuple((i->second.areas.second != key)? i->second.areas.second: i->second.areas.first, key,  i->second.equation_num), values++});

}

VectorXcd SRSolver::Ac(string key1, string key2, int num) {
    VectorXcd ac(2 * initData.num_of_collocation_points);
    auto search = colloc_enum.find(make_tuple(key1, key2, num));
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
    auto search = colloc_enum.find(make_tuple(key1, key2, num));
    auto search2 = colloc_enum.find(make_tuple(key2, key1, num));
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

MatrixXcd SRSolver::Vandermonde_complete(calc f) {
    /*MatrixXcd vc(0,0);
    map<string, data_points<data_point_with_azimuth> >::iterator i;
    for(i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i)
    {
        MatrixXcd tmp;

        MatrixXcd old = vc;
        tmp = Vandermonde_for_cell(i->second.tag, Settings.get_order(i->second.tag));
        vc = catMat(old, tmp, CAT::RightBottom);

        vc.conservativeResize(old.rows() + tmp.rows(), old.cols() + tmp.cols());
        vc.bottomLeftCorner(old.rows(), 0).setZero();
        vc.topRightCorner(0, old.cols()).setZero();
        vc.bottomRightCorner(tmp.rows(), tmp.cols()) = tmp;
    }*/
    MatrixXcd ret(0,0);
    int count = 0;
    map<int, MatrixXcd> tmp_storage;
    map<string, data_points<data_point_with_azimuth> >::iterator i;
    for(i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i)
    {
        tmp_storage.insert({i->second.equation_num, Vandermonde_for_cell(f, i->second.tag, Settings.get_order(i->second.tag))});
        count++;
    }
    for(int i = 0; i<count; i++)
    {
        auto search = tmp_storage.find(i);
        ret = catMat(ret, search->second, CAT::RightBottom);
    }
    return ret;
}

VectorXcd SRSolver::Dsrep(calc f, data_point_with_azimuth z, int ORDER) {
    VectorXcd dsrep(ORDER + 1);
    dsrep = Vandermonde(f, z.complex_coordinates, ORDER) * exp(cd(0,-2*z.Azimuth));
    return dsrep;
}

MatrixXcd SRSolver::Dsrep_for_cell(calc f, string key, int ORDER) {
    MatrixXcd dsrep_fc(0, ORDER+1);
    auto search = initData.data_points_collection.find(key);
    vector<data_point_with_azimuth>::iterator i;
    VectorXcd sum(ORDER+1); sum.setZero();
    for(i = search->second.data.begin(); i != search->second.data.end(); ++i)
    {
        dsrep_fc.conservativeResize(dsrep_fc.rows()+1, NoChange);
        VectorXcd tmp = Dsrep(f, *i, ORDER);
        dsrep_fc.row(dsrep_fc.rows()-1) = tmp;
        sum += tmp;
    }
    update_norm(sum, search->second.equation_num);
    return dsrep_fc;
}


MatrixXcd SRSolver::Dsrep_complete(calc f) {
    MatrixXcd ret(0,0);
    int count = 0;
    map<int, MatrixXcd> tmp_storage;
    map<string, data_points<data_point_with_azimuth> >::iterator i;
    for(i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i)
    {
        tmp_storage.insert({i->second.equation_num, Dsrep_for_cell(f, i->first, Settings.get_order(i->second.tag))});
        count++;
    }
    for(int i = 0; i<count; i++)
    {
        auto search = tmp_storage.find(i);
        ret = catMat(ret, search->second, CAT::RightBottom);
    }
    MatrixXcd tmp = build_norm();
    EQU_part = catMat(EQU_part, tmp, CAT::Right);
    return ret;
}

void SRSolver::build_matrices() {
    values = 0;
    ABlock = Vandermonde_complete(powZ);
    CBlock = C_complete();
    AcBlock = Ac_complete();
    AResult = -CBlock * AcBlock.inverse() * ABlock;
    AResult = catMat(AResult, AResult, CAT::RightBottom);

    V = Dsrep_complete(powZ_POLE);
    V_conj = Dsrep_complete(powZ_conj_POLE);
    // matrix of norm is made up in DSREP_COMPLETE functions

    dEQU_part = matrix_complex_to_real(EQU_part, TRANSFORM::ReIm);
    DSR_block = catMat(V, V_conj, CAT::Right);
    dDSR_block = matrix_complex_to_real(DSR_block, TRANSFORM::ImRe);
    dAResult = matrix_complex_to_real(AResult, TRANSFORM::ReImImRe);
}

void SRSolver::update_norm(VectorXcd &to_add, int eq_num) {
    if(norm.find(eq_num)!=norm.end())
    {
        norm.erase(eq_num);
    }
    norm.insert({eq_num, to_add});
}

MatrixXcd SRSolver::build_norm() {
    MatrixXcd ret(0,0);
    for(int i = 0; i<initData.num_of_zones; i++)
    {
        MatrixXcd tmp = get_norm(i).transpose();
        ret = catMat(ret, tmp, CAT::RightBottom);
    }
    return ret;
}

VectorXcd SRSolver::get_norm(int key) {
    auto search = norm.at(key);
    return search;
}

VectorXd SRSolver::construct_RHS() {
    int size = initData.num_of_collocation_points * 8 + initData.total_num_of_points + initData.num_of_zones;
    VectorXd ret(size);
    ret.setZero();
    int tmp_start = int(ret.rows()) - initData.num_of_zones;
    map<string, data_points<data_point_with_azimuth> >::iterator i;
    for(i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i)
        ret(tmp_start + i->second.equation_num) = i->second.number_of_points;
    return ret;
}

void SRSolver::LSM_solve() {
    VectorXd rhs = construct_RHS();
    RHS = rhs;
    MatrixXd mts(0,0), tmp(0,0);
    tmp = catMat(dAResult, dDSR_block, CAT::Bottom);
    mts = catMat(tmp, dEQU_part, CAT::Bottom);
    //cout << mts << endl;
    JacobiSVD<MatrixXd> svd(mts, ComputeThinU | ComputeThinV);
    dCoef = svd.solve(RHS);
}
