// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include "Imagine/LinAlg/MyEigen.h"
#include <Eigen/Dense>
using namespace Eigen;

// Eigen value decomposition of packed symmetric matrix
template <typename T>
void subSymEigenValues(int *n,T *ap,T *w,T *z,int *info) 
{
  T *t= new T [(*n)*(*n)];
  symToMatrix(*n,ap,t);
  Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > AMap (t,*n,*n,OuterStride<>(*n));
   Eigen::JacobiSVD<Matrix<T, Dynamic, Dynamic> > svd (AMap, ComputeFullU | ComputeFullV);
   Map<Matrix<T, Dynamic, Dynamic>, 0, OuterStride<> > zMap (z,*n,*n,OuterStride<>(*n));
   Map<Matrix<T, Dynamic, 1>, 0, InnerStride<0> > wMap (w, *n);
   wMap=svd.singularValues();
   zMap=svd.matrixU();
   Matrix<T, Dynamic, Dynamic> v=svd.matrixV();
   *info=1-AMap.isApprox(zMap * wMap.asDiagonal() * v.adjoint());
   for (int i=0;i<*n;i++){
     if (v.col(i).isApprox(-zMap.col(i)))
     {
       wMap(i)=-wMap(i);
     }
   };
   delete[] t;
}

void symEigenValues(int *n, double *ap, double *w, double *z, int* info) { subSymEigenValues<double>(n, ap, w, z, info); }
void symEigenValues(int *n, float *ap, float *w, float *z, int* info) { subSymEigenValues<float>(n, ap, w, z, info); }

