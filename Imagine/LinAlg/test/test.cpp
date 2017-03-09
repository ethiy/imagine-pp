// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// So far, this file is aimed at using each function at least once.
// Hence, it is provided more as a test for compilation than as a true example...

#include <Imagine/Common.h>     
#include <Imagine/LinAlg.h>

#include <cmath>
#include <iostream>

using namespace Imagine;
using namespace std;

template <typename T>
void vectors() {
    // NB: Plus all functions of Array class!
    cout << "Vector functions" << endl;
    Vector<T> a;                     // non allocated
    Vector<T> b(4);                  // allocated with specified size
    T t[]={1,2,3};                   // pre-allocated
    Vector<T> e(t,3);
    T *t2=new T[3];
    Vector<T> e2(t2,3,true);         // ...
    Vector<T> c(b);                  // copy constructor
    b=Vector<T>::Zero(4);            // Vector with constant 0 value
    b.fill(1.);                      // filling with constant value
    c=b;                             // assignment
    a=b.clone();                     // cloning (fresh memory)
    c=b.getSubVect(1,2);             // sub vector
    c=b.getSubVectRef(1,2);          // sub vector ref (beware of restrictions!)
    c=a+b;                           // +
    c+=b;                            // +=
    c=a-b;                           // -
    c-=b;                            // -=
    c=a+1;                           // + scalar
    c+=1;                            // += scalar
    c=a-1;                           // - scalar
    c-=1;                            // -= scalar
    c=-a;                            // unary -
    c=a*2;                           // * scalar 
    c*=2;                            // *= scalar 
    c=a/2;                           // / scalar 
    c/=2;                            // /= scalar 
    c=1+a;                           // scalar + Vector
    c=1-a;                           // scalar - Vector
    c=2*a;                           // scalar * Vector
    T x;
    x=a*b;                           // scalar product
    x=norm2(a);                      // squared Euclidean norm
    x=norm(a);                       // Euclidean norm
    c.normalize();                   // Euclidean in-place normalization
    c=normalized(a);                 // Euclidean normalization
    x=maxNorm(a);                    // Maximum norm
    x=sum(a);                        // sum of values
    x=mean(a);                       // mean of values
    Vector<T> K(2);
    K.fill(1);
    c=convolution(K,a);              // Full Convolution 
    c=truncConvolution(K,a,1);       // Truncated convolution
    Vector<T> v1(4),v2(4);
    v1.fill(1);v2.fill(2);
    Matrix<T> O=outerProduct(v1,v2); // outer product
    a[1]=2;b[2]=2;
    x=correlation(a,b);              // correlation
    x=normalizedCorrelation(a,b);    // normalized correlation
    double y=dist(a,b);              // distance*/
}

