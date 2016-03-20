#include <iostream>

#include "init_data.h"
#include "subfield_rec_solver.h"
#include "text_output.h"

using namespace std;
using namespace aux_stuff;

int main(int argc, char* argv[]) {
    string argv1(argv[1]), argv2(argv[2]), argv3(argv[3]);
    init_data tmp1(argv1, argv2);
    settings Settings(argv3);
    SRSolver solver(tmp1, Settings);
    solver.build_matrices();
    cout << solver.dAResult << endl << endl << solver.dEQU_part << endl << endl << solver.dDSR_block << endl << endl;
    solver.LSM_solve();
    text_output output(solver.dCoef, Settings, tmp1);
    output.make_polynoms(PHI_SUB_ZERO_POLE, XI_SUB_ZERO_POLE);
    cout << endl << output.get_formatted_output();
}