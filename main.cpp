#include <iostream>

#include "init_data.h"
#include "subfield_rec_solver.h"
#include "output.h"
#include "FinalPSolver.h"

using namespace std;
using namespace aux_stuff;

int main(int argc, char* argv[]) {
    string azimuth_data(argv[1]), cpoints(argv[2]), sets(argv[3]), stress(argv[4]);
    init_data initData(azimuth_data, cpoints);
    stress_data stressData(stress);
    settings Settings(sets);
    SRSolver solver(initData, Settings);
    solver.build_matrices();
    cout << solver.dAResult << endl << endl << solver.dEQU_part << endl << endl << solver.dDSR_block << endl << endl;
    solver.LSM_solve();
    output output(solver.dCoef, Settings, initData);
    output.make_polynoms(PHI_SUB_ZERO_POLE, XI_SUB_ZERO_POLE);
    FinalPSolver(stressData, output);
    cout << endl << output.get_formatted_output();
}