template <typename T>
void matrices() {
    // NB: Plus all functions of MultiArray class!
    cout << "Matrix functions" << endl;
    Matrix<T> A;                         // non allocated
    Matrix<T> B(3,4);                    // allocated with specified size
    for(int i=0; i<3; i++)
        for(int j=0; j<4; j++)
            B(i,j)=rand()/(T)RAND_MAX;
    T tt[]={1,2,3,4,5,6};                // pre-allocated
    Matrix<T> D(tt,3,2);        
    T *tt2=new T[6];
    for(int i=0; i<6; i++)
        tt2[i]=rand()/(T)RAND_MAX;
    Matrix<T> D2(tt2,3,2,true);          // ...
    Matrix<T> C(B);                      // copy constructor
    A=B;                                 // assignment
    A=B.clone();                         // cloning (fresh memory)
    int m=A.nrow(),n=A.ncol();           // Dimensions
    A=Matrix<T>::Zero(3,4);              // Matrix with constant 0 value
    A.fill(1);                           // filling with constant value
    Matrix<T> I=Matrix<T>::Identity(4);  // Identity
    Vector<T> d(tt,6);                   // diagonal
    B=Diagonal(d);                       // ...
    A(1,2)=3;
    Vector<T> v,w;
    v=A.getCol(2);                       // Get column
    A.setCol(1,v);                       // Set column
    v=A.getRow(1);                       // Get row
    A.setRow(2,v);                       // Set row
    v=A.getDiagonal();                   // Get diagonal
    A.setDiagonal(v);                    // Set diagonal
    v=A.getColRef(2);                    // Vector pointing to column (beware of restrictions!)
    v=A.getSubColRef(2,1,2);             // Vector pointing to sub-column (beware of restrictions!)
    B=A.getSubMat(1,2,1,2);              // Get sub matrix
    B=A.getColsRef(1,2);                 // Matrix pointing to part of columns (beware of restrictions!)
    v=Vector<T>(4).fill(1);
    w=A*v;                               // matrix * vector
    v=tmult(A,w);                        // matrix^T * vector
    A=A*transpose(A);                    // transpose
    A(1,2)=2;
    B=inverse(A);                        // inverse
    Matrix<T>A32(3,2); A32.fill(1.);
    Matrix<T>A23(2,3); A23.fill(1.);
    Matrix<T>A24(2,4); A24.fill(1.);
    Matrix<T>A42(4,2); A42.fill(1.);
    Matrix<T> A34;
    A34=A32*A24;                         // matrix * matrix
    A34=tmult(A23,A24);                  // matrix^T * matrix
    A34=multt(A32,A42);                  // matrix * matrix^T
    A34=tmultt(A23,A42);                 // matrix^T * matrix^T
    C=A+B;                               // +
    C+=B;                                // +=
    C=A-B;                               // -
    C-=B;                                // -=
    C=-A;                                // unary -
    C=A*2;                               // * scalar 
    C*=2;                                // *= scalar 
    C=A/2;                               // / scalar 
    C/=2;                                // /= scalar 
    C=2*A;                               // scalar * Matrix
    T a;
    a=dot(A,C);                          // scalar product
    a=norm(A);                           // frobenius norm
    a=norm(A,'1');                       // 1-norm
    a=norm(A,'I');                       // infinity-norm
    a=norm(A,'M');                       // max norm...
    a=rcond(A);                          // reciprocal condition number

    Vector<T> S;                         // Singular value decomposition
    Matrix<T> U,Vt;
    svd(A,U,S,Vt);                           // square matrix
    cout << "SVD check 1: " 
        << norm(A-U*Diagonal(S)*Vt) << endl; // Check result
    svd(A34,U,S,Vt);                         // non square matrix
    cout << "SVD check 2: " 
         << norm(A34-U*Matrix<T>::Zero(3,4).setDiagonal(S)*Vt) << endl; // Check result
    svd(A34,U,S,Vt,true);                    // non square, complete U and Vt
    cout << "SVD check 3: " 
        << norm(Vt*transpose(Vt)-Matrix<T>::Identity(4)) << endl; // Check Vt...
    
    initRandom(1);                                             // Linear solve
    A.setSize(5,5);
    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            A(i,j)=T(doubleRandom());
    Vector<T> b(5),x;
    for (int j=0;j<5;j++)
            b[j]=T(doubleRandom());

    x=linSolve(A,b);


    cout << "Square system: " << norm(A*x-b) << endl;          // Check
    C=A.getSubMat(0,5,0,4); 
    x=linSolve(C,b);
    cout << "Over determined system: " << norm(C*x-b) << endl; // Check (min possible but not 0)
    C=A.getSubMat(0,4,0,5);
    x=linSolve(C,b.getSubVect(0,4));
    cout << "Minimum norm under determined system: " 
        << norm(C*x-b.getSubVect(0,4)) << " " << norm(x) << endl; // Check (min |x| possible but not 0)...

    x=pseudoInverse(A)*b;                                      // pseudo-inverse
    cout << "Pseudo inverse, square: " << norm(A*x-b) << endl; // Check it, square case
    C=A.getSubMat(0,5,0,4); 
    x=pseudoInverse(C)*b;
    cout << "Pseudo inverse, over determined: " << norm(C*x-b) << endl; // Check it, over determined case
    C=A.getSubMat(0,4,0,5);
    x=pseudoInverse(C)*b.getSubVect(0,4);
    cout << "Pseudo inverse, under determined: " 
        << norm(C*x-b.getSubVect(0,4)) << " " << norm(x) << endl;       // Check it, under determined case...

    Matrix<T> Q,R;                        // QR decomposition
    QR(D,Q,R);
    cout << "QR " << norm(D-Q*R) << endl; // check thin QR
    QR(D,Q,R,true);
    cout << "QR " << norm(D-Q*R) << endl; // check full QR...


    B=A*transpose(A);   //symmetric positive-definite
    Matrix<T> L=cholesky(B);                                     // Cholesky decomposition
    cout << "Lower Cholesky " << norm(B-L*transpose(L)) << endl; // Check lower
    U=cholesky(B,false);
    cout << "Upper Cholesky " << norm(B-transpose(U)*U) << endl; // Check upper...

    cout << "A=" << A << endl;
    cout << "Det: " << det(A) << endl;
    cout << "Determinants: " << det(A)*det(inverse(A))-1 << endl;// Determinant
    cout << "Determinants: " << det(B)*det(inverse(B))-1 << endl;// Check sym pos-def acceleration...

    ofstream out("tmp.txt"); // ASCII write
    out << A << endl;        // ...
    out.close();
    ifstream in("tmp.txt");  // ASCII read
    in >> A;                 // ...
    in.close(); 

}

