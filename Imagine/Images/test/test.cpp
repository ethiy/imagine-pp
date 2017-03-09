/// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// So far, this file is aimed at using each function at least once.
// Hence, it is provided more as a test for compilation than as a true example...

#include <Imagine/Images.h>

using namespace std;
using namespace Imagine;

void images() {
    // NB: see also functiosn of base classes (MultiArray and Array)
    cout << "Testing Image functions!" << endl;
    Image<byte> A;                          // non allocated
    Image<byte,3> B(Coords<3>(20,20,20));   // allocated with specified size
    Image<byte> C(20,20);                   // allocated with specified size (2D alias)
    Image<byte,3> D(20,20,20);              // allocated with specified size (3D alias)
    byte t1[]={1,2,3,4,5,6};                // pre-allocated
    Image<byte> E(t1,Coords<2>(2,3));
    byte *t2=new byte[6];
    Image<byte> F(t2,Coords<2>(2,3),true);  // ...
    Image<byte> G(t1,2,3);                  // pre-allocated, 2D
    Image<byte,3> H(t1,2,3,1);              // pre-allocated, 3D
    Image<byte>I(E);                        // copy constructor
    Image<byte>Jb(20,20);                   // from different type
    for(int i=0; i<Jb.height(); i++)
        for(int j=0; j<Jb.width(); j++)
            Jb(j,i) = byte(rand()%256);
    Image<double>Jd(Jb);
    Image<Color>Jcb(20,20);
    for(int i=0; i<Jcb.height(); i++)
        for(int j=0; j<Jcb.width(); j++)
            Jcb(j,i)=Color(byte(rand()%256),byte(rand()%256),byte(rand()%256));
    Image<RGB<double> >Jcd(Jcb);            // ...
    A=E;                                    // assignment
    A=E.clone();                            // cloning (fresh memory)
    Jd=Jb;                                  // different type assignment
    Jcd=Jcb;                                // ...
    A.fill(12);                             // filling with constant value
    A=C.getSubImage(Coords<2>(1,1),Coords<2>(10,10));   // sub image
    A=C.getSubImage(1,1,10,10);                         // sub image 2D
    H=D.getSubImage(1,1,1,10,10,10);                    // sub image 3D

    float v1=Jb.interpolate(1.2f,3.7f);                         // interpolation
    RGB<double> v2=Jcb.interpolate(FVector<double,2>(1.2,3.7)); // ...

    byte a,b,c,d;
    a=I.neumann(-2,1);b=I.neumann(1,-2);c=I.neumann(4,1);d=I.neumann(1,4);          // Neumann access
    a=I.dirichlet(-2,1);b=I.dirichlet(1,-2);c=I.dirichlet(4,1);d=I.dirichlet(1,4);  // Dirichlet access
    a=I.mirror(-2,1);b=I.mirror(1,-2);c=I.mirror(4,1);d=I.mirror(1,4);              // mirror access
    a=I.invMirror(-2,1);b=I.invMirror(1,-2);c=I.invMirror(4,1);d=I.invMirror(1,4);  // inversed mirror access

    cout << sum(Jd) << ' ' << sum(Jcd) << endl;         // sum of pixels
    cout << norm2(Jd) << ' ' << norm2(Jcd) <<  endl;    // squared Euclidean norm
    cout << norm(Jd) <<  ' ' << norm(Jcd) << endl;      // Euclidean norm

    Image< RGB<double> >O(20,20),P(20,20);
    O.fill(RGB<double>(1.,3.,5.));
    P.fill(RGB<double>(12.,13.,14.));
    O=-O;                           // unary -
    O=O+P;                          // image +  
    O+=P;                           // image += 
    O=O-P;                          // image -  
    O-=P;                           // image -=
    O=P+RGB<double>(1.,2.,3.);      // constant +
    O=RGB<double>(1.,2.,3.)+P;      // constant + image
    O+=RGB<double>(1.,2.,3.);       // constant +=
    O=P-RGB<double>(1.,2.,3.);      // constant -
    O=RGB<double>(1.,2.,3.)-P;      // constant - image
    O-=RGB<double>(1.,2.,3.);       // constant -=
    O=P*2.;                         // scalar *
    O=2*P;                          // scalar * image
    O*=2.;                          // scalar *=
    O=P/2.;                         // scalar /
    O/=2.;                          // scalar /=
    Image<double> Q(20,20);
    Q.fill(1.5);                    
    O=P*Q;                          // pointwise scalar *
    O*=Q;                           // pointwise scalar *=
    O=P/Q;                          // pointwise scalar /
    O/=Q;                           // pointwise scalar /=
}
void io_transparency() {
    cout << "Testing IO transparency functions!" << endl;
    Window w = openWindow(1000,700);

    Image<AlphaColor> I;         // Load PNG image
    load(I, srcPath("sup.png"));
    Image<AlphaColor> Ia;
    load(Ia,srcPath("ryu.gif")); //Load GIF image

    // Create mask
    Image<AlphaColor> Ib;
    load(Ib,srcPath("ryu.gif"));                // Load Image
    createMaskFromColor(Ib,Color(112,136,136)); // ...

    save(Ib,"out.png"); // save image with alpha channel
    Image<AlphaColor> Isaved;
    load(Isaved, "out.png"); //Reload the saved image

    cout << "GIF opaque image" << endl;
    display(Ia);        //Display GIF Image
    click();

    cout << "Superimposed transparent PNG image" << endl;
    display(I);         //Display PNG Image
    click();
    
    cout << "Two transparent images" << endl;
    clearWindow();
    display(I);         //Display PNG Image
    display(Ib);        //Display GIF Image without background
    click();

    cout << "Transparent image" << endl;
    clearWindow();
    display(I);         //Display PNG Image
    click();

    cout << "Saved and reloaded PNG transparent image" << endl;
    display(Isaved);    //Display saved Image (GIF -> PNG)
    click();
    closeWindow(w);
}

