// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// So far, this file is aimed at using each function at least once.
// Hence, it is provided more as a test for compilation than as a true example...

#include <Imagine/Graphics.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

using namespace Imagine;
using namespace std;

void windows() {
    cout << "Testing Window functions!" << endl;
    Window W1=openWindow(300,200);                                  // Open
#ifdef IMAGINE_OPENGL
    Window W2=openWindow3D(200,300, "3D");
#endif
    Window W3=openComplexWindow(300,200,"3 tabs",3);                // Complex Open
#ifdef IMAGINE_OPENGL
    string names[]={"2D a","2D b","3D"};                            //
    WindowType types[]={WINDOW_2D,WINDOW_2D,WINDOW_3D};             //
    Window W4=openComplexWindow(512,360,"2D/2D/3D",3,names, types); // ...
#else
    string names[]={"2D a","2D b"};                                 //
    WindowType types[]={WINDOW_2D,WINDOW_2D};                       //
    Window W4=openComplexWindow(512,360,"2D/2D",2,names, types);    // ...
#endif
    setActiveWindow(W3,1);      // ...
    showWindow(W1);             // show
    showWindow(W4,2);           // ...
    setActiveWindow(W4,1);
    setBackGround(YELLOW);
    setActiveWindow(W1);
    setBackGround(GREEN);
    setActiveWindow(W4,2);      // background (2D only)
    setBackGround(RED);         // background (3D only)
    cout << "Click in red tab" << endl;
    click();
    clearWindow();              // clear (3D)
    setActiveWindow(W1);
    clearWindow();              // clear (2D)
    cout << "Click" << endl;
    anyClick();
    closeWindow(W1);            // close
#ifdef IMAGINE_OPENGL
    closeWindow(W2);
#endif
    closeWindow(W3);
    closeWindow(W4);            // ...
}

void draw2D() {
    cout << "Testing 2D functions!" << endl;
    Window W=openWindow(500,500);
    drawLine(0,0,300,200,RED);                                          // line
    drawLine(IntPoint2(0,200),IntPoint2(300,0),Color(120,120,255),2,true);  // line (IntPoint2)
    drawEllipse(30,30,200,100,BLUE);                                    // ellipse
    drawEllipse(IntPoint2(200,100),100,200,Color(255,120,0),4,true);    // ellipse (IntPoint2)
    drawCircle(30,430,50,BLACK);                                        // circle
    drawCircle(IntPoint2(200,400),80,Color(55,250,30),3,true);          // circle (IntPoint2)
    drawRect(310,130,100,40,BLUE);                                      // rectangle
    drawRect(IntPoint2(200,400),30,20,Color(55,120,200),2,true);        // rectangle (IntPoint2)
    fillEllipse(330,30,30,100,CYAN);                                    // filled ellipse
    fillEllipse(IntPoint2(100,300),200,30,Color(55,220,200),true);      // filled ellipse (IntPoint2)
    fillCircle(330,43,30,YELLOW);                                       // filled circle
    fillCircle(IntPoint2(200,200),20,Color(255,250,230),true);          // filled circle (IntPoint2)
    fillRect(110,130,100,40,BLUE);                                      // filled rectangle
    fillRect(IntPoint2(300,200),30,20,Color(55,120,200),true);          // filled rectangle (IntPoint2)
    drawPoint(200,300,RED);                                             // point
    drawPoint(IntPoint2(230,120),BLUE,true);                            // point (IntPoint2)
    drawArrow(300,300,400,300,RED);                                     // arrow
    drawArrow(IntPoint2(300,300),IntPoint2(350,350),BLUE,14,6,2,2);     // arrow (IntPoint2)
    drawArrow(300,300,300,400,GREEN,40.,10.,1);                         // arrow (angle)
    drawArrow(IntPoint2(300,300),IntPoint2(250,350),BLACK,60.,17.,0);   // arrow (angle IntPoint2)
    int x[]={100,200,170},y[]={200,250,220};                            // polygon
    fillPoly(x,y,3,YELLOW);                                             // inside
    drawPoly(x,y,3,RED);                                                // contour
    IntPoint2 p[]={IntPoint2(400,400),IntPoint2(300,450),IntPoint2(350,480)};   // polygon (IntPoint2)
    fillPoly(p,3,YELLOW);                                               // inside
    drawPoly(p,3,BLUE,3);                                               // contour
    int xy[]={120,30,200,60,160,80};                                    // polygon (one array)
    fillPoly(xy,3,BLACK);                                               // inside
    drawPoly(xy,3,GREEN,5);                                             // contour
    drawString(400,10,"Hello",BLACK);                                   // strings
    drawString(400,210,"Hello !",RED,15,35.,true);
    drawString(IntPoint2(400,200),"Hello !!",BLUE,14,270.);             // ...
    noRefreshBegin();                                                   // No refresh section
    for (int i=0;i<200;i+=5)
        drawPoint(i+10,250-i,RED);
    noRefreshEnd();                                                     // ...
    noRefreshPush();                                                    // No refresh section (push/pop)
    for (int i=0;i<200;i+=5)
        drawCircle(i+10,i+10,3,BLUE);
    noRefreshPop();                                                     // ...
    cout << "Please click" << endl;
    anyClick();
    closeWindow(W);
}

