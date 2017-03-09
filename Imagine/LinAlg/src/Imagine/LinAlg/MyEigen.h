// ===========================================================================
// Imagine++ Libraries
// Copyright (C); Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

void symToMatrix(int n, const double *ap, double *t);
void symToMatrix(int n, const float *ap, float *t);

// Vectors equalization (replaces xcopy)
void equalize(int n, const double *s, int a, double *t, int b);
void equalize(int n, const float *s, int a, float *t, int b);

// Linear combination alpha * X + Y
void combine(int n, double alpha, const double *X, double *Y);
void combine(int n, float alpha, const float *X, float *Y);

// Scalar product
double scalarProduct(int n, const double *X, const double *Y);
float scalarProduct(int n, const float *X, const float *Y);

// Product by a number
void multiply(int n, double alpha, double *X);
void multiply(int n, float alpha, float *X);

// Norm 2 (euclidian)
double squaredNorm(int n, const double *X);
float squaredNorm(int n, const float *X);

// Affine transformation Y <- alpha * [A, A transpose, A adjoint] * X + beta * B (replaces xgemv)
void affinity(int m, int n, double alpha, const double *A, const double *X, double beta, double *Y, char t);
void affinity(int m, int n, float alpha, const float *A, const float *X, float beta, float *Y, char t);

// Matrix product C <- alpha * [A, A transpose, A adjoint] * [B, B transpose, B adjoint] + beta * C (replaces xgemm)
void matrixProduct(int m, int n, int K, double alpha, const double *A, int lda, const double *B, int ldb, double beta, double *C, char t1, char t2);
void matrixProduct(int m, int n, int K, float alpha, const float *A, int lda, const float *B, int ldb, float beta, float *C, char t1, char t2);

// Matrix/vector product (replaces xspmv)
void vectorProduct(int n,double alpha,const double  *ap,const double *x,double beta,double* y);
void vectorProduct(int n,float alpha,const float *ap,const float *x,float beta,float* y);

// LU-inverse
void matrixInverse(int *n, double *a,int *lda,int *ipiv,int *info);
void matrixInverse(int *n, float *a,int *lda,int *ipiv,int *info);

//corriger
//info=0 si succès, -i si ieme parametre illegal, i si bdsdc ne converge pas
//info important car utilisé dans Matrix.h
// Singular values decomposition (SVD) (replaces xgesdd_)
/* *jobz est inusité et est présent dans la signature de Imagine::svd... */
void singularValuesDecomposition(const char *jobz,int *m,int *n, double *a, double *s, double *u, double *vt, int *info);
void singularValuesDecomposition(const char *jobz,int *m,int *n, float *a, float *s, float *u, float *vt, int *info);

//Non stable en Eigen (experimental);
//info important car utilisé dans Matrix.h
// Returns Eigen values
void eigenValues(int *n, double *a, double *wr, double *wi, double *vr, int *info);
void eigenValues(int *n, float *a, float *wr, float *wi, float *vr, int *info);

//Experimental et pas de décomposition uplow='U' dans eigen et seulement pour les matrices def pos
//info important car utilisé dans Matrix.h
// Cholesky decomposition (replaces xpotf2_)
void choleskyDecomposition(const char* job, int *n, double* a, int *info);
void choleskyDecomposition(const char* job, int *n, float* a, int *info);

// Matrix norms (replaces xlange_)
double matrixNorm(char* norm, int *m, int *n, double *a, int *lda);
float matrixNorm(char* norm, int *m, int *n, float *a, int *lda);

//info important car utilisé dans Matrix.h
// System solving by LU decomposition
void LUSystemSolve(int *n, double *a, int *ipiv, double *b, int *info);
void LUSystemSolve(int *n, float *a, int *ipiv, float *b, int *info);

//corriger: info + retour b
//info important car utilisé dans Matrix.h
// System solving by QR decomposition
void QRSystemSolve(int *m, int *n, double *a, double *b, int *info);
void QRSystemSolve(int *m, int *n, float *a, float *b, int *info);

//Besoin de la précédente
//corriger
//info important car utilisé dans Matrix.h
void QRFactorization(int *m, int *n, int *k, double *a, double *r, int *info);
void QRFactorization(int *m, int *n, int *k, float *a, float *r, int *info);

//Il faut reconstituer la matrice
//corriger
//info important car utilisé dans Matrix.h
void conditionNumber(int *n, double *a, int *lda, double *rcond, int *info);
void conditionNumber(int *n, float *a, int *lda, float *rcond, int *info);

// Pas de calcul d'inverse avec ldlt dans eigen
//#if 0
//info important car utilisé dans SymMatrix.h
void symInverse(int *n, double *ap, double *t, int *info);
void symInverse(int *n, float *ap, float *t, int *info);

//pas de calcul d'inverse avec llt dans eigen
//On va donc resoudre AX=B avec B=(1,0,0,0...); puis B=(0,1,0,....); etc...
//Puis on constitue la matrice inverse avec les n colonnes
//corriger
//#if 0
//info important car utilisé dans Matrix.h
void symDPInverse(int *n, double *ap, double *t, int *info);
void symDPInverse(int *n, float *ap, float *t, int *info);

//SVD+valeures propres+vecteurs propres
//corriger
//info important car utilisé dans SymMatrix.h
void symEigenValues(int *n, double *ap, double *w, double *z, int* info);
void symEigenValues(int *n, float *ap, float *w, float *z, int* info);

//Besoin de 
//corriger
//info important car utilisé dans SymMatrix.h
// Linear system solve
void symSolve(int *n, double *ap, int *ipiv, double *b, int *info);
void symSolve(int *n, float *ap, int *ipiv, float *b, int *info);

// Determinant
double determinant(int *m, int *n, double *A, int *info);
float determinant(int *m, int *n, float *A, int *info);

double symDeterminant(int *n, double *ap, int *info);
float symDeterminant(int *n, float *ap, int *info);
