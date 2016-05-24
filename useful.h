//
// Created by leonsht on 3/5/16.
//


#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Dense>
#include <complex>
#include <tuple>
#include <string>
#include <fstream>

using namespace std;
using namespace Eigen;

typedef complex<double> cd;
typedef cd (*calc)(cd, int, cd, cd, bool);
typedef string (*sub_pol)(int, cd, cd, cd, bool, bool);

#ifndef STRESS_REC_REFACTORED_USEFULL_LINEAR_ALGEBRA_H
#define STRESS_REC_REFACTORED_USEFULL_LINEAR_ALGEBRA_H

#define ORDER_ABSENCE 10
#define POLYNOMS_ARENT_READY 11

#define BLANK_CD cd(0.0, 0.0)




namespace aux_stuff
{
    cd powZ(cd z, int n, cd zero = BLANK_CD, cd pole = BLANK_CD, bool pole_x = false);
    cd powZ_conj(cd z, int n, cd zero = BLANK_CD, cd pole = BLANK_CD, bool pole_x = false);
    cd powZ_POLE(cd z, int n, cd zero = BLANK_CD, cd pole = BLANK_CD, bool pole_x = true);
    cd powZ_conj_POLE(cd z, int n, cd zero = BLANK_CD, cd pole = BLANK_CD, bool pole_x = false);
    cd powZ_integrated(cd z, int n, cd zero = BLANK_CD, cd pole = BLANK_CD, bool pole_x = false);


    string PHI_SUB_NOPOLE(int ORDER, cd coef, cd zero = cd(0.0,0.0), cd pole = cd(0.0, 0.0), bool pole_x = false, bool D = true);
    string XI_SUB_NOPOLE(int ORDER, cd coef, cd zero = cd(0.0,0.0), cd pole = cd(0.0, 0.0), bool pole_x = false, bool D = true);
    string PHI_SUB_ZERO(int ORDER, cd coef, cd zero, cd pole, bool pole_x, bool D);
    string XI_SUB_ZERO(int ORDER, cd coef, cd zero, cd pole, bool pole_x, bool D);
    string PHI_SUB_ZERO_POLE(int ORDER, cd coef, cd zero, cd pole, bool pole_x, bool D);
    string XI_SUB_ZERO_POLE(int ORDER, cd coef, cd zero, cd pole, bool pole_x, bool D);

    bool is_file_empty(ifstream& pFile);
    double fromPI_to_PI(double angle);
    string print_complex(cd);


    enum CAT {RightBottom = 1, Right = 2, Bottom = 3};
    enum TRANSFORM {ReIm = 1, ImRe = 2, ReImImRe = 3};

    template <typename T> Matrix<T, Dynamic, Dynamic> catMat(Matrix<T, Dynamic, Dynamic> &t, Matrix<T, Dynamic, Dynamic> &u, CAT cat)
    {
        int new_size_x, new_size_y;
        int start_x, start_y;
        if(cat == CAT::Bottom)
        {
            new_size_x = (int) max(t.cols(), u.cols());
            new_size_y = (int) (t.rows() + u.rows());
            start_y = (int) t.rows();
            start_x = 0;
        }
        else if(cat == CAT::Right)
        {
            new_size_x = (int) (t.cols() + u.cols());
            new_size_y = (int) max(t.rows(), u.rows());
            start_y = 0;
            start_x = (int) t.cols();
        }
        else if(cat == CAT::RightBottom)
        {
            new_size_x = (int) (t.cols() + u.cols());
            new_size_y = (int) (t.rows() + u.rows());
            start_y = (int) t.rows();
            start_x = (int) t.cols();
        }
        Matrix<T, Dynamic, Dynamic> ret(new_size_y, new_size_x);
        ret.setZero();
        ret.block(0, 0, t.rows(), t.cols()) = t;
        ret.block(start_y, start_x, u.rows(), u.cols()) = u;

        return ret;
    };

    template <typename T> Matrix<T, Dynamic, Dynamic> matrix_complex_to_real(Matrix<complex<T>, Dynamic, Dynamic> &c, TRANSFORM transform)
    {
        Matrix<T, Dynamic, Dynamic> ret((transform != ReImImRe)? c.rows() : 2*c.rows(), 2*c.cols());
        ret.setZero();
        for(int i = 0; i<c.rows(); i++)
        {
            for(int j = 0; j<c.cols(); j++)
            {
                if(transform == ReIm)
                {
                    ret(i, j) = real(c(i,j));
                    ret(i, j+c.cols()) = -imag(c(i,j));
                }
                else if(transform == ImRe)
                {
                    ret(i, j) = imag(c(i,j));
                    ret(i, j+c.cols()) = real(c(i,j));
                }
                else if(transform == ReImImRe)
                {
                    ret(i, j) = real(c(i,j));
                    ret(i, j+c.cols()) = -imag(c(i,j));
                    ret(i+c.rows(), j) = imag(c(i,j));
                    ret(i+c.rows(), j+c.cols()) = real(c(i,j));
                }
            }
        }
        return ret;
    };
}


#endif //STRESS_REC_REFACTORED_USEFULL_LINEAR_ALGEBRA_H