void io() {
    cout << "Testing IO functions!" << endl;
    Image<byte> I;  
    load(I,srcPath("test.jpg"));        // load grey
    save(I,"out_grey.png");             // save grey
    Image<Color> J; 
    load(J,srcPath("test.jpg"));        // load color
    save(J,"out_color.tif");            // save color
    save(J,"out_color.jpg",95);         // ...
    Image<byte> R,G,B;
    load(R,G,B,srcPath("test.jpg"));    // load color chanels
    save(R,G,B,"out_color.png");        // save color chanels
    int w=I.width(),h=I.height();
    Window W=openWindow(4*w,3*h);
    setActiveWindow(W);
    display(I);                         // display grey
    display(J,w,0);                     // display color
    display(R,G,B,2*w,0,false,1.5);     // display color (3 chanels)
    Image<double> K(I);
    K/=255.;                            // [0,1] image
    display(rainbow(K),0,h);            // to rainbow
    display(rainbow(K,.2,.8),w,h);      // to rainbow (given range)
    display(grey(K),2*w,h);             // to grey
    display(grey(K,.2,.8),3*w,h);       // to grey (given range)
    Image< RGB<double> > L(J);
    L/=255.;                            // [0,1]^3 image
    display(color(L),0,2*h);            // to color
    display(color(L,RGB<double>(.2,.3,.1),RGB<double>(.8,1.,.6)),w,2*h);    // to color (given range)

    Image<byte,3> M(130,120,110);
    for (int k=0;k<110;k++)
        for (int j=0;j<120;j++)
            for (int i=0;i<130;i++)
                M(i,j,k)=i+j+k;
    display(cut2D(M,Coords<3>(0,5,0),0,2),2*w,2*h); // 2D cut (here {j=5})

    // Analyze tests
    saveAnalyze<float>(I,"out");                // saving byte into float
    Image<byte> I0,K0;
    loadAnalyze(I0,"out");                      // checking
    if (I(10,10)!=I0(10,10))
        cout << "Analyze error!!!" << endl;
    saveAnalyze<double>(K,"out");               // saving double into double
    loadAnalyze(K0,"out");                      // checking
    if (K(10,10)!=K0(10,10))
        cout << "Analyze error!!!" << endl;     // ...
    anyClick(); closeWindow(W);
}

