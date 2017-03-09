#include "GraphicsUtilities.h"
#include "OpenGLWindow.h"
#include "Imagine/Graphics/ImageIO.h"
#include <QPixmap>

namespace Imagine {
void display(const QImage& image, int xoff, int yoff, bool xorMode, double fact)
{
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "display",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QImage, image),
                              Q_ARG(int, xoff), Q_ARG(int, yoff),
                              Q_ARG(bool, xorMode), Q_ARG(double, fact));
}
// Qt creator functions depend on little or big endian.
// The functions below allow users to ignore that fact and to use the classical rgba format.
void bgraTorgba(byte *&rgba, int h, int w)
{
    byte btemp;
    for(int i=0; i<w*h; i++)
    {
        btemp = rgba[4*i+2];
        rgba[4*i+2] = rgba[4*i+0]; // b->r
        rgba[4*i+0] = btemp; // r -> b
    }
    //rgba -> bgra or bgra -> rgba
}
void bgraTorgba(AlphaColor *&acols, int w, int h)
{
    byte btemp;
    for(int i=0; i<w*h; i++)
    {
        btemp = acols[i].b();
        acols[i].b() = acols[i].r(); // b-> r
        acols[i].r() = btemp;        // r-> b
    }
    // rgba -> bgra or bgra -> rgba
}

// ====================================================================== //
//! Image drawing functions

QImage qcolorImage(const uchar* in, int w, int h) {
    if(w%4==0) // For unknown reason, the line below does not work otherwise
        return QImage(in,w,h,w*3,QImage::Format_RGB888);
    QImage image(w,h,QImage::Format_RGB888);
    for(int i=0; i<h; i++)
        memcpy(image.scanLine(i), in+3*w*i, 3*w);
    return image;
}
QImage qcolorAlphaImage(const uchar* in, int w, int h) {
    return QImage(in, w, h, w*4, QImage::Format_ARGB32);
}

void putColorImage(int x, int y, const Color* cols,
                   int w, int h, bool xorMode, double fact)
{
    oops2D();
    QImage image = qcolorImage(reinterpret_cast<const uchar*>(cols),w,h);
    display(image, x, y, xorMode, fact);
}
void putAlphaColorImage(int x, int y, AlphaColor *cols, int w, int h, bool xorMode, double fact)
{
    oops2D();
    bgraTorgba(cols,w,h);
    QImage image = qcolorAlphaImage(reinterpret_cast<const uchar*>(cols), w, h);
    display(image, x, y, xorMode, fact);
    bgraTorgba(cols,w,h);
}

void putColorImage(int x, int y, const byte *rgb,
                   int w, int h, bool xorMode, double fact)
{
    oops2D();
    QImage image = qcolorImage(reinterpret_cast<const uchar*>(rgb), w, h);
    display(image, x, y, xorMode, fact);
}

void putColorImage(int x, int y, const byte *r, const byte *g, const byte *b,
                   int w, int h, bool xorMode, double fact)
{
    oops2D();
    byte* rgb = new byte[3*w*h];
    for(int i = 0; i < w*h; i++) {
        rgb[3*i+0] = r[i];
        rgb[3*i+1] = g[i];
        rgb[3*i+2] = b[i];
    }
    putColorImage(x, y, rgb, w, h, xorMode, fact);
    delete[] rgb;
}
//With Alpha Channel
void putColorImage(int x, int y, const byte *r, const byte *g, const byte *b,
                   const byte *a, int w, int h, bool xorMode, double fact) {
    oops2D();
    byte* rgba = new byte[4*w*h];
    for(int i=0; i< w*h; i++) {
        rgba[4*i+0] = b[i];
        rgba[4*i+1] = g[i];
        rgba[4*i+2] = r[i];
        rgba[4*i+3] = a[i];
    }
    QImage image = qcolorAlphaImage(reinterpret_cast<const uchar*>(rgba), w, h);
    display(image, x, y, xorMode, fact);
    delete[] rgba;
}
void putAlphaColorImage(int x, int y, byte *rgba, int w, int h, bool xorMode, double fact)
{
    oops2D();
    bgraTorgba(rgba, w, h);
    QImage image= qcolorAlphaImage(reinterpret_cast<const uchar*>(rgba), w, h);
    display(image, x, y, xorMode, fact);
    bgraTorgba(rgba,w,h);
}
void putAlphaColorImage(const IntPoint2 &p, byte *rgba, int w, int h, bool xorMode, double fact)
{
    oops2D();
    bgraTorgba(rgba, w, h);
    QImage image= qcolorAlphaImage(reinterpret_cast<const uchar*>(rgba), w, h);
    display(image, p.x(), p.y(), xorMode, fact);
    bgraTorgba(rgba,w,h);
}

