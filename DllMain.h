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
#  ifdef MODULE_API_EXPORTS
#    define MODULE_API __declspec(dllexport)
#  else
#    define MODULE_API __declspec(dllimport)
#  endif
#else
#  define MODULE_API
#endif

struct Stensor
        {
                double xx; double yy; double zz; double xy; double xz; double yz;
        };

// three functions must be executed in before using non-void functions
MODULE_API void load_initial(char * orientations, char * stresses);
MODULE_API void load_pressures(char * upper_pressures, char * densitites);

MODULE_API void exec_initial();
//  /\   /\
// /++\ /++\
// |||  ||| these three functions
// |||  ||| in the following order load_initial(), load_pressures(), exec_initial()

MODULE_API double get_stress(double x, double y, double z, double azimuth);


MODULE_API void init_crack(double *x, double *y, double *z, double *azimuths, double *pressures);
MODULE_API int get_stress_tensor(double x, double y, double z, double planar_angle, Stensor * ret);
MODULE_API int get_tensor_xyz(double x, double y, double z, Stensor * ret);
MODULE_API int get_tensor_xyz0(double x, double y, double z, Stensor * ret);
MODULE_API int get_tensor_main(double x, double y, double z, Stensor * ret);
MODULE_API double get_orientation(double x, double y, double z);
MODULE_API void stress_before(double *point, double *direction0, double *direction1, double *direction2, double *sigma);
MODULE_API void stress_after(double *point, double *direction0, double *direction1, double *direction2, double *sigma);




#ifdef __cplusplus
}
#endif



#endif //STRESS_REC_REFACTORED_DLLMAIN_H
