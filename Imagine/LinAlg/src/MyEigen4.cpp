// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include "Imagine/LinAlg/MyEigen.h"
#include <Eigen/Dense>

using namespace Eigen;

//Existe dans Eigen Blas
//Experimental et pas de decomposition uplow='U' dans eigen et seulement pour les matrices def pos
//info important car utilise dans Matrix.h

// Cholesky decomposition (replaces xpotf2_)
template <typename T>
void subCholeskyDecomposition(const char* job, int *n, T* a, int *info)
{ 
    Map<Matrix<T, Dynamic, Dynamic> > AMap (a,*n,*n);
    Eigen::LLT<Matrix<T, Dynamic, Dynamic> > llt (AMap);
    AMap = (*job == 'L') ? llt.matrixLLT() : llt.matrixU();
    *info = int(llt.info());
};

void choleskyDecomposition(const char* job, int *n, double* a, int *info) { subCholeskyDecomposition<double>(job, n, a, info); }
void choleskyDecomposition(const char* job, int *n, float* a, int *info) { subCholeskyDecomposition<float>(job, n, a, info); }

// Norms
template <typename T>
T subMatrixNorm(char* norm, int *m, int *n, T *a, int *lda)
{
    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (a,*m,*n,OuterStride<>(*lda)); 

    T to_return = 0;
    switch (*norm)
    {
        case 'M':
            to_return = AMap.template lpNorm<Infinity>();
            break;
        case ('1'):
            to_return = (AMap.colwise().sum()).maxCoeff();
            break;
        case ('I'):
            to_return = (AMap.rowwise().sum()).maxCoeff();
            break;
        case ('F'):
            to_return = AMap.norm();
            break;
        default: assert(false);
    }

    return to_return;
}

double matrixNorm(char* norm, int *m, int *n, double *a, int *lda) { return subMatrixNorm<double>(norm, m, n, a, lda); }
float matrixNorm(char* norm, int *m, int *n, float *a, int *lda) { return subMatrixNorm<float>(norm, m, n, a, lda); }

// System solving by LU decomposition (replaces xgetrs_)
template <typename T>
void subLUSystemSolve(int *n,T *a,int *ipiv, T *b,int *info) 
{
  Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (a,*n,*n,OuterStride<>(*n));
  Map<Matrix<T, Dynamic, 1>, 0, InnerStride<1> > BMap (b,*n);
  Matrix<T, Dynamic, Dynamic> B = BMap;
  T nb = B.norm();
  // Eigen::FullPivLU<Matrix<T, Dynamic, Dynamic> > lu(AMap);

  // BMap = lu.solve(B);
  //  BMap = AMap.fullPivLu().solve(B);
  BMap = AMap.colPivHouseholderQr().solve(B);

  /* // test
  std::cout << "-- LU system solve : ||AX - B||_2 = " << (AMap * BMap - B).norm() << std::endl;
  std::cout << "A " << std::endl;
  printM(a, *n, *n);
  std::cout << "solution" << std::endl;
  printV(b, *n);
  std::cout << "AB " << std::endl;
  T* c = new T[*n];
  affinity(*n, *n, 1, a, b, 0, c, 'N');
  printV(c, *n);
  std::cout << "-- LU system solve : ||AX - B||_2 = " << (AMap * BMap - B).norm() << std::endl;
  delete[] c;
  */

  *info = ((AMap * BMap - B).norm() <= nb * 1.0e-3f) ? 0 : 1;

}

void LUSystemSolve(int *n,double *a,int *ipiv,double *b,int *info) { subLUSystemSolve<double>(n, a, ipiv, b, info); }
void LUSystemSolve(int *n,float *a,int *ipiv,float *b,int *info) { subLUSystemSolve<float>(n, a, ipiv, b, info); }

// System solving by QR decomposition (replaces xgels_)
template <typename T>
void subQRSystemSolve(int *m,int *n,T *a,T *b,int *info) 
{
    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (a, *m, *n, OuterStride<>(*m));
    Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > BMap (b, std::max(*m,*n), 1, OuterStride<>(std::max(*m, *n)));
    *info = 0;
    Eigen::HouseholderQR<Matrix<T, Dynamic, Dynamic> > qr(AMap);
    Matrix<T, Dynamic, Dynamic> x = qr.solve(BMap.block(0, 0, *m, 1));
    if(*m <= *n) *info = 1 - (AMap * x).isApprox(BMap.block(0, 0, *m, 1));
    BMap.block(0, 0, *n, 1) = x;
}

void QRSystemSolve(int *m, int *n, double *a, double *b, int *info) { subQRSystemSolve<double>(m, n, a, b, info); }
void QRSystemSolve(int *m, int *n, float *a, float *b, int *info) { subQRSystemSolve<float>(m, n, a, b, info); }

// QR factorization
template <typename T>
void subQRFactorization(int *m,int *n,int *k,T *a,T *r,int *info)
{
    Map<Matrix<T, Dynamic, Dynamic> > AMap (a, *m, *k);
    Map<Matrix<T, Dynamic, Dynamic> > RMap (r, *n, *k);
    Eigen::HouseholderQR<Matrix<T, Dynamic, Dynamic> > qr(AMap);
    Matrix<T, Dynamic, Dynamic> R1 = Matrix<T, Dynamic, Dynamic>::Zero(*m, *k);
    R1= qr.matrixQR().template triangularView<Upper>();
#ifdef _WIN32
    for(int i=0; i<*n; i++)
        for(int j=0; j<*k; j++)
            RMap(i,j) = R1(i,j);
#else
    RMap= R1.block(0, 0, *n, *k);
#endif
    Matrix<T, Dynamic, Dynamic> q = qr.householderQ();
    Matrix<T, Dynamic, Dynamic> original = q.block(0, 0, *m, *n) * RMap;
    *info=AMap.isApprox(original);
    if (*n == *k)
#ifdef _WIN32
    for(int i=0; i<*m; i++)
        for(int j=0; j<*k; j++)
            AMap(i,j) = q(i,j);
#else
        AMap=q.block(0, 0, *m, *k);
#endif
    else
    {
        Map<Matrix<T, Dynamic, Dynamic> > QMap (a, *m, *m);
        QMap = q;
    }
}

void QRFactorization(int *m, int *n, int *k, double *a, double *r, int *info) { subQRFactorization<double>(m, n, k, a, r, info); }
void QRFactorization(int *m, int *n, int *k, float *a, float *r, int *info) { subQRFactorization<float>(m, n, k, a, r, info); }

// Reciprocal condition number of triangular matrix
template <typename T>
void subConditionNumber(int *n,T *a,int *lda,T *rcond,int *info)
{
    char x = '1';
    T l = (matrixNorm(&x, n, n, a, lda)); 
    if (l != 0)
    {
        *rcond = 1 / l;
        *info = 0;
    }
    else *info = 1;
}

void conditionNumber(int *n, double *a, int *lda, double *rcond, int *info) { subConditionNumber<double>(n, a, lda, rcond, info); }
void conditionNumber(int *n, float *a, int *lda, float *rcond, int *info) { subConditionNumber<float>(n, a, lda, rcond, info); }
