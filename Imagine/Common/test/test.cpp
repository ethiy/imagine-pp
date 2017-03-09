// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// So far, this file is aimed at using each function at least once.
// Hence, it is provided more as a test for compilation than as a true example...

#include <Imagine/Common.h>

#include <iostream>
#include <fstream>

using namespace std;
using namespace Imagine;

void base() {
    cout << "Imagine++ version is " << VERSION << endl;                                                 // Version number
    cout << "File named xxx in source path is replaced by: " << srcPath("xxx") << endl;               // C source path
    string name="xxx";                                                                                  // String source path
    cout << "File named string xxx in source path is replaced by: " << stringSrcPath(name) << endl;        // ...
}

void fArrays() {
    cout << "Testing FArray functions!" << endl;
    FArray<char,3> a;                       // uninitialized 
    FArray<char,3> b('.');                  // filled with constant value
    char tt[]={'a','b','c'};                // filled from C array
    FArray<char,3> c(tt);                   // (copying array into fresh memory)
    FArray<char,3> dd(c);                   // copy constructor
    FArray<char,3> di(c);                   // copy from different type
    FArray<char,2> e('a','b');              // alias for 2D case
    FArray<char,3> f('a','b','c');          // alias for 3D case
    a.fill('x');                            // Fills with constant value
    dd.copy(tt);                            // Copies C array into FArray
    di.copy(tt);                            // Copies C array of different type into FArray
    dd=b;                                   // assignment (copies values)
    di=a;                                   // assignment from different type
    cout << a.size() << endl;               // size
    char x,y;
    x=a[0];                                 // read access []
    c[0]=x;                                 // write access []
    y=a.data()[1];                          // data pointer (read)
    a.data()[0]=x;                          // data pointer (write)
    for (FArray<char,3>::const_iterator cit=f.begin() ; cit!=f.end(); ++cit)        // const iterator
        cout << *cit << endl;                                                       // ...
    for (FArray<char,3>::iterator it=f.begin() ; it!=f.end(); ++it)                 // Iterator
        *it='x';                                                                    // ...
    if (a==b)   cout << "a equals b" << endl;               // ==
    if (a!=b)   cout << "a is different from b" << endl;    // !=
    pair<char,char> r = range(a);           // range
    ofstream out("tmp.bin",ios::binary);    // binary write
    write(out,a);                           // ...
    out.close();
    ifstream in("tmp.bin",ios::binary);     // binary read
    read(in,a);                             // ...
    in.close();
    out.open("tmp.txt");                    // ASCII write
    out << a << endl;                       // ...
    out.close();
    in.open("tmp.txt");                     // ASCII read
    in >> a;                                // ...
    in.close();

}

void fVectors() {
    // NB: functions of base class FArray are indeed available on FVector
    cout << "Testing FVector functions!" << endl;   
    FVector<double,3> a;                    // uninitialized 
    FVector<double,3> b(1.5);               // filled with constant value
    double tt[]={1,2,3};                    // filled from C array
    FVector<double,3> c(tt);                //              (copying array into fresh memory)
    FVector<double,3> dd(c);                // copy constructor
    FVector<int,3> di(c);                   // copy from different type
    FVector<double,2> e(1.5,2.5);           // alias for 2D case
    FVector<double,3> f(1.5,2.5,3.5);       // alias for 3D case
    a.fill(1.3);                            // Fills with constant value
    b=FVector<double,3>::Zero();            // Vector with const 0 value
    dd=c;                                   // assignment (copies values)
    di=c;                                   // assignment from different type
    double x,y,z;
    x=f.x();                                // read alias 0
    f.x()=x;                                // write alias 0
    y=f.y();                                // read alias 1
    f.y()=y;                                // write alias 1
    z=f.z();                                // read alias 2
    f.z()=z;                                // write alias 2
    c=a+b;                                  // +
    c=a-b;                                  // -
    c+=a;                                   // +=
    c-=a;                                   // -=
    c=a+3.;                                 // + scalar
    c=a-3.;                                 // - scalar
    c+=3.;                                  // += scalar
    c-=3.;                                  // -= scalar
    b=-a;                                   // unary -
    x=a*b;                                  // scalar product
    x=e^FVector<double,2>(2,1);             // 2D cross product
    c=a^b;                                  // 3D cross product
    c=a*2;                                  // * scalar
    c=a/2;                                  // / scalar
    c*=2;                                   // *= scalar
    c/=2;                                   // /= scalar
    c=2.*a;                                 // scalar * FVector
    c=2.+a;                                 // scalar + FVector
    c=2.-a;                                 // scalar - FVector
    x=norm2(a);                             // squared Euclidean norm
    x=norm(a);                              // Euclidean norm
    c=normalized(dd);                       // Euclidean normalization
    dd.normalize();                         // Euclidean in-place normalization
    x=maxNorm(a);                           // Maximum norm
    int i=intNorm2(di);                     // integer squared Euclidean norm
    i=intNorm1(di);                         // integer L1-norm
    x=doubleNorm2(di);                      // double squared Euclidean norm
    x=doubleNorm(di);                       // double Euclidean norm
    x=doubleNorm1(di);                      // double L1-norm
    x=sum(a);                               // sum of coordinates
    c=mult(a,b);                            // pointwise *
    c=div(a,b);                             // pointwise /
    c=sqrt(a);                              // pointwise sqrt
    c=log(a);                               // pointwise log
    c=exp(a);                               // pointwise exp
    c=pmin(a,b);                            // pointwise min
    c=pmax(a,b);                            // pointwise max
    x=squaredDist(di,di);                   // squared distance
    x=dist(di,di);                          // distance
    x=intL1Dist(di,di);                     // Integer L1-distance
    x=L1Dist(di,di);                        // L1-distance
}

