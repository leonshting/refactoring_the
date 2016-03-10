#include <iostream>

#include "init_data.h"
#include "subfield_rec_solver.h"
#include "settings.h"

using namespace std;

int main(int argc, char* argv[]) {
    string argv1(argv[1]), argv2(argv[2]), argv3(argv[3]);
    init_data tmp1(argv1, argv2);
    settings Settings(argv3);
    SRSolver solver(tmp1, Settings);
    solver.build_matrices();
    cout << solver.dAResult << endl << endl << solver.dEQU_part << endl << endl << solver.dDSR_block << endl << endl;
    solver.LSM_solve();
    cout << solver.dCoef;
}