void events2() {
    /// Menu
    Window win = openWindow(800,400,"Test Event");
    Event ev;
    //Displaying menu's buttons
    IntPoint2 P1(250,150), P2(250,250);
    int w=300, h=50;
    IntPoint2 Q1(P1.x()+w/3,P1.y()+h*3/5);
    IntPoint2 Q2(P2.x()+w/3,P2.y()+h*3/5);
    fillRect(P1,w,h,AlphaColor(150,150,150,255));
    drawString(Q1,"NEW GAME",WHITE);
    fillRect(P2,w,h,Color(150,150,150));
    drawString(Q2,"LOAD GAME", WHITE);
    bool b = false;

    // receiving mouse move events even if no button is pressed
    enableMouseTracking(true);

    do {
        getEvent(-1,ev); // ev becomes the next event
        switch (ev.type) {
        case EVT_NONE:
            cout << "No event" << endl;
            break;

        case EVT_MOTION: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Cursor is in the "NEW GAME" box.
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                // Changing the box's style
                fillRect(P1,w,h,Color(128,139,203));
                drawString(Q1,"NEW GAME",YELLOW);
            } else if(P2.x()<=x && x<P2.x()+w && P2.y()<=y && y<P2.y()+h) {
                // Cursor is in the "LOAD GAME" box.
                // Changing the box's style
                fillRect(P2,w,h,Color(128,139,203));
                drawString(Q2,"LOAD GAME", YELLOW);
            } else {
                fillRect(P1,w,h,Color(150,150,150));
                drawString(Q1,"NEW GAME",WHITE);
                fillRect(P2,w,h,Color(150,150,150));
                drawString(Q2,"LOAD GAME", WHITE);
            }
            break;
        }

        case EVT_KEY_ON:
            cout << "Use your mouse!"<< endl;
            break;

        case EVT_BUT_ON: {
            int x = ev.pix.x();   // cursor's x coord
            int y = ev.pix.y();   // cursor's y coord
            // Click on the NEW GAME box
            if(P1.x()<=x && x<P1.x()+w && P1.y()<=y && y<P1.y()+h) {
                cout << "Starting a new Tetris game !!" << endl;
                b = true;         // Stop the menu's loop
            }
            break;
        }

        default: break;
        }
    } while ((ev.type!=EVT_KEY_ON || ev.key!='q' )&& !b);
    closeWindow(win);
    /// ...

    /// Ball
    win = openWindow(500,500,"Ball");
    // receiving mouse move events only with button pressed
    enableMouseTracking(false);

    cout << "Use your arrow keys. Press 'q' to quit." << endl;
    int x=50, y=200, r=5;
    int xt=x, yt=y;
    fillCircle(x,y,r,GREEN);
    while(true) {
        int k = getKey();
        if(k == 'q')
            break;
        bool update = true;
        switch(k){
        case KEY_UP:   y-=5; break;
        case KEY_DOWN: y+=5; break;
        case KEY_LEFT: x-=5; break;
        case KEY_RIGHT:x+=5; break;
        default: update=false; break;
        }
        if(update) {
            fillCircle(xt,yt,r,WHITE);
            fillCircle(x,y,r,GREEN);
            xt = x; yt = y;
        }
    }
    closeWindow(win);
    /// ...
}

