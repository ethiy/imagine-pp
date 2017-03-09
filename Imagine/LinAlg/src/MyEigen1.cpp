// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include "Imagine/LinAlg/MyEigen.h"
#include <Eigen/Dense>
#include <iostream>
using namespace Eigen;

template <typename T>
void subSymToMatrix (int n, const T *ap, T *t)
{
    for (int i = 0 ; i < n ; i++)
        for (int j = 0 ; j <= i ; j++)
        {
            t[i + n * j] = ap[j + (i * (i + 1) / 2)];
            t[j + n * i] = t[i + n * j];
        }
}

void symToMatrix(int n, const double *ap, double *t) { subSymToMatrix<double>(n, ap, t); }
void symToMatrix(int n, const float *ap, float *t) { subSymToMatrix<float>(n, ap, t); }

// Vectors equalization (replaces xcopy)
template <typename T>
void subEqualize(int n, const T *s, int a, T *t, int b)
{
    Map<const Matrix<T, Dynamic, 1>, 0, InnerStride<> > sMap (s, n, InnerStride<>(a));
    Map<Matrix<T, Dynamic, 1>, 0, InnerStride<> > tMap (t, n, InnerStride<>(b));
    tMap = sMap;
}

void equalize(int n, const double *s, int a, double *t, int b) { subEqualize<double>(n, s, a, t, b); }
void equalize(int n, const float *s, int a, float *t, int b) { subEqualize<float>(n, s, a, t, b); }

// Linear combination alpha * X + Y
template <typename T>
void subCombine(int n, T alpha, const T *X, T *Y) 
{ 
    Map<const Matrix<T, Dynamic, 1>, 0, InnerStride<> > sMap (X, n, InnerStride<>(1));
    Map<Matrix<T, Dynamic, 1>, 0, InnerStride<> > tMap (Y, n, InnerStride<>(1));
    tMap = alpha * sMap + tMap;
}

void combine(int n, double alpha, const double *X, double *Y) { subCombine<double>(n, alpha, X, Y); }
void combine(int n, float alpha, const float *X, float *Y) { subCombine<float>(n, alpha, X, Y); }

// Scalar product
template <typename T>
T subScalarProduct(int n, const T *X, const T *Y)
{ 
    Map<const Matrix<T, Dynamic, 1>, 0, InnerStride<> > sMap (X, n, InnerStride<>(1));
    Map<const Matrix<T, Dynamic, 1>, 0, InnerStride<> > tMap (Y, n, InnerStride<>(1));
    double s = sMap.dot(tMap);
    return T(s);
}

double scalarProduct(int n, const double *X, const double *Y) { return subScalarProduct<double>(n, X, Y); }
float scalarProduct(int n, const float *X, const float *Y) { return subScalarProduct<float>(n, X, Y); }

// Product by a number
template <typename T>
void subMultiply(int n, T alpha, T *X)
{
    Map<Matrix<T, Dynamic, 1>, 0, InnerStride<> > XMap (X, n, InnerStride<>(1));
    XMap = alpha * XMap; 
}

void multiply(int n, double alpha, double *X) { subMultiply<double>(n, alpha, X); }
void multiply(int n, float alpha, float *X) { subMultiply<float>(n, alpha, X); }

// Norm 2 (euclidian)
template <typename T>
T subSquaredNorm(int n, const T *X)
{
    Map<const Matrix<T, Dynamic, 1>, 0, InnerStride<> > XMap (X, n, InnerStride<>(1));
    return ((T) XMap.squaredNorm());
}

double squaredNorm(int n, const double *X) { return subSquaredNorm<double>(n, X); }
float squaredNorm(int n, const float *X) { return subSquaredNorm<float>(n, X); }

// Affine transformation Y <- alpha * [A, A transpose, A adjoint] * X + beta * B (replaces xgemv)
template <typename T>
void subAffinity(int m, int n, T alpha, const T *A, const T *X, T beta, T *Y, char t)
{
    Map<const Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (A, m, n, OuterStride<>(m));

    if (!(t == 'T' || t == 'C'))
    {
        int tmp = m;
        m = n;
        n = tmp;
    }

    Map<const Matrix<T, Dynamic, 1>, 0, InnerStride<> > XMap (X, m, InnerStride<>(1));
    Map<Matrix<T, Dynamic, 1>, 0, InnerStride<> > YMap (Y, n, InnerStride<>(1));

    if (t == 'T') YMap = alpha * AMap.transpose() * XMap + beta * YMap;
    else if (t == 'C') YMap = alpha * AMap.adjoint() * XMap + beta * YMap;
    else YMap = alpha * AMap * XMap + beta * YMap;
}

void affinity(int m, int n, double alpha, const double *A, const double *X, double beta, double *Y, char t) { subAffinity<double>(m, n, alpha, A, X, beta, Y, t); }
void affinity(int m, int n, float alpha, const float *A, const float *X, float beta, float *Y, char t) { subAffinity<float>(m, n, alpha, A, X, beta, Y, t); }