void fMatrices() {
    cout << "Testing FMatrix functions!" << endl;
    FMatrix<double,2,3> A;                  // uninitialized
    FMatrix<double,2,3> B(1.5);             // filled with constant value
    double t1[6]={1,2,3,4,5,6};             // filled from C array
    FMatrix<double,2,3> C(t1);              // (copying array into fresh memory)
    double t2[2][3]={{1,2,3},{4,5,6}};      // filled from bidim C array
    FMatrix<double,2,3> D(t2);              // (copying array into fresh memory)
    FMatrix<double,2,3> Ed(D);              // copy constructor
    FMatrix<int,2,3> Ei(D);                 // copy from different type
    A.fill(1.3);                            // Fills with constant value
    B=FMatrix<double,2,3>::Zero();          // Matrix with constant 0 value
    Ed=B;                                   // assignment (copies values)
    Ei=B;                                   // assignment from different type
    int s=A.size();                         // size
    int m=A.nrow();                         // number of rows
    int n=A.ncol();                         // number of columns
    double x;
    x=A(1,2);                               // read access
    A(1,2)=x;                               // write access
    x=A[4];                                 // 1D read access []
    A[4]=x;                                 // 1D write access []
    x=A.data()[4];                          // data pointer (read)
    A.data()[4]=x;                          // data pointer (write)
    FMatrix<double,2,2> I;                  // identity
    I=FMatrix<double,2,2>::Identity();      // ...
    FVector<double,2> d(2.);                // diagonal
    I=Diagonal(d);                          // ...
    FVector<double,3> v(1,2,3);             // cross product matrix
    FMatrix<double,3,3> P;                  // i.e. such that for all w, P*w = v^w
    P=FMatrix<double,3,3>::CrossProd(v);    // ...
    if (A==B)   cout << "A equals B" << endl;               // ==
    if (A!=B)   cout << "A is different from B" << endl;    // !=
    C=A+B;                                  // +
    C=A-B;                                  // -
    C+=A;                                   // +=
    C-=A;                                   // -=
    C=A+3.;                                 // + scalar
    C=A-3.;                                 // - scalar
    C+=3.;                                  // += scalar
    C-=3.;                                  // -= scalar
    B=-A;                                   // unary -
    C=A*2;                                  // * scalar
    C=A/2;                                  // / scalar
    C*=2;                                   // *= scalar
    C/=2;                                   // /= scalar
    C=2.*A;                                 // scalar * FMatrix
    C=2.+A;                                 // scalar + FMatrix
    C=2.-A;                                 // scalar - FMatrix
    FMatrix<double,3,2> At=transpose(A);    // transpose
    FMatrix<double,3,2> A32(1.);
    FMatrix<double,2,3> A23(1.);
    FMatrix<double,2,4> A24(1.);
    FMatrix<double,4,2> A42(1.);
    FMatrix<double,3,4> A34;
    A34=A32*A24;                        // matrix * matrix
    A34=tmult(A23,A24);                 // matrix^T * matrix
    A34=multt(A32,A42);                 // matrix * matrix^T
    A34=tmultt(A23,A42);                // matrix^T * matrix^T
    FVector<double,2> v2(1.);
    FVector<double,3> v3;
    v3=A32*v2;                          // matrix * vector
    v2=tmult(A32,v3);                   // matrix^T * vector
    double t9[]={1,2,9,3,4,6,5,7,2};    // Some values
    FMatrix<double,1,1> A11(t9);
    FMatrix<double,2,2> A22(t9);
    FMatrix<double,3,3> A33(t9);
    x=det(A11); x=det(A22); x=det(A33);     // Determinant
    cout << A11*inverse(A11) << endl;       // 1x1 inverse
    cout << A22*inverse(A22) << endl;       // 2x2 inverse
    cout << A33*inverse(A33) << endl;       // 3x3 inverse
    v2=A23.getCol(0);                       // Get column
    A23.setCol(0,v2);                       // Set column
    v3=A23.getRow(0);                       // Get row
    A23.setRow(0,v3);                       // Set row
    x=norm2(A);                             // Squared Frobenius norm
    x=norm(A);                              // Frobenius norm
    ofstream out("tmp.bin",ios::binary);    // binary write
    write(out,A);                           // ...
    out.close();
    ifstream in("tmp.bin",ios::binary);     // binary read
    read(in,A);                             // ...
    in.close();
    out.open("tmp.txt");                    // ASCII write
    out << A << endl;                       // ...
    out.close();
    in.open("tmp.txt");                     // ASCII read
    in >> A;                                // ...
    in.close();
}