template <typename T>
void symMatrices() {
    // NB: Plus all functions of Array class!
    cout << "SymMatrix functions" << endl;
    SymMatrix<T> A;                     // non allocated
    SymMatrix<T> B(10);                 // allocated with specified size
    SymMatrix<T> C(B);                  // copy constructor
    T t[]={1,2,3,4,5};                  // pre-allocated
    SymMatrix<T> D(t,3);
    T *t2=new T[5];
    SymMatrix<T> D2(t2,3,true);         // ...
    Matrix<T> E(4,4);
    SymMatrix<T> F(E);                  // conversion Matrix -> SymMatrix
    F=B;                                // assignment
    F=B.clone();                        // cloning (fresh memory)
    F.setSize(5);                       // setSize
    int nr=F.nrow(),nc=F.ncol();        // numbers of rows and columns (both equal to specified size!)
    F.fill(2);                          // filling with constant value
    F=SymMatrix<T>::Zero(5);            // Matrix with constant 0 value
    F=SymMatrix<T>::Identity(5);        // Identity
    T a=F(2,2);                         // read access
    F(2,3)=a;                           // write access
    Matrix<T> G=F.getSubMat(1,3,0,4);   // Get sub matrix
    Vector<T> d=F.getDiagonal();        // Get diagonal
    F.fill(1);F(0,0)=2;F(0,1)=3;F(1,2)=2;F(2,3)=4;F(3,4)=-1;
    Vector<T> v1=Vector<T>(5).fill(2);
    Vector<T> v2=F*v1;                  // matrix * vector
    SymMatrix<T> invF=inverse(F);                                // inverse
    cout << "Inverse: " << norm(F*invF-Matrix<T>::Identity(5)) << endl;// ...
    cout << "Determinant: " << det(F)*det(invF)-1 << endl;       // determinant
    Matrix<T> Q;                                                 // Eigen values
    Vector<T> Lambda;
    EVD(F,Q,Lambda);
    cout << "Check EVD: "
        << norm(Q*transpose(Q)- Matrix<T>::Identity(5)) << " "
        << norm(Q*Diagonal(Lambda)*transpose(Q)-F) << endl;      // ...
    
    F=F*F;
    invF=posDefInverse(F);                          // positive-definite inverse
    cout << "Inverse: " << norm(F*invF-Matrix<T>::Identity(5)) << endl; // ...
    
    G.setSize(5);
    G.fill(3);
    Matrix<T> P(F);                     // conversion SymMatrix -> Matrix
    P=F*G;                              // symmatrix * symmatrix
    P=P*F;                              // matrix * symmatrix
    P=F*P;                              // symmatrix * matrix
    F=F+G;                              // +
    F+=G;                               // +=
    F=F-G;                              // -
    F-=G;                               // -=
    F=F*2;                              // * scalar
    F*=2;                               // *= scalar
    F=2*F;                              // scalar * SymMatrix
    F=F/2;                              // / scalar
    F/=2;                               // /= scalar
    F=-F;                               // unary -
    
    Vector<T> b=Vector<T>(5).fill(1);   // Linear solve
    Vector<T> x=linSolve(F,b);
    cout << norm(F*x-b) << endl;        // ...
    
    ofstream out("tmp.bin",ios::binary);    // binary write
    F.write(out);                           // ...
    out.close();
    ifstream in("tmp.bin",ios::binary);     // binary read
    F.read(in);                             // ...
    in.close();
    out.open("tmp.txt");                    // ASCII write
    out << F << endl;                       // ...
    out.close();
    in.open("tmp.txt");                     // ASCII read
    in >> F;                                // ...
    in.close();
    
}

