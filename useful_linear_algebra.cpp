//
// Created by leonsht on 09.03.16.
//
#include "useful_linear_algebra.h"

complex<double> powZ(complex<double> z, int n) {
    return pow(z,n);
}

complex<double> powZ_conj(complex<double> z, int n) {
    return conj(z)*powZ(z,n);
}
