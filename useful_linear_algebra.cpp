//
// Created by leonsht on 09.03.16.
//
#include "useful_linear_algebra.h"

#include <iostream>

complex<double> powZ(complex<double> z, int n) {
    return pow(z,n);
}

complex<double> powZ_conj(complex<double> z, int n) {
    return conj(z)*powZ(z,n);
}

string PHI_SUB_NOPOLE(int num , int ORDER, cd coef) {
    stringstream ret;

}

string print_complex(cd z) {
    return "(" + to_string(z.real()) + ") + (1j*(" + to_string(z.imag()) + "))"
}