void setMaskFromColor(byte *&r, byte *&g, byte *&b, byte *&a, int w, int h, const Color &col)
{
    for(int i=0;i<w*h;i++)
    {
       if(r[i] == col.x() && g[i] == col.y() && b[i] == col.z())
       {
           a[i] = 0;
       }
    }
}
void setMaskFromColor(byte *&rgba, int w, int h, const Color &col)
{
    for(int i=0; i<w*h; i++)
    {
        byte r = rgba[4*i+0];
        byte g = rgba[4*i+1];
        byte b = rgba[4*i+2];
        if(r == (col.x()) && g == col.y() && b == col.z())
            rgba[4*i+3] = 0;
    }
}
void setMaskFromColor(AlphaColor *&acols, int w, int h, AlphaColor col)
{
    for(int i=0; i<w*h; i++)
    {
        if(int(acols[i].r()) == col.r() && int(acols[i].g()) == col.g() && int(acols[i].b()) == col.b())
            acols[i].a() = int(0);
    }
}

bool loadAlphaColorImage(const std::string &name, byte *&rgba, int &w, int &h)
{
    rgba = 0; w=h=0;
    QImage image(QString::fromStdString(name));
    if(image.isNull())
        return false;
    image = image.convertToFormat(QImage::Format_ARGB32);
    w = image.width(); h = image.height();
    rgba = new byte[4*w*h];
    if(w%4==0)
        memcpy(rgba, image.bits(), 4*w*h);
    else for(int i=0; i<h; i++)
             memcpy(rgba+4*w*i, image.scanLine(i), 4*w);

    bgraTorgba(rgba,w,h);
    return true;
}

bool loadAlphaColorImage(const std::string &name, AlphaColor *&acols, int &w, int &h)
{
    acols =0; w = h = 0;
    QImage image(QString::fromStdString(name));
    if (image.isNull())
        return false;
    image = image.convertToFormat(QImage::Format_ARGB32);
    w = image.width(); h = image.height();
    acols = new AlphaColor[w*h];
    memcpy(acols, image.bits(), 4*w*h);
    bgraTorgba(acols, w, h);
    return true;
}
bool loadColorImage(const std::string &name, byte *&r, byte *&g, byte *&b, byte *&a, int &w, int &h)
{
    r=g=b=a=0; w=h=0;
    QImage image(QString::fromStdString(name));
    if(image.isNull())
        return false;
    image = image.convertToFormat(QImage::Format_ARGB32);
    w = image.width(); h = image.height();
    r = new byte[w*h]; g = new byte[w*h]; b = new byte[w*h]; a = new byte[w*h];
    for(int i=0; i<h; i++){
        const byte* in = image.scanLine(i);
        for(int j=0, k = w*i; j<w; j++, k++)
        {
            b[k] = *in++;
            g[k] = *in++;
            r[k] = *in++;
            a[k] = *in++;
        }
    }
    return true;
}
AlphaColor* convertColorToAlphaColor(const Color *cols, int w, int h)
{
    AlphaColor* acols = new AlphaColor[w*h];
    for(int i=0; i<w*h; i++)
    {
        acols[i].r() = cols[i].r();
        acols[i].g() = cols[i].g();
        acols[i].b() = cols[i].b();
        acols[i].a() = byte(255);
    }
    return acols;
}


