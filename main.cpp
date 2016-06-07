#include <iostream>

#include "init_data.h"
#include "subfield_rec_solver.h"
#include "output.h"
#include "FinalPSolver.h"
#include "pressures.h"
#include "d3_zone.h"

using namespace std;
using namespace aux_stuff;

int main(int argc, char* argv[]) {
    try {
        string azimuth_data(argv[1]), stress_data(argv[2]), sets(argv[3]), pressures(argv[4]);
        string density(argv[5]);
        settings Settings(sets);
        d3_zone d3Zone(azimuth_data, stress_data, Settings);
        d3Zone.init_pressures(pressures, density);
        d3Zone.cut_to_layers();
        d3Zone.layer_exec();


    }
    catch(int a)
    {
        cout << "Something's gone wrong" << endl;
    }


    return 0;
}