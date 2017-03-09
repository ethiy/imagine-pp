#ifndef IMAGINE_GRAPHICS_PAINTINGWINDOW_H
#define IMAGINE_GRAPHICS_PAINTINGWINDOW_H

#include <vector>
#include <QScrollArea>
#include <QWidget>
#include <QPainter>
#include <QEvent>

#include "Imagine/Graphics/Types.h"
class QTabWidget;

namespace Imagine {

    class ScrollArea : public QScrollArea
    {
        Q_OBJECT

    public:
        ScrollArea(QWidget* parent=0);
        void closeEvent(QCloseEvent* event);

    };
    // Only 2D Drawing
    class PaintingWindow : public QWidget
    {
        Q_OBJECT

    public:
        PaintingWindow(Window win, int width, int height, 
                       const QString& windowTitle = "Imagine++",
                       int x=-1, int y=-1, int subWinId=0,
                       QWidget* parent=0);
        QScrollArea* scrollArea() { return scrollArea_; }
        QSize sizeHint() { return pixmap_.size(); }

        void mousePressEvent  (QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event) { mousePressEvent(event); }
        void mouseMoveEvent   (QMouseEvent* event) { mousePressEvent(event); }
        void keyPressEvent    (QKeyEvent*   event);
        void keyReleaseEvent  (QKeyEvent*   event) { keyPressEvent(event); }

    signals:
        void pressedMouseButtons(int x,int y, Qt::MouseButtons buttons,
                                 QEvent::Type type, Qt::KeyboardModifiers mod,
                                 Window win, int subWin);
        void pressedKey(int key, QEvent::Type type, Qt::KeyboardModifiers mod,
                        Window win, int subWin);
    public slots:
        void drawPoint(int x,int y, const QColor& c, bool xorMode=false);
        void drawLine(int x1,int y1, int x2,int y2, const QColor& c,
                      int penWidth=1, bool xorMode=false);
        void drawCircle(int xc,int yc, int r, const QColor& c, int penWidth=1,
                        bool xorMode=false);
        void drawEllipse(int x,int y, int w,int h, const QColor& c,
                         int penWidth=1, bool xorMode=false);
        void drawRect(int x,int y, int w,int h, const QColor& c,
                      int penWidth=1, bool xorMode=false);
        void drawPoly(const QPolygonF& polygon, const QColor& c, int width,
                      bool xorMode=false);
        void drawText(int x,int y, const QString& s, const QColor& c, int size,
                      qreal alpha, bool italic, bool bold, bool underline,
                      bool xorMode=false);
        void drawArrow(int a,int b,int c,int d, const QColor&  col,
                       int arrowWidth, int arrowHeight, int style, int width,
                       bool xorMode=false);

        void fillCircle(int x,int y,int r, const QColor& c, bool xorMode=false);
        void fillEllipse(int x,int y, int w,int h, const QColor& c,
                         bool xorMode=false);
        void fillRect(int x,int y, int w,int h, const QColor& c,
                      bool xorMode=false);
        void fillPoly(const QPolygonF& polygon, const QColor& c,
                      bool xorMode=false);

        void capture(QImage* im) { *im = pixmap_.toImage(); }

        void display(const QImage& image, int xoff=0, int yoff=0,
                     bool xorMode=false, double fact=1.);
        void display(const QPixmap& pixmap, int xoff=0, int yoff=0,
                     bool xorMode=false, double fact=1.);
        void setBackground(const QColor &col);
        void enableMouseTracking(bool en);
        void clear();
        void allowUpdates(bool allow) {
            setUpdatesEnabled(allow); }

    protected:
        void paintEvent(QPaintEvent* event);

    private:
        QScrollArea* scrollArea_;
        QPixmap  pixmap_;
        QPainter painter_;

    private:
        Window win_;
        int subWinId_;
    };

#ifdef IMAGINE_OPENGL
    class OpenGLWindow;
#endif

    class WindowInternal {
    public:
        QTabWidget* tab;
        std::vector<PaintingWindow*> contents;
#ifdef IMAGINE_OPENGL
        std::vector<OpenGLWindow*> contents3D;
#else
        std::vector<PaintingWindow*> contents3D;
#endif
        int activeWin;
        WindowInternal(int width, int height,
                       const QList<QString>& tabsNames,
                       const QList<WindowType>& tabsTypes,
                       const QString& name = "Imagine++",
                       int x=-1, int y=-1);
    };

} /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_PAINTINGWINDOW_H */
