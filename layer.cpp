//
// Created by Леонид Штанько on 25.04.16.
//

#include "layer.h"
#include "init_data.h"
#include "subfield_rec_solver.h"
#include "output.h"
#include "FinalPSolver.h"

#include <fstream>
/*
layer::layer(string borders) {
    ifstream b(borders);
    while(!b.eof())
    {
        string filename;
        b >> filename;
        border tmp(filename);
        Bs.push_back(tmp);
    }
}
*/
rect_layer::rect_layer(data_points<data_point_with_azimuth> &D, data_points<data_point_with_stress> &St, settings &S,  double z0,
                       double z1):Data(D), Sets(S), Stress(St)
{
    X0 = Sets.X0; X1 = Sets.X1;
    Y0 = Sets.Y0; Y1 = Sets.Y1;
    Z0 = z0; Z1 = z1;
    num_of_points = (int) D.data.size();
}

void rect_layer::init_solver() {
    init_data tmp_data(Data);
    SRSolver solver(tmp_data, Sets);
    solver.build_matrices();
    solver.LSM_solve();
    out = new output(solver.dCoef, Sets, tmp_data);
    out->make_polynoms(PHI_SUB_ZERO_POLE, XI_SUB_ZERO_POLE);
}

void rect_layer::init_full_solver() {
    stress_data tmp_data(Stress);
    FinalPSolver finalPSolver(tmp_data, *out);
    finalPSolver.compose();
    finalPSolver.solve();
    delete out;
    out = new output(finalPSolver.Output);
}



