// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include "Imagine/LinAlg/MyEigen.h"
#include <Eigen/Dense>

using namespace Eigen;

//N'existe pas dans Eigen Blas
//corriger
//info=0 si succes, -i si ieme parametre illegal, i si bdsdc ne converge pas
//info important car utilise dans Matrix.h
// Singular values decomposition
/* jobz est non usite... et est dans la liste des arguments de Imagine::svd */
template <typename T>
void subSingularValuesDecomposition(const char *jobz,int *m,int *n, T *a, T *s, T *u, T *vt, int *info)
{
    assert((*jobz == 'A') || (*jobz == 'S')); // ?
    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (a, *m, *n, OuterStride<>(*m));
    Eigen::JacobiSVD<Matrix<T, Dynamic, Dynamic> > svd (AMap, ComputeFullU | ComputeFullV);
    Matrix<T, Dynamic, Dynamic> u1 = svd.matrixU();
    Matrix<T, Dynamic, Dynamic> v1 = svd.matrixV();
    Matrix<T, Dynamic, Dynamic> sv = svd.singularValues();
    Map<Matrix<T, Dynamic, 1> > sMap (s, sv.rows());
    sMap = sv;
    Map<Matrix<T, Dynamic, Dynamic> > uMap (u, u1.rows(), u1.cols());
    uMap = u1;
    Map<Matrix<T, Dynamic, Dynamic> > vtMap (vt, v1.rows(), v1.cols());
    vtMap = v1.transpose();
    Matrix<T, Dynamic, Dynamic> sigma = Matrix<T, Dynamic, Dynamic>::Zero(*m,*n);
    for (int i = 0 ; i < sMap.rows() ; i++){
        sigma(i, i) = sMap(i);
    };
    *info = 1 - AMap.isApprox(uMap * sigma * vtMap);
}

void singularValuesDecomposition(const char *jobz,int *m,int *n, double *a, double *s, double *u, double *vt, int *info) { subSingularValuesDecomposition<double>(jobz, m, n, a, s, u, vt, info); }
void singularValuesDecomposition(const char *jobz,int *m,int *n, float *a, float *s, float *u, float *vt, int *info) { subSingularValuesDecomposition<float>(jobz, m, n, a, s, u, vt, info); }

// Returns Eigen values (replaces xgeev_)
template <typename T>
void subEigenValues(int *n, T *a, T *wr, T *wi, T *vr, int *info) 
{
    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (a, *n, *n, OuterStride<>(*n));

    EigenSolver<Matrix<T, Dynamic, Dynamic> > ces(AMap);
    *info = 1 - int(ces.info());
    Matrix<std::complex<T>, Dynamic, 1> w1 = ces.eigenvalues();
    Map<Matrix<T, Dynamic, 1> > wrMap (wr, w1.rows());
    Map<Matrix<T, Dynamic, 1> > wiMap (wi, w1.rows());
    Matrix<std::complex<T>, Dynamic, Dynamic> Vr = ces.eigenvectors();
    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > VrMap (vr, *n, Vr.cols(), OuterStride<>(1));
    wrMap = w1.real();
    wiMap = w1.imag();
    int j = 0;
    while (j < Vr.cols()) 
    {
        Matrix<T, Dynamic, 1> Xr = Vr.col(j).real();
        Matrix<T, Dynamic, 1> Xc = Vr.col(j).imag();
        if (Xc.isZero())
        {
            VrMap.col(j) = Xr;
            j++;
        }
        else
        {
            VrMap.col(j) = Xr;
            VrMap.col(j + 1) = Xc;
            j += 2;
        };
    }
}

void eigenValues(int *n, double *a, double *wr, double *wi, double *vr, int *info) { subEigenValues<double>(n, a, wr, wi, vr, info); }
void eigenValues(int *n, float *a, float *wr, float *wi, float *vr, int *info) { subEigenValues<float>(n, a, wr, wi, vr, info); }
