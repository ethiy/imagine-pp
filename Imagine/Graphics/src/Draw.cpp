#include "Imagine/Graphics/ConfigGraphics.h"
#include "GraphicsUtilities.h"
#include "OpenGLWindow.h"
#include "Imagine/Graphics/Draw.h"
#include <QDebug>

namespace Imagine {
// ======================================================================
//! Drawing commands
void drawPoint(int x, int y, const Color& c, bool xorMode) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawPoint",
                              Qt::QueuedConnection,
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b())),
                              Q_ARG(bool, xorMode));
}

void drawCircle(int x,int y,int r, const Color& c, int penW, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawCircle",
                              Qt::QueuedConnection,
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(int, r),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b())),
                              Q_ARG(int, penW),
                              Q_ARG(bool, xorM));
}

void drawEllipse(int x,int y,int w,int h,const Color &c, int penW,bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawEllipse",
                              Qt::QueuedConnection,
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(int, w), Q_ARG(int, h),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b())),
                              Q_ARG(int, penW),
                              Q_ARG(bool, xorM));
}

void drawLine(int x1,int y1,int x2,int y2,const Color& c,int penW,bool xorM){
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawLine",
                              Qt::QueuedConnection,
                              Q_ARG(int, x1), Q_ARG(int, y1),
                              Q_ARG(int, x2), Q_ARG(int, y2),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b())),
                              Q_ARG(int, penW),
                              Q_ARG(bool, xorM));
}

void drawRect(int x,int y,int w,int h,const Color& c, int penW, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawRect",
                              Qt::QueuedConnection,
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(int, w), Q_ARG(int, h),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b())),
                              Q_ARG(int, penW),
                              Q_ARG(bool, xorM));
}

void drawPoly(const QPolygonF& poly, const Color& c, int width, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawPoly",
                              Qt::QueuedConnection,
                              Q_ARG(QPolygonF, poly),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b())),
                              Q_ARG(int, width),
                              Q_ARG(bool, xorM));
}

void drawPoly(const int*x,const int*y,int n,const Color& c,int w, bool xorM) {
    QPolygonF poly;
    for (int i=0; i<n; ++i)
        poly << QPointF(qreal(x[i]), qreal(y[i]));
    drawPoly(poly, c, w, xorM);
}

void drawPoly(const IntPoint2* p, int n, const Color& c, int w, bool xorM) {
    QPolygonF poly;
    for (int i=0; i<n; ++i)
        poly << QPointF(qreal(p[i].x()), qreal(p[i].y()));
    drawPoly(poly, c, w, xorM);
}

void drawString(int x, int y, const std::string &s, const AlphaColor& c,
                int fontSize, double alpha, bool italic, bool bold,
                bool underlined, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawText",
                              Qt::QueuedConnection,
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(QString, QString::fromStdString(s)),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b(), c.a())),
                              Q_ARG(int, fontSize),
                              Q_ARG(qreal, qreal(alpha)),
                              Q_ARG(bool, italic),
                              Q_ARG(bool, bold),
                              Q_ARG(bool, underlined),
                              Q_ARG(bool, xorM));
}

void drawArrow(int x1, int y1, int x2, int y2, const AlphaColor& c,
               int arrowWidth, int arrowHeight,
               int style, int width, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "drawArrow",
                              Qt::QueuedConnection,
                              Q_ARG(int, x1), Q_ARG(int, y1),
                              Q_ARG(int, x2), Q_ARG(int, y2),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b(), c.a())),
                              Q_ARG(int, arrowWidth), Q_ARG(int, arrowHeight),
                              Q_ARG(int, style), Q_ARG(int, width),
                              Q_ARG(bool, xorM));
}

void fillEllipse(int x, int y, int w, int h, const AlphaColor& c, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "fillEllipse",
                              Qt::QueuedConnection,
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(int, w), Q_ARG(int, h),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b(), c.a())),
                              Q_ARG(bool, xorM));
}

