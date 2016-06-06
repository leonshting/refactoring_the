//
// Created by Леонид Штанько on 03.06.16.
//

#ifndef STRESS_REC_REFACTORED_DLLMAIN_H
#define STRESS_REC_REFACTORED_DLLMAIN_H

#include "output.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
        #ifdef MODULE_API_EXPORTS
                #define MODULE_API __declspec(dllexport)
        #else
                #define MODULE_API __declspec(dllimport)
#endif
#else
        #define MODULE_API
#endif

struct MODULE_API Stensor
        {
                double xx; double yy; double zz; double xy; double xz; double yz;
        };


void MODULE_API  load_initial(char * orientations, char * stresses);
double MODULE_API get_stress(double x, double y, double z, double azimuth);
void MODULE_API init_crack(double *x, double *y, double *z, double *azimuths, double *pressures);
int MODULE_API get_crack_stress(double x, double y, double z, Stensor * ret);

#ifdef __cplusplus
}
#endif



#endif //STRESS_REC_REFACTORED_DLLMAIN_H
