// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// A first example...
#include <Imagine/Graphics.h>

using namespace std;
using namespace Imagine;

const bool stepByStep=true; // Set false for a quick test of most functions

// ============= Sample 12
void aWindow()
{
    cout << "A window ... click when done" << endl;
    Window W=openWindow(300,200);   // A 300x200 window
    fillRect(20,10,150,100,RED);    // A 150x100 filled RED rectangle in (20,10)
    if (stepByStep) click();        // Wait for a click
    closeWindow(W);                 // Close window...
}

// ============= Sample 2
void twoWindows()
{
    cout << "Two windows ... click when done" << endl;
    // A 300x200 window in (10,10)
    Window W1=openWindow(300,200,"A first window",10,10);
    // A 150x100 RED rectangle in (20,10) (up-left corner)
    drawRect(20,10,150,100,RED);
    // A 200x300 window in (320,10)
    Window W2=openWindow(200,300,"A second window",330,10);
    // Note that openWindow does not make the new window the current one
    setActiveWindow(W2);
    // A BLUE line from (20,10) to (150,270)
    drawLine(20,10,150,270,BLUE);
    setActiveWindow(W1);
    drawLine(20,10,250,170,GREEN);// Another line, in GREEN, in the first window
    if (stepByStep) anyClick();   // Wait for a click in any window
    closeWindow(W1);
    closeWindow(W2);
}

// ============= Sample 3
void twoDimBasics() {
    cout << "Basic 2D drawings ... click when done" << endl;
    Window W=openWindow(512,512,"2D basics");
    // Lines
    drawLine(20,10,300,100,RED,5); // Line (20,10)-(300,100) in RED, thickness=5
    drawLine(IntPoint2(320,100),IntPoint2(500,100),BLACK,5); // Specify 2 pixels instead of 4 coords
    // Rects
    drawRect(400,10,100,50,BLUE,3);                     // A 100x50 rectangle in (400,10) (up-left corner)
    fillRect(IntPoint2(400,400),100,50,GREEN);              // A filled rectangle
    // Ellipspe
    drawEllipse(50,350,50,90,CYAN,2);                   // A 50x90 ellipse in (50,350) (up-left corner), thick=2
    drawCircle(IntPoint2(200,200),40,RED);                  // A circle centered in (200,200), radius=40    
    fillEllipse(350,150,90,100,Color(128,128,128));     // A filled grey ellipse
    // Points
    for (int i=0;i<20;i+=2)
        drawPoint(i+100,i+200,BLACK);                   // Some BLACK points
    // Strings
    drawString(50,250,"a string",RED);                     // A RED string in (50,200)
    drawString(40,270,"another string",MAGENTA,18,0,true); // size=18, italic
    // size=24, angle=-10, bold
    drawString(30,300,"yet another string",BLACK,24,-10,false,true);
    // Polygons
    int px[]={201,200,260,240},py[]={301,350,330,280};
    fillPoly(px,py,4,BLUE);                             // A filled polygon (px[i],py[i])
    int t[]={300,300,300,400,400,350};
    fillPoly(t,3,GREEN);                                // A filled polygon (t[2*i],t[2*i+1])
    IntPoint2 P[]={IntPoint2(100,100),IntPoint2(100,150),IntPoint2(150,120)};
    drawPoly(P,3,RED,3);                                // A polygon P[i] (thickness=3)
    // Arrows
    drawArrow(100,470,200,450,BLUE);                    // An arrow from (100,450) to (200,450)
    drawArrow(300,470,200,450,RED,30,10,1);             // tip=30x10 pixels, style=1
    drawArrow(200,450,250,400,BLACK,20,20,2);           // tip=20x20 pixels, style=2
    drawArrow(200,450,150,400,GREEN,35.,8.,0,2);        // tip: (angle,length)=(35,8) , style=0, width=2
    if (stepByStep) click();
    closeWindow(W);
}

// ============= Sample 4
void bitmapBasics() {
    cout << "Basic bitmap drawings... click when done" << endl;
    Window W=openWindow(512,512,"Bitmaps");
    byte r[256*256],g[256*256],b[256*256];              // byte arrays
    for (int j=0;j<256;j++) {
        for (int i=0;i<256;i++) {
            r[i+256*j]=i;                               // Some (RED,GREEN,BLUE) functions of (i,j)
            g[i+256*j]=255-i;
            b[i+256*j]=(j<128)?255:0;
        }
    }
    putColorImage(0,0,r,g,b,256,256);                   // Draw this 256x256 (r,g,b) bitmap in (0,0)

    Color cols[256*256];                                // A Color array
    for (int j=0;j<256;j++) 
        for (int i=0;i<256;i++) 
            cols[i+256*j]=Color(i,(2*j)%256,(i+j)%256); // Colors, functions of (i,j)
    putColorImage(IntPoint2(0,256),cols,256,256);           // Draw this 256x256 color bitmap in (0,256)

    byte grey[256*256];                                 // A grey array
    for (int j=0;j<256;j++) 
        for (int i=0;i<256;i++) 
            grey[i+256*j]=byte(128+127*sin((i+j)/10.)); // Some pattern
    putGreyImage(256,0,grey,256,256);                   // Draw at point (256,0);
    if (stepByStep) click();
    closeWindow(W);
}