void fillRect(int x, int y, int w, int h, const AlphaColor& c, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "fillRect",
                              Qt::QueuedConnection,
                              Q_ARG(int, x), Q_ARG(int, y),
                              Q_ARG(int, w), Q_ARG(int, h),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b(), c.a())),
                              Q_ARG(bool, xorM));
}

void fillCircle(int xc, int yc, int r, const AlphaColor& c, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "fillCircle",
                              Qt::QueuedConnection,
                              Q_ARG(int, xc), Q_ARG(int, yc),
                              Q_ARG(int, r),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b(), c.a())),
                              Q_ARG(bool, xorM));
}

void fillPoly(const QPolygonF& polygon, const AlphaColor& c, bool xorM) {
    oops2D();
    QMetaObject::invokeMethod(activeWindow(), "fillPoly",
                              Qt::QueuedConnection,
                              Q_ARG(QPolygonF, polygon),
                              Q_ARG(QColor, QColor(c.r(), c.g(), c.b(), c.a())),
                              Q_ARG(bool, xorM));
}

void fillPoly(const int x[], const int y[], int n, const AlphaColor& col, bool xorM){
    QPolygonF poly;
    for (int i=0; i<n; ++i)
        poly << QPointF(qreal(x[i]), qreal(y[i]));
    fillPoly(poly, col, xorM);
}

void fillPoly(const int xy[], int n, const AlphaColor& col, bool xorM) {
    QPolygonF poly;
    for (int i=0; i<n; ++i)
        poly << QPointF(qreal(xy[2*i]), qreal(xy[2*i+1]));
    fillPoly(poly, col, xorM);
}

void fillPoly(const IntPoint2* p, int n, const AlphaColor& col, bool xorM) {
    QPolygonF poly;
    for (int i=0; i<n; ++i)
        poly << QPointF(qreal(p[i].x()), qreal(p[i].y()));
    fillPoly(poly, col, xorM);
}

#ifdef IMAGINE_OPENGL
void showMesh(const Mesh& mesh, bool reinitCam) {
    oops3D();
    QMetaObject::invokeMethod(activeWindow3D(), "addMesh",
                              Qt::QueuedConnection,
                              Q_ARG(Mesh, mesh),
                              Q_ARG(bool, reinitCam));
}

void hideMesh(const Mesh& mesh, bool reinitCam) {
    oops3D();
    QMetaObject::invokeMethod(activeWindow3D(), "removeMesh",
                              Qt::QueuedConnection,
                              Q_ARG(Mesh, mesh),
                              Q_ARG(bool, reinitCam));
}

void setCamera(const DoublePoint3& pos,
               const DoublePoint3& dir,
               const DoubleVector3& up) {
    QMetaObject::invokeMethod(activeWindow3D(), "setLookAt",
                              Qt::QueuedConnection,
                              Q_ARG(double, pos.x()),
                              Q_ARG(double, pos.y()),
                              Q_ARG(double, pos.z()),
                              Q_ARG(double, dir.x()),
                              Q_ARG(double, dir.y()),
                              Q_ARG(double, dir.z()),
                              Q_ARG(double, up.x()),
                              Q_ARG(double, up.y()),
                              Q_ARG(double, up.z()));
}
#endif

// ======================================================================
//! No refresh functions

void noRefreshBegin() {
    oopsActive();
    QMetaObject::invokeMethod(activeWindow(), "allowUpdates",
                              Qt::QueuedConnection, Q_ARG(bool,false));
}

void noRefreshEnd() {
    oopsActive();
    QMetaObject::invokeMethod(activeWindow(), "allowUpdates",
                              Qt::QueuedConnection, Q_ARG(bool,true));
}

int noRefreshStack(int i)
{
    static int n=0;
    if(i==0)
        n=0;
    else {
        int p=n+i;
        if(p<0)
            qDebug() << "Cannot noRefreshPop : Empty Stack";
        else n=p;
    }
    return n;
}

} /* namespace Imagine */
