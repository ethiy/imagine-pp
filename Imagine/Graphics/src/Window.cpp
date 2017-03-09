#include "GraphicsUtilities.h"
#include "Imagine/Graphics/Window.h"

namespace Imagine {


void endGraphics() {
    guiApp()->mutex.lock();
    QWidget* w = activeWindow();
    guiApp()->mutex.unlock();
    if(w) {
        std::cout << "Please click in any window to terminate Graphics"
                  << std::endl;
        anyClick();
    }
}

Window openWindow(int w, int h, const std::string& windowTitle,int x, int y) {
    WindowType type=WINDOW_2D;
    return openComplexWindow(w,h,windowTitle,1,&windowTitle,&type,x,y);
}

Window openWindow3D(int w, int h, const std::string& windowTitle,int x, int y) {
    WindowType type=WINDOW_3D;
    return openComplexWindow(w,h,windowTitle,1,&windowTitle,&type,x,y);
}

Window openComplexWindow(int w, int h, const std::string& name,
                         int tabsNb,
                         const std::string* tabsNames,
                         const WindowType* tabsTypes, int x, int y) {
    QList<QString> tabsnames;
    for(int i=0; i<tabsNb; i++)
        tabsnames.append( (tabsNames==0) ? 
                          QString("") : QString::fromStdString(tabsNames[i]) );
    QList<WindowType> tabstypes;
    for(int i=0; i<tabsNb; i++)
        tabstypes.append(tabsTypes? tabsTypes[i]: WINDOW_2D);
    QMetaObject::invokeMethod(guiApp(), "createWindow",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(int, w), Q_ARG(int, h),
                              Q_ARG(QList<QString>, tabsnames),
                              Q_ARG(QList<WindowType>, tabstypes),
                              Q_ARG(QString, QString::fromStdString(name)),
                              Q_ARG(int, x), Q_ARG(int, y));
    return guiApp()->createdWindows.back();
}

void closeWindow(Window w) {
    QMetaObject::invokeMethod(guiApp(), "closeWindow",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(Window, w));
}

void setActiveWindow(Window w, int subWin) {
    QMetaObject::invokeMethod(guiApp(), "setActiveWindow",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(Window, w),
                              Q_ARG(int, subWin));
}

void setBackGround(const Color &col) {
    oopsActive();
    QColor c(col.r(), col.g(), col.b());
    QMetaObject::invokeMethod(activeWindow(), "setBackground",
                              Qt::QueuedConnection,
                              Q_ARG(QColor, c));
}
void enableMouseTracking(bool en) {
    oopsActive();
    QMetaObject::invokeMethod(activeWindow(), "enableMouseTracking",
                              Qt::QueuedConnection,
                              Q_ARG(bool, en));
}

void clearWindow() {
    oopsActive();
    QMetaObject::invokeMethod(activeWindow(), "clear",
                              Qt::QueuedConnection);
}

void showWindow(Window w, int subWin) {
    QMetaObject::invokeMethod(guiApp(), "showWindow",
                              Qt::QueuedConnection,
                              Q_ARG(Window, w),
                              Q_ARG(int, subWin));
}

} /* namespace Imagine */