bool saveAlphaColorImage(const std::string &name,
                    const byte *r, const byte *g, const byte *b, const byte *a,
                    int w, int h, int quality)
{
    byte* rgba = new byte[4*w*h];
    for(int i = 0; i < w*h; i++)
        {
            rgba[4*i] = b[i];
            rgba[4*i+1] = g[i];
            rgba[4*i+2] = r[i];
            rgba[4*i+3] = a[i];
        }
    bool ok =  QImage(reinterpret_cast<const uchar*>(rgba),
                      w, h, w*4, QImage::Format_ARGB32).
        save(QString::fromStdString(name), 0, quality);
    delete[] rgba;
    return ok;
}
bool saveAlphaColorImage(const std::string &name, byte *rgba,
                    int w, int h, int quality)
{
    bool isSaved = false;
    bgraTorgba(rgba,w,h);
    isSaved = QImage(reinterpret_cast<const uchar*>(rgba),
                  w, h, w*4, QImage::Format_ARGB32).save(QString::fromStdString(name), 0, quality);
    bgraTorgba(rgba,w,h);
    return isSaved;
}
bool saveAlphaColorImage(const std::string& name,AlphaColor* cols,
                    int w, int h, int quality)
{
    bool isSaved = false;
    bgraTorgba(cols,w,h);
    isSaved = QImage(reinterpret_cast<const uchar*>(cols),
                  w, h, w*4, QImage::Format_ARGB32).
        save(QString::fromStdString(name), 0, quality);
    bgraTorgba(cols,w,h);
    return isSaved;
}

//En "With Alpha Channel"
/*//////////////////////////////////////////////////////////*/
void putGreyImage(int x, int y, const byte* g,
                  int w, int h, bool xorMode, double fact)
{
    oops2D();
    QImage image(g, w, h, w, QImage::Format_Indexed8);
    QVector<QRgb> colorTable(256);
    for (int i = 0; i < 256; ++i)
        colorTable[i] = qRgb(i, i, i);
    image.setColorTable(colorTable);
    display(image, x, y, xorMode, fact);
}


// ====================================================================== //
//! Image loading functions

bool loadColorImage(const std::string& name, Color *&cols,
                    int& w, int& h)
{
    cols=0; w=h=0;
    QImage image(QString::fromStdString(name));
    if (image.isNull())
        return false;
    image = image.convertToFormat(QImage::Format_RGB888);
    w = image.width(); h = image.height();
    cols = new Color[w*h];
    if(w%4==0)
        memcpy(cols, image.bits(), 3*w*h);
    else for(int i=0; i<h; i++)
             memcpy(cols+w*i, image.scanLine(i), 3*w);
    return true;
}


bool loadColorImage(const std::string &name, byte *&rgb,
                    int &w, int &h)
{
    rgb=0; w=h=0;
    QImage image(QString::fromStdString(name));
    if(image.isNull())
        return false;
    image = image.convertToFormat(QImage::Format_RGB888);
    w = image.width(); h = image.height();
    rgb = new byte[3*w*h];
    if(w%4==0)
        memcpy(rgb, image.bits(), 3*w*h);
    else for(int i=0; i<h; i++)
             memcpy(rgb+3*w*i, image.scanLine(i), 3*w);
    return true;
}

bool loadColorImage(const std::string &name, byte *&r, byte *&g, byte *&b,
                    int &w, int &h)
{
    r=g=b=0; w=h=0;
    QImage image(QString::fromStdString(name));
    if(image.isNull())
        return false;
    image = image.convertToFormat(QImage::Format_RGB888);
    w = image.width(); h = image.height();
    r = new byte[w*h]; g = new byte[w*h]; b = new byte[w*h];
    for(int i=0; i<h; i++) {
        const byte* in=image.scanLine(i);
        for(int j=0,k=w*i; j<w; j++,k++) {
            r[k] = *in++;
            g[k] = *in++;
            b[k] = *in++;
        }
    }
    return true;
}


bool loadGreyImage(const std::string& name, byte*& g,
                   int& w, int& h)
{
    g = 0; w = 0; h = 0;
    QImage image(QString::fromStdString(name));
    if (image.isNull())
        return false;
    w = image.width(); h = image.height();
    g = new byte[w*h];
    if(!image.isGrayscale())
        {
            for(int y = 0; y < h; ++y)
                for(int x = 0; x < w; ++x)
                    g[x+w*y] = byte( qGray( image.pixel(x,y) ) );
        }
    else
        {
            for(int y = 0; y < h; ++y)
                for(int x = 0; x < w; ++x)
                    g[x+w*y] = byte( qRed( image.pixel(x,y) ) );
        }

    return true;
}

// ====================================================================== //
//! Image saving functions