// Matrix product C <- alpha * [A, A transpose, A adjoint] * [B, B transpose, B adjoint] + beta * C (replaces xgemm)
template <typename T>
void subMatrixProduct(int m, int n, int K, T alpha, const T *A, int lda, const T *B, int ldb, T beta, T *C, char t1, char t2) 
{

    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > CMap (C, m, n, OuterStride<>(m));

    if (!(t1 == 'T' || t1 == 'C'))
    {
        int tmp = m;
        m = K;
        K = tmp;
    }

    Map<const Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (A, K, m, OuterStride<>(lda));

    if (!(t1 == 'T' || t1 == 'C'))
    {
        int tmp = m;
        m = K;
        K = tmp;
    }

    if (!(t2 == 'T' || t2 == 'C'))
    {
        int tmp = n;
        n = K;
        K = tmp;
    }

    Map<const Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > BMap (B, n, K, OuterStride<>(ldb));

    if (t1 == 'T') 
        if (t2 == 'T') CMap = alpha * AMap.transpose() * BMap.transpose() + beta * CMap;
        else if (t2 == 'C') CMap = alpha * AMap.transpose() * BMap.adjoint() + beta * CMap;
        else CMap = alpha * AMap.transpose() * BMap + beta * CMap;
    else if (t1 == 'C')
        if (t2 == 'T') CMap = alpha * AMap.adjoint() * BMap.transpose() + beta * CMap;
        else if (t2 == 'C') CMap = alpha * AMap.adjoint() * BMap.adjoint() + beta * CMap;
        else CMap = alpha * AMap.adjoint() * BMap + beta * CMap;
    else
        if (t2 == 'T') CMap = alpha * AMap * BMap.transpose() + beta * CMap;
        else if (t2 == 'C') CMap = alpha * AMap * BMap.adjoint() + beta * CMap;
        else CMap = alpha * AMap * BMap + beta * CMap;
} 

void matrixProduct(int m, int n, int K, double alpha, const double *A, int lda, const double *B, int ldb, double beta, double *C, char t1, char t2) { subMatrixProduct<double>(m, n, K, alpha, A, lda, B, ldb, beta, C, t1, t2); }
void matrixProduct(int m, int n, int K, float alpha, const float *A, int lda, const float *B, int ldb, float beta, float *C, char t1, char t2) { subMatrixProduct<float>(m, n, K, alpha, A, lda, B, ldb, beta, C, t1, t2); }

// Matrix/vector product (replaces xspmv)
template <typename T>
void subVectorProduct(int n,T alpha,const T *ap,const T *x,T beta,T* y)
{
    T* t=new T [n * n];
    Map<const Matrix<T, Dynamic, 1>, 0, InnerStride<> > XMap (x, n, InnerStride<>(1));
    Map<Matrix<T, Dynamic, 1>, 0, InnerStride<> > YMap (y, n, InnerStride<>(1));
    symToMatrix(n, ap, t);
    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > apMap (t, n, n, OuterStride<>(n));
    YMap = alpha * apMap * XMap + beta * YMap;
    delete[] t;
}

void vectorProduct(int n,double alpha,const double *ap, const double *x,double beta,double* y) { subVectorProduct<double>(n, alpha, ap, x, beta, y); }
void vectorProduct(int n,float alpha,const float *ap,const float *x,float beta,float* y) { subVectorProduct<float>(n, alpha, ap, x, beta, y); }

// TODO:
//info=0 si succes, -i si le ieme parametre a une valeure illegale, i si u(i,i);=0 (transformation LU impossible = mineurs principaux tous nuls)
// LU-inverse
template <typename T>
void subMatrixInverse(int *n, T *a,int *lda,int *ipiv,int *info) 
{ 
    Map<Matrix<T, Dynamic, Dynamic> > AMap (a,*n,*n);
    Map<VectorXi> pMap (ipiv, *n);
    Eigen::FullPivLU<Matrix<T, Dynamic, Dynamic> > lu(AMap);
    MatrixXi P = lu.permutationP();
    MatrixXi Pi = pMap;

    for (int i = 0 ; i < P.rows() - 1 ; i++)
        for (int j = i + 1 ; j < P.cols() ; j++)
            if (P(i, j) == 1) { Pi(i) = j; Pi(j) = i; };

    //pMap = Pi;

    if(lu.isInvertible() && AMap.isApprox(lu.reconstructedMatrix()))
    {
        AMap = lu.inverse();
        *info = 0;
    }
    else *info = 1;
}

void matrixInverse(int *n, double *a,int *lda,int *ipiv,int *info) { subMatrixInverse<double>(n, a, lda, ipiv, info); }
void matrixInverse(int *n, float *a,int *lda,int *ipiv,int *info) { subMatrixInverse<float>(n, a, lda, ipiv, info); }











