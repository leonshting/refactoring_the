//
// Created by leonsht on 09.03.16.
//

#include "useful.h"

#include <iostream>

complex<double> aux_stuff::powZ(cd z, int n, cd zero, cd pole, bool pole_x) {
    return pow(z - zero,n);
}

complex<double> aux_stuff::powZ_conj(cd z, int n, cd zero, cd pole, bool pole_x) {
    return conj(z) * powZ(z - zero,n);
}

cd aux_stuff::powZ_conj_POLE(cd z, int n, cd zero, cd pole, bool pole_x) {
    if(pole_x)
        return powZ_conj(z - zero, n)/(z - pole);
    else
        return powZ_conj(z-zero, n);
}

cd aux_stuff::powZ_POLE(cd z, int n, cd zero, cd pole, bool pole_x) {
    if(pole_x)
        return powZ(z - zero, n)/(z - zero);
    else
        return powZ(z-zero, n);
}

string aux_stuff::print_complex(cd z) {
    string REpart = (z.real()!= 0.0)? "(" + to_string(z.real()) + ")": "";
    string IMpart = (z.imag()!= 0.0)? "(" + to_string(z.imag()) + ")": "";

    if(REpart == "" && IMpart == "")
        return "";
    else if(REpart != "" && IMpart != "")
        return REpart + " + 1j*" + IMpart;
    else
        if(REpart != "") return REpart;
        else return IMpart;

}

string aux_stuff::PHI_SUB_NOPOLE(int ORDER, cd coef, cd zero, cd pole, bool pole_x) {
    stringstream ret;
    ret <<"("<< print_complex(coef) << ") * z**" << ORDER;
    return ret.str();
}

string aux_stuff::XI_SUB_NOPOLE(int ORDER, cd coef, cd zero, cd pole, bool pole_x) {
    stringstream ret;
    ret << "(z.conjugate())" << " * " << PHI_SUB_ZERO(ORDER, coef, zero, pole, pole_x);
    return ret.str();
}

string aux_stuff::PHI_SUB_ZERO(int ORDER, cd coef, cd zero, cd pole, bool pole_x) {
    stringstream ret;
    ret <<"("<< print_complex(coef) << ") * (z - " << print_complex(zero) << ")**" << ORDER;
    return ret.str();
}

string aux_stuff::XI_SUB_ZERO(int ORDER, cd coef, cd zero, cd pole, bool pole_x) {
    stringstream ret;
    ret << "(z.conjugate())" << " * " + PHI_SUB_ZERO(ORDER, coef, zero, pole, pole_x);
    return ret.str();
}


string aux_stuff::XI_SUB_ZERO_POLE(int ORDER, cd coef, cd zero, cd pole, bool pole_x) {
    if(pole_x)
        return XI_SUB_ZERO(ORDER, coef, zero, pole, pole_x) + "/(z - " + print_complex(pole) + ")";
    else
        return XI_SUB_ZERO(ORDER, coef, zero, pole, pole_x);
}

string aux_stuff::PHI_SUB_ZERO_POLE(int ORDER, cd coef, cd zero, cd pole, bool pole_x) {
    if(pole_x)
        return PHI_SUB_ZERO(ORDER, coef, zero, pole, pole_x) + "/(z - " + print_complex(pole) + ")";
    else
        return PHI_SUB_ZERO(ORDER, coef, zero, pole, pole_x);
}