bool saveColorImage(const std::string& name,const Color* cols,
                    int w, int h, int quality)
{
    return QImage(reinterpret_cast<const uchar*>(cols),
                  w, h, w*3, QImage::Format_RGB888).
        save(QString::fromStdString(name), 0, quality);
}

bool saveColorImage(const std::string &name, const byte *rgb,
                    int w, int h, int quality)
{
    return QImage(reinterpret_cast<const uchar*>(rgb),
                  w, h, w*3, QImage::Format_RGB888).save(QString::fromStdString(name), 0, quality);
}

bool saveColorImage(const std::string &name,
                    const byte *r, const byte *g, const byte *b,
                    int w, int h, int quality)
{
    byte* rgb = new byte[3*w*h];
    for(int i = 0; i < w*h; i++)
        {
            rgb[3*i] = r[i];
            rgb[3*i+1] = g[i];
            rgb[3*i+2] = b[i];
        }
    bool ok =  QImage(reinterpret_cast<const uchar*>(rgb),
                      w, h, w*3, QImage::Format_RGB888).
        save(QString::fromStdString(name), 0, quality);
    delete[] rgb;
    return ok;
}

bool saveGreyImage(const std::string& name, const byte* g,
                   int w, int h, int quality)
{
    QImage image(g, w, h, w, QImage::Format_Indexed8);
    QVector<QRgb> colorTable(256);
    for (int i = 0; i < 256; ++i)
        colorTable[i] = qRgb(i, i, i);
    image.setColorTable(colorTable);
    return image.save(QString::fromStdString(name), 0, quality);
}

// ====================================================================== //
//! Image capture functions

QImage captureImage() {
    QImage img;
    QMetaObject::invokeMethod(activeWindow(), "capture",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QImage*, &img));
    return img;
}

static void extractColor(const QImage& img, Color* c, int w, int h) {
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++) {
            QColor col(img.pixel(j,i));
            c[i*w+j].r() = col.red();
            c[i*w+j].g() = col.green();
            c[i*w+j].b() = col.blue();
        }
}
static void extractColor(const QImage& img, byte* RGB, int w, int h) {
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++) {
            QColor col(img.pixel(j,i));
            RGB[3*(i*w+j)+0] = col.red();
            RGB[3*(i*w+j)+1] = col.green();
            RGB[3*(i*w+j)+2] = col.blue();
        }
}
static void extractColor(const QImage& img, byte*R,byte*G,byte*B, int w,int h) {
    for(int i=0; i<h; i++)
        for(int j=0; j<w; j++) {
            QColor col(img.pixel(j,i));
            R[i*w+j] = col.red();
            G[i*w+j] = col.green();
            B[i*w+j] = col.blue();
        }
}

Color capturePoint(int x, int y)
{
    Color c;
    captureRectangle(x,y, &c, 1,1);
    return c;
}

void captureRectangle(int x, int y, Color *c, int w, int h)
{
    QImage img = captureImage();
    img = img.copy(x, y, w, h);
    extractColor(img, c, w, h);
}

void captureRectangle(int x, int y, byte *RGB, int w, int h)
{
    QImage img = captureImage();
    img = img.copy(x, y, w, h);
    extractColor(img, RGB, w, h);
}

void captureRectangle(int x, int y, byte *R, byte *G, byte *B, int w, int h)
{
    QImage img = captureImage();
    img = img.copy(x, y, w, h);
    extractColor(img, R,G,B, w, h);
}

static QImage captureWindow(int& w, int& h) {
    QImage img = captureImage();
    w = img.width();
    h = img.height();
    return img;
}  

void captureWindow(Color *&cols, int &w, int &h)
{
    QImage img = captureWindow(w,h);
    cols = new Color[w*h];
    extractColor(img, cols, w, h);
}

void captureWindow(byte *&RGB, int &w, int &h)
{
    QImage img = captureWindow(w,h);
    RGB = new byte[3*w*h];
    extractColor(img, RGB, w, h);
}

void captureWindow(byte *&R, byte *&G, byte *&B, int &w, int &h)
{
    QImage img = captureWindow(w,h);
    R = new byte[w*h];
    G = new byte[w*h];
    B = new byte[w*h];
    extractColor(img, R,G,B, w, h);
}

class NativeBitmapInternal {
public:
    QPixmap* pm;
    int* count;

