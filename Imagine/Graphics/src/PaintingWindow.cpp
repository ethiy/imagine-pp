#include "Imagine/Graphics/ConfigGraphics.h"
#include "PaintingWindow.h"
#include "OpenGLWindow.h"
#include "GraphicsUtilities.h"
#include <QTabWidget>
#include <QtGui>
#include <iostream>


#ifdef _WIN32
#undef min
#undef max
#endif

namespace Imagine {
// == ScrollArea ==

ScrollArea::ScrollArea(QWidget* parent)
: QScrollArea(parent)
{
    setAlignment(Qt::AlignCenter);
}

void ScrollArea::closeEvent(QCloseEvent* event)
{ if(event->spontaneous()) exit(0); }

// == PaintingWindow ==

PaintingWindow::PaintingWindow(Window win, int width, int height,
                               const QString& windowTitle, int x, int y,
                               int subWinId, QWidget* parent)
: QWidget(0)
, pixmap_(width, height)
, painter_(&pixmap_)
, win_(win)
, subWinId_(subWinId)
{
    setFocusPolicy(Qt::StrongFocus);
    scrollArea_ = new ScrollArea(parent);
    resize(sizeHint());

    int fixSize = +4;
    if(x!=-1 && y!=-1)
        scrollArea_->move(x,y);
    scrollArea_->setWindowTitle(windowTitle);
    scrollArea_->setWidget(this);
    scrollArea_->setFocusProxy(this);
    scrollArea_->resize(width+fixSize,height+fixSize);

    pixmap_.fill();
    update();
    if(parent==0)
        scrollArea_->show();
}

void PaintingWindow::mousePressEvent(QMouseEvent *event)
{
    Qt::MouseButtons button = event->button();
#ifdef Q_OS_MAC
    if(event->modifiers()==Qt::ControlModifier &&
       event->button()==Qt::LeftButton)
#if QT_VERSION < 0x040700
        button = Qt::MidButton;
#else
        button = Qt::MiddleButton;
#endif
#endif
    emit pressedMouseButtons(event->x(), event->y(), button,
                             event->type(), event->modifiers(),
                             win_, subWinId_);
}

void PaintingWindow::keyPressEvent(QKeyEvent* event)
{
    if(! (event->type()==QEvent::KeyRelease && event->isAutoRepeat()))
        emit pressedKey(event->key(), event->type(), event->modifiers(),
                        win_, subWinId_);
}

void PaintingWindow::drawPoint(int x, int y, const QColor& c, bool xorMode)
{
    painter_.setPen(c);
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.drawPoint(x, y);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::drawCircle(int xc, int yc, int r, const QColor& c,
                                int penWidth, bool xorMode)
{
    drawEllipse(xc-r,yc-r,2*r+1,2*r+1,c,penWidth,xorMode);
}

void PaintingWindow::drawLine(int x1, int y1, int x2, int y2,
                              const QColor& c, int penWidth, bool xorMode)
{
    painter_.setPen(QPen(c, penWidth));
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.drawLine(x1, y1, x2, y2);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::drawEllipse(int x, int y, int w, int h,
                                 const QColor& c, int penWidth, bool xorMode)
{
    painter_.setPen(QPen(c, penWidth));
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.drawEllipse(x+penWidth, y+penWidth, w-2*penWidth, h-2*penWidth);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::drawPoly(const QPolygonF& polygon, const QColor& c,
                              int width, bool xorMode)
{
    painter_.setPen(QPen(c, width));
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.drawPolygon(polygon);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::drawRect(int x, int y, int w, int h, const QColor& c,
                              int penWidth, bool xorMode)
{
    painter_.setPen(QPen(c, penWidth));
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.drawRect(x, y, w, h);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::drawText(int x,int y,const QString& s,const QColor& c,
                              int fontSize, double alpha, bool italic,
                              bool bold, bool underline, bool xorMode)
{
    QFont font;
    font.setPointSize(fontSize);
    font.setItalic(italic);
    font.setBold(bold);
    font.setUnderline(underline);
    painter_.setPen(c);
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.setFont(font);
    painter_.rotate(qreal(alpha));
    painter_.drawText(x, y, s);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter_.resetTransform();
}

void PaintingWindow::drawArrow(int a, int b, int c, int d,
                               const QColor& col,
                               int arrowWidth, int arrowHeight, int style,
                               int width, bool xorMode)
{
    double sl;
    double dx = c-a;
    double dy = d-b;
    double norm= qSqrt(dx*dx+dy*dy);
    if (norm < 0.999) { // null vector
        painter_.setPen(QPen(col, width));
        if(xorMode)
            painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
        painter_.drawPoint(a, b);
        update();
        if(xorMode)
            painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
        return;
    }

    QPainterPath path;
    QPolygonF pts;

    qreal dx_norm = dx / norm;
    qreal dy_norm = dy / norm;
    qreal p1x = a+dx_norm*(norm-arrowWidth) + arrowHeight/2.*dy_norm;
    qreal p1y = b+dy_norm*(norm-arrowWidth) - arrowHeight/2.*dx_norm;
    qreal p2x = a+dx_norm*(norm-arrowWidth) - arrowHeight/2.*dy_norm;
    qreal p2y = b+dy_norm*(norm-arrowWidth) + arrowHeight/2.*dx_norm;
    switch(style) {
    case 0:
        painter_.setPen(QPen(col, width));
        if(xorMode)
            painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
        painter_.drawLine(a, b, c, d);
        painter_.drawLine(c, d, int(p1x), int(p1y));
        painter_.drawLine(c, d, int(p2x), int(p2y));
        break;
    case 1:
        pts << QPointF(p2x, p2y);
        pts << QPointF(c, d);
        pts << QPointF(p1x, p1y);
        sl = norm-(arrowWidth*.7);
        pts << QPointF(a+dx_norm*sl+dy_norm*width, 
                       b+dy_norm*sl-dx_norm*width);
        pts << QPointF(a+dy_norm*width, b-dx_norm*width);
        pts << QPointF(a-dy_norm*width, b+dx_norm*width);
        pts << QPointF(a+dx_norm*sl-dy_norm*width,
                       b+dy_norm*sl+dx_norm*width);
        path.addPolygon(pts);
        painter_.fillPath(path, col);
        break;
    case 2:
        pts << QPointF(p2x, p2y);
        pts << QPointF(c, d);
        pts << QPointF(p1x, p1y);
        sl = norm-arrowWidth;
        pts << QPointF(a+dx_norm*sl+dy_norm*width, 
                       b+dy_norm*sl-dx_norm*width);
        pts << QPointF(a+dy_norm*width, b-dx_norm*width);
        pts << QPointF(a-dy_norm*width, b+dx_norm*width);
        pts << QPointF(a+dx_norm*sl-dy_norm*width,
                       b+dy_norm*sl+dx_norm*width);
        path.addPolygon(pts);
        painter_.fillPath(path, col);
        break;
    default:
        break;
    }
    
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::display(const QImage& image, int xoff, int yoff,
                             bool xorMode, double fact)
{
    painter_.scale(qreal(fact), qreal(fact));
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.drawImage(xoff/fact, yoff/fact, image);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter_.resetTransform();
}

void PaintingWindow::display(const QPixmap& pixmap, int xoff, int yoff,
                             bool xorMode, double fact)
{
    painter_.scale(qreal(fact), qreal(fact));
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.drawPixmap(xoff/fact, yoff/fact, pixmap);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter_.resetTransform();
}

void PaintingWindow::setBackground(const QColor &col)
{
    fillRect(0, 0, width(), height(), col);
    QPalette newPalette(this->palette());
    newPalette.setColor(QPalette::Window, col);
    setPalette(newPalette);
}

void PaintingWindow::enableMouseTracking(bool en)
{
    setMouseTracking(en);
}

void PaintingWindow::fillCircle(int x, int y, int r, const QColor& c, bool xorMode)
{
    fillEllipse(x-r,y-r,2*r+1,2*r+1,c,xorMode);
}

void PaintingWindow::fillEllipse(int x, int y, int w, int h, 
                                 const QColor& c, bool xorMode)
{
    QPainterPath path;
    path.addEllipse(qreal(x), qreal(y), qreal(w), qreal(h));
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.fillPath(path, c);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::fillPoly(const QPolygonF& polygon, const QColor& c, bool xorMode)
{
    QPainterPath path;
    path.addPolygon(polygon);
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.fillPath(path, c);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::fillRect(int x, int y, int w, int h, 
                              const QColor& c, bool xorMode)
{
    painter_.setPen(c);
    if(xorMode)
        painter_.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
    painter_.fillRect(x, y, w, h, c);
    update();
    if(xorMode)
        painter_.setCompositionMode(QPainter::CompositionMode_SourceOver);
}

void PaintingWindow::clear()
{
    pixmap_.fill();
    update();
}

void PaintingWindow::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, pixmap_);
    this->QWidget::paintEvent(event);
}

// == WindowInternal ==

WindowInternal::WindowInternal(int width, int height,
                               const QList<QString>& tabsNames,
                               const QList<WindowType>& tabsTypes,
                               const QString& name,
                               int x, int y) {
    tab = 0;
    activeWin = 0;
    int nSubWins = std::max(1,tabsNames.size());
    if(nSubWins<=1) {
        if(tabsTypes.empty() || tabsTypes[0]==WINDOW_2D) {
            contents.push_back(new PaintingWindow(this, width, height, name,
                                                  x, y));
            contents3D.push_back(0);
        } else {
            contents.push_back(0);
#ifdef IMAGINE_OPENGL
            contents3D.push_back(new OpenGLWindow(this, 0, width, height, name,
                                                  x, y));
#else
            contents3D.push_back(0);
#endif
        }
    } else {
        tab = new QTabWidget;
        tab->setWindowTitle(name);
        for(int i=0; i<tabsNames.size(); i++) {
            if(i>=tabsTypes.size() || tabsTypes[i]==WINDOW_2D) {
                contents.push_back(new PaintingWindow(this, width, height,
                                                      tabsNames[i],
                                                      -1,-1, i, tab));
                tab->addTab(contents[i]->scrollArea(), tabsNames[i]);
#ifdef IMAGINE_OPENGL
                contents3D.push_back(0);
#endif
            } else {
                contents.push_back(0);
#ifdef IMAGINE_OPENGL
                contents3D.push_back(new OpenGLWindow(this, i, width, height,
                                                      tabsNames[i], -1,-1,tab));
#else
                contents3D.push_back(0);
#endif
                tab->addTab(contents3D[i], tabsNames[i]);
            }
        }
        // Fix size. This is heuristic, How to make this automatic?
        if( QString(qVersion()).startsWith("4.7") )
#ifdef __APPLE__
            tab->resize(width+8, height+31);
#else
            tab->resize(width+10, height+30);
#endif
        else
            tab->resize(width+12, height+39);
        tab->show();
    }
}

} /* namespace Imagine */