// ============= Sample 5
void mouseBasics() {
    cout << "Basic mouse functions" << endl;
    Window W=openWindow(512,512,"Mouse");
    drawString(10,10,"Please click anywhere",BLACK);
    if (stepByStep) click();    
    drawString(10,40,"click again (left=BLUE, middle=RED, right=done)",BLACK);
    int button;     
    IntPoint2 p;
    while ((button=getMouse(p))!=3)                     // Get clicked point p, and used button (1,2,3)=(left,middle,right)
        fillCircle(p,5,(button==1)?BLUE:RED);
    closeWindow(W);
}

// ============= Sample 6
void imageBasics() {
    cout << "Basic image reading/writing. click when done" << endl; 
    int w,h;                                            // Dimensions
    byte *r,*g,*b;                                      // RGB bitmaps
    loadColorImage(srcPath("ksmall.jpg"),r,g,b,w,h);    // Read image (and allocate)
    Window W=openWindow(w,2*h,"Images");
    putColorImage(0,0,r,g,b,w,h);                       // Draw it
    saveColorImage("outcol.png",r,g,b,w,h);             // Write image
    saveColorImage("outcol.tif",r,g,b,w,h);             // Write image
    saveColorImage("outcol.jpg",r,g,b,w,h);             // Write image
    delete[]r;delete[]g;delete[]b;                      // ...

    Color *I;                                           // Color bitmap
    loadColorImage("outcol.png",I,w,h);                 // Read again (in one Color array)
    putColorImage(0,h,I,w,h,false,2.0);                 // Draw it under previous one, scaling 2.0
    delete[]I;

    byte *grey;                                         // grey bitmap
    loadGreyImage("outcol.png",grey,w,h);               // Read again (and convert into grey if not already)
    putGreyImage(20,2*h/3,grey,w,h,false,0.5);          // Draw it somewhere, scale 0.5
    saveGreyImage("outgrey.tif",grey,w,h);              // Write grey image
    delete[]grey;
    if (stepByStep) click();
    closeWindow(W);
}

// ============= Sample 7
void captureFunctions()
{
    int w = 456;
    int h = 444;
    Window w1 = openWindow(w,h,"Capture Functions : Source");

    // Loading and displaying image
    byte *img_source;
    if(!loadColorImage(srcPath("forty-licks.png"), img_source, w, h))
        return;
    putColorImage(0,0,img_source,w,h);

    // Capture of a rectangle section
    IntPoint2 p1(0,0);
    IntPoint2 p2(0,0);
    getMouse(p1);
    do {
        getMouse(p2);
    } while(p2.x()-p1.x()<=0 || p2.y()-p1.y()<=0);
    byte *capt_r = new byte[(p2.x()-p1.x())*(p2.y()-p1.y())];
    byte *capt_g = new byte[(p2.x()-p1.x())*(p2.y()-p1.y())];
    byte *capt_b = new byte[(p2.x()-p1.x())*(p2.y()-p1.y())];
    captureRectangle(p1.x(), p1.y(), capt_r, capt_g, capt_b, p2.x()-p1.x(), p2.y()-p1.y());

    // Recopie
    Window w2 = openWindow(w,h,"Capture Functions : Destination");
    setActiveWindow(w2);
    putColorImage(p1.x(), p1.y(), capt_r, capt_g, capt_b, p2.x()-p1.x(), p2.y()-p1.y());
    delete [] capt_r;
    delete [] capt_g;
    delete [] capt_b;

    click();
    closeWindow(w1);
    closeWindow(w2);
}

// ============= Sample 8
void naiveAnimation()
{
    Window w = openWindow(300, 300);

    for(int i = 0; i < 10; i++)
    {
        fillRect(rand()%300, rand()%300, rand()%50, rand()%50,
            Color(rand()%256, rand()%256, rand()%256));
        milliSleep(40);
    }
    click();
    cout << "Finished!" << endl;
    closeWindow(w);
}

// ============= Sample 9
void fastDrawings() {
    cout << "Fast drawings ... click when done" << endl;
    Window W=openWindow(512,512,"Fast drawings");
    // Use a "NoRefresh" section around many small drawings
    noRefreshBegin();
    for (int i=0;i<1000;i++) {
        double r=200*i/1000.;
        drawPoint(256+int(r*cos(i/120.)),int(256+r*sin(i/120.)),BLUE);
    }
    noRefreshEnd();
    // Use XORs to draw and erase easily
    for (int i=0;i<100;i+=5) {
        drawLine(511-5*i,511,5*i,0,RED,1,true);     // Draw
        milliSleep(25);
        drawLine(511-5*i,511,5*i,0,RED,1,true);     // Erase
    }
    // Use "Native Bitmap" to avoid conversion each time you draw 
    const int sz=128;
    NativeBitmap natBM(sz,sz);                      // Native bitmap (fixed constant size)
    byte r[sz*sz],g[sz*sz],b[sz*sz];                // Some r,g,b bitmap
    for (int y=0;y<sz;y++) {
        for (int x=0;x<sz;x++) {
            r[x+sz*y]=2*x;
            g[x+sz*y]=2*y;
            b[x+sz*y]=2*(x+y);
        }
    }
    natBM.setColorImage(0,0,r,g,b,sz,sz);           // Copy r,g,b bitmap in native bitmap
    Color cl[64*64];                                // Some Color bitmap    
    for (int y=0;y<64;y++)
        for (int x=0;x<64;x++)
            cl[x+64*y]=Color((x+y)%256,0,0);
    natBM.setColorImage(IntPoint2(32,32),cl,64,64); // Copy Color bitmap to a sub region of native bitmap
    for (int x=0;x<sz;x++)
        natBM.setPoint(x,x,RED);                    // Draw some points in native bitmap
    putNativeBitmap(0,0,natBM);                     // Draw it in (0,0)
    putNativeBitmap(300,0,natBM,false,1.5);         // Draw it in (300,0), scaled x1.5
    putNativeBitmap(0,300,natBM,false,0.75);        // Draw it in (0,300), scaled x.75

    for (int i=0;i<20;i++) {                        // Draw it quickly in circle (using XOR), with vaying factor
        double f=1+0.8*sin(i/2.);
        putNativeBitmap(int(256-sz/2+100*cos(i/4.0)),int(256-sz/2+100*sin(i/4.0)),natBM,true,f); // draw
        milliSleep(100);
        putNativeBitmap(int(256-sz/2+100*cos(i/4.0)),int(256-sz/2+100*sin(i/4.0)),natBM,true,f); // erase
    }
    if (stepByStep) click();
    closeWindow(W);
}

// ============= Sample 9
void imageAnimation()
{
    cout << "check 'ksmall.jpg' path" << endl;
    cout << srcPath("ksmall.jpg") << endl;

    // Read image.
    Color* cols;
    int w, h;
    loadColorImage(srcPath("ksmall.jpg"), cols, w, h);

    Window W = openWindow(2*w, h);

    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            drawPoint(x, y, cols[y*w+x]);

    noRefreshBegin();
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            drawPoint(w+x, y, cols[y*w+x]);
    noRefreshEnd();

    std::cout << "wait for click!" << std::endl;
    click();

    int x = 0, y = 0;
    int step = 1;
    for(int i = 0; i < 5*w/2; i++)
    {
        putColorImage(x, y, cols, w, h);
        milliSleep(1);
        clearWindow();

        x += step;
        if (x < 0 || x > w)
            step *= -1;
    }
    click();
    closeWindow(W);
    cout << "Finished!" << endl;
}

// ============= Sample 10
void advancedEvents()
{
    cout << "Advanced event handling" << endl;
    Window W=openComplexWindow(512,384,"Events",3);
    drawString(10,10,"Move, click, press key, etc.",RED);
    drawString(10,30,"Come back here again and press Up Arrow when done",RED);
    Event ev;
    do {
        getEvent(500,ev); // Wait an event (return if no event for 500ms)
        switch (ev.type){
        case EVT_NONE:
            cout << "No event for 500ms" << endl;
            break;
        case EVT_MOTION:
            cout << "Motion" << endl;
            break;
        case EVT_KEY_ON:
            cout << "Key " << ev.key << " pressed"<< endl;
            break;
        case EVT_KEY_OFF:
            cout << "Key " << ev.key << " released"<< endl;
            break;
        case EVT_BUT_ON:
            cout << "Button " << ev.button << " pressed"<< endl;
            break;
        case EVT_BUT_OFF:
            cout << "Button " << ev.button << " released"<< endl;
            break;
        }
        if (ev.type!=EVT_NONE)
            cout << " Mouse=[" << ev.pix.x() <<','<<ev.pix.y() << "] "
                 << ",State="<< ev.state 
                 << ",Win=" << ev.win << ",SubWin=" << ev.subWin << endl;
    } while (ev.win!=W || ev.subWin!=0 || ev.type!=EVT_KEY_ON||ev.key!=KEY_UP);
    closeWindow(W);
}