void colors() {
    // NB: functions of base class FVector are indeed also available on RGB/RGBA
    cout << "Testing Color functions!" << endl;
    RGB<double> a;                  // uninitialized 
    RGB<double> b(.6);              // filled with constant value
    RGB<double> c(.12,.3,.43);      // rgb values
    double t1[]={.2,1.,.23};        // filled from C array
    RGB<double> d(t1);              //  ...
    RGB<double> e(d);               // copy constructor
    RGB<float> f(e);                // from another type
    double x;
    x=e.r();                        // Read RED alias
    e.r()=x;                        // Write RED alias
    x=e.g();                        // Read GREEN alias
    e.g()=x;                        // Write GREEN alias
    x=e.b();                        // Read BLUE alias
    e.b()=x;                        // Write BLUE alias
    RGBA<double>g(.1,.2,.6,.3);     // RGBA -> RGB
    RGB<float> h(g);                // ...
    float grey=float(c);            // to greyscale
    byte i=123;                     // byte alias   
    Color col(12,234,13);           // color alias
    AlphaColor acol(12,134,13,255); // color alias with alpha channel
    AlphaColor acol1(12,134,13);    // same as above (255 = opaque; 0 = transparent)
    // ...
    col=WHITE;                      // predefined WHITE
    col=BLACK;                      // predefined BLACK
    col=RED;                        // predefined RED
    col=GREEN;                      // predefined GREEN
    col=BLUE;                       // predefined BLUE
    col=MAGENTA;                    // predefined MAGENTA
    col=CYAN;                       // predefined CYAN
    col=YELLOW;                     // predefined YELLOW
    acol = AWHITE;                  // predifined WHITE with alpha channel
    RGBA<double> j;                 // uninitialized rgba
    RGBA<double> k(.6);             // rgb filled with constant value, a=1
    RGBA<double> l(.12,.3,.43,.9);  // rgba values
    RGBA<double> q(.12,.3,.43);     // rgba values from r, g, b
    double t2[]={.2,1.,.23,.3};     // rgba filled from C array
    RGBA<double> m(t2);             //  ...
    RGBA<double> n(l);              // rgba copy constructor
    RGBA<float> o(l);               // rgba from another type
    RGBA<double>p(e);               // RGB -> RGBA
    x=n.r();                        // RGBA Read RED alias
    n.r()=x;                        // RGBA Write RED alias
    x=n.g();                        // RGBA Read GREEN alias
    n.g()=x;                        // RGBA Write GREEN alias
    x=n.b();                        // RGBA Read BLUE alias
    n.b()=x;                        // RGBA Write BLUE alias
    x=n.a();                        // RGBA Read alpha alias
    n.a()=x;                        // RGBA Write alpha alias
    grey=float(o);                  // RGBA to greyscale
    FVector<double,3> yuv=RGB2YUV(Color(12,234,123));   // RGB to YUV
    col=YUV2RGB<byte>(yuv);                             // YUV to RGB
}

