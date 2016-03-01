#include <iostream>

#include "init_data.h"
#include "subfield_rec_solver.h"


using namespace std;

int main(int argc, char* argv[]) {
    string stragrv1(argv[1]), strargv2(argv[2]);
    init_data tmp1(stragrv1, strargv2);
    SRSolver solver(tmp1);
    cout << "somo";
}