// ============= Sample 10
void subWindows()
{
    cout << "A window with sub windows..." << endl;
    string names[]={"sub window 0","sub window 1","sub window 2"};
    //        Imagine::WindowType types[]={WINDOW_2D,WINDOW_2D,WINDOW_2D};
    // A 512x360 window with three 2D subwindows
    Window W=openComplexWindow(512,360,"Sub windows",3,names);
    drawString(10,100,"Please go and click in sub window 2",BLACK);
    setActiveWindow(W,2); // Third subwindow
    drawString(10,20,"You've found it!",BLUE);
    if (stepByStep) click();
    drawString(10,40,"Now click in any sub window...",BLUE);
    if (stepByStep) anyClick();
    setActiveWindow(W,2);
    drawString(10,60,"Well done!",RED);
    closeWindow(W);
}

#ifdef IMAGINE_OPENGL
void threeDim()
{
    DoublePoint3 centerSphere(0, 0, -4);
    Mesh Sphere = Mesh::Sphere(centerSphere, 0.8);
    Sphere.setOpacity(0.5f);

   DoublePoint3 centerCylinder(0, 0, 5);
   DoubleVector3 axisCylinder(2, 0, 0);
   Mesh Cylinder = Mesh::Cylinder(centerCylinder, axisCylinder, 0.8);

    DoublePoint3 centerCone(0, 0, 2);
    DoubleVector3 axisCone(0, -2, 0);
    Mesh Cone = Mesh::Cone(centerCone, axisCone, 0.8);

    DoublePoint3 centerPlane(0, 0, -1);
    DoubleVector3 axisPlane1(2, 0, 0);
    DoubleVector3 axisPlane2(1, 2, 0);
    Mesh Plane = Mesh::Plane(centerPlane, axisPlane1, axisPlane2);

    DoublePoint3 centerCube(0, 0, 4);
    DoubleVector3 axis1Cube(0, 0, 1);
    DoubleVector3 axis2Cube(1, 0, 0);
    DoubleVector3 axis3Cube(0, 1, 0);
    Mesh Cube = Mesh::Cube(centerCube, axis1Cube, axis2Cube, axis3Cube);
    Cube.setOpacity(0.5f);

    DoublePoint3 baseArrow(0, -3, 0);
    DoubleVector3 shaftArrow(0, 6, 0);
    Mesh Arrow = Mesh::Arrow(baseArrow, shaftArrow, 0.5);

    const int n = Sphere.vertices().size();
    DoublePoint3 *points_ = new DoublePoint3[n];
    for(int i = 0; i < n; i++)
    {
        points_[i].x() = Sphere.vertices()[i].x() + 3;
        points_[i].y() = Sphere.vertices()[i].y() + 3;
        points_[i].z() = Sphere.vertices()[i].z() + 3;
    }
    Mesh PointCloud = Mesh::PointCloud(points_, Sphere.vertices().size());
    PointCloud.setColor(Color(255, 0, 0));
    Mesh PolyLine = Mesh::PolyLine(points_, n, false);

    string fileName = srcPath("bunny.obj");
    cout << "Reading filename: \"" << fileName << "\"" << endl;
    Mesh mesh;
    readMeshFromObjFile(mesh, fileName);

    Window glWindow = openWindow3D(512, 512, "3D Window");
    setActiveWindow(glWindow);

                     showMesh(mesh); click(); hideMesh(mesh);
    mesh=Sphere;     showMesh(mesh); click(); hideMesh(mesh);
    mesh=Cylinder;   showMesh(mesh); click(); hideMesh(mesh);
    mesh=Cone;       showMesh(mesh); click(); hideMesh(mesh);
    mesh=Plane;      showMesh(mesh); click(); hideMesh(mesh);
    mesh=Cube;       showMesh(mesh); click(); hideMesh(mesh);
    mesh=Arrow;      showMesh(mesh); click(); hideMesh(mesh);
    mesh=PointCloud; showMesh(mesh); click(); hideMesh(mesh);
    mesh=PolyLine;   showMesh(mesh); click(); hideMesh(mesh);

    click();

    closeWindow(glWindow);
}

#endif

int main(int argc, char** argv)
{
    aWindow();
    twoWindows();
    twoDimBasics();
    bitmapBasics();
    mouseBasics();
    imageBasics();
    subWindows();
    naiveAnimation(); 
    imageAnimation();
    fastDrawings();
    advancedEvents();
    captureFunctions();

#ifdef IMAGINE_OPENGL
    threeDim();
#endif

    endGraphics();
    return 0;
}
