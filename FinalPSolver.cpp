//
// Created by leonsht on 21.03.16.
//

#include "FinalPSolver.h"

FinalPSolver::FinalPSolver(stress_data &stressData, output &O):StressData(stressData), Output(O)
{
    RHS.resize(stressData.total_num_of_points); RHS.setZero();
    A.resize(stressData.total_num_of_points, 2); A.setZero();
    Answer.resize(2); Answer.setZero();
}

cd FinalPSolver::full_stress(cd z, double azimuth, string &key) {
    cd P = Output.getP(z, key);
    cd D = Output.getD(z, key);
    return cd(2*P.real(), 0.0) + D * exp(cd(0.0, -2.0 * azimuth));
}

double FinalPSolver::normal_stress(cd z, double azimuth, string &key) {
    return full_stress(z, azimuth, key).real();
}

double FinalPSolver::shear_stress(cd z, double azimuth, string &key) {
    return full_stress(z, azimuth, key).imag();
}

void FinalPSolver::compose() {
    int count = 0;
    map<string, data_points<data_point_with_stress>>::iterator i;
    for(i = StressData.data_points_collection.begin(); i != StressData.data_points_collection.end(); ++i)
    {
        vector<data_point_with_stress>::iterator j;
        for(j = i->second.data.begin(); j != i->second.data.end(); ++j)
        {
            Vector2d tmp;
            tmp(0) = normal_stress(j->complex_coordinates, j->Azimuth, i->second.tag);
            tmp(1) = 1.0;
            A.row(count) = tmp;
            RHS(count) = j->Stress;
            count++;
        }
    }
}

void FinalPSolver::solve() {
    JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);
    Answer = svd.solve(RHS);
    Output.finAnswer = Answer;
    Output.fin_ISREADY = true;
}