void arrays() {
    cout << "Testing Array functions!" << endl;
    Array<char> a;                  // non allocated
    Array<char> b(3);               // allocated with specified size
    char t[4]={'a','b','c','d'};    // pre-allocated
    Array<char> c(t,4); 
    char* t2=new char[3];
    Array<char> c2(t2,3,true);      // ...  
    Array<char> dc(b);              // copy constructor (sharing memory)
    Array<int> di(b);               // from different type
    list<char>l;                    // from list
    l.push_front('a');
    Array<char>e(l);                // ...
    b.setSize(5);                   // setSize
    a=b;                            // assignment (sharing memory)
    di=b;                           // different type assignment
    a=c.clone();                    // cloning (fresh memory)
    if (a.empty())                  // is empty?
        cout<< "a is empty" << endl;// ...
    size_t s=a.size();              // number of elements
    b.fill('x');                    // filling with constant value
    char x;
    x=b[2];                         // read access []
    b[2]=x;                         // write access []
    x=b.data()[2];                  // data pointer (read)
    b.data()[2]=x;                  // data pointer (write)
    for (Array<char>::const_iterator cit=a.begin() ; cit!=a.end(); ++cit)   // const iterator
        cout << *cit << endl;                                               // ...
    for (Array<char>::iterator it=a.begin() ; it!=a.end(); ++it)            // Iterator
        *it='x';                                                            // ...
    e=b.getSubArray(1,2);           // sub array (fresh memory)
    if (a==b)   cout << "a equals b" << endl;               // ==
    if (a!=b)   cout << "a is different from b" << endl;    // !=
    pair<char,char> p=range(a);         // range
    Array< Coords<2> > f(2);                    // pointwise range
    f[0]=Coords<2>(1,5);
    f[1]=Coords<2>(4,2);
    pair<Coords<2>,Coords<2> > p2=prange(f);    // ...
    ofstream out("tmp.bin",ios::binary);    // binary write
    write(out,a);                           // ...
    out.close();
    ifstream in("tmp.bin",ios::binary);     // binary read
    read(in,a);                             // ...
    in.close();
    out.open("tmp.txt");                    // ASCII write
    out << a << endl;                       // ...
    out.close();
    in.open("tmp.txt");                     // ASCII read
    in >> a;                                // ...
    in.close();
}

void coords() {
    cout << "Testing coords functions!" << endl;
    Coords<3> a;            // uninitialized
    Coords<3> b(1);         // filled with constant value
    int t[]={1,2,3};        // filled from C array
    Coords<3> c(t);         // (copying array into fresh memory)
    Coords<3> d(c);         // copy constructor
    Coords<2> e(1,2);       // alias for 2D case
    Coords<3> f(1,2,3);     // alias for 3D case

    CoordsIterator<2> it1;                                          // uninitialized iterator
    CoordsIterator<2> it2(Coords<2>(1,1),Coords<2>(5,3));           // iterator for 1<=x<=5, 1<=y<=3
    it1=it2;                                                        // iterator assignment
    if (it1==it2)   cout << "it1 equals it2" << endl;               // ==
    if (it1!=it2)   cout << "it1 is different from it2" << endl;    // !=
    for (CoordsIterator<2> it(Coords<2>(0,0),Coords<2>(1,2));   it != CoordsIterator<2>() ; ++ it) // pre ++
        cout << *it << endl;                                                                        // dereference
    for (CoordsIterator<2> it(Coords<2>(0,0),Coords<2>(1,2));   it != CoordsIterator<2>() ; )       // post ++ and member selection
        cout << it++->x() << endl;                                                                  // ...
    size_t p=f.prod();      // product of coordinates
}