void events() {
    // Basics
    Window W=openComplexWindow(500,500,"events",2);
    cout << "Testing event functions!" << endl;
    cout << "Please click in first tab" << endl;
    int button=click();                             // click
    cout << "button clicked: " << button << endl;
    cout << "click again in any tab" << endl;
    button=anyClick();                              // click any
    cout << "button clicked: " << button << endl;
    Window W1;
    int sw;
    cout << "click again in any tab" << endl;
    button=anyClick(W1,sw);                         // click any (returning window)
    cout << "button clicked: " << button << endl;
    int x,y;
    cout << "click again in first tab" << endl;
    button=getMouse(x,y);                           // get mouse
    cout << "button clicked: " << button << " pos: " << x << ',' << y << endl;
    IntPoint2 p;
    cout << "click again in first tab" << endl;
    button=getMouse(p);                             // get mouse (IntPoint2)
    cout << "button clicked: " << button << " pos: " << p << endl;
    cout << "click again in any tab" << endl;
    button=anyGetMouse(x,y,W1,sw);                  // get mouse (any window)
    cout << "button clicked: " << button << " pos: " << x << ',' << y
         << " subWin: " << sw << endl;
    cout << "click again" << endl;
    button=anyGetMouse(p,W1,sw);                    // get mouse (any window, IntPoint2)
    cout << "button clicked: " << button << " pos: " << p
         << " subWin: " << sw << endl;
    do {                                            // get key
        cout << "Please press UP arrow in first tab" << endl;
    } while (getKey() != KEY_UP);                   // ...
    cout << "Press key, check modifier keys let you proceed" << endl;
    getKey(false);
    cout << "Press key, check modifier keys do *not* let you proceed" << endl;
    getKey(true);
    cout << "Please press some key in any tab (modifier keys ignored)" << endl;
    int key=anyGetKey(W1,sw);                       // get key (any window)
    cout << "Please press some key in any tab (modifier keys OK)" << endl;
    key=anyGetKey(W1,sw, false);                   // get key (any window)
    cout << "Key: " << key << " subWin: " << sw << endl;
    for (int i=0;i<4;i++) {                         // sleep
        cout << i << endl;
        milliSleep(300);                            // 300ms
    }                                               // ...
    // Advanced
    cout << "Generate events, press 'q' key done" << endl;              // manually process events
    Event ev;
    do {
        getEvent(500,ev);
        switch (ev.type) {
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
            cout << " Mouse=[" << ev.pix.x() <<','<<ev.pix.y() << "] ,State="<< ev.state
                 << ",Win=" << ev.win << ",SubWin=" << ev.subWin << endl;
    } while (ev.type!=EVT_KEY_ON || ev.key!='q'); // ...
    unGetEvent(ev);         // unget event
    flushEvents();          // flush events

    cout << "Please click" << endl;
    anyClick();
    closeWindow(W);
}

void transparency() {
    cout << "Testing image transparency" << endl;
    Window WTransp = openWindow(1024,512,"Transparency");

    int W, H;
    byte *r1, *g1, *b1;
    loadColorImage(srcPath("ksmall.jpg"), r1,g1,b1, W, H);
    // Load Image with Alpha channel
    int w,h,w1,h1;
    byte *R,*G,*B, *A;
    byte *r,*g,*b, *a;
    loadColorImage(srcPath("sup.png"),R,G,B,A,w,h); // Load PNG Image
    loadColorImage(srcPath("test.jpg"), r,g,b,a,w1,h1); // Load JPEG Image

    cout << "Transparent image (R,G,B,A) from PNG" << endl;
    putColorImage(0,0,R,G,B,A,w,h);
    click();// Display image with alpha channel
    cout << "Two opaque images" << endl;
    putColorImage(IntPoint2(100,100),r,g,b,a,w1,h1);
    // ...

    putColorImage(0,0,r1,g1,b1,W,H);
    click();
    // put alphacolor bitmap (1 rgba (RGBA) array)
    cout << "Tranparent image (RGBA) from PNG" << endl;
    byte *rgba;
    loadAlphaColorImage(srcPath("sup.png"),rgba,w,h); // Load PNG Image
    putAlphaColorImage(0,0,rgba,w,h);
    putAlphaColorImage(IntPoint2(100,100),rgba,w,h);
    // ...
    click();

    // create mask from a color
    loadColorImage(srcPath("ryu.gif"), r, g, b, a, w1, h1); // Load color with alpha channel (for transparency, using PNG or GIF is better)
    setMaskFromColor(r,g,b,a,w1,h1,Color(112,136,136));      // Hide the background color
    cout << "First Mask" << endl;
    putColorImage(0,0,r,g,b,a,w1,h1);                        // Display Image with alpha channel
    click();
    // ...

    // Save Image with an alpha channel
    if(saveAlphaColorImage("out.png",r,g,b,a,w1,h1))
        cout << "Image saved" << endl;
    else
        cout << "Image is *not* saved -> something is wrong" << endl;
    // ...

    // Load Image with AlphaColor
    clearWindow();
    setBackGround(BLACK);
    AlphaColor *AC;
    int Aw, Ah;
    if(loadAlphaColorImage("out.png", AC, Aw, Ah)) // Load PNG Image with a transparent background
        cout << "out.png loaded" << endl;
    cout << "Transparent image saved and reloaded on black background" << endl;
    putAlphaColorImage(0,0,AC,Aw,Ah);            // Display Image with Alpha channel
    // ...
    click();
    delete [] AC;

    clearWindow();
    putColorImage(0,0,r1,g1,b1,W,H);
    // create a mask from a color (AlphaColor array)
    AlphaColor *C;
    loadAlphaColorImage(srcPath("ryu.gif"),C,w,h);   // Load a GIF image
    setMaskFromColor(C, w, h, Color(112,136,136));   // Hide the background color
    cout << "2nd Mask for AlphaColor" << endl;
    saveAlphaColorImage("ryu2.png", C, w, h);        // Save image to PNG with transparency
    putAlphaColorImage(0,0,C,w,h);                   // Display Image with an alpha channel
    click();
    // ...

    delete[] C;
    delete[] R; delete[] G; delete[] B; delete[] A;
    delete[] r; delete[] g; delete[] b; delete[] a;

    clearWindow();

    // load color image (1 rgba array)
    byte* RGBA;
    byte* RGBA1;
    loadAlphaColorImage(srcPath("ryu.gif"), RGBA, w1, h1); //GIF
    loadAlphaColorImage(srcPath("sup.png"), RGBA1,w,h); //PNG
    // ...

    putColorImage(0,0,r1,g1,b1,W,H);
    click();

    // create a mask from a color (rgba array)
    loadAlphaColorImage(srcPath("ryu.gif"), RGBA, w1, h1);  // Load a GIF Image (prefer PNG)
    setMaskFromColor(RGBA, w1, h1, Color(112,136,136));     // Hide the background color
    saveAlphaColorImage("ruy.png", RGBA, w1, h1);           // Save Image to PNG without background color (ie. with transparency)
    putAlphaColorImage(0,0,RGBA1,w,h);                      // Display Image with an alpha channel
    // ...
    click();

    putAlphaColorImage(0,0,RGBA,w1,h1);
    cout << "3rd mask for RGBA" << endl;
    click();

    delete[] r1; delete[] g1; delete[] b1;
    delete[] rgba;
    delete[] RGBA;
    delete[] RGBA1;

    // convert Color image to Color image with alpha channel
    Color* C1;
    loadColorImage(srcPath("test.jpg"),C1,w,h); // Load JPEG IMAGE
    AlphaColor* aC;
    aC = convertColorToAlphaColor(C1,w,h); // Add alpha Channel
    setMaskFromColor(aC,w,h,Color(255,255,255)); // Hide the white color
    putAlphaColorImage(0,0,aC,w,h); // Display Image with alpha channel
    // ...

    click();

    // Fading display
    byte *ri, *gi, *bi, *ai;
    int wi, hi;
    loadColorImage(srcPath("index.jpg"), ri, gi, bi, ai, wi, hi);
    for(int i = 0; i < 50; i++)
    {
        for(int j=0; j<wi*hi; j++)
        {
            ai[j] = i;
        }
        putColorImage(0,0,ri,gi,bi,ai,wi,hi);
        milliSleep(75);
    }
    click();
    // ...
    delete[] C1; delete[] aC;
    delete[] ri; delete[] gi; delete[] bi; delete[] ai;
    closeWindow(WTransp);
}

void bitmaps() {
    cout << "Testing bitmap functions!" << endl;

    // Basic displays

    Window W2=openWindow(1024,512,"2D");
    byte r[256*256],g[256*256],b[256*256];                  // put color bitmap (3 arrays)
    for (int j=0;j<256;j++) {
        for (int i=0;i<256;i++) {
            r[i+256*j]=i;                                   // Some (RED,GREEN,BLUE) functions of (i,j)
            g[i+256*j]=255-i;
            b[i+256*j]=(j<128)?255:0;
        }
    }
    putColorImage(0,0,r,g,b,256,256);                       // Draw this 256x256 (r,g,b) bitmap in (0,0)
    putColorImage(IntPoint2(256,0),r,g,b,256,256,false,.5); // ... and in (256,0), shrinked

    Color* cols=new Color[256*256];                         // put color bitmap (Color array)
    for (int j=0;j<256;j++)
        for (int i=0;i<256;i++)
            cols[i+256*j]=Color(i,(2*j)%256,(i+j)%256);     // Colors, functions of (i,j)
    putColorImage(384,0,cols,256,256);                      // Draw this 256x256 color bitmap in (384,0)
    putColorImage(IntPoint2(640,0),cols,256,256,false,.75); // ... and in (640,0), shrinked
    delete [] cols;

    byte* rgb=new byte[3*256*256];                          // put color bitmap (1 rgb array)
    for (int j=0;j<256;j++)
        for (int i=0;i<256;i++) {
            rgb[3*(i+256*j)]=i/2;                           // RED
            rgb[3*(i+256*j)+1]=255-j/2;                     // GREEN
            rgb[3*(i+256*j)+2]=128;                         // BLUE
        }
    putColorImage(0,256,rgb,256,256);                       // Draw this 256x256 rgb bitmap in (0,256)
    putColorImage(IntPoint2(256,256),rgb,256,256,false,.25);    // ... and in (256,256), shrinked
    delete [] rgb;

    byte* grey=new byte[256*256];                           // put grey bitmap
    for (int j=0;j<256;j++)
        for (int i=0;i<256;i++)
            grey[i+256*j]=byte(128+127*sin((i+j)/10.));     // Some pattern
    putGreyImage(384,256,grey,256,256);                     // Draw at point (384,256);
    putGreyImage(IntPoint2(640,256),grey,256,256,false,1.5);    // ... and (640,256), expanded
    delete [] grey;

    // Loading/Saving

    int w,h;                                            // load color image (3 arrays)
    byte *R,*G,*B;
    loadColorImage(srcPath("ksmall.jpg"),R,G,B,w,h);
    putColorImage(10,10,R,G,B,w,h);
    saveColorImage("out1.png",R,G,B,w,h);
    delete[]R;
    delete[]G;
    delete[]B;                      // ...

    Color *C;                                           // load color image (Color array)
    loadColorImage(srcPath("ksmall.jpg"),C,w,h);
    putColorImage(40,40,C,w,h);
    saveColorImage("out2.tif",C,w,h);
    delete[]C;                                          // ...

    byte *RGB;                                          // load color image (1 rgb array)
    loadColorImage(srcPath("ksmall.jpg"),RGB,w,h);
    putColorImage(70,70,RGB,w,h);
    saveColorImage("out3.jpg",RGB,w,h);
    saveColorImage("out4.jpg",RGB,w,h,95);
    delete[]RGB;                                        // ...

    byte *I;                                            // load grey image
    loadGreyImage(srcPath("ksmall.jpg"),I,w,h);
    putGreyImage(100,100,I,w,h);
    saveGreyImage("out5.png",I,w,h);
    delete[]I;                                          // ...

    // Captures

    Window Wcap=openWindow(800,400,"Captures");
    setActiveWindow(Wcap);
    fillRect(0,0,1024,512,Color(80,80,80));
    setActiveWindow(W2);                                // 2D capture (3 arrays)
    captureWindow(R,G,B,w,h);
    setActiveWindow(Wcap);
    putColorImage(10,10,R,G,B,w,h,false,.25);
    delete[]R;
    delete[]G;
    delete[]B;                      // ...
    setActiveWindow(W2);                                // 2D capture (Color array)
    captureWindow(C,w,h);
    setActiveWindow(Wcap);
    putColorImage(542,10,C,w,h,false,.25);
    delete[]C;                                          // ...
    setActiveWindow(W2);                                // 2D capture (1 array)
    captureWindow(RGB,w,h);
    setActiveWindow(Wcap);
    putColorImage(276,10,RGB,w,h,false,.25);
    delete[]RGB;                                        // ...

    setActiveWindow(W2);
    Color c1=capturePoint(10,10);                       // 2D capture (point)
    cout << "Color at (10,10): " << c1 << endl;
    Color c2=capturePoint(IntPoint2(10,10));                // 2D capture (point) (IntPoint2)
    cout << "Color at (10,10): " << c2 << endl;
    byte r1[100*50],g1[100*50],b1[100*50];
    byte rgb1[100*50*3];
    Color cols1[100*50];
    captureRectangle(IntPoint2(50,10),r1,g1,b1,100,50); // 2D capture (subwindow 3 arrays) (IntPoint2)
    captureRectangle(IntPoint2(50,10),cols1,100,50);        // 2D capture (subwindow Color array) (IntPoint2)
    captureRectangle(IntPoint2(50,10),rgb1,100,50);     // 2D capture (subwindow 1 array) (IntPoint2)
    setActiveWindow(Wcap);
    putColorImage(10,150,r1,g1,b1,100,50);
    putColorImage(120,150,cols1,100,50);
    putColorImage(230,150,rgb1,100,50);
    setActiveWindow(W2);
    captureRectangle(150,10,r1,g1,b1,100,50);           // 2D capture (subwindow 3 arrays)
    captureRectangle(150,10,cols1,100,50);              // 2D capture (subwindow Color array)
    captureRectangle(150,10,rgb1,100,50);               // 2D capture (subwindow 1 array)
    setActiveWindow(Wcap);
    putColorImage(340,150,r1,g1,b1,100,50);
    putColorImage(450,150,cols1,100,50);
    putColorImage(560,150,rgb1,100,50);
#ifdef IMAGINE_OPENGL
    Window W3=openWindow3D(256,256,"3D drawings");
    setActiveWindow(W3);
    Mesh cone=Mesh::Cone(DoublePoint3(0,0,0),DoubleVector3(0,1,0),0.25);
    cone.setColor(CYAN);
    showMesh(cone);
    cout << "Click on cone window to capture" << endl;
    click();
    captureWindow(R,G,B,w,h);                           // 3D capture (3 arrays)
    captureWindow(C,w,h);                               // 3D capture (Color array)
    captureWindow(RGB,w,h);                         // 3D capture (1 array)
    setActiveWindow(Wcap);
    putColorImage(10,220,R,G,B,w,h,false,.5);
    putColorImage(160,220,C,w,h,false,.5);
    putColorImage(310,220,RGB,w,h,false,.5);
    delete[]R;
    delete[]G;
    delete[]B;
    delete[]C;
    delete[]RGB;
    click();

#if 0
    setActiveWindow(W3);                                // zbuffer capture
    float *Z;
    captureZBuffer(Z,w,h);
    I=new byte[w*h];
    float mn=1e10,mx=-1e10;
    for (int i=0;i<w*h;i++) {
        mn=min(mn,Z[i]);
        mx=max(mx,Z[i]);
    }
    for (int i=0;i<w*h;i++)
        I[i]=byte(255*(Z[i]-mn)/(mx-mn));               // normalized grey levels
    setActiveWindow(Wcap);
    putGreyImage(460,220,I,w,h,false,.5);
    delete[]Z;
    delete[]I;                                          // ...
#endif

    // Native bitmaps
#endif
    const int sz=128;
    NativeBitmap bm(sz,sz);     // with dimensions
    byte r2[sz*sz],g2[sz*sz],b2[sz*sz];                 // Set color image (3 arrays)
    for (int y=0;y<sz;y++) {
        for (int x=0;x<sz;x++) {
            r2[x+sz*y]=x;
            g2[x+sz*y]=y;
            b2[x+sz*y]=(x+y);
        }
    }
    bm.setColorImage(0,0,r2,g2,b2,sz,sz);               // twice the same (just to check both variants)
    bm.setColorImage(IntPoint2(0,0),r2,g2,b2,sz,sz);        // ...
    Color cols2[64*64];                                 // Set color image (Color array)
    for (int y=0;y<64;y++)
        for (int x=0;x<64;x++)
            cols2[x+64*y]=Color((x+y)%256,0,0);
    bm.setColorImage(32,32,cols2,64,64);                // twice the same (just to check both variants)
    bm.setColorImage(IntPoint2(32,32),cols2,64,64);     // ...
    byte rgb2[3*64*64];                                 // Set color image (1 array)
    for (int y=0;y<64;y++)
        for (int x=0;x<64;x++) {
            rgb2[3*(x+64*y)]=x;
            rgb2[3*(x+64*y)+1]=y;
            rgb2[3*(x+64*y)+2]=x+y;
        }
    bm.setColorImage(64,0,rgb2,64,64);                  // twice the same (just to check both variants)
    bm.setColorImage(IntPoint2(64,0),rgb2,64,64);           // ...
    byte grey2[64*64];                                  // Set grey image
    for (int y=0;y<64;y++)
        for (int x=0;x<64;x++)
            grey2[(x+64*y)]=x+2*y;
    bm.setGreyImage(0,64,grey2,64,64);                  // twice the same (just to check both variants)
    bm.setGreyImage(IntPoint2(0,64),grey2,64,64);           // ...
    for (int x=0;x<sz;x++)  {                           // Set point
        bm.setPoint(x,x,RED);                           // twice the same (just to check both variants)
        bm.setPoint(x,x,RED);
    }                                                   // ...
    setActiveWindow(W2);
    clearWindow();
    showWindow(W2);
    putNativeBitmap(0,0,bm);                            // Put native bitmap
    putNativeBitmap(IntPoint2(300,0),bm,false,1.5);
    putNativeBitmap(0,300,bm,false,0.75);
    for (int i=0;i<1024;i+=8) {
        putNativeBitmap(i,200,bm,true,0.5);             // use XOR to display/undisplay
        milliSleep(100);
        putNativeBitmap(i,200,bm,true,0.5);
    }                                                   // ...
    cout << "Please click" << endl;
    anyClick();
    closeWindow(W2);
#ifdef IMAGINE_OPENGL
    closeWindow(W3);
#endif
    closeWindow(Wcap);
}
#ifdef IMAGINE_OPENGL
void draw3D() {
    cout << "Testing 3D functions!" << endl;
    // Basics
    Window W=openWindow3D(1000,1000,"3D");


    DoublePoint3 dP[8]={DoublePoint3(-1,-1,-1),DoublePoint3(1,-1,-1),DoublePoint3(1,1,-1),DoublePoint3(-1,1,-1),    // constructor (double)
                        DoublePoint3(-1,-1,1),DoublePoint3(1,-1,1),DoublePoint3(1,1,1),DoublePoint3(-1,1,1)
                       };
    Triangle dT[12]={Triangle(0,2,1),Triangle(2,0,3),Triangle(4,5,6),Triangle(6,7,4),   // A cube
                     Triangle(0,1,5),Triangle(5,4,0),Triangle(1,2,6),Triangle(6,5,1),
                     Triangle(2,3,7),Triangle(7,6,2),Triangle(3,0,4),Triangle(4,7,3)
                    };

    Mesh dM(dP,8,dT,12);                                                                // ...
    FloatPoint3 fP[8]={FloatPoint3(3,-1,-1),FloatPoint3(5,-1,-1),FloatPoint3(5,1,-1),FloatPoint3(3,1,-1),   // constructor (float)
                       FloatPoint3(3,-1,1),FloatPoint3(5,-1,1),FloatPoint3(5,1,1),FloatPoint3(3,1,1)
                      };
    Triangle fT[12]={Triangle(0,2,1),Triangle(2,0,3),Triangle(4,5,6),Triangle(6,7,4),   // A cube
                     Triangle(0,1,5),Triangle(5,4,0),Triangle(1,2,6),Triangle(6,5,1),
                     Triangle(2,3,7),Triangle(7,6,2),Triangle(3,0,4),Triangle(4,7,3)
                    };
    Mesh fM(fP,8,fT,12);

    // ...
    cout << "Two cubes" << endl;
    showMesh(dM);
    showMesh(fM);                           // ...
    dM.setColor(RED);                       // set color
    fM.setColor(BLUE);                      // ...
    fM.setOpacity(.3f);                     // opacity
    cout << "Play with navigation (use CTRL + mouse and kb)" << endl;
    cout << "Then click..." << endl;
    anyClick();
    hideMesh(dM);
    hideMesh(fM);              // hide mesh

    int n=10;                                                                           // shading tests
    DoublePoint3 *P=new DoublePoint3[n*n];
    for (int j=0;j<n;j++)
        for (int i=0;i<n;i++)
            P[i+n*j]=DoublePoint3(double(i)/n,double(j)/n,.2f*cos(double(i)*6/n)*sin(double(j)*6/n));   // A surface z=cos(x)*sin(y)
    Triangle *T=new Triangle[2*(n-1)*(n-1)];
    for (int j=0;j<n-1;j++) {
        for (int i=0;i<n-1;i++) {
            T[2*(i+(n-1)*j)]=Triangle(i+n*j,i+1+n*j,i+n*(j+1));
            T[2*(i+(n-1)*j)+1]=Triangle(i+1+n*j,i+1+n*(j+1),i+n*(j+1));
        }
    }
    Mesh S;
    S=Mesh(P,n*n,T,2*(n-1)*(n-1),0,0,CONSTANT_COLOR,FLAT_SHADING);                  // No normal interpolation
    cout << "Flat shading, computed normals" << endl;
    showMesh(S);
    anyClick();
    hideMesh(S,false);
    S=Mesh(P,n*n,T,2*(n-1)*(n-1),0,0,CONSTANT_COLOR,SMOOTH_SHADING);    // Guess normals
    cout << "Smooth shading, computed normals" << endl;
    showMesh(S,false);
    anyClick();
    hideMesh(S,false);
    DoublePoint3* N=new DoublePoint3[n*n];                                  // normals
    for (int j=0;j<n;j++) {
        for (int i=0;i<n;i++) {
            double fx=-6*.2*sin(double(i)*6/n)*sin(double(j)*6/n);
            double fy=6*.2*cos(double(i)*6/n)*cos(double(j)*6/n);
            N[i+n*j]=DoublePoint3(-fx,-fy,1);
        }
    }
    S=Mesh(P,n*n,T,2*(n-1)*(n-1),0,0,CONSTANT_COLOR,SMOOTH_SHADING,N);  // Given true normals
    cout << "Smooth shading, true normals" << endl;
    showMesh(S, false);
    anyClick();                                                     // ...
    hideMesh(S, false);

    Color *cols=new Color[2*(n-1)*(n-1)];                                           // set colors
    S=Mesh(P,n*n,T,2*(n-1)*(n-1),0,0,FACE_COLOR,SMOOTH_SHADING);
    for (int i=0;i<2*(n-1)*(n-1);i++)
        cols[i]=Color(intRandom(0,255),intRandom(0,255),intRandom(0,255));
    S.setColors(TRIANGLE,cols);
    delete[] cols;
    cout << "Random triangle colors" << endl;
    showMesh(S, false);
    anyClick();
    hideMesh(S, false);
    S=Mesh(P,n*n,T,2*(n-1)*(n-1),0,0,VERTEX_COLOR,SMOOTH_SHADING);
    cols=new Color[n*n];
    for (int i=0;i<n*n;i++)
        cols[i]=Color(intRandom(0,255),intRandom(0,255),intRandom(0,255));
    S.setColors(VERTEX, cols);
    delete[] cols;
    cout << "Random vertex colors" << endl;
    showMesh(S, false);
    anyClick(); // ...
    hideMesh(S, false);

    float *vals=new float[2*(n-1)*(n-1)];                                           // set values
    S=Mesh(P,n*n,T,2*(n-1)*(n-1),0,0,FACE_VALUE,SMOOTH_SHADING);
    for (int i=0;i<2*(n-1)*(n-1);i++)
        vals[i]=float(i)/(2*(n-1)*(n-1));
    S.setRange(0.,1.);
    S.setValues(TRIANGLE,vals);
    delete[] vals;
    cout << "Face value coloring" << endl;
    showMesh(S, false);
    anyClick();
    hideMesh(S, false);
    S=Mesh(P,n*n,T,2*(n-1)*(n-1),0,0,VERTEX_VALUE,SMOOTH_SHADING);
    vals=new float[n*n];
    for (int i=0;i<n*n;i++)
        vals[i]=float(i)/(n*n);
    S.setRange(0.,1.);
    S.setValues(VERTEX,vals);
    delete[] vals;
    cout << "Vertex value coloring" << endl;
    showMesh(S, false);
    anyClick();                                                                     // ...
    Color LUT[3]={BLACK,BLUE,WHITE};            // change LUT
    //  S.setLookupTable(LUT,3);                    // ...
    S.setLookupTable(LUT[0],LUT[1]);
    cout << "Vertex value coloring with custom LUT" << endl;
    showMesh(S, false);
    anyClick();
    S.setDefaultLookupTable();                  // Default LUT...
    cout << "Vertex value coloring with default LUT" << endl;
    showMesh(S, false);
    anyClick();
    hideMesh(S);

#if 0
    MeshClipping cut;                                       // clipping
    cut.addClippingPlane(DoublePoint3(.5,.5,0),DoubleVector3(1,0,0));
    cut.addClippingPlane(DoublePoint3(.5,.5,0),DoubleVector3(0,1,0));   // a corner
    cut.clipOn();
    S=VtkMesh(P,n*n,T,2*(n-1)*(n-1),CONSTANT_COLOR,PHONG_SHADING);
    showMesh(S,cut);
    anyClick();
    cut.showClippedOn();
    cut.setClipOpacity(.3);
    cut.setClipColor(RED);
    hideMesh(S,false);                                      // re-display (without camera reset) with transparentcut
    showMesh(S,cut,false);
    anyClick();                                             // ...
#endif

    delete[] P;
    delete[] T;
    delete[] N;

    DoublePoint3 P3[]={DoublePoint3(0,0,0),DoublePoint3(1,0,0),DoublePoint3(0,1,0)};        // set points
    Triangle T3(0,1,2);
    S=Mesh(P3,3,&T3,1,0,0,CONSTANT_COLOR);
    cout << "Triangle" << endl;
    showMesh(S);
    anyClick();
    DoublePoint3 Q3[]={DoublePoint3(0,0,0),DoublePoint3(1,0,0),DoublePoint3(0,2,0)};
    S.setVertices(Q3);
    cout << "Bigger triangle" << endl;
    showMesh(S, false);
    anyClick();
    DoublePoint3 P4[]={DoublePoint3(0,0,0),DoublePoint3(1,0,0),DoublePoint3(0,1,0),DoublePoint3(1,1,1)}; // set geometry
    Triangle T4[]={Triangle(0,1,2),Triangle(1,3,2)};
    S.setGeometry(P4,4,T4,2);                                                   // ...
    cout << "Two triangles" << endl;
    showMesh(S, false);
    anyClick();
    hideMesh(S);

#if 0
    Mesh* M;
    int id,but;
    cout << "Use shift and mouse to pick a triangle" << endl;
    pickMeshCell(M,id,but,-1);                                  // pick triangle
    cout << "Use shift and mouse to pick a vertex" << endl;
    pickMeshPoint(M,id,but,-1);                                 // pick vertex
#endif

    Mesh Ar=Mesh::Arrow(DoublePoint3(-2,0,0),DoubleVector3(0.5,0,0),0.1);       // arrow
    Ar.setColor(RED);
    showMesh(Ar);                                          // ...
    Mesh Sp=Mesh::Sphere(DoublePoint3(0,2,0),0.5);                          // sphere
    Sp.setColor(BLUE);
    showMesh(Sp);                                         // ...
    Mesh Cn=Mesh::Cone(DoublePoint3(2,0,0),DoubleVector3(-0.5,0,0),0.3);        // cone
    Cn.setColor(GREEN);
    showMesh(Cn);                                        // ...
    DoublePoint3 PTSCL[]={DoublePoint3(0,0,2),DoublePoint3(1,0,2),DoublePoint3(0,1,2),DoublePoint3(1,1,2),
                          DoublePoint3(0,0,1),DoublePoint3(1,0,1),DoublePoint3(0,1,1),DoublePoint3(1,1,1)
                         };       // set points
    Mesh Cp=Mesh::PointCloud(PTSCL,8);      // pointcloud
    Cp.setColor(MAGENTA);
    showMesh(Cp);                                      // ...
    Mesh Cpl=Mesh::PolyLine(PTSCL,8,true);      // polyline
    Cpl.setColor(WHITE);
    showMesh(Cpl);                                      // ...
    Mesh Cb=Mesh::Cube(DoublePoint3(0,-2,0),DoubleVector3(.1,0,0),DoubleVector3(.1,.2,0),DoubleVector3(0,.1,.3));   // parallelepiped
    Cb.setColor(CYAN);
    showMesh(Cb);                                                                 // ...
    Mesh Pl=Mesh::Plane(DoublePoint3(0.5,0,1.5),DoubleVector3(.2,0,0),DoubleVector3(0,.3,0));   // plane
    Pl.setColor(MAGENTA);
    showMesh(Pl);                                                  // ...
    Mesh Cl=Mesh::Cylinder(DoublePoint3(-0.5,-0.5,1.5),DoubleVector3(0,1,0),0.2);   // cylinder
    Cl.setColor(YELLOW);
    showMesh(Cl);                                           // ...
    anyClick();

#if 0
    DoublePoint3 src[]={DoublePoint3(0,0,0),DoublePoint3(1,0,0)};                   // landmark apply
    DoublePoint3 dest[]={DoublePoint3(0,0,0),DoublePoint3(cos(.1),sin(.1),0)};
    for (int i=0;i<50;i++) {
        Ar.landMarkTransform(src,dest,2,false,false,true);
        milliSleep(10);
    }                                                               // ...
    Ar.resetPosition();                                             // reset apply

    setAmbient(.2);                             // set ambient
    DoublePoint3 pos;
    DoubleVector3 dir,up;
    double zoom;
    getCamera(pos,dir,up,zoom);                 // get camera
    for (int i=0;i<50;i++) {                    // set camera
        zoom*=1.05;
        setCamera(pos,dir,up,zoom);
    }                                           // ...
    reInitCamera();                             // reinit camera
    anyClick();
#endif

    closeWindow(W);
}
#endif
int main(int argc, char** argv)
{
    windows();
    transparency();
    draw2D();
    events();
    bitmaps();
    events2();
#ifdef IMAGINE_OPENGL
    draw3D();
#endif
    endGraphics();              // terminates
    return 0;
}