void algos() {
    cout << "Testing Algos functions!" << endl;
    Image<Color> I;
    load(I,srcPath("test.jpg"));
    int w=I.width(),h=I.height();
    Window W=openWindow(4*w,4*h);
    setActiveWindow(W);
    display(I);
    display(scaleUp(I,2),w,0);              // scale up (fast naive)
    display(scaleDown(I,2),3*w,0);          // scale down (fast naive)
    display(reduce(I,2),7*w/2,0);           // reduction (integer factor)
    display(reduce(I,100,50),0,h);          // reduction (dimensions)
    display(reduce(I,100,50,true),100,h);   // ...
    display(reduce(I,1.6),200,h);           // reduction (double factor)
    display(enlarge(I,400,400),350,h);      // enlargement (dimensions)
    display(enlarge(I,400,400,true),600,h); // ...
    display(enlarge(I,1.5),0,2*h);          // enlargement (factor)
    Image< RGB<double> > J(I);                  // Deriche
    display(color(deriche(J,3.,0,0)),w,2*h);                                    
    display(color(deriche(J,1.,1,1)),2*w,2*h);  // ...                                  
    inPlaceDeriche(J,2.,2,0);                   // in place Deriche     
    display(color(J),3*w,2*h);                  // ...
    J=I;
    display(color(blur(J,3)),0,3*h);                        // blur
    display(color(blur(J,FVector<double,2>(5,.01))),w,3*h); // anositropic blur
    inPlaceBlur(J,1.);                                      // in place blur
    display(color(J),2*w,3*h);
    inPlaceBlur(J,FVector<double,2>(3,.01));                // in place anisotropic blur
    display(color(J),3*w,3*h);
    anyClick();
    closeWindow(W);
}

void schemes(){
    cout << "Testing PDE schemes" << endl;
    Image<double,3> u(64,64,64);
    Coords<3> p0(10,0,63);                          // Some point
    FVector<size_t,3> dp,dm;
    neighbourOffsets(u,p0,dp,dm);                   // neighb offsets
    cout << dp << " " << dm << endl;
    Coords<3> pp,pm;
    neighbourCoords(u,p0,pp,pm);                    // neighb coords
    cout << pp << " " << pm << endl;
    
    FVector<double,3> center(32);
    for (CoordsIterator<3> it=u.coordsBegin();it!=u.coordsEnd();++it)
        u(*it)=norm(FVector<double,3>(*it)-center); // Sphere
    Coords<3> p(10,10,10);                          // Some point

    cout << gradient(u,p) << endl << normal(u,p) << endl; // Gradient and unit normal of iso level at p
    cout << derivative(u,p,0) << ' ';               // Derivatives at p
    cout << derivative(u,p,1) << ' ';                 
    cout << derivative(u,p,2) << endl;              // ...  
    cout << laplacian(u,p) << endl;                 // Laplacian at p
    cout << gaussianCurvature(u,p) << endl;         // Gaussian curvature of iso level at p
    cout << meanCurvature(u,p) << endl;             // Mean curvature of iso level at p
    cout << meanCurvatureMotion(u,p) << endl;       // Level set Mean curvature motion at p
    // 2D
    Image<double> u2(64,64);
    FVector<double,2> center2(32);
    for (CoordsIterator<2> it=u2.coordsBegin();it!=u2.coordsEnd();++it)
        u2(*it)=norm(FVector<double,2>(*it)-center2);   // Circle
    Coords<2> p2(10,20);                                // Some point

    cout << gradient(u2,p2) << endl << normal(u2,p2) << endl; // Gradient and unit normal of iso level at p
    cout << derivative(u2,p2,0) << ' '                  // Derivatives at point p
        << derivative(u2,p2,1) <<  endl                 
        << laplacian(u2,p2) << endl                     // Laplacian at point p
        << meanCurvature(u2,p2) << endl             // Mean curvature of iso level at point p
        << meanCurvatureMotion(u2,p2) << endl;      // Level set 'Mean curvature motion' at point p
}

int main() {
    images();       // images
    io();           // files / display
    algos();        // algos
    schemes();      // PDE schemes (used by level set methods, ...)
    io_transparency(); //Images with alpha channel
    endGraphics();
    return 0;
}
