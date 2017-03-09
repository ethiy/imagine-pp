// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include "Imagine/LinAlg/MyEigen.h"
#include <Eigen/Dense>
using namespace Eigen;

//N'existe pas dans Eigen Blas
// Pas de calcul d'inverse avec ldlt dans eigen
//corriger
//info important car utilise dans SymMatrix.h
template <typename T>
void subSymInverse(int *n,T *ap,T *t,int *info) 
{
  symToMatrix(*n,ap,t);
  Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > apMap (t,*n,*n,OuterStride<>(*n));
  Matrix<T, Dynamic, Dynamic> Ai (*n,*n);
  Eigen::LDLT<Matrix<T, Dynamic, Dynamic> > ldlt(apMap);
  Matrix<T, Dynamic, Dynamic> id=Matrix<T, Dynamic, Dynamic>::Identity(*n,*n);
  for (int i=0; i<*n;i++) {
  Ai.col(i)=ldlt.solve(id.col(i));
  };
  *info=1-(apMap*Ai).isApprox(id);
  apMap=Ai;
}

void symInverse(int *n, double *ap, double *t, int *info) { subSymInverse<double>(n, ap, t, info); }
void symInverse(int *n, float *ap, float *t, int *info) { subSymInverse<float>(n, ap, t, info); }

//N'existe pas dans Eigen Blas
//pas de calcul d'inverse avec llt dans eigen
//On va donc resoudre AX=B avec B=(1,0,0,0...) puis B=(0,1,0,....) etc...
//Puis on constitue la matrice inverse avec les n colonnes
//corriger
//info important car utilise dans Matrix.h
template <typename T>
void subSymDPInverse(int *n,T *ap,T* t,int *info) 
{
  symToMatrix(*n,ap,t);
  Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > apMap (t,*n,*n,OuterStride<>(*n));
  Matrix<T, Dynamic, Dynamic> Ai (*n,*n);
  Eigen::LLT<Matrix<T, Dynamic, Dynamic> > llt(apMap);
  Matrix<T, Dynamic, Dynamic> id=Matrix<T, Dynamic, Dynamic>::Identity(*n,*n);
  for (int i=0; i<*n;i++) {
  Ai.col(i)=llt.solve(id.col(i));
  };
  *info=1-(apMap*Ai).isApprox(id);
  apMap=Ai;
}

void symDPInverse(int *n, double *ap, double *t, int *info) { subSymDPInverse<double>(n, ap, t, info); }
void symDPInverse(int *n, float *ap, float *t, int *info) { subSymDPInverse<float>(n, ap, t, info); }

// System of linear equations with packed symmetric matrix
template <typename T>
void subSymSolve(int *n,T *ap,int *,T *b,int *info) 
{
  T *t= new T [(*n)*(*n)];
  symToMatrix(*n,ap,t);
  Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (t,*n,*n,OuterStride<>(*n));
  Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > BMap (b,*n,1,OuterStride<>(*n));
  Eigen::LDLT<Matrix<T, Dynamic, Dynamic> > ldlt (AMap);
  Matrix<T, Dynamic, Dynamic> x=ldlt.solve(BMap);
  *info=1-(AMap*x).isApprox(BMap);
  BMap=x;
  delete [] t;
}

void symSolve(int *n, double *ap, int *ipiv, double *b, int *info) { subSymSolve<double>(n, ap, ipiv, b, info); }
void symSolve(int *n, float *ap, int *ipiv, float *b, int *info) { subSymSolve<float>(n, ap, ipiv, b, info); }

// Determinant
template <typename T>
T subDeterminant(int *m, int *n, T *A, int *info)
{
   Map<Matrix<T, Dynamic, Dynamic>,0, OuterStride<> > AMap (A,*m,*n,OuterStride<>(*m));
   Eigen::FullPivLU<Matrix<T, Dynamic, Dynamic> > lu(AMap);
   *info = 0;
   return(lu.determinant());
}

double determinant(int *m, int *n, double *A, int *info) { return subDeterminant<double>(m, n, A, info); }
float determinant(int *m, int *n, float *A, int *info) { return subDeterminant<float>(m, n, A, info); }

template <typename T>
T subSymDeterminant(int *n,T *ap,int *info) 
{
  T *t= new T [(*n)*(*n)];
  symToMatrix(*n,ap,t);
   Map<Matrix<T, Dynamic, Dynamic>,0, OuterStride<> > AMap (t,*n,*n,OuterStride<>(*n));
   Eigen::FullPivLU<Matrix<T, Dynamic, Dynamic> > lu(AMap);
  *info=1-AMap.isApprox(lu.reconstructedMatrix());
  delete[] t;
  return(lu.determinant());
} 

double symDeterminant(int *n, double *ap, int *info) { return subSymDeterminant<double>(n, ap, info); }
float symDeterminant(int *n, float *ap, int *info) { return subSymDeterminant<float>(n, ap, info); }
