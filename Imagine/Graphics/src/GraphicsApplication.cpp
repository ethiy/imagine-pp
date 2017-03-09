#include "Imagine/Graphics/ConfigGraphics.h"
#include "GraphicsApplication.h"
#include "GraphicsUtilities.h"
#include "PaintingWindow.h"
#include "OpenGLWindow.h"
#include "Imagine/Graphics/Mesh.h"
#include <QMetaType>
#include <QTabWidget>
class QPolygonF;


namespace Imagine {

#ifdef IMAGINE_OPENGL
class OpenGLWindow;
#endif

GraphicsApplication::GraphicsApplication(int& argc, char **argv)
: QApplication(argc, argv)
, activeWindow(0)
, mutex(QMutex::NonRecursive)
{
    qRegisterMetaType<Window>("Window");
#ifdef IMAGINE_OPENGL
    qRegisterMetaType<OpenGLWindow *>("OpenGLWindow");
#endif
    qRegisterMetaType<QList<QString> >("QList<QString>");
    qRegisterMetaType<QList<WindowType> >("QList<WindowType>");
    qRegisterMetaType<QPolygonF>("QPolygonF");
    qRegisterMetaType<Color *>("Color *");
#ifdef IMAGINE_OPENGL
    qRegisterMetaType<Mesh>("Mesh");
#endif
    qRegisterMetaType<QPixmap*>("QPixmap*");
    qRegisterMetaType<byte *>("byte *");
    qRegisterMetaType<QImage>("QImage");
    qRegisterMetaType<QImage*>("QImage*");

    connect(&userThread, SIGNAL(finished()), this, SLOT(quit()));
    setQuitOnLastWindowClosed(false);
}

void GraphicsApplication::createWindow(int w, int h,
                                       const QList<QString>& tabsNames,
                                       const QList<WindowType>& tabsTypes,
                                       const QString& name, int x, int y) {
    Window win = new WindowInternal(w, h, tabsNames, tabsTypes, name, x, y);
    createdWindows.push_back(win);
    for(size_t i=0; i<win->contents.size(); i++)
        if(win->contents[i])
        {
            connectWindowIOEventsToUserThread(win->contents[i]);
        }
        else
            connectWindowIOEventsToUserThread((QWidget*)win->contents3D[i]);
    if (createdWindows.size() == 1)
        setActiveWindow(win, 0);

}

void GraphicsApplication::setActiveWindow(Window w, int subWin) {
    activeWindow = w;
    if(subWin>=0 && (size_t)subWin<w->contents.size())
        w->activeWin = subWin;
}
void GraphicsApplication::showWindow(Window w, int subWin) {
    if(! (0<=subWin && subWin<(int)w->contents.size())) {
        std::cerr << "showWindow: the subWin index is invalid" << std::endl;
        return;
    }
    QWidget* top = w->contents[subWin];
    if(! top) top = w->contents3D[subWin];
    while(top->parentWidget())
        top = top->parentWidget();
    top->raise();
    if(w->tab)
        w->tab->setCurrentIndex(subWin);
    setActiveWindow(w,subWin);
}

void GraphicsApplication::closeWindow(Window w) {
    QList<Window>::iterator wi =
        std::find(createdWindows.begin(), createdWindows.end(), w);
    if(wi==createdWindows.end()) {
        qFatal("Could not find complex painting window!");
        quit();
    }
    createdWindows.erase(wi);

    QWidget* top = w->contents[0];
    if(! top) top = w->contents3D[0];
    while(top->parentWidget())
        top = top->parentWidget();
    if(!top->close()) {
        qFatal("Could not close window!");
        quit();
    }

    if(activeWindow == w)
        activeWindow = 0;
    delete w;
}

void GraphicsApplication::connectWindowIOEventsToUserThread(QWidget* w) {
    // User thread listens to mouse events.
    connect(w, SIGNAL(pressedMouseButtons(int, int, Qt::MouseButtons,QEvent::Type, Qt::KeyboardModifiers, Window, int)),
            &userThread, SLOT(clicked(int, int, Qt::MouseButtons, QEvent::Type, Qt::KeyboardModifiers, Window, int)));
    // User thread listens to keyboard events in Windows
    connect(w, SIGNAL(pressedKey(int, QEvent::Type, Qt::KeyboardModifiers, Window, int)),
            &userThread, SLOT(pressedKey(int, QEvent::Type, Qt::KeyboardModifiers, Window, int)));
}

void GraphicsApplication::createBitmap(int w, int h) {
   createdPixmap = new QPixmap(w,h);
}

void GraphicsApplication::deleteBitmap(QPixmap* pm) {
    delete pm;
}

void GraphicsApplication::drawBitmap(QPixmap* pm, int x,int y,
                                     const QImage& image) {
    QPainter paint(pm);
    paint.drawImage(x,y,image);
}

void GraphicsApplication::display(QPixmap* pm, int x,int y,
                                  bool xorMode, double fact) {
    activeWindow2D()->display(*pm,x,y,xorMode,fact);
}

} /* namespace Imagine */