void multiArrays() {
    cout << "Testing multi Array functions!" << endl;
    MultiArray<char,2> a;                       // non allocated
    MultiArray<char,2> b(Coords<2>(3,4));       // allocated with specified size
    MultiArray<char,2> c2(2,3);                 // constructor, 2D alias
    MultiArray<char,3> c3(2,3,4);               // constructor, 3D alias
    char t[6]={'a','b','c','d','e','f'};            // pre-allocated
    MultiArray<char,2> e(t,Coords<2>(2,3));     
    char *t2=new char[6];       
    MultiArray<char,2> e2(t2,Coords<2>(2,3),true);  // ...
    MultiArray<char,2> g(t,2,3);                // pre-allocated, 2D alias
    MultiArray<char,3> i(t,1,2,3);              // pre-allocated, 3D alias
    MultiArray<char,2> jc(e);                   // copy constructor
    MultiArray<int,2> ji(e);                    // from different type
    e.setSize(Coords<2>(4,4));                  // setSize
    g.setSize(3,3);                             // setSize, 2D alias
    i.setSize(3,2,1);                           // setSize, 3D alias
    a=b;                                        // assignment
    ji=jc;                                      // different type assignment
    a=b.clone();                                // cloning (fresh memory)
    a.fill('x');                                // filling with constant value
    Coords<2> sizes=a.sizes();                  // sizes
    size_t s=a.totalSize();                     // number of elements
    int s1=a.size(1);                           // i^th size
    int w=c3.width();                           // Size. alias 0
    int h=c3.height();                          // Size. alias 1
    int d=c3.depth();                           // Size. alias 2
    a=c2.getSubArray(Coords<2>(1,1),Coords<2>(1,2)); // sub array (fresh memory)
    FArray<size_t,3> stride=c3.stride();        // stride
    size_t st1=c3.stride(1);                    // i^th stride
    size_t o=c3.offset(Coords<3>(1,0,1));       // offset
    size_t o2=c2.offset(1,0);                   // offset 2D alias
    size_t o3=c3.offset(1,0,1);                 // offset 3D alias
    char x;
    x=a(Coords<2>(0,1));                        // read access ()
    a(Coords<2>(0,1))=x;                        // write access ()
    x=a(0,1);                                   // read access 2D alias
    a(0,1)=x;                                   // write access 2D alias
    x=c3(1,0,1);                                // read access 3D alias
    c3(1,0,1)=x;                                // write access 3D alias
    for (CoordsIterator<3> it=i.coordsBegin(); it != i.coordsEnd(); ++it )  // coords iterator
        cout << "[" << *it << "]=" << i(*it) << endl;                           // ...
    ofstream out("tmp.bin",ios::binary);    // binary write
    write(out,i);                           // ...
    out.close();
    ifstream in("tmp.bin",ios::binary);     // binary read
    read(in,i);                             // ...
    in.close();
    out.open("tmp.txt");                    // ASCII write
    out << i << endl;                       // ...
    out.close();
    in.open("tmp.txt");                     // ASCII read
    in >> i;                                // ...
    in.close();
}

void rands() {
    cout << "Testing random functions!"<<endl;
    initRandom(0);                          // Init with given seed
    initRandom();                           // Init with time dependent seed
    cout << doubleRandom() << " ";          // double in [0;1]
    cout << intRandom(10,20) << " ";        // int in [a;b]
    cout << uintRandom(15) << " ";          // unsigned int in [0;a]
    cout << size_tRandom(15) << " ";        // size_t in [0;a]
    cout << gaussianRandom() << endl;       // double following a normal Gaussian law
}


void timers() {
    cout << "Testing Timer functions!"<<endl;
    Timer t;            // construct
    // some code 1
    double x=t.lap();   // seconds for code 1
    // some code 2
    x=t.lap();          // seconds for code 1+2
    t.reset();          // reset    
    // some code 3
    x=t.lap();          // seconds for code 3
}

void io() {
    cout << "Testing IO functions!"<<endl;
    FVector<double,3> v(1/3.,2.,3.);    // object to save   
    saveText(v,"tmp.txt",15);           // save object (ASCII with given precision)
    loadText(v,"tmp.txt");              // load object (ASCII)
    saveBinary(v,"tmp.bin");            // save object (binary)
    loadBinary(v,"tmp.bin");            // load object (binary)
}

int main() {
    base();         // Basics
    fArrays();      // Fixed Arrays
    fVectors();     // Fixed Vectors
    fMatrices();    // Fixed matrices
    colors();       // Colors
    arrays();       // Arrays
    coords();       // Coordinates (used by arrays) 
    multiArrays();  // nD Arrays
    rands();        // Random numbers generation
    timers();       // Timers
    io();           // Input/output
    waitKey();        // Wait before terminating program
    return 0;
}