// Functions related to FMatrix in LinAlg
template <typename T>
void fmatrices() {
    cout << "FMatrix functions" << endl;
    FMatrix<T,3,4> A( T(1) );
    A(1,1)=A(1,2)=A(2,1)=T(3);
    FMatrix<T,3,3> A2=A*transpose(A);
    A2(1,2)=2;
    A2=inverseFMatrix(A2);               // test fast call to direct inversion
    FMatrix<T,4,4> A3=transpose(A)*A;
    A3(1,2)=12;A3(1,1)=0;A3(0,0) = 4;
    cout << "A3=" << A3 << endl;
    FMatrix<T,4,4> A4 = inverseFMatrix(A3);               // inverse
    cout << "A3*A4=" << A3*A4 << endl;

    FVector<T,3> S;                      // Singular value decomposition:
    FMatrix<T,3,3> U, Vt;
    svd(A2,U,S,Vt);                      // -square
    cout << "SVD check 1: " 
         << norm(A2-U*Diagonal(S)*Vt) << endl;
    FMatrix<T,4,4> Vt2;
    svd(A,U,S,Vt2);                      // -non square
    FMatrix<T,3,4> S2(T(0));
    for(int i=0; i < 3; i++)
        S2(i,i) = S[i];
    cout << "SVD check 2: " 
         << norm(A-U*S2*Vt2) << endl;
    svd(A,U,S,Vt2,true);                 // non square matrix, complete U and Vt
    cout << "SVD check 3: "              // Check Vt...
         << norm(Vt2*transpose(Vt2)-FMatrix<T,4,4>::Identity()) << endl;
    
    initRandom(1);                       // Linear solve:
    FMatrix<T,5,5> B;
    for (int i=0;i<5;i++)
        for (int j=0;j<5;j++)
            B(i,j)=T(doubleRandom());
    FVector<T,5> b,x;
    for (int j=0;j<5;j++)
        b[j]=T(doubleRandom());
    x=linSolve(B,b);
    cout << "Square system: " << norm(B*x-b) << endl; // -square
    FMatrix<T,5,4> C( B.data() );
    FVector<T,4> x2=linSolve(C,b);
    cout << "Over determined system: " 
         << norm(C*x2-b) << endl;                   // -over-determined (min possible but not 0)
    FMatrix<T,4,5> D( B.data() );
    FVector<T,4> d(b.data());
    FVector<T,5> x3=linSolve(D,d);
    cout << "Minimum norm under determined system: " 
        << norm(D*x3-d) << " " << norm(x3) << endl; // -under-determined (min |x| possible but not 0)...

    x=pseudoInverse(B)*b;                         // Pseudo-inverse:
    cout << "Pseudo inverse, square: " 
         << norm(B*x-b) << endl;                  // -square case
    x2=pseudoInverse(C)*b;     
    cout << "Pseudo inverse, over determined: " 
         << norm(C*x2-b) << endl;                 // -over determined case
    x3=pseudoInverse(D)*d; // Erreur quand passage en double
    cout << "Pseudo inverse, under determined: " 
        << norm(D*x3-d) << " " << norm(x3) << endl; // -under determined case...

    T tt[]={1,2,3,4,5,6};                           // pre-allocated
    FMatrix<T,3,2> D2(tt);      
    FMatrix<T,3,2> Q; FMatrix<T,2,2> R;             // QR decomposition:
    QR(D2,Q,R);
    cout << "QR " << norm(D2-Q*R) << endl;          // -thin QR
    FMatrix<T,3,3> Q2; FMatrix<T,3,2> R2;
    QRAll(D2,Q2,R2);
    cout << "QR " << norm(D2-Q2*R2) << endl;        // -full QR...

    FMatrix<T,5,5> E=B*transpose(B);                // sym pos-def
    FMatrix<T,5,5> L=cholesky(E);                   // Cholesky decomposition:
    cout << "Lower Cholesky " 
         << norm(E-L*transpose(L)) << endl;         // -lower
    FMatrix<T,5,5> V=cholesky(E,false);
    cout << "Upper Cholesky " 
         << norm(E-transpose(V)*V) << endl;         // -upper...
    
    cout << "Determinants: "     // Determinant
         << detFMatrix(B)*detFMatrix(inverseFMatrix(B))-1 << endl;
    cout << "Determinants: "                        
         << detFMatrix(E)*detFMatrix(inverseFMatrix(E))-1 << endl;
                                 // Check sym pos-def acceleration...

}

int main() {
    vectors<float>();
    vectors<double>();
    matrices<float>();
    matrices<double>();
    symMatrices<float>();
    symMatrices<double>();
    fmatrices<float>();
    fmatrices<double>();
    waitKey();
    return 0;
}