    void alloc(int w, int h);
    void kill();
    void copy(const NativeBitmapInternal& I);

    NativeBitmapInternal(int w, int h);
    NativeBitmapInternal(const NativeBitmapInternal& I) { copy(I); }
    ~NativeBitmapInternal() { kill(); }
    const NativeBitmapInternal& operator=(const NativeBitmapInternal& I) {
        if(this != &I) { kill(); copy(I); }
        return I;
    }
};

NativeBitmapInternal::NativeBitmapInternal(int w,int h) {
    QMetaObject::invokeMethod(guiApp(), "createBitmap",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(int, w), Q_ARG(int, h));
    pm = guiApp()->createdPixmap;
    count=new int(1);
}

void NativeBitmapInternal::kill() {
    if(! --*count) {
        delete count;
        QMetaObject::invokeMethod(guiApp(), "deleteBitmap",
                                  Qt::BlockingQueuedConnection,
                                  Q_ARG(QPixmap*, pm));
    }
}

void NativeBitmapInternal::copy(const NativeBitmapInternal& I) {
    pm=I.pm;
    count=I.count;
    ++*count;
}

NativeBitmap::NativeBitmap()
  : priv(0) {}

NativeBitmap::NativeBitmap(int w, int h)
  : priv(new NativeBitmapInternal(w,h))
{}

NativeBitmap::NativeBitmap(const NativeBitmap& I)
  : priv(I.priv==0? 0: new NativeBitmapInternal(*I.priv)) {}

NativeBitmap::~NativeBitmap() {
    delete priv;
}

const NativeBitmap& NativeBitmap::operator=(const NativeBitmap& I) {
    if(this != &I) {
        delete priv;
        priv = (I.priv==0? 0: new NativeBitmapInternal(*I.priv));
    }
    return I;
}

void NativeBitmap::setColorImage(int x,int y,
                                 const byte *r,const byte *g,const byte *b,
                                 int w,int h) {
    if(! priv) {
        std::cerr <<"Cannot use setColorImage on empty NativeBitmap"<<std::endl;
        return;
    }
    byte* rgb = new byte[3*w*h];
    for(int i = 0; i < w*h; i++) {
        rgb[3*i] = r[i];
        rgb[3*i+1] = g[i];
        rgb[3*i+2] = b[i];
    }
    QImage image = qcolorImage(reinterpret_cast<const uchar*>(rgb), w, h);
    QMetaObject::invokeMethod(guiApp(), "drawBitmap",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QPixmap*, priv->pm),
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(QImage, image));
    delete [] rgb;
}

void NativeBitmap::setColorImage(int x,int y,const Color *cols,int w,int h) {
    if(! priv) {
        std::cerr <<"Cannot use setColorImage on empty NativeBitmap"<<std::endl;
        return;
    }
    QImage image = qcolorImage(reinterpret_cast<const uchar*>(cols), w, h);
    QMetaObject::invokeMethod(guiApp(), "drawBitmap",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QPixmap*, priv->pm),
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(QImage, image));
}

void NativeBitmap::setGreyImage(int x,int y,const byte *g,int w,int h) {
    if(! priv) {
        std::cerr <<"Cannot use setGreyImage on empty NativeBitmap"<<std::endl;
        return;
    }
    QImage image(g, w, h, w, QImage::Format_Indexed8);
    QVector<QRgb> colorTable(256);
    for (int i = 0; i < 256; ++i)
        colorTable[i] = qRgb(i, i, i);
    image.setColorTable(colorTable);
    QMetaObject::invokeMethod(guiApp(), "drawBitmap",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QPixmap*, priv->pm),
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(QImage, image));
}

void NativeBitmap::setPoint(int x,int y,Color col) {
    setColorImage(x,y,&col,1,1);
}

void putNativeBitmap(int x, int y, const NativeBitmap& bm,
                     bool xorMode, double fact) {
    if(! bm.priv) {
        std::cerr <<"putNativeBitmap with empty NativeBitmap"<<std::endl;
        return;
    }
    oops2D();
    QMetaObject::invokeMethod(guiApp(), "display",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QPixmap*, bm.priv->pm),
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(bool, xorMode),
                              Q_ARG(double, fact));
}
} /* namespace Imagine */
