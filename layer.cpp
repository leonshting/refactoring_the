//
// Created by Леонид Штанько on 25.04.16.
//

#include "layer.h"
#include "init_data.h"
#include "subfield_rec_solver.h"
#include "output.h"
#include "FinalPSolver.h"

#include <fstream>
#include <limits>
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
    out = nullptr;
}

void rect_layer::init_solver() {
    init_data tmp_data(Data);
    SRSolver solver(tmp_data, Sets);
    solver.build_matrices();
    solver.LSM_solve();
    out = new output(solver.dCoef, Sets, tmp_data);
    out->make_polynoms(PHI_SUB_ZERO, XI_SUB_ZERO);
}

void rect_layer::init_full_solver() {
    stress_data tmp_data(Stress);
    FinalPSolver finalPSolver(tmp_data, *out);
    finalPSolver.compose();
    finalPSolver.solve();
    delete out;
    out = new output(finalPSolver.Output);
}


void rect_layer::get_best() {
    int best_O = Sets.default_order;
    init_solver();
    double maxn = std::numeric_limits<double>::max();
    double min_disrepancy = maxn;
    for(int i = 1; i < Sets.upper_order; i++)
    {
        double avg_disrepancy = 0.0;
        for(int j = 0; j < Sets.num_of_validations; j++)
        {
            Sets.reset_default_order(i);
            auto tmp_data = Data.get_randomized_part(0.6);
            init_solver(tmp_data);
            avg_disrepancy += out->get_disrepancy_over_principals();
        }
        if(avg_disrepancy/Sets.num_of_validations < min_disrepancy)
        {
            best_O = i;
            min_disrepancy = avg_disrepancy/Sets.num_of_validations;
        }
    }
    Sets.reset_default_order(best_O);
    for(int i = 1; i < 10; i++)
    {
        output old(*out);
        auto tmp_data = Data.get_randomized_part(double(i)/10.0);
        for(int j = 0; j < Sets.num_of_validations; j++)
        {
            init_solver(tmp_data);
            if(out->get_disrepancy_over_principals() > old.get_disrepancy_over_principals())
            {
                delete out;
                out = new output(old);
            }
        }
    }

}

void rect_layer::init_solver(data_points<data_point_with_azimuth> &data) {
    init_data tmp_data(data);
    init_data to_fill(Data);
    SRSolver solver(tmp_data, Sets);
    solver.build_matrices();
    solver.LSM_solve();
    delete out;
    out = new output(solver.dCoef, Sets, to_fill, tmp_data);
    out->make_polynoms(PHI_SUB_ZERO, XI_SUB_ZERO);